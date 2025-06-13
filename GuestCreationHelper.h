
#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Guest.h"
#include "EnumClasses.h"
#include <filesystem>


constexpr char filename[] = "guests.dat";


void createAndSaveGuest() {
    std::cout << "=== Create new guest ===\n";

    
    std::cout << "Enter full guest's name: ";
    std::string nameStr;
    std::getline(std::cin, nameStr);

   
    std::cout << "Enter guest's email: ";
    std::string emailStr;
    std::getline(std::cin, emailStr);

   
    int guestNumber;
    std::cout << "Enter unique guest's id: ";
    std::cin >> guestNumber;

   
    std::cout << "Enter phone number "
        << EnumClasses::MAX_NUMBERS
        << " for example 0887123456): ";
    std::string phoneInput;
    std::cin >> phoneInput;

    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    
    int phoneDigits[EnumClasses::MAX_NUMBERS] = { 0 };
    if (phoneInput.length() < static_cast<size_t>(EnumClasses::MAX_NUMBERS)) {
        std::cout << "Warning: The number entered is less than "
            << EnumClasses::MAX_NUMBERS << " digits. Will be padded with leading zeros.\n";
    }
    
    size_t offset = (phoneInput.length() > static_cast<size_t>(EnumClasses::MAX_NUMBERS))
        ? phoneInput.length() - EnumClasses::MAX_NUMBERS
        : 0;
    size_t idx = 0;
    for (size_t i = offset; i < phoneInput.length() && idx < EnumClasses::MAX_NUMBERS; ++i, ++idx) {
        char c = phoneInput[i];
        if (!std::isdigit(c)) {
            std::cout << "Not valid symbol '" << c
                << "' at possition " << i
                << ". 0 is set instead of this number.\n";
            phoneDigits[idx] = 0;
        }
        else {
            phoneDigits[idx] = c - '0';
        }
    }

    Guest newGuest; 

    
    newGuest.setName(nameStr.c_str());
    newGuest.setEmail(emailStr.c_str());

   
    newGuest.setGuestNum(guestNumber);

  
    newGuest.setPhoneNum(phoneDigits);

    
    newGuest.setReservationsCount(0);

   
   
    std::ofstream outFile(filename, std::ios::binary | std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open file for recording: guests.dat\n";
    }
    else {
        newGuest.saveToFile(outFile);
        outFile.close();
        std::cout << "Guest details were successfully saved to file. guests.dat.\n";
    }

    

    std::cout << "The guest \"" << nameStr << "\" (ID: " << guestNumber << ") is created.\n";
}

