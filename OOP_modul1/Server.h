#include <vector>
class Program;
class Server
{
public:
    int id;
    std::vector<Program*> p;
    std::vector<Server*> servers;
    std::vector<int> time;
};
