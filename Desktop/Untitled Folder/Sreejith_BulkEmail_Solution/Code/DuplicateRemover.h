
/********    SOLUTION FOR DUPLICATE MAIL PROBLEM TO SAME SENDER, SAME RECEIVER WITH SAME SUBJECT AND BODY    ************/
//It is implemented to avoid multiple email to a same person with same subject and message body.

#ifndef BULKMAIL_DUPLICATEREMOVER_H        // Check whether the header file is already included
#define BULKMAIL_DUPLICATEREMOVER_H        // If not already defined, define it

#include <map>
#include <vector>

#include "boost/optional/optional.hpp"

#include "CommonFuncs.h"
#include "RetrieveData.h"

namespace BulkEmail
{
    class DuplicateRemover
    {
    public:
        typedef boost::optional<unsigned int> EmailRecordIdOpt;    //Optional Value - because Id is optional in Map
        
        int removeDuplicates(std::vector<EmailContentsRecord>& eMailContentVector,
                             RetreiveData retreiveData_);
        
    protected:
    
        // MultiMap is a special kind of map, defined in Standard Template Library of C++, used because the Key may be same 
        // for different email Records
        // We are only storing Ids of records with respect to the key, inorder to save the space.
        // Otherwise, space required will be huge for extremely large database table
        std::multimap<unsigned int,EmailRecordIdOpt> _emailRecordsIdMap;
        
        EmailRecordIdOpt                                  _emailIdOpt;
    };
    
    //Function marks the duplicates and return number of duplicates
    int DuplicateRemover::removeDuplicates(std::vector<EmailContentsRecord>& eMailContentVector,
                                           RetreiveData retreiveData_)
    {
        unsigned int hashVal;
        
        std::vector<EmailContentsRecord>::iterator iter;
        
        int no_of_dups = 0;
        
        for(iter = eMailContentVector.begin(); iter!=eMailContentVector.end(); iter++)
        {
            hashVal = getHashValue(*iter);
            
            // Check Whether Key already exist
            std::multimap<unsigned int,EmailRecordIdOpt>::iterator map_Iter = _emailRecordsIdMap.find(hashVal);

            // If Key is not present in map, Add Id of specific record in database to the map
            if(map_Iter== _emailRecordsIdMap.end())
            {
                _emailRecordsIdMap.insert(std::make_pair(hashVal,iter->_id));
            }
            // If Key is present in map, take the records of corresponding Id's and check one by one
            // If any of records contain same data except the key field, dont enter into the map as will as returning Vector
            // Otherwise, Add Id of specific record in database to the map
            else
            {
                while(map_Iter!=_emailRecordsIdMap.end())
                {
                    EmailContentsRecord emailContent;
                    std::pair <std::multimap<unsigned int,EmailRecordIdOpt>::iterator,std::multimap<unsigned int,EmailRecordIdOpt>::iterator> ret;
                    ret = _emailRecordsIdMap.equal_range(hashVal);
                    
                    _emailIdOpt = iter->_id;
                    
                    //This loop is to get all the id's of records corresponding to a particular key
                    for (map_Iter=ret.first; map_Iter!=ret.second; ++map_Iter)
                    {
                       //Make new function to Retreive record of id
                       emailContent = retreiveData_.getEmailRecordById(*map_Iter->second); 

                       if(emailContent == *iter)  //"==" is Defined in CommonFuncs.h file
                       {
                            iter->_isDuplicate = true;
                            no_of_dups++;
                       }
                    }
                }
                if(no_of_dups==0) //If unique record add it to map of (hashkey, DatabaseId)
                {
                    //Add Id of specific record to the map
                    _emailRecordsIdMap.insert(std::make_pair(hashVal,*_emailIdOpt));
                }
            }
        }
        return no_of_dups;
    }
}

#endif
