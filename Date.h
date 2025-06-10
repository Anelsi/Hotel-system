#pragma once
#include <string>  
#include <ostream>  
#include <istream> 



class Date {
private:
    int day = 1;
    int month = 1;
    int year = 1;

    bool isLeapYear(int y) const;
    int getDaysInMonth(int m, int y) const;


public:

    Date() = default;

    Date(int d, int m, int y);


    int getDay() const;
    int getMonth() const;
    int getYear() const;


    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    int getDifferenceInDays(const Date& other) const;
    bool operator<(const Date& other) const;
    std::string toString() const;


    void saveToFile(std::ostream& out) const;
    void loadFromFile(std::istream& in);

    Date& operator++();

};



