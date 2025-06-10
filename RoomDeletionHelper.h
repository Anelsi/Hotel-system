// File: RoomDeletionHelper.h
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Room.h"

/// Функция, която чете всички стаи от "rooms.txt", показва ги на потребителя,
/// позволява му да избере стая (по номер) за изтриване, след което обновява "rooms.txt",
/// като презаписва само останалите стаи.
/// Ако файлът не съществува или е празен, извежда съответно съобщение.
void displayAndDeleteRoomFromFile() {
    std::ifstream inFile("rooms.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: cannot open file for reading: rooms.txt\n";
        return;
    }

    // Зареждаме всички стаи във вектор
    std::vector<Room> rooms;
    while (true) {
        Room temp;
        temp.loadFromFile(inFile); // прочита: roomNum, basePrice, typeInt, statusInt, strategyName, strategyParam 
        if (!inFile) {
            break; // стигнали сме до края (или файлът е празен)
        }
        rooms.push_back(std::move(temp));
    }
    inFile.close();

    if (rooms.empty()) {
        std::cout << "There are currently no rooms registered in rooms.txt.\n";
        return;
    }

    // Показваме всички заредени стаи
    std::cout << "=== List of available rooms ===\n";
    for (size_t i = 0; i < rooms.size(); ++i) {
        const Room& r = rooms[i];
        std::cout << i + 1 << ". Room" << r.getRoomNum()
            << " | Type: " << r.getRoomType()
            << " | Status: " << r.getStatusType()
            << " | Base price: " << r.getBasePrice() << " BGN\n";
    }

    // Подканваме потребителя да въведе номер на стаята, която иска да изтрие
    std::cout << "\nEnter the room number (RoomNum) you want to delete: ";
    int delRoomNum;
    std::cin >> delRoomNum;
    if (!std::cin) {
        std::cerr << "Invalid input.\n";
        return;
    }

    // Намираме индекса на тази стая във вектора (по точното поле roomNum)
    auto it = std::find_if(rooms.begin(), rooms.end(),
        [delRoomNum](const Room& r) {
            return r.getRoomNum() == delRoomNum;
        });

    if (it == rooms.end()) {
        std::cout << "No room with number found. " << delRoomNum << ".\n";
        return;
    }

    // Премахваме избраната стая от вектора
    rooms.erase(it);

    // Презаписваме файла "rooms.txt" само с останалите стаи
    std::ofstream outFile("rooms.txt", std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: cannot open file for writing: rooms.txt\n";
        return;
    }
    for (const Room& r : rooms) {
        r.saveToFile(outFile); // записва: roomNum basePrice typeInt statusInt strategyName strategyParam + '\n' :contentReference[oaicite:0]{index=0}
    }
    outFile.close();

    std::cout << "Room" << delRoomNum << " was deleted successfully from rooms.txt.\n";
}

