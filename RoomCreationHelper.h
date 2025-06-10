// File: RoomCreationHelper.h
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "Room.h"
#include "Accommodation.h"
#include "PricingStrategyFactory.h"  // интеграция с фабриката за стратегии

/// Функция, която чете от стандартен вход параметрите на нова стая,
/// създава обект Room, асоциира му зададена ценова стратегия,
/// записва го във файл и го добавя към обекта Accommodation.
void createAndAddRoom(Accommodation& accommodation) {
    std::cout << "=== Create new room ===\n";

    // 1) Въвеждаме номер на стаята
    int roomNumber;
    std::cout << "Enter room number: ";
    std::cin >> roomNumber;

    // 2) Въвеждаме базова цена
    double basePrice;
    std::cout << "Enter base price: ";
    std::cin >> basePrice;

    // 3) Въвеждаме тип стая (като текст)
    std::string roomTypeStr;
    std::cout << "Enter room type (Single, Double, Apartment, Deluxe, Conference) : ";
    std::cin >> roomTypeStr;

    // 4) Въвеждаме статус (като текст)
    std::string statusStr;
    std::cout << "Enter room status (Available, Reserved, underRenovation): ";
    std::cin >> statusStr;

    // 5) Въвеждаме име и параметър за PricingStrategy
    std::string strategyName, strategyParam;
    std::cout << "Enter pricing strategy (Occupancy, Seasonal, Weekend, Regular) или \"null\" за без стратегия: ";
    std::cin >> strategyName;
    if (strategyName != "null") {
        std::cout << "Enter parameter for pricing strategy (for example \"Low\"/\"Medium\"/\"High\" за Occupancy, "
            "\"Spring\"/\"Summer\"/... за Seasonal, \"Saturday\"/\"Sunday\" за Weekend; null for Regular): ";
        std::cin >> strategyParam;
    }

    // Изчистване на входния буфер
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // --- Преобразуване на низове към enum-стойности ---

    // Тип стая
    EnumClasses::RoomType roomTypeEnum = EnumClasses::RoomType::Single;  // по подразбиране
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

    // Статус
    EnumClasses::Status statusEnum = EnumClasses::Status::Available;  // по подразбиране
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

    // --- Създаване на PricingStrategy през фабриката ---
    PricingStrategy* stratPtr = nullptr;
    if (strategyName != "null") {
        // Ако фабриката върне nullptr, предупреждаваме и продължаваме без стратегия
        stratPtr = PricingStrategyFactory::createStrategy(strategyName.c_str(),
            strategyParam.empty() ? nullptr : strategyParam.c_str());
        if (!stratPtr) {
            std::cout << "Warning: Failed to create strategy \""
                << strategyName << "\" with parameter \"" << strategyParam
                << "\". Will be used without strategy.\n";
        }
    }

    // --- Създаваме обект Room с подадените стойности ---
    Room newRoom(roomNumber, basePrice, roomTypeEnum, statusEnum, stratPtr);

    // Забележка: конструкторът на Room клонира подадената PricingStrategy* 
    //       (виж Room::copyFrom и Room::setStrategy) :contentReference[oaicite:0]{index=0}

    // --- Записване на новата стая във файл ---
    // Файлът "rooms.txt" се отваря в режим append, за да не презаписваме вече съществуващи стаи
    std::ofstream outFile("rooms.txt", std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open file for recording: rooms.txt\n";
    }
    else {
        newRoom.saveToFile(outFile);
        // saveToFile записва: roomNum, basePrice, roomType (int), status (int),
        //                    име на стратегия и параметъра ѝ или "null null" :contentReference[oaicite:1]{index=1}
        outFile.close();
        std::cout << "Room data was saved to the file rooms.txt successfully.\n";
    }

    // --- Добавяме новата стая към системата Accommodation ---
    accommodation.addNewRoom(newRoom);
    std::cout << "The room was successfully added to the accommodation system.\n";

    // --- Освобождаме временната стратегия, подадена на конструктора (Room е клонирал указателя) ---
    delete stratPtr;
}
