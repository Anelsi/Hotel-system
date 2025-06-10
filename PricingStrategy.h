#pragma once
class PricingStrategy
{
public:

    virtual PricingStrategy* clone() const = 0;

    virtual const char* getName() const = 0;
    virtual const char* getParameter() const = 0;

    virtual double calculatePrice(double basePrice) const = 0;
    virtual ~PricingStrategy() = default;
};


