#include <iostream>

#include "simtime.h"

SimTime* SimTime::pInstance = NULL; 

SimTime* SimTime::Instance()
{
    
    if (!pInstance) 
    {
        pInstance = new SimTime();
    }

    return (pInstance);

}

void SimTime::Initialize(int y)
{
    year    = y;
    weeks   = 1;
    days    = 1;
    hours   = 0;
    minutes = 0;
    seconds = 0;
    month   = 1;
    day_of_month = 1;
    day_of_week  = SUNDAY;

    prev_sec   = seconds;
    prev_min   = minutes;
    prev_hour  = hours;
    prev_day   = days;
    prev_week  = weeks;
    prev_month = month;
    prev_year  = year;
}

void SimTime::CalcDayOfWeek (int d)
{
    day_of_week = (DaysOfWeek) (d % 7);
}

void SimTime::CalcMonthDay (int w, int d)
{
    int julianDay = (w-1)*7 + d;

    if (julianDay <= 31)
    {
        month = 1;
        day_of_month  = julianDay;
    }
    else if (julianDay <= 59)
    {
        month = 2;
        day_of_month  = julianDay-31;        
    }
    else if (julianDay <= 90)
    {
        month = 3;
        day_of_month  = julianDay-59;        
    }
    else if (julianDay <= 120)
    {
        month = 4;
        day_of_month  = julianDay-90;        
    }
    else if (julianDay <= 151)
    {
        month = 5;
        day_of_month  = julianDay-120;        
    }
    else if (julianDay <= 181)
    {
        month = 6;
        day_of_month  = julianDay-151;        
    }
    else if (julianDay <= 212)
    {
        month = 7;
        day_of_month  = julianDay-181;        
    }
    else if (julianDay <= 243)
    {
        month = 8;
        day_of_month  = julianDay-212;        
    }
    else if (julianDay <= 273)
    {
        month = 9;
        day_of_month  = julianDay-243;        
    }
    else if (julianDay <= 304)
    {
        month = 10;
        day_of_month  = julianDay-273;        
    }
    else if (julianDay <= 334)
    {
        month = 11;
        day_of_month  = julianDay-304;        
    }
    else 
    {
        month = 12;
        day_of_month  = julianDay-334;        
    }

}

char * SimTime::GetDate()
{
    sprintf (dateString, "%4d/%02d/%02d", year, month, day_of_month);
    return (dateString);
}

char * SimTime::GetTime()
{
    sprintf (timeString, "%4d/%02d/%02d %02d:%02d:%02d", year, month, day_of_month, hours, minutes, seconds);
    return (timeString);
}


bool SimTime::IsWeekDay()
{
    return (day_of_week != SATURDAY && day_of_week != SUNDAY);
}

void SimTime::Tick()
{
    prev_sec   = seconds;
    prev_min   = minutes;
    prev_hour  = hours;
    prev_day   = days;
    prev_week  = weeks;
    prev_month = month;
    prev_year  = year;
    FastForwardDays(1);

 //   printf ()
}

void SimTime::FastForwardSeconds(int n)
{
    prev_sec = seconds;
    if ((seconds+n) < 60)
        seconds+=n;
    else
    {
        seconds = seconds + n - 60;
        FastForwardMinutes(1);
    }
}

void SimTime::FastForwardMinutes(int n)
{
    prev_min = minutes;
    if ((minutes+n) < 60)
        minutes+=n;
    else
    {
        minutes = minutes + n - 60;
        FastForwardHours(1);
    }
}

void SimTime::FastForwardHours(int n)
{
    prev_hour = hours;
    if ((hours+n) < 24)
        hours+=n;
    else
    {
        hours = hours + n - 24;
        FastForwardDays(1);
    }
}

void SimTime::FastForwardDays(int n)
{
    prev_day = days;
    if ((days+n) <=7)
        days+=n;
    else
    {
        days = days + n - 7;
        FastForwardWeeks(1);
    }
    CalcMonthDay (weeks, days);
    CalcDayOfWeek (days);
}

void SimTime::FastForwardWeeks(int n)
{
    prev_week = weeks;
    if ((weeks+n) <=52)
        weeks+=n;
    else
    {
        weeks = weeks + n - 52;
        FastForwardYears(1);
    }
    CalcMonthDay (weeks, days);
}


void SimTime::FastForwardYears(int n)
{
    prev_year = year;
    year+=n;
}


