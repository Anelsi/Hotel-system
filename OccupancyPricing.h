#pragma once
#include "PricingStrategy.h"
#include <cstring>
#include "EnumClasses.h"

#include <iostream>

class OccupancyPricing : public PricingStrategy
{
private:

    EnumClasses::OccupancyLevel level;

public:

    OccupancyPricing(EnumClasses::OccupancyLevel level);


    double calculatePrice(double basePrice) const override;

    const char* getName() const override;

    const char* getParameter() const override;

    void setOccupancyLevel(const char* occ);
    const char* getOccupancyLevel() const;
    PricingStrategy* clone() const override;
};


