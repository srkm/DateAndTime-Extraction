#ifndef BULKMAIL_COMMON_FUNCS_H        // Check whether the header file is already included
#define BULKMAIL_COMMON_FUNCS_H        // If not already defined, define it

#include <string>

#include "Common.h"

namespace BulkEmail
{
    //Function Which returns the portion of email address after "@"
    std::string getServerAddress(std::string senderEmail_)
    {
        return senderEmail_.substr(senderEmail_.find("@")+1); 
    }
    
    //Implemented == Operator for EmailContentsRecord, return true if string values are equal
    bool operator == (EmailContentsRecord r1, EmailContentsRecord r2)
    {
        return ( r1._senderEmail == r2._senderEmail &&
                 r1._receiverEmail == r2._receiverEmail &&
                 r1._subject == r2._subject &&
                 r1._body == r2._body );
    }
    
    
    unsigned int getHashValue(EmailContentsRecord emailRecord_)
    {
        unsigned int value;
        int minLen1 = std::min(emailRecord_._senderEmail.length(),emailRecord_._receiverEmail.length());
        int minLen2 = std::min(emailRecord_._body.length(),emailRecord_._subject.length());
        int minLen = std::min(minLen1, minLen2);
        
        for(int i=0; i<minLen; i++)
        {
            value = ((int)(emailRecord_._senderEmail[0]) << (int)(emailRecord_._senderEmail[2]) );
            value += ((int)(emailRecord_._receiverEmail[2]) << (int)(emailRecord_._receiverEmail[1]));
            value += ((int)(emailRecord_._body[2]) << (int)(emailRecord_._body[1]));
            value += ((int)(emailRecord_._subject[2]) << (int)(emailRecord_._subject[1]));
        }
        return (value%1000003);
    }
}

#endif
