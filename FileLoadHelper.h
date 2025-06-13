#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Room.h"
#include "Accommodation.h"
#include "Reservation.h"


inline void loadRoomsFromFile(Accommodation& accommodation) {
    std::ifstream in("rooms.txt");
    if (!in.is_open()) {
        std::cerr << "Error: cannot open file for reading: rooms.txt\n";
        return;
    }

   
    while (true) {
       
        Room temp;
        
        temp.loadFromFile(in);
        if (!in) {
            
            break;
        }
        
        accommodation.addNewRoom(temp);
    }

    in.close();
}


inline std::vector<Reservation> loadReservationsFromFile() {
    std::vector<Reservation> result;
    std::ifstream in("reservations.dat", std::ios::binary);
    if (!in.is_open()) {
        std::cerr << "Error: cannot open file for reading: reservations.dat\n";
        return result;
    }

   
    while (true) {
        Reservation temp;
        temp.loadFromFile(in);
        if (!in) {
            
            break;
        }
        result.push_back(std::move(temp));
    }

    in.close();
    return result;
}


