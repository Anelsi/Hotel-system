// File: GuestCreationHelper.h
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Guest.h"
#include "EnumClasses.h"

/// Функция, която чете от стандартен вход данните за нов гост,
/// създава обект Guest, записва го във файл и уведомява потребителя.
void createAndSaveGuest() {
    std::cout << "=== Create new guest ===\n";

    // 1) Въвеждаме пълно име (свободен ред, може да има интервали)
    std::cout << "Enter full guest's name: ";
    std::string nameStr;
    std::getline(std::cin, nameStr);

    // 2) Въвеждаме имейл
    std::cout << "Enter guest's email: ";
    std::string emailStr;
    std::getline(std::cin, emailStr);

    // 3) Въвеждаме уникален номер на госта (цяло число)
    int guestNumber;
    std::cout << "Enter unique guest's id: ";
    std::cin >> guestNumber;

    // 4) Въвеждаме телефонен номер – точно EnumClasses::MAX_NUMBERS цифри, без интервали
    std::cout << "Enter phone number "
        << EnumClasses::MAX_NUMBERS
        << " for example 0887123456): ";
    std::string phoneInput;
    std::cin >> phoneInput;

    // Изчистваме входния буфер
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Проверка и конвертиране на телефонния низ в масив от int
    int phoneDigits[EnumClasses::MAX_NUMBERS] = { 0 };
    if (phoneInput.length() < static_cast<size_t>(EnumClasses::MAX_NUMBERS)) {
        std::cout << "Warning: The number entered is less than "
            << EnumClasses::MAX_NUMBERS << " digits. Will be padded with leading zeros.\n";
    }
    // Взимаме последните MAX_NUMBERS символа (ако е по-дълъг), или целия низ, ако е точно дължината
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
    // Ако телефонният низ е по-къс от MAX_NUMBERS, останалите цифри ще бъдат 0 (установено по-горе).

    // --- Създаване на обект Guest и задаване на стойности ---
    Guest newGuest;  // конструкторът задава: name=nullptr, email=nullptr, reservations=nullptr, guestNum=0, reservationsCount=0, guestStatus=Regular :contentReference[oaicite:1]{index=1}

    // Задаваме име и имейл (сетърите алокират динамично памет) :contentReference[oaicite:2]{index=2}
    newGuest.setName(nameStr.c_str());
    newGuest.setEmail(emailStr.c_str());

    // Задаваме гост-номер
    newGuest.setGuestNum(guestNumber);

    // Задаваме телефонния масив
    newGuest.setPhoneNum(phoneDigits);

    // Тъй като е нов гост, няма резервации → задаваме reservationsCount = 0, статусът остава Regular
    newGuest.setReservationsCount(0);

    // --- Записваме новия гост във файл ---
    // Използваме двоичен файл "guests.dat", append режим
    std::ofstream outFile("guests.dat", std::ios::binary | std::ios::app);
    if (!outFile.is_open()) {
        std::cerr << "Error: Cannot open file for recording: guests.dat\n";
    }
    else {
        newGuest.saveToFile(outFile);
        outFile.close();
        std::cout << "Guest details were successfully saved to file. guests.dat.\n";
    }

    // Забележка: Ако на по-късен етап искате да зареждате всички гости от файла,
    // можете да ползвате Guest::loadFromFile(in) във функция, която обхожда целия файл.

    std::cout << "The guest \"" << nameStr << "\" (ID: " << guestNumber << ") is created.\n";
}

