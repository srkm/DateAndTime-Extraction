/**
 * Retrieve EmailRecords from database
 *
 * In Common.h, Structure EmailContentsRecord is defined. It is filled here.
 *
 * Here we fill vector(queue) of EmailContentsRecord of size 'noOfRecords_'(eg-1000 recs)
 */
 
#ifndef BULKMAIL_RETREIVEDATA_H        // Check whether the header file is already included
#define BULKMAIL_RETREIVEDATA_H        // If not already defined, define it

#include <exception>
#include <iostream>
#include <vector>
#include <mysql++/mysql++.h>
#include <mysql++/qparms.h>

#include "Common.h"

namespace BulkEmail
{

// Class Retrivedata which retrieves the email records  from the database table	 

     class RetreiveData
     {
     public:
        RetreiveData(std::string databaseName_, 
                 std::string dbAddress_, 
                 std::string userName_,
                 std::string password_);
        ~RetreiveData();
        
        bool connect();
        unsigned int getEmailRecords(int noOfRecords_, std::vector<EmailContentsRecord>& emailVector_); 
        bool updateEmailRecords(const std::vector<EmailContentsRecord>& emailVector_);
        EmailContentsRecord getEmailRecordById(int id_);
        
     private:
            std::string                                     _databaseName;
            std::string                                     _dbAddress;
            std::string                                     _userName;
            std::string                                     _password;  
            // Connect to the database.
            mysqlpp::Connection                             _conn;
     };
} //End of namespace BulkEmail

#endif
