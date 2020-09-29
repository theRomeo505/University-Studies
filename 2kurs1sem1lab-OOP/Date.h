#pragma once

class Date {
public:
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    //bool OE;
    Date();
    Date(int day, int month, int year, int hour, int min, int sec);
    void show();
    bool isRight();
    void add(Duration d);
    int weekday();
    int weeknumber_year();
    int weeknumbermonth();
    void alternate();
    void ulian();
};