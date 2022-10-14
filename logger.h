#pragma once 

#ifndef loggerHeader
#define loggerHeader

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
      
#include <math.h>
#include <chrono>
#include <string>
#include "log_message.h"

#include <signal.h>
#include <string.h>
#include <thread>
#include <vector>


#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>

// #endif


class logger{

    public:
        logger(std::string appName);
        ~logger();
        void write(std::string message);
        static int callback(void *NotUsed, int argc, char **argv, char **azColName); 
        std::vector<log_message> readAll();
        std:: string getDate();

    private:
    
    const char* fileName = "data.db";
    std::string appName2;
    sqlite3* db;     // Pointer to SQLite connection
    
};

#endif
