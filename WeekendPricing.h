#pragma once
#include<cstring>

#include "PricingStrategy.h"
#include <iostream>
#include "EnumClasses.h"



class WeekendPricing : public PricingStrategy {

private:

    EnumClasses::DayOfWeek currentDay;

public:
    WeekendPricing();
    PricingStrategy* clone() const override;

    //da pravq li def construcor i koga go pravq nego WeekendPricing();
    WeekendPricing(EnumClasses::DayOfWeek day);
    //kato syzdam takyv initializer constructoor trybva li gore v klasa da definiram def stoinost

    void setDay(const char* dayStr);
    const char* getDay() const;
    double calculatePrice(double basePrice) const override;

    const char* getName() const override;
    const char* getParameter() const override;
};

