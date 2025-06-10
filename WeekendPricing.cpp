#include "WeekendPricing.h"


WeekendPricing::WeekendPricing(EnumClasses::DayOfWeek day) : currentDay(day) {

};

void WeekendPricing::setDay(const char* dayStr) {

    if (strcmp(dayStr, "Monday") == 0) {
        currentDay = EnumClasses::DayOfWeek::Monday;
    }

    else if (strcmp(dayStr, "Tuesday") == 0) {
        currentDay = EnumClasses::DayOfWeek::Tuesday;
    }

    else if (strcmp(dayStr, "Wednesday") == 0) {
        currentDay = EnumClasses::DayOfWeek::Wednesday;
    }

    else if (strcmp(dayStr, "Thursday") == 0) {
        currentDay = EnumClasses::DayOfWeek::Thursday;
    }
    else if (strcmp(dayStr, "Friday") == 0) {
        currentDay = EnumClasses::DayOfWeek::Friday;
    }

    else if (strcmp(dayStr, "Saturday") == 0) {
        currentDay = EnumClasses::DayOfWeek::Saturday;
    }

    else if (strcmp(dayStr, "Sunday") == 0) {
        currentDay = EnumClasses::DayOfWeek::Sunday;
    }

    else {
        std::cout << "Invalid day: " << dayStr << std::endl;
    }

}

const char* WeekendPricing::getDay() const {
    switch (currentDay) {

    case EnumClasses::DayOfWeek::Monday: return "Monday";

    case EnumClasses::DayOfWeek::Tuesday: return "Tuesday";

    case EnumClasses::DayOfWeek::Wednesday: return "Wednesday";

    case EnumClasses::DayOfWeek::Thursday: return "Thursday";

    case EnumClasses::DayOfWeek::Friday: return "Friday";

    case EnumClasses::DayOfWeek::Saturday: return "Saturday";

    case EnumClasses::DayOfWeek::Sunday: return "Sunday";


    default: return "Unknown";
    }
}

double WeekendPricing::calculatePrice(double basePrice) const {

    if (currentDay == EnumClasses::DayOfWeek::Saturday || currentDay == EnumClasses::DayOfWeek::Sunday) {
        return basePrice * 1.20;

    }

    return basePrice;
}
PricingStrategy* WeekendPricing::clone() const {

    return new WeekendPricing(*this);

}

WeekendPricing::WeekendPricing()
    : currentDay(EnumClasses::DayOfWeek::Monday) {};

const char* WeekendPricing::getName() const {
    return "Weekend";
}

const char* WeekendPricing::getParameter() const {
    switch (currentDay) {
    case EnumClasses::DayOfWeek::Monday: return "Monday";
    case EnumClasses::DayOfWeek::Tuesday: return "Tuesday";
    case EnumClasses::DayOfWeek::Wednesday: return "Wednesday";
    case EnumClasses::DayOfWeek::Thursday: return "Thursday";
    case EnumClasses::DayOfWeek::Friday: return "Friday";
    case EnumClasses::DayOfWeek::Saturday: return "Saturday";
    case EnumClasses::DayOfWeek::Sunday: return "Sunday";
    default: return "Unknown";
    }
}
