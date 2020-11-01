#pragma once
class Data;
class Program
{
public:
    void send(Data* d);
    void send(Data* d, int pediod);
    void sendRandom(Data* d);
};

