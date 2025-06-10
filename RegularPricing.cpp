#include "RegularPricing.h"



double RegularPricing::calculatePrice(double basePrice) const {

    return basePrice;

}
PricingStrategy* RegularPricing::clone() const {

    return new RegularPricing(*this);

}

const char* RegularPricing::getName() const {
    return "Regular";
}

const char* RegularPricing::getParameter() const {
    return "";
}