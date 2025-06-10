#include "PricingStrategyFactory.h"


PricingStrategy* PricingStrategyFactory::createStrategy(const char* strategyType, const char* parameter) {
    if (strcmp(strategyType, "Occupancy") == 0) {
        OccupancyPricing* strat = new OccupancyPricing(EnumClasses::OccupancyLevel::Medium);
        if (parameter) {
            if (strcmp(parameter, "Low") == 0)
                strat->setOccupancyLevel("Low");
            else if (strcmp(parameter, "Medium") == 0)
                strat->setOccupancyLevel("Medium");
            else if (strcmp(parameter, "High") == 0)
                strat->setOccupancyLevel("High");
            else {
                delete strat;
                std::cout << "Invalid occupancy level: " << parameter << std::endl;
                return nullptr;
            }
        }
        return strat;
    }
    else if (strcmp(strategyType, "Seasonal") == 0) {
        SeasonalPricing* strat = new SeasonalPricing(EnumClasses::Season::Spring);
        if (parameter) {
            if (strcmp(parameter, "Spring") == 0)
                strat->setSeason("Spring");
            else if (strcmp(parameter, "Summer") == 0)
                strat->setSeason("Summer");
            else if (strcmp(parameter, "Autumn") == 0)
                strat->setSeason("Autumn");
            else if (strcmp(parameter, "Winter") == 0)
                strat->setSeason("Winter");
            else {
                delete strat;
                std::cout << "Invalid season: " << parameter << std::endl;
                return nullptr;
            }
        }
        return strat;
    }
    else if (strcmp(strategyType, "Weekend") == 0) {
        WeekendPricing* strat = new WeekendPricing(EnumClasses::DayOfWeek::Monday);
        if (parameter) {
            if (strcmp(parameter, "Saturday") == 0)
                strat->setDay("Saturday");
            else if (strcmp(parameter, "Sunday") == 0)
                strat->setDay("Sunday");
            else {
                delete strat;
                std::cout << "Invalid day: " << parameter << std::endl;
                return nullptr;
            }
        }
        return strat;
    }
    else if (strcmp(strategyType, "Regular") == 0) {
        return new RegularPricing();
    }
    else {
        std::cout << "Unknown strategy type: " << strategyType << std::endl;
        return nullptr;
    }

}

