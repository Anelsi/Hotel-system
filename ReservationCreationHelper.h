// File: ReservationCreationHelper.h
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Guest.h"
#include "Room.h"
#include "Reservation.h"
#include "EnumClasses.h"
#include "PricingStrategyFactory.h"  // ако искате да прилагате стратегия при създаването на стая
#include "Date.h"                    // за обектите Date

/// Функция, която чете от стандартен вход данните за нова резервация,
/// създава обекти Guest и Room, конструира Reservation и я записва във файл.
void createAndSaveReservation() {
    std::cout << "=== Create new reservation ===\n";

    // --- Част 1: Въвеждаме информация за госта ---
    std::cout << "\n-- Guest data --\n";

    // 1.1) Въвеждаме пълно име (свободен ред)
    std::cout << "Enter guest's name: ";
    std::string guestName;
    std::getline(std::cin, guestName);

    // 1.2) Въвеждаме имейл
    std::cout << "Enter guest's email: ";
    std::string guestEmail;
    std::getline(std::cin, guestEmail);

    // 1.3) Въвеждаме уникален номер (ID) на госта (цяло число)
    std::cout << "Enter unique guest's id: ";
    int guestID;
    std::cin >> guestID;

    // 1.4) Въвеждаме телефонен номер – точно EnumClasses::MAX_NUMBERS цифри
    std::cout << "Enter guest's phone number (" << EnumClasses::MAX_NUMBERS
        << " for example: 0887123456): ";
    std::string phoneInput;
    std::cin >> phoneInput;

    // Почиства входния буфер
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Конвертираме телефонния низ в масив от int
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
    // Ако е по-кратък, останалите цифри остават 0

    // Създаваме обект Guest и задаваме полетата
    Guest tempGuest;
    tempGuest.setName(guestName.c_str());
    tempGuest.setEmail(guestEmail.c_str());
    tempGuest.setGuestNum(guestID);
    tempGuest.setPhoneNum(phoneDigits);
    // Започваме с 0 резервации → статусът ще е Regular по подразбиране
    tempGuest.setReservationsCount(0);

    // --- Част 2: Въвеждаме информация за стаята ---
    std::cout << "\n-- Room data --\n";

    // 2.1) Въвеждаме номер на стаята
    std::cout << "Enter room number: ";
    int roomNumber;
    std::cin >> roomNumber;

    // 2.2) Въвеждаме базова цена
    std::cout << "Enter base price: ";
    double basePrice;
    std::cin >> basePrice;

    // 2.3) Въвеждаме тип на стаята (Single, Double, Apartment, Deluxe, Conference)
    std::cout << "Enter room type (Single, Double, Apartment, Deluxe, Conference): ";
    std::string roomTypeStr;
    std::cin >> roomTypeStr;

    // 2.4) Въвеждаме статус (Available, Reserved, underRenovation)
    std::cout << "Enter room status (Available, Reserved, underRenovation): ";
    std::string statusStr;
    std::cin >> statusStr;

    // 2.5) (по желание) Въвеждаме ценова стратегия
    std::cout << "Enter pricing strategy (Occupancy, Seasonal, Weekend, Regular) или \"null\" за без стратегия: ";
    std::string stratName, stratParam;
    std::cin >> stratName;
    if (stratName != "null") {
        std::cout << "Enter parameter for strategy (напр. за Occupancy: Low/Medium/High; Seasonal: Spring/Summer/...; Weekend: Saturday/Sunday; Regular – null): ";
        std::cin >> stratParam;
    }
    // Изчистване на буфера
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Конвертираме с низ към enum
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

    // Създаваме ценовата стратегия чрез фабриката (ако е подадена)
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

    // Конструираме обект Room с подадените параметри
    Room tempRoom(roomNumber, basePrice, roomTypeEnum, statusEnum, tempStrat);
    // Room-конструкторът клонира стратегията, така че можем спокойно да изтрием tempStrat след това
    delete tempStrat;

    // --- Част 3: Въвеждаме дати за настаняване и напускане ---
    std::cout << "\n-- Reservation's dates --\n";

    int dayIn, monthIn, yearIn;
    std::cout << "Check in: ";
    std::cin >> dayIn >> monthIn >> yearIn;

    int dayOut, monthOut, yearOut;
    std::cout << "Check out: ";
    std::cin >> dayOut >> monthOut >> yearOut;

    // Създаваме обекти Date; приемаме, че Date има конструктор Date(int, int, int)
    Date checkInDate(dayIn, monthIn, yearIn);
    Date checkOutDate(dayOut, monthOut, yearOut);

    // Проверка: checkOut трябва да е след checkIn според логиката в Reservation::setCheckOutDate(...)
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

    // --- Част 4: Създаваме обект Reservation ---
    // Конструкторът на Reservation клонира подадения Guest и Room вътре
    Reservation newRes(tempGuest, checkInDate, checkOutDate, tempRoom);

    // По подразбиране newRes.isActive = true и изчислява numNights + totalPrice вътре в конструктора :contentReference[oaicite:0]{index=0}

    // --- Част 5: Записваме резервацията във файл ---
    // Използваме двоичен файл "reservations.dat", append режим
    std::ofstream outFile("reservations.dat", std::ios::binary | std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open file for recording: reservations.dat\n";
    }
    else {
        newRes.saveToFile(outFile);
        outFile.close();
        std::cout << "\nThe reservation was successfully saved in reservations.dat.\n";
    }

    // --- Финално съобщение ---
    std::cout << "\nReservation #" << newRes.getReservationID()
        << " for guest \"" << tempGuest.getName()
        << "\" in room " << tempRoom.getRoomNum()
        << "from " << dayIn << "." << monthIn << "." << yearIn
        << " to " << dayOut << "." << monthOut << "." << yearOut
        << " is registrated.\n\n";
}

