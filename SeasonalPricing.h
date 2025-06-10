#pragma once
#include "PricingStrategy.h"
#include <cstring>
#include <iostream>
#include "EnumClasses.h"



class SeasonalPricing : public PricingStrategy {
private:
    EnumClasses::Season currentSeason;

public:
    SeasonalPricing();
    SeasonalPricing(EnumClasses::Season season);

    void setSeason(const char* seasonStr);
    const char* getSeason() const;

    double calculatePrice(double basePrice) const override;
    PricingStrategy* clone() const override;


    const char* getName() const override;

    const char* getParameter() const override;
};


