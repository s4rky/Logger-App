

#include "logger.h"


using namespace std;

int main(int argc, char **argv){
    if(argc <= 1) // if the user did not input the correct number of command line arguments then print a warning statement
    {
        cout << "You need to add more command line arguments\n";
        return -1;
    }
    string appName = argv[1]; // take the name of the app from the second argument in the command line
    logger *log = new logger(appName); 
    vector<log_message> appLog = log->readAll(); // read all of data in the database table

  for(int i = 0; i < appLog.size(); i++) // loop through the database to print out in the correct format
  {
        cout<<appLog.at(i).get_message()<<": ";
        cout<<appLog[i].get_timestamp()<<"\n";
  }

  delete log;
}
