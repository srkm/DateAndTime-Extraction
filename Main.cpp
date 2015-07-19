//EmailProcessor is our Important class which controls the entire project
//Main creates an object of it

#include "EmailProcessor.h"

namespace BulkEmail
{
    int main()
    {
        int noOfThreads,noOfRecords;
        std::string databaseName, dbAddress, userName, password;
        
        // Main just calls EmailProcessor which in turn calls all other classes
        std::cout<<"Enter No of threads, No of Records";
        std::cin>>noOfThreads>>noOfRecords;
        std::cout<<"Enter Database name, address, username and password";
        std::cin>>databaseName>>dbAddress>>userName>>password;
        
        EmailProcessor mailProcessor(noOfRecords,
                                     noOfThreads, 
                                     databaseName,
                                     dbAddress, 
                                     userName,
                                     password);
        
    }
} //End namespace BulkEmail
