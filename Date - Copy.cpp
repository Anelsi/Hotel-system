#include "Date.h"
#include <stdexcept>
#include <iomanip>
#include <sstream>
#define _CRT_SECURE_NO_WARNINGS




Date::Date(int d, int m, int y) : day(d), month(m), year(y) {

};


int Date::getDay() const {
    return day;
}
int Date::getMonth() const {
    return month;
}
int Date::getYear() const {
    return year;
}


void Date::setYear(int y) {
    if (y >= 1900 && y <= 2100) {
        year = y;
    }
    else {
        throw std::invalid_argument("not valid year");
    }
}

void Date::setMonth(int m) {
    if (m >= 1 && m <= 12) {
        month = m;
    }
    else {
        throw std::invalid_argument("not valid month");
    }
}

void Date::setDay(int d) {
    int maxDay = getDaysInMonth(month, year);
    if (d >= 1 && d <= maxDay) {
        day = d;
    }
    else {
        throw std::invalid_argument("not valid day");
    }
}

int Date::getDaysInMonth(int m, int y) const {
    switch (m) {
    case 2: return isLeapYear(y) ? 29 : 28;
    case 4: case 6: case 9: case 11: return 30;
    default: return 31;
    }
}

bool Date::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


int countDaysFromEpoch(int day, int month, int year) {
    static const int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int days = year * 365;

    // Добавяме високосни години
    for (int y = 0; y < year; ++y) {
        if (isLeapYear(y)) {
            days++;
        }
    }

    // Добавяме дни от месеците
    for (int m = 1; m < month; ++m) {
        days += daysInMonth[m - 1];
        if (m == 2 && isLeapYear(year)) {
            days++; // февруари във високосна година
        }
    }

    days += day;
    return days;
}

int Date::getDifferenceInDays(const Date& other) const {
    int thisDays = countDaysFromEpoch(this->day, this->month, this->year);
    int otherDays = countDaysFromEpoch(other.day, other.month, other.year);

    // Връща абсолютната разлика
    return (thisDays > otherDays) ? (thisDays - otherDays) : (otherDays - thisDays);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << day << "."
        << std::setw(2) << std::setfill('0') << month << "."
        << year;
    return oss.str();
};
Date& Date::operator++() {
    day++;

    int daysInCurrentMonth = getDaysInMonth(month, year);
    if (day > daysInCurrentMonth) {
        day = 1;
        month++;

        if (month > 12) {
            month = 1;
            year++;
        }
    }

    return *this;
}
void Date::saveToFile(std::ostream& out) const {
    out << day << ' ' << month << ' ' << year << ' ';
}

void Date::loadFromFile(std::istream& in) {
    int d, m, y;
    in >> d >> m >> y;
    setDay(d);
    setMonth(m);
    setYear(y);
}

