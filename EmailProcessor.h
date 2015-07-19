/*
 *                                  Design
 *                                  ------
 *
 * Make three Main threads, Each having a vector(or Queue) of EmailContentsRecord whose maxSize will be 1000. We will fill 
 * these vectors with the help of retrieve data class defined in the Bulk Email namespace. The reason behind the 3 main thread
 * is that while two processes are sending the mails, the other thread can retrieve data from database. Retrieve data does 
 * operate serially. We can use mutex variables for locking purposes.
 *
 * Each of the three main threads have (_numOfThreads/3) child(secondary) threads which can be processed concurrently. 
 *
 * This class is the most important class class which parallelises (1) Getting data from Database (and)
 *                                                                 (2) Sending SMTP Email Messages.
 *
 * Retrieving records is serial operation, by using the mutex variables. 
 *
 * Each Thread took a EmailContentRecordVector, send emails to all records in vector
*/


#ifndef BULKMAIL_EMAILPROCESSOR_H        // Check whether the header file is already included
#define BULKMAIL_EMAILPROCESSOR_H        // If not already defined, define it

#include <thread>
#include <mutex>

#include "DuplicateRemover.h"
#include "EmailSender.h"

namespace BulkEmail
{
    class EmailProcessor
    {
    public:
        bool initializeThreads();

        bool getData();

        EmailProcessor(int numOfRecords,
                       int numOfThreads_,
                       std::string databaseName_, 
                       std::string dbAddress_, 
                       std::string userName_,
                       std::string password_);
        
        bool sender(EmailContentsRecord emailContentsRec_, EmailSender emailSender_);

    private:
        std::thread                             _mainThreads[3];
        RetreiveData                            _retreiveData;
        int                                     _numOfRecords;
        int                                     _numOfThreads;
        DuplicateRemover                        _duplicateRemover;
    };

//Constructor of EmailProcessor        
    EmailProcessor::EmailProcessor(int numOfRecords_,
                                   int numOfThreads_,
                                   std::string databaseName_, 
                                   std::string dbAddress_, 
                                   std::string userName_,
                                   std::string password_)
    :_numOfRecords(numOfRecords_)
    ,_numOfThreads(numOfThreads_)
    ,_retreiveData(RetreiveData(databaseName_, 
                                dbAddress_, 
                                userName_,
                                password_))
    {
    }

//Function to initialize the Main Threads 
    bool EmailProcessor::initializeThreads()       
    {
        for(int i=0;i<3;i++)
        {
            _mainThreads[i]=std::thread(&EmailProcessor::getData,this);  // Three Main threads Initialized
        }
    }

// Function Which Parallelizes the call to actual RetreiveData 
    bool EmailProcessor::getData()
    {
        std::vector<EmailContentsRecord>        _emailVector; //Actual Vector storage of each 
        
        std::thread                             _secondaryThreads[_numOfThreads/3];
        
        EmailSender                             _emailSender;
        
        std::mutex                              _mtx;
        
        int noOfActualRecords = 0;
        
        do      //do-while loop is used because, default value of variable noOfActualRecords is set as zero
        {
            _mtx.lock(); //To Protect the database retrieval from Concurrent access. Provide serial access
        
            // Reteive data from database. Function 'getEmailRecords' return how many records are actually retrieved
            noOfActualRecords = _retreiveData.getEmailRecords(_numOfRecords,_emailVector);
            
            _retreiveData.updateEmailRecords(_emailVector);    //Update hasProcessed = true for all records in Vector
            
            _mtx.unlock(); //Unlock the mutex. Now code is free to execute parallely
                    
            if(noOfActualRecords==0)
                return false;
                
            int numOfDuplicateRecs = _duplicateRemover.removeDuplicates(_emailVector,_retreiveData);
            
            noOfActualRecords = noOfActualRecords - numOfDuplicateRecs;
            
            for(unsigned int it=0;it<noOfActualRecords;it+=(_numOfThreads/3))
            {
                for(int j=0;j<(_numOfThreads/3);j++)
                if(!_emailVector[it]._isDuplicate)  //Confirm not a duplicate email
                {
                    //create _numOfThreads/3 threads of sender() function with arguments
                    _secondaryThreads[j]=std::thread(&EmailProcessor::sender,this,_emailVector[it],_emailSender); 
                }
            }
            _emailVector.clear();  //Removes all contents of vector
        }
        while(noOfActualRecords != 0); //Stop if entire table is retrieved
        
        return true;
    }

// Function calling  sendEmail function defined in EmailSender.h file
    bool EmailProcessor::sender(EmailContentsRecord emailContentsRec_, EmailSender emailSender_)
    {
        emailSender_.sendEmail(emailContentsRec_);
    }
    
} //End namespace BulkEmail

#endif
