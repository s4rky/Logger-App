#include "logger.h"

using namespace std;

    
    string logger:: getDate(){
      
      time_t now ; // current date/time based on current system
      now = time(NULL);
      char *t = strtok(ctime(&now),"\n"); // convert now to string form

      return(t); //return the date/time
      }
      
    
    logger::logger(string appName){ //A constructor, taking the name of the app that is being logged, or whose log messages are to be accessed.  This name is passed as a string parameter to this method.  This does all the necessary set up so that messages can then be written to or read from the log in question.

      cout<<"opening file : "<<appName<<"\n";
      appName2= appName;

      char* err = 0;     // Save any error messages
     
      int rc;
      int openFile;  // Save the result of opening the file

      int exit = 0;

      /* Open database */
      exit = sqlite3_open(fileName, &db);     // Save the result of opening the file
      


      /**CHECK IF THE DATABASE IS OPENED OR NOT**/
        
        if(exit)  // If the database is not opened then throw an error
        {
          cerr<<"ERROR: Can't open database"<<"\n";
          sqlite3_free(err);
        }

        else // otherwise, continue 
        {
          cout<<"Success: Opened database"<<"\n";
        }

       /* Create SQL statement */
      string sql = "create table if not exists " + appName + 
      "(timestamp varchar(255), message varchar(255));\n";     // Save any SQL


       /* Execute SQL statement */
      rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err); 

      /**Check if there is an error or table is created**/
     
      if(rc != SQLITE_OK)
      {
        cerr<<"SQL error:"<< err <<"\n";
        sqlite3_free(err);
      }

      else
      {
        cout<<"Success: Table created"<<"\n";
      }
    }

    logger::~logger() //A destructor, doing all the necessary tear down when logging is done, usually just before your app terminates.
    {
      sqlite3_close(db);
      cout<<"Success: Table closed"<<"\n";
    }


  void logger:: write(string log_msg){ //Takes a log message as a string parameter, and records the message text to the log for the app, along with a timestamp for when write() was called.  This timestamp can also be recorded as text.
    char* err = 0;     // Save any error messages
    int exit = 0;
    string sql;
    int rc;


    string time = getDate(); // get the current time 



    /* Create SQL statement */
    sql = "insert into "+ appName2 +" values (\"" +time+"\", \""+log_msg+"\")";


    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err);

      if(rc != SQLITE_OK)
      {
        std::cerr<<"SQL error: %s\n", err;
        sqlite3_free(err);
      }

      else{
        cout<<"Success: records created"<<"\n";
      }
    }


    // Takes no parameters and returns a vector containing all log messages that have been recorded for the app.  This vector contains log_message objects, as discussed below.
    vector<log_message> logger::readAll()
    {
      sqlite3_stmt *stmnt;
      vector<log_message> logmsg;
      string col0;
      string col1;


      string sql = "select * from " + appName2 ;
      int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmnt, 0);
      
      if(rc != SQLITE_OK)
      {
        cout<<"Error: could not fetch data\n";
        sqlite3_close(db);
      }

      else
      {
        cout<<"Success: Records found\n";
      }

      rc = sqlite3_step(stmnt);

      //printf("INSIDE THE LOGGER CLASS\n");
      while(rc == SQLITE_ROW)
      {
        col0  = (const char*) (sqlite3_column_text(stmnt, 0));
        col1 = (const char*) (sqlite3_column_text(stmnt, 1));
        log_message log(col0, col1);
        logmsg.push_back(log);
        rc = sqlite3_step(stmnt);
      }

      sqlite3_finalize(stmnt);
      sqlite3_close(db);

      return logmsg;
    }
