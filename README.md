
First of all, the database can be created with fields  

	Field            Type                Constraints	                                              
	id               unsigned int        auto_increment	 NOT NULL 
	senderEmail		   varchar(50)      	 NOT NULL 
	receiverEmail		 varchar(50)     		 NOT NULL   
	subject		    	 varchar(50)
	body 			       varchar(5000)			 NOT NULL 
	hasProcessed     bool                NOT NULL 

Create Table
CREATE TABLE Email_Content_db (id int  NOT NULL AUTO_INCREMENT,  senderEmail varchar(50) NOT NULL , receiverEmail  varchar(50) NOT NULL , subject varchar(50), body  varchar(5000) NOT NULL , hasProcessed bool NOT NULL );



I would like to take noOfRecords (eg: 1000 records)  rows at a time from the records table and add it to the Queue. We will fill  these vectors with the help of retreive data class defined in the Bulk Email namespace. Three  main threads are used here. Reason is that, while two processes are sending the mails, the other thread can retreive data from database. Retreive data is serial . Mutex variables are used for locking purposes.

Each thread has a list of EmailContentsRecord(which is defined in Common.h)
 
After retreiving the records, we must check for duplicates emails. Which means  sender,receiver,subject and body are same. In order to find a solution for this , a special kind of map  called multmap is used , defined in Standard Template Library of C++. It used because the Key may be same for different email Records. We are only storing Ids of records with respect to the key, inorder to save the space.[fully explained in DuplicateRemover.h]

Actual C++ Record stored in Common.h has an extra field called isDuplicate, which is false by default. If the DuplicateFinder found that email record is a duplicate, it will mark that field as true.
These values will not be actually processed by sender.

Value of numOfThreads required is taken from client at the start of progam. Each of main threads have numOfThreads/3 secondary threads. Then by calling numOfThreads/3 threads concurrently, each having a record sends the email to the receiver. Email Sending is defined in EmailSender. It will sends only the records with isDuplicate = false. jwsmtp library is used to send the emails.  SMTP ServerAddress is taken from sender email ID, by taking values after “@”.  Port number is selected from portnumber Map, corresponding to the ServerAddress.

Note :- Actual Number of threads can vary , according to the computing power of the server which is running. It can be increased or decreased. Maximum number of record stored at a time is only 3000. So the space is not a problem.


To Run:

1. create a directory named _External_Library_Files_ in the same place where Code directory is being placed and copy jwsmtp Library files to it

2. Install mysqlpp library 

3. Install boost library

4. g++ Compiler
