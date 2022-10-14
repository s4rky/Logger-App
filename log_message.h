
#pragma once 

#include <string>

class log_message
{
    public:
    log_message(std::string, std::string);
    ~log_message();
    std::string get_message();
    std::string get_timestamp();

    private:
    std::string msg;
    std::string timestamp;
};


