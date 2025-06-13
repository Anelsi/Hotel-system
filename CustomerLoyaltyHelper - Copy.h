// File: CustomerLoyaltyHelper.h
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

    // 1) Прочитаме всички резервации от файла и ги групираме в map<guestNum, Guest>
    std::map<int, Guest> guestsMap;
    while (true) {
        Reservation tempRes;
        tempRes.loadFromFile(inFile);  // чете reservationID, isActive, numNights, totalPrice, дати, guest->loadFromFile, room->loadFromFile :contentReference[oaicite:0]{index=0}
        if (!inFile) {
            break;  // край на файла или грешка
        }

        // Взимаме указател към госта, вложен в резервацията
        Guest* resGuestPtr = tempRes.getGuest();  // връща Guest* :contentReference[oaicite:1]{index=1}
        int guestNum = resGuestPtr->getGuestNum();  // уникален номер на госта

        // Ако още нямаме такъв гост в картата, копираме го (без резервации)
        if (guestsMap.find(guestNum) == guestsMap.end()) {
            // Създаваме копие на самия гост (данни: име, email, phoneNum и пр.)
            Guest guestCopy = *resGuestPtr;
            // Задаваме му начално 0 резервации
            guestCopy.setReservationsCount(0);
            guestsMap.emplace(guestNum, std::move(guestCopy));
        }

        // Добавяме текущата резервация към списъка на този гост
        // (tempRes съдържа собствения си обект Guest, но ние клонираме tempRes)
        guestsMap[guestNum].addReservation(tempRes);  // Guest::addReservation клонира резервацията :contentReference[oaicite:2]{index=2}
    }
    inFile.close();

    if (guestsMap.empty()) {
        std::cout << "No reservations available, therefore no customer loyalty data.\n";
        return;
    }

    // 2) Преобразуваме map в vector за по-лесна обработка
    std::vector<Guest> guestList;
    guestList.reserve(guestsMap.size());
    for (auto& pair : guestsMap) {
        // Нека за всеки гост обновим статуса преди показване
        pair.second.updateGuestStatus();  // базира се на броя резервации :contentReference[oaicite:3]{index=3}
        guestList.push_back(pair.second);
    }

    // 3) Показваме Общ отчет за клиентската лоялност
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
        int stays = guest.getTotalStays();    // брой резервации (нощувки) :contentReference[oaicite:4]{index=4}
        double spent = guest.getTotalSpent();    // общо похарчени BGN :contentReference[oaicite:5]{index=5}
        const char* status = guest.getGuestStatus();   // "Regular", "Gold" или "Platinium" :contentReference[oaicite:6]{index=6}
        double discountPct = guest.getDiscount() * 100; // процентно изражение на отстъпката :contentReference[oaicite:7]{index=7}

        std::cout << std::left
            << std::setw(20) << guest.getName()
            << std::setw(10) << stays
            << std::setw(15) << (std::to_string(spent) + " BGN")
            << std::setw(12) << status
            << std::setw(10) << (std::to_string(discountPct) + "%")
            << "\n";
    }

    // 4) Намираме и показваме най-лоялния гост (по брой резервации)
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

