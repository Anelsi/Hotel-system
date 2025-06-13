
#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>

#include "Guest.h"
#include "Reservation.h"


inline void displayCustomerLoyalty() {
    std::ifstream inFile("reservations.dat", std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error: cannot open file for reading: reservations.dat\n";
        return;
    }

    std::map<int, Guest> guestsMap;
    while (true) {
        Reservation tempRes;
        tempRes.loadFromFile(inFile); 
        if (!inFile) {
            break;  
        }

        Guest* resGuestPtr = tempRes.getGuest();  
        int guestNum = resGuestPtr->getGuestNum(); 

        if (guestsMap.find(guestNum) == guestsMap.end()) {
            
            Guest guestCopy = *resGuestPtr;
            
            guestCopy.setReservationsCount(0);
            guestsMap.emplace(guestNum, std::move(guestCopy));
        }

     
        guestsMap[guestNum].addReservation(tempRes); 
    }
    inFile.close();

    if (guestsMap.empty()) {
        std::cout << "No reservations available, therefore no customer loyalty data.\n";
        return;
    }

    
    std::vector<Guest> guestList;
    guestList.reserve(guestsMap.size());
    for (auto& pair : guestsMap) {
     
        pair.second.updateGuestStatus();  
        guestList.push_back(pair.second);
    }

    
    std::cout << "\n=== Customer Loyalty Report ===\n\n";
    std::cout << std::left
        << std::setw(20) << "Guest Name"
        << std::setw(10) << "Stays"
        << std::setw(15) << "Total Spent"
        << std::setw(12) << "Status"
        << std::setw(10) << "Discount"
        << "\n";
    std::cout << std::string(67, '-') << "\n";

    for (const auto& guest : guestList) {
        int stays = guest.getTotalStays();    
        double spent = guest.getTotalSpent();  
        const char* status = guest.getGuestStatus();  
        double discountPct = guest.getDiscount() * 100; 

        std::cout << std::left
            << std::setw(20) << guest.getName()
            << std::setw(10) << stays
            << std::setw(15) << (std::to_string(spent) + " BGN")
            << std::setw(12) << status
            << std::setw(10) << (std::to_string(discountPct) + "%")
            << "\n";
    }

    
    int maxStays = -1;
    size_t idxMostLoyal = 0;
    for (size_t i = 0; i < guestList.size(); ++i) {
        if (guestList[i].getTotalStays() > maxStays) {
            maxStays = guestList[i].getTotalStays();
            idxMostLoyal = i;
        }
    }
    const Guest& mostLoyal = guestList[idxMostLoyal];

    std::cout << "\nMost Loyal Guest:\n";
    std::cout << "Name: " << mostLoyal.getName() << "\n";
    std::cout << "Stays: " << mostLoyal.getTotalStays() << "\n";
    std::cout << "Total Spent: " << mostLoyal.getTotalSpent() << " BGN\n";
    std::cout << "Status: " << mostLoyal.getGuestStatus() << "\n";
    std::cout << "Discount: " << (mostLoyal.getDiscount() * 100) << "%\n\n";
}

