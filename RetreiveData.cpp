#include "RetreiveData.h"

namespace BulkEmail
{
    namespace   //Unnamed Namespace. Its scope is limited to this specific file
    {
    // sql_create of size six, which is needed to retrieves mySql database record

        sql_create_6(Email_Content_db,                                // DB Name
                1,6,                                              // No of Keys, Total no of fields
                int, id,
                std::string, senderEmail,
                std::string, receiverEmail,
                std::string, subject,
                std::string, body,
                bool, hasProcessed);        
     }  // end of Unnamed namespace
     
//Constructor of database. It stores the values required for this class, by taking these necessary values as arguments 

    RetreiveData::RetreiveData(std::string databaseName_, 
                       std::string dbAddress_, 
                       std::string userName_,
                       std::string password_)
    :_databaseName(databaseName_)
    ,_dbAddress(dbAddress_)
    ,_userName(userName_)
    ,_password(password_)
    {
    }

// Inorder to establish the Connection to database

    bool RetreiveData::connect()
    {
        try
        {
            if(!_conn.connect(_databaseName, _dbAddress, _userName, _password))
            {
            std::cout<<"Failed connecting to database"; 
            return false;
            }
        }
        catch(const std::exception& e)
        {
            std::cout<<"Failed connecting to database error = "<<e.what(); 
            return false;
        }
    }


// This function returns the number of records returned. Normally it will be noOfRecords itself. 
// But considering the last case, ie the end of database table, it might be less than noOfRecords
// For that case, it will return the number of records that actually fetched from database

    unsigned int RetreiveData::getEmailRecords(int noOfRecords_, std::vector<EmailContentsRecord>& emailVector_)
    {
    try
    {
            emailVector_.clear(); //First, Clear all the records in emailVector
            
            mysqlpp::Query query = _conn.query("SELECT id, senderEmail, receiverEmail, subject, body, hasProcessed, "\
                                       "FROM Email_Content_db WHERE hasProcessed=false ORDER BY id LIMIT noOfRecords_");
            query.parse();
            std::vector<Email_Content_db> resultVector;
            query.storein(resultVector);  //Fill records into the resultvector

            if(0 == resultVector.size())
            {
            std::cout<<"\nZero records";
            return 0;
            }
            
            for(int i=0; i<resultVector.size();i++)
            {
                //Fill values to emailVector
                
                emailVector_[i]=EmailContentsRecord();
                
                emailVector_[i]->_id = resultVector[i].id;
                emailVector_[i]->_senderEmail = resultVector[i].senderEmail;
                emailVector_[i]->_receiverEmail =resultVector[i].receiverEmail;
                emailVector_[i]->_subject = resultVector[i].subject;
                emailVector_[i]->_body = resultVector[i].body;
                emailVector_[i]->_hasProcessed = resultVector[i].hasProcessed;
            }
            
           return resultVector.size();
    }
    catch (const std::exception& e)
    {
       std::cout<<"Failed while running get query "<<e.what();
       return 0;
    }
    }

// set hasProcessed value to true for all elements in the vector 
// const vector is taken as argument because it is pass by reference(share common memory)
// but at the same time it cant modify the vector data
    bool RetreiveData::updateEmailRecords(const std::vector<EmailContentsRecord>& emailVector_) 
    {
        try
        {
            for(i=0; i<emailVector_.size();i++)
            {
                mysqlpp::Query query = _conn.query("UPDATE Email_Content_db SET hasProcessed=true "\
                                                   "WHERE id = ");
                query<<emailVector_.id_;
             
                if (query.execute())
                {
                    return true;
                }
                else
                {
                    std::cout<<"Failed to updating table " <<query.error();
                    return false;
                }
            }
        }
        catch (const std::exception& e)
        {
        std::cout<<"Failed while running update query "<<e.what();
        return false;
        }
    }
    
// This function is called when a record already present in the hash-table(here we actually used a map)
// Thus we need to retrieve the records corresponding to that Id's presented in the map corresponding to generated key
// and confirm that the record is duplicate or not.

    EmailContentsRecord RetreiveData::getEmailRecordById(int id_)
    {
        try
        {
            mysqlpp::Query query = _conn.query("SELECT id, senderEmail, receiverEmail, subject, body, hasProcessed, "\
                                               "FROM Email_Content_db WHERE hasProcessed=true and id =");
            query<<id;
            query.parse();
            Email_Content_db dbEmailRec;
            query.storein(dbEmailRec);

            EmailContentsRecord                          emailContentsRec;
            emailContentsRec=EmailContentsRecord();

            emailContentsRec->_id = dbEmailRec[i].id;
            emailContentsRec->_senderEmail = dbEmailRec[i].senderEmail;
            emailContentsRec->_receiverEmail =dbEmailRec[i].receiverEmail;
            emailContentsRec->_subject = dbEmailRec[i].subject;
            emailContentsRec->_body = dbEmailRec[i].body;
            emailContentsRec->_hasProcessed = dbEmailRec[i].hasProcessed;

            return emailContentsRec;
        }
        catch (const std::exception& e)
        {
            std::cout<<"Failed while running get query "<<e.what();
            return 0;
        }
    }

//Destructor of RetreiveData. It will disconnect the database after program termination
    RetreiveData::~RetreiveData()
    {
        try
        {
            if(_conn.connected())
            {
            _conn.disconnect();
            }
        }
        catch(const std::exception& e)
        {
            std::cout<<"Failed to close connection error"<<e.what();
        }
    }
}