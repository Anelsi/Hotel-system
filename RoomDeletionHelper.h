
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Room.h"

void displayAndDeleteRoomFromFile() {
    std::ifstream inFile("rooms.txt");
    if (!inFile.is_open()) {
        std::cerr << "Error: cannot open file for reading: rooms.txt\n";
        return;
    }

   
    std::vector<Room> rooms;
    while (true) {
        Room temp;
        temp.loadFromFile(inFile); 
        if (!inFile) {
            break; 
        }
        rooms.push_back(std::move(temp));
    }
    inFile.close();

    if (rooms.empty()) {
        std::cout << "There are currently no rooms registered in rooms.txt.\n";
        return;
    }

   
    std::cout << "=== List of available rooms ===\n";
    for (size_t i = 0; i < rooms.size(); ++i) {
        const Room& r = rooms[i];
        std::cout << i + 1 << ". Room" << r.getRoomNum()
            << " | Type: " << r.getRoomType()
            << " | Status: " << r.getStatusType()
            << " | Base price: " << r.getBasePrice() << " BGN\n";
    }

    
    std::cout << "\nEnter the room number (RoomNum) you want to delete: ";
    int delRoomNum;
    std::cin >> delRoomNum;
    if (!std::cin) {
        std::cerr << "Invalid input.\n";
        return;
    }

    
    auto it = std::find_if(rooms.begin(), rooms.end(),
        [delRoomNum](const Room& r) {
            return r.getRoomNum() == delRoomNum;
        });

    if (it == rooms.end()) {
        std::cout << "No room with number found. " << delRoomNum << ".\n";
        return;
    }

    
    rooms.erase(it);
    
    std::ofstream outFile("rooms.txt", std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: cannot open file for writing: rooms.txt\n";
        return;
    }
    for (const Room& r : rooms) {
        r.saveToFile(outFile);
    }
    outFile.close();

    std::cout << "Room" << delRoomNum << " was deleted successfully from rooms.txt.\n";
}

