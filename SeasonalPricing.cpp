#pragma once
#include "SeasonalPricing.h"
#include <cstring>
#include <iostream>
#include "EnumClasses.h"

SeasonalPricing::SeasonalPricing(EnumClasses::Season season) : currentSeason(season) {

}

void SeasonalPricing::setSeason(const char* seasonStr) {
    if (strcmp(seasonStr, "Spring") == 0) {
        currentSeason = EnumClasses::Season::Spring;
    }

    else if (strcmp(seasonStr, "Summer") == 0) {
        currentSeason = EnumClasses::Season::Summer;
    }

    else if (strcmp(seasonStr, "Autumn") == 0) {
        currentSeason = EnumClasses::Season::Autumn;
    }

    else if (strcmp(seasonStr, "Winter") == 0) {
        currentSeason = EnumClasses::Season::Winter;
    }

    else {
        std::cout << "Invalid season: " << seasonStr << std::endl;
    }

}


const char* SeasonalPricing::getSeason() const {

    switch (currentSeason) {

    case EnumClasses::Season::Spring: return "Spring";

    case EnumClasses::Season::Summer: return "Summer";

    case EnumClasses::Season::Autumn: return "Autumn";

    case EnumClasses::Season::Winter: return "Winter";

    default: return "Unknown";

    }
}

double SeasonalPricing::calculatePrice(double basePrice) const {
    switch (currentSeason) {

    case EnumClasses::Season::Spring:

        return basePrice * 1.10;

    case EnumClasses::Season::Summer:

        return basePrice * 1.25;

    case EnumClasses::Season::Autumn:

        return basePrice * 0.95;

    case EnumClasses::Season::Winter:

        return basePrice * 0.85;

    default:

        return basePrice;
    }
}
SeasonalPricing::SeasonalPricing()
    : currentSeason(EnumClasses::Season::Spring) {}

PricingStrategy* SeasonalPricing::clone() const {

    return new SeasonalPricing(*this);

}
const char* SeasonalPricing::getName() const {
    return "Seasonal";
}

const char* SeasonalPricing::getParameter() const {
    switch (currentSeason) {
    case EnumClasses::Season::Spring: return "Spring";
    case EnumClasses::Season::Summer: return "Summer";
    case EnumClasses::Season::Autumn: return "Autumn";
    case EnumClasses::Season::Winter: return "Winter";
    default: return "Unknown";
    }
}
