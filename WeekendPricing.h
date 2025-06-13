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

    
    WeekendPricing(EnumClasses::DayOfWeek day);
    

    void setDay(const char* dayStr);
    const char* getDay() const;
    double calculatePrice(double basePrice) const override;

    const char* getName() const override;
    const char* getParameter() const override;
};

