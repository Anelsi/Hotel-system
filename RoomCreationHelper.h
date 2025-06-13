
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Room.h"
#include "Accommodation.h"
#include "PricingStrategyFactory.h" 

void createAndAddRoom(Accommodation& accommodation) {
    std::cout << "=== Create new room ===\n";

    
    int roomNumber;
    std::cout << "Enter room number: ";
    std::cin >> roomNumber;

    
    double basePrice;
    std::cout << "Enter base price: ";
    std::cin >> basePrice;

    
    std::string roomTypeStr;
    std::cout << "Enter room type (Single, Double, Apartment, Deluxe, Conference) : ";
    std::cin >> roomTypeStr;

   
    std::string statusStr;
    std::cout << "Enter room status (Available, Reserved, underRenovation): ";
    std::cin >> statusStr;

    
    std::string strategyName, strategyParam;
    std::cout << "Enter pricing strategy (Occupancy, Seasonal, Weekend, Regular) or \"null\" for no startegy";
    std::cin >> strategyName;
    if (strategyName != "null") {
        std::cout << "Enter parameter for pricing strategy (for example \"Low\"/\"Medium\"/\"High\" за Occupancy, "
            "\"Spring\"/\"Summer\"/... за Seasonal, \"Saturday\"/\"Sunday\" за Weekend; null for Regular): ";
        std::cin >> strategyParam;
    }

    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    
    EnumClasses::RoomType roomTypeEnum = EnumClasses::RoomType::Single;
    if (roomTypeStr == "Single") {
        roomTypeEnum = EnumClasses::RoomType::Single;
    }
    else if (roomTypeStr == "Double") {
        roomTypeEnum = EnumClasses::RoomType::Double;
    }
    else if (roomTypeStr == "Apartment") {
        roomTypeEnum = EnumClasses::RoomType::Apartment;
    }
    else if (roomTypeStr == "Deluxe") {
        roomTypeEnum = EnumClasses::RoomType::Deluxe;
    }
    else if (roomTypeStr == "Conference") {
        roomTypeEnum = EnumClasses::RoomType::Conference;
    }
    else {
        std::cout << "Warning: Invalid type. Will default to: Single.\n";
    }

    
    EnumClasses::Status statusEnum = EnumClasses::Status::Available;  
    if (statusStr == "Available") {
        statusEnum = EnumClasses::Status::Available;
    }
    else if (statusStr == "Reserved") {
        statusEnum = EnumClasses::Status::Reserved;
    }
    else if (statusStr == "underRenovation") {
        statusEnum = EnumClasses::Status::underRenovation;
    }
    else {
        std::cout << "Warning: Invalid status. Will default to: Available.\n";
    }

    
    PricingStrategy* stratPtr = nullptr;
    if (strategyName != "null") {
        
        stratPtr = PricingStrategyFactory::createStrategy(strategyName.c_str(),
            strategyParam.empty() ? nullptr : strategyParam.c_str());
        if (!stratPtr) {
            std::cout << "Warning: Failed to create strategy \""
                << strategyName << "\" with parameter \"" << strategyParam
                << "\". Will be used without strategy.\n";
        }
    }

    
    Room newRoom(roomNumber, basePrice, roomTypeEnum, statusEnum, stratPtr);

    
    std::ofstream outFile("rooms.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open file for recording: rooms.txt\n";
    }
    else {
        newRoom.saveToFile(outFile);
       
        outFile.close();
        std::cout << "Room data was saved to the file rooms.txt successfully.\n";
    }

    
    accommodation.addNewRoom(newRoom);
    std::cout << "The room was successfully added to the accommodation system.\n";

    
    delete stratPtr;
}
