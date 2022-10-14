


#include "logger.h"


int stop;

using namespace std;

void inthand(int param) { stop = 1; }

int main(int argc, char **argv) {

  vector<string> msg;
  int radnom;

  string argvstring = argv[0];
  size_t pos = argvstring.find("/");      // position of "/" in str
  string appName = argvstring.substr(pos + 1); // get from "/" to the end
  cout << "name of app is " << appName << "\n";
  logger *log = new logger(appName);

  signal(SIGINT, inthand);

  // push all of the command line arguments into the vector
  for (int i = 1; i < argc; ++i) { 
    msg.push_back(argv[i]);
  }

  // randomly select one of the messages and write them into the database
  while (!stop) {
    radnom = rand() % msg.size();
    string sel_msg = msg[radnom]; // select random messages to write into the database
    log->write(sel_msg);
    sleep(rand() % 10); // make the program sleep between 1 to 10 seconds while inserting new data into the database
  }

  delete log;
  printf("exiting safely\n");

  return 0;
}
