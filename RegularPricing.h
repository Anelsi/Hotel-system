#pragma once
#include "PricingStrategy.h"



class RegularPricing : public PricingStrategy
{
public:
    double calculatePrice(double basePrice) const override;
    PricingStrategy* clone() const override;

    const char* getName() const override;

    const char* getParameter() const override;

};

