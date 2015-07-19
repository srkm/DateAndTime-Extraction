
/*
 * A Structure of Email Components which is needed for most of classes are stored here
*/ 

#ifndef BULKMAIL_COMMON_H        // Check whether the header file is already included
#define BULKMAIL_COMMON_H        // If not already defined, define it

#include <iostream>

namespace BulkEmail
{
    //Structure for storing the retrieved database records

    struct EmailContentsRecord
    {
        EmailContentsRecord()  //Default Constructor
        {}
        
        //Actual Constructor
        EmailContentsRecord(unsigned int id_,
                            std::string senderEmail_,
                            std::string receiverEmail_,
                            std::string subject_,
                            std::string body_,
                            bool hasProcessed_)
        :_id(id_)
        ,_senderEmail(senderEmail_)
        ,_receiverEmail(receiverEmail_)
        ,_body(body_)
        ,_hasProcessed(hasProcessed_)
        ,_isDuplicate(false)                     //Default value is false
        {
        }
    
        unsigned int _id;
        std::string _senderEmail;
        std::string _receiverEmail;
        std::string _subject;
        std::string _body;
        bool _hasProcessed;
        bool _isDuplicate;
    };
} 

#endif
