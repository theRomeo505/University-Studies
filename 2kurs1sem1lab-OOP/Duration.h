#pragma once
class Date;
class Duration {
public:
    //int year;
    //int month;
    int day;
    //int hour;
    //int min;
    int sec;
    Duration(Date d1, Date d2);
    int insec();
    int indays();
    //Date todate();
};

