#pragma once
#include "PricingStrategy.h"
#include "OccupancyPricing.h"
#include "SeasonalPricing.h"
#include "WeekendPricing.h"
#include "RegularPricing.h"
#include <cstring>
#include <iostream>

class PricingStrategyFactory {
public:

    static PricingStrategy* createStrategy(const char* strategyType, const char* parameter = nullptr);
};





