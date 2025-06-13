
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Guest.h"
#include "Room.h"
#include "Reservation.h"
#include "EnumClasses.h"
#include "PricingStrategyFactory.h" 
#include "Date.h"                

void createAndSaveReservation() {
    std::cout << "=== Create new reservation ===\n";

    
    std::cout << "\n-- Guest data --\n";

  
    std::cout << "Enter guest's name: ";
    std::string guestName;
    std::getline(std::cin, guestName);

    
    std::cout << "Enter guest's email: ";
    std::string guestEmail;
    std::getline(std::cin, guestEmail);

   
    std::cout << "Enter unique guest's id: ";
    int guestID;
    std::cin >> guestID;

  
    std::cout << "Enter guest's phone number (" << EnumClasses::MAX_NUMBERS
        << " for example: 0887123456): ";
    std::string phoneInput;
    std::cin >> phoneInput;

    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

   
    int phoneDigits[EnumClasses::MAX_NUMBERS] = { 0 };
    if (phoneInput.length() < static_cast<size_t>(EnumClasses::MAX_NUMBERS)) {
        std::cout << "Warning: The number entered is less than"
            << EnumClasses::MAX_NUMBERS << " digits. Will be padded with leading zeros.\n";
    }
    size_t offset = (phoneInput.length() > static_cast<size_t>(EnumClasses::MAX_NUMBERS))
        ? phoneInput.length() - EnumClasses::MAX_NUMBERS
        : 0;
    size_t idx = 0;
    for (size_t i = offset; i < phoneInput.length() && idx < EnumClasses::MAX_NUMBERS; ++i, ++idx) {
        char c = phoneInput[i];
        if (!std::isdigit(c)) {
            std::cout << "Invalid character '" << c
                << "' at possition " << i
                << ". 0 will be set instead of this number.\n";
            phoneDigits[idx] = 0;
        }
        else {
            phoneDigits[idx] = c - '0';
        }
    }
    

    
    Guest tempGuest;
    tempGuest.setName(guestName.c_str());
    tempGuest.setEmail(guestEmail.c_str());
    tempGuest.setGuestNum(guestID);
    tempGuest.setPhoneNum(phoneDigits);
    
    tempGuest.setReservationsCount(0);

    
    std::cout << "\n-- Room data --\n";

  
    std::cout << "Enter room number: ";
    int roomNumber;
    std::cin >> roomNumber;

    
    std::cout << "Enter base price: ";
    double basePrice;
    std::cin >> basePrice;

    std::cout << "Enter room type (Single, Double, Apartment, Deluxe, Conference): ";
    std::string roomTypeStr;
    std::cin >> roomTypeStr;

    std::cout << "Enter room status (Available, Reserved, underRenovation): ";
    std::string statusStr;
    std::cin >> statusStr;

   
    std::cout << "Enter pricing strategy (Occupancy, Seasonal, Weekend, Regular) or \"null\" for no strategy ";
    std::string stratName, stratParam;
    std::cin >> stratName;
    if (stratName != "null") {
        std::cout << "Enter parameter for strategy (for example Occupancy: Low/Medium/High; Seasonal: Spring/Summer/...; Weekend: Saturday/Sunday; Regular – null): ";
        std::cin >> stratParam;
    }
  
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    
    EnumClasses::RoomType roomTypeEnum = EnumClasses::RoomType::Single;
    if (roomTypeStr == "Single")        roomTypeEnum = EnumClasses::RoomType::Single;
    else if (roomTypeStr == "Double")   roomTypeEnum = EnumClasses::RoomType::Double;
    else if (roomTypeStr == "Apartment")roomTypeEnum = EnumClasses::RoomType::Apartment;
    else if (roomTypeStr == "Deluxe")   roomTypeEnum = EnumClasses::RoomType::Deluxe;
    else if (roomTypeStr == "Conference")roomTypeEnum = EnumClasses::RoomType::Conference;
    else {
        std::cout << "Warning: Invalid type. Single will be used by default..\n";
    }

    EnumClasses::Status statusEnum = EnumClasses::Status::Available;
    if (statusStr == "Available")        statusEnum = EnumClasses::Status::Available;
    else if (statusStr == "Reserved")    statusEnum = EnumClasses::Status::Reserved;
    else if (statusStr == "underRenovation") statusEnum = EnumClasses::Status::underRenovation;
    else {
        std::cout << "Warning: Invalid status. Will default to Available.\n";
    }

   
    PricingStrategy* tempStrat = nullptr;
    if (stratName != "null") {
        tempStrat = PricingStrategyFactory::createStrategy(
            stratName.c_str(),
            stratParam.empty() ? nullptr : stratParam.c_str());
        if (!tempStrat) {
            std::cout << "Warning: Failed to create strategy \""
                << stratName << "\". Will be used without strategy.\n";
        }
    }

    
    Room tempRoom(roomNumber, basePrice, roomTypeEnum, statusEnum, tempStrat);
    
    delete tempStrat;

  
    std::cout << "\n-- Reservation's dates --\n";

    int dayIn, monthIn, yearIn;
    std::cout << "Check in: ";
    std::cin >> dayIn >> monthIn >> yearIn;

    int dayOut, monthOut, yearOut;
    std::cout << "Check out: ";
    std::cin >> dayOut >> monthOut >> yearOut;

    
    Date checkInDate(dayIn, monthIn, yearIn);
    Date checkOutDate(dayOut, monthOut, yearOut);

    
    try {
        if (!((yearOut > yearIn) ||
            (yearOut == yearIn && monthOut > monthIn) ||
            (yearOut == yearIn && monthOut == monthIn && dayOut > dayIn))) {
            throw std::invalid_argument("not valid date");
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << " Reservation can not be created.\n";
        return;
    }

    
    Reservation newRes(tempGuest, checkInDate, checkOutDate, tempRoom);

    
    std::ofstream outFile("reservations.dat", std::ios::binary | std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open file for recording: reservations.dat\n";
    }
    else {
        newRes.saveToFile(outFile);
        outFile.close();
        std::cout << "\nThe reservation was successfully saved in reservations.dat.\n";
    }

    
    std::cout << "\nReservation #" << newRes.getReservationID()
        << " for guest \"" << tempGuest.getName()
        << "\" in room " << tempRoom.getRoomNum()
        << "from " << dayIn << "." << monthIn << "." << yearIn
        << " to " << dayOut << "." << monthOut << "." << yearOut
        << " is registrated.\n\n";
}

