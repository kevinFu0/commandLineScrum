#include <algorithm> 
#include <iomanip>
#include <string>
#include <vector>

#include <ctime>
#include <cstdlib>
#include <map>
#include <cstring>
#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;


class Date {

private:
    int day;
    int month;
    int year;

public:
    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date() {
        this->day = 1;
        this->month = 1;
        this->year = 2000;
    }

    bool operator>(Date obj) {
        if (month == obj.month && year == obj.year) {
            return day > obj.day;
        }

        if (year == obj.year) {
            return month > obj.month;
        }

        return year > obj.year;
    }

    string asString() {
        stringstream ss;

        ss << month << "/" << day << "/" << year << endl;

        return ss.str();
    }

    static Date createDate() {
        cout << "Enter your date in format: mm/dd/yyyy" << endl;

        int month;
        int day;
        int year;
        while (true) {
            scanf("%d/%d/%d", &month, &day, &year);

            if (!(month >= 1 && month <= 12)) {
                cout << "Please re-enter a date with a valid month" << endl;
            }

            if (!(year >= 1 && year <= 2100)) {
                cout << "Re - enter a date with a valid year" << endl;
            }

            if (!(day >= 1 && day <= 31)) {
                cout << "Re-enter a date with a valid day" << endl;
            }

            else {
                break;
            }
        }


        Date temp = Date(day, month, year);
        return temp;
    }
};
