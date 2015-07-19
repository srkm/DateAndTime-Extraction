#ifndef BULKMAIL_EMAILSENDER_H        // Check whether the header file is already included
#define BULKMAIL_EMAILSENDER_H        // If not already defined, define it

#include <boost/assign/list_of.hpp>
#include <exception>

#include "Common.h"
#include "../_External_Library_Files_/jwsmtp.h"   // Include the jwSMTP External library.

#define correct_response "250"

namespace BulkEmail
{
    class EmailSender
    {
    public:
        EmailSender();
        bool sendEmail(EmailContentsRecord emailContentsRecord_);
    protected:
        //Automatic selection of port according to sender email
        std::map<std::string,int> _portMap;
    };
    
    EmailSender::EmailSender()
    {
        _portMap.insert(std::make_pair("smtp.live.com", 465));
        _portMap.insert(std::make_pair("smtp.mail.yahoo.com", 465));
        _portMap.insert(std::make_pair("smtp.gmail.com", 465));
        _portMap.insert(std::make_pair("default", 25));
    }
    
    
    bool EmailSender::sendEmail(EmailContentsRecord emailContentsRecord_)
    {
        try
        {
            jwsmtp::mailer mail(emailContentsRecord_._receiverEmail.c_str(), 
                        emailContentsRecord_._senderEmail.c_str(), 
                        emailContentsRecord_._subject.c_str(), 
                        emailContentsRecord_._body.c_str(), 
                        std::string(getServerAddress("smtp."+emailContentsRecord_._senderEmail)).c_str(), // the smtp server
                        _portMap.find(std::string("smtp."+getServerAddress(emailContentsRecord_._senderEmail)))->second, 
                        // default smtp port (25), here we changed to 465 to support major email providers
                        false); 
            // A valid response will begin with the string “250”(correct_response defined as macro) response codes
            if(mail.response().substr(0,3) != correct_response) 
            {
                return false;
            }
            
            return true;
        }
        catch(const std::exception& e)
        {
            std::cout << "Error: " << e.what() << ".\n";
        }
    }
} //End namespace BulkEmail

#endif
