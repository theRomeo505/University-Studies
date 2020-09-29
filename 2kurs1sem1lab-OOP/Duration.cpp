#include "Duration.h"
#include "Date.h"
class Duration;
   Duration::Duration(Date d1, Date d2) {
        int months[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
        Date d(d2.day - d1.day, d2.month - d1.month, d2.year - d1.year, d2.hour - d1.hour, d2.min - d1.min, d2.sec - d1.sec);
        this->sec = d2.hour * 3600 + d2.min * 60 + d2.sec - 3600 * d1.hour - 60 * d1.min - d1.sec;
        this->day = d2.year * 365 + d2.day - d1.year * 365 - d1.day;
        for (int i = 0; i < d2.month; i++)
            this->day += months[i];
        for (int i = 0; i < d1.month; i++)
            this->day -= months[i];
        while (this->sec > 3600 * 24)
        {
            this->sec -= 3600 * 24;
            this->day += 1;
        }
        while (this->sec < 0) {
            this->sec += 3600 * 24;
            this->day -= 1;
        }
    }
    int Duration::insec() {
        return this->sec + this->day * 3600 * 24;
    }
    int Duration::indays()
    {
        return this->day + this->sec / 86400;
    }
   // Date Duration::todate() {
     //   return Date(day, 0, 0, 0, 0, sec);
    //}
