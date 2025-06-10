// File: FileLoadHelper.h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Room.h"
#include "Accommodation.h"
#include "Reservation.h"

/// Зарежда всички стаи от текстовия файл "rooms.txt" и ги добавя в дадения обект Accommodation.
/// Използва Room::loadFromFile(std::istream&).
inline void loadRoomsFromFile(Accommodation& accommodation) {
    std::ifstream in("rooms.txt");
    if (!in.is_open()) {
        std::cerr << "Error: cannot open file for reading: rooms.txt\n";
        return;
    }

    // Четем докато има данни
    while (true) {
        // Опитваме да извикаме loadFromFile:
        Room temp;
        // loadFromFile ще прочете: roomNum, basePrice, typeInt, statusInt, strategyName, strategyParam
        temp.loadFromFile(in);
        if (!in) {
            // Ако е станала грешка (или сме стигнали EOF), прекъсваме.
            break;
        }
        // Добавяме стаята в Accommodation (тоя метод клонира вътрешно Room-а)
        accommodation.addNewRoom(temp);
    }

    in.close();
}

/// Зарежда всички резервации от двоичния файл "reservations.dat", като използва Reservation::loadFromFile(std::ifstream&),
/// и връща std::vector<Reservation> с прочетените обекти.
/// Ако възникне проблем при отваряне на файла, връща празен вектор.
inline std::vector<Reservation> loadReservationsFromFile() {
    std::vector<Reservation> result;
    std::ifstream in("reservations.dat", std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Error: cannot open file for reading: reservations.dat\n";
        return result;
    }

    // Всяко loadFromFile чете:
    //   reservationID, isActive, numNights, totalPrice,
    //   checkInDate, checkOutDate,
    //   след това guest->loadFromFile(in), room->loadFromFile(in)
    while (true) {
        Reservation temp;
        temp.loadFromFile(in);
        if (!in) {
            // Ако сме стигнали до края или възникне грешка, прекъсваме
            break;
        }
        result.push_back(std::move(temp));
    }

    in.close();
    return result;
}


