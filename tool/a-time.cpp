#include <stdio.h>
#include <time.h>

/*
 * current system is EDT time
 * UTC
 * GMT = UTC
 * PST = UTC-8
 * EST = UTC-5
 * EDT = UTC-4
 * BeiJing = UTC+8
 * */

/*
 * get time zone info
 * # timedatectl list-timezones | grep Shanghai
 * # timedatectl list-timezones | grep UTC
 * # timedatectl set-timezone UTC
 * */


#define HOUR_SECONDS 60*60
#define DAY_SECONDS  24
#define UTC_FIXED    4*HOUR_SECONDS

void get_time(int year, int mon, int day, int hour, int min, int sec)
{
    struct tm tm1;
    tm1.tm_year = year-1900;       // 1900 start
    tm1.tm_mon = mon-1;            // 0-11
    tm1.tm_mday = day;             // 1-31
    tm1.tm_hour = hour;            // 0-23
    tm1.tm_min = min;              // 0-59
    tm1.tm_sec = sec;              // 0-59

    time_t t1 = mktime(&tm1);
    printf("UTC time_t %04d-%02d-%02d %02d:%02d:%02d: %u->%u\n",
           //year, mon, day, hour, min, sec, t1, t1-UTC_FIXED);
           year, mon, day, hour, min, sec, t1, t1);
}

void get_time2(time_t t)
{
    struct tm tm1;
    //time_t t1 = t+UTC_FIXED;
    time_t t1 = t;
    localtime_r(&t1, &tm1);

    printf("UTC time_t %u: %04d-%02d-%02d %02d:%02d:%02d\n",
           t1, tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday,
           tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
}
int main()
{
    time_t now;
    time(&now);
    printf("now time: %u\n", now);

    get_time(2018, 4, 1, 14, 0, 0);
    get_time(2018, 5, 31, 14, 0, 0);
    get_time(2018, 5, 24, 14, 46, 0);
    get_time(2018, 9, 1, 14, 46, 0);
    get_time(2018, 8, 1, 1, 40, 0);

    get_time(2019, 8, 1, 1, 40, 0);
    get_time(2020, 8, 1, 1, 40, 0);
    get_time(2021, 8, 1, 1, 40, 0);

    get_time2(1522591200);
    get_time2(1527775200);
    get_time2(1534142447);

    return 0;
}
