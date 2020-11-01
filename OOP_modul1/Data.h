#include <iostream>
//#include "Server.h"
//#include "Program.h"
class Server;
class Program;
class Data
{
public:
    Server *fromS;
    Server *toS;
    Program *fromP;
    Program *toP;
    int size;
    bool needanswer;
    std::string type;
};

