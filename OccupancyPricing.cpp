#include "OccupancyPricing.h"

OccupancyPricing::OccupancyPricing(EnumClasses::OccupancyLevel level) :level(level) {


};


void OccupancyPricing::setOccupancyLevel(const char* occ) {
    if (strcmp(occ, "Low") == 0) {
        level = EnumClasses::OccupancyLevel::Low;
    }
    else if (strcmp(occ, "Medium") == 0) {
        level = EnumClasses::OccupancyLevel::Medium;
    }
    else if (strcmp(occ, "High") == 0) {
        level = EnumClasses::OccupancyLevel::High;
    }
    else {
        std::cout << "Invalid occupancy level: " << occ << std::endl;

    }
    std::cout << "Occupancy level set to: " << getOccupancyLevel() << std::endl;
}

const char* OccupancyPricing::getOccupancyLevel() const {
    switch (level) {
    case EnumClasses::OccupancyLevel::Low: return "Low";
    case EnumClasses::OccupancyLevel::Medium: return "Medium";
    case EnumClasses::OccupancyLevel::High: return "High";

    default: return "Unknown";
    }
}
PricingStrategy* OccupancyPricing::clone() const {

    return new OccupancyPricing(*this);

}

double OccupancyPricing::calculatePrice(double basePrice) const {
    switch (level) {
    case EnumClasses::OccupancyLevel::Low:
        return basePrice * 0.9;
    case EnumClasses::OccupancyLevel::Medium:
        return basePrice;
    case EnumClasses::OccupancyLevel::High:
        return basePrice * 1.2;
    default:
        std::cout << "Unknown occupancy level. Returning base price." << std::endl;
        return basePrice;
    }
}

const char* OccupancyPricing::getName() const {
    return "Occupancy";
}

const char* OccupancyPricing::getParameter() const {
    switch (level) {
    case EnumClasses::OccupancyLevel::Low: return "Low";
    case EnumClasses::OccupancyLevel::Medium: return "Medium";
    case EnumClasses::OccupancyLevel::High: return "High";
    default: return "Unknown";
    }
}
