#include "Date.h"
#include "Duration.h"
#include <iostream>
//using namespace std;
//class Duration;
//class Date; 
     Date::Date() {
        this->year = 2000;
        this->month = 1;
        this->day = 1;
        this->hour = 1;
        this->min = 1;
        this->sec = 1;
        //this->OE = true;
       // this->next = NULL;
    }
    Date::Date(int day, int month, int year, int hour, int min, int sec) {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->min = min;
        this->sec = sec;
        //   this->next = NULL;
    }
  void  Date::show() {
        std::cout << day << ' ' << month << ' ' << year << " " << ((hour / 10 == 0) ? " 0" : " ") << hour << ((min / 10 == 0) ? ":0" : ":") << min << ((sec / 10 == 0) ? ":0" : "0") << sec << endl;
    }
  bool  Date::isRight() {
        int months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (hour < 0 || hour >= 24 || min < 0 || min>59 || sec < 0 || sec>60 || day > 31 || day <= 0 || month <= 0 || month > 12 || year <= 0
            || day > months[month - 1] || (!(year % 4 == 0 && year % 100 != 0) && month == 2 && day == 29))
            return false;
        return true;
    }
    void Date::add(Duration d) { 
        int months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        //this->day += d.day;
        int m =month;
        //this->month += d.month;
        //this->year += d.year;
        //this->hour += d.hour;
        //this->min += d.min;
        sec += d.insec();
        min += sec / 60;
        sec += this->sec % 60;
       
        while (this->min >= 60)
        {
            this->min -= 60;
            this->hour++;
        }
        while (this->hour >= 24) {
            this->hour -= 24;
            this->day++;
        }
        while (this->day > months[m]) {
            this->day -= months[m];
            m++;
            if (m == 13)
                m = 1;
            this->month++;
        }
        while (this->month > 12)
        {
            this->month -= 12;
            this->year++;
        }
    }
    int Date::weekday() {
        Date d(1, 1, 1900, 0, 0, 0); // Monday
        std::string weekd[7] = { "mon","tue","wed","th","fri","sat","sun" };
        Duration dur(*this, d);
        std::cout << weekd[(dur.indays()) % 7];
        return dur.indays() % 7 + 1;
    }
    int Date::weeknumber_year() {
        int dday = 0;
        int months[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        for (int i = 0; i < this->month - 1; i++) {
            dday += months[i];
        }
        dday += this->day;
        dday -= this->weekday() - 1; // monday
        return dday / 7;
    }
    int Date::weeknumbermonth() {
        int dday = this->day - this->weekday() + 1;
        return dday / 7;
    }
    void Date::alternate() {
        std::string weekd[7] = { "mon","tue","wed","th","fri","sat","sun" };
        std::string months[12] = { "jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec" };
        std::cout << this->weeknumbermonth() << weekd[this->weekday()] << " of " << months[this->month];
    }
    void Date::ulian() {
        int a = (14 - this->month) / 12;
        int y = this->year + 4800 - a;
        int m = this->month + 12 * a - 3;
        int jdn = this->day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
        cout << "julian day " << jdn;
    }

