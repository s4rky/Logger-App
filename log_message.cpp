
#include "log_message.h"

using namespace std;


    log_message::log_message(string thismsg, string thistimestamp){
        msg = thismsg;
        timestamp = thistimestamp;
    }
    
    
    log_message::~log_message(){
    }

    string log_message::get_message(){
        return msg;
    }

    string log_message::get_timestamp(){
        return timestamp;
    }

