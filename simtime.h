#ifndef SIMTIME_H
#define SIMTIME_H

enum UpdateRate {PER_SECOND, PER_MINUTE, HOURLY, DAILY, WEEKLY, MONTHLY, YEARLY};
enum DaysOfWeek {SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};


class SimTime
{
    public:
        static SimTime* Instance();
        void Initialize(int y);

        int GetYear(){return year;};
        int GetMonth(){return month;};
        int GetWeek(){return weeks;};
        int GetDay(){return days;};
        int GetDayOfMonth(){return day_of_month;};
        int GetHours(){return hours;};
        int GetMinutes(){return minutes;};
        int GetSeconds(){return seconds;};
        bool IsWeekDay();
        bool NewSecond(){return (seconds != prev_sec);};
        bool NewMinute(){return (minutes != prev_min);};
        bool NewHour(){return (hours != prev_hour);};
        bool NewDay(){return (days != prev_day);};
        bool NewWeek(){return (weeks != prev_week);};
        bool NewMonth(){return (month != prev_month);};
        bool NewYear(){return (year != prev_year);};

        char *GetDate();
        char *GetTime();

        void Tick();  // one day
        void FastForwardSeconds(int n);
        void FastForwardMinutes(int n);
        void FastForwardHours(int n);
        void FastForwardDays(int n);
        void FastForwardWeeks(int n);
        void FastForwardYears(int n);

    private:
        SimTime(){};  // private constructor
        SimTime(SimTime const&){};
        SimTime& operator=(SimTime const&){};
        static SimTime* pInstance; 

        void CalcMonthDay (int w, int d);
        void CalcDayOfWeek (int d);


        int year;
        int month;
        int day_of_month;
        DaysOfWeek day_of_week;
        int weeks;
        int days;
        int hours;
        int minutes;
        int seconds;

        int prev_year;
        int prev_month;
        int prev_week;
        int prev_day;
        int prev_hour;
        int prev_min;
        int prev_sec;

        char timeString[80];
        char dateString[80];

};

#endif
