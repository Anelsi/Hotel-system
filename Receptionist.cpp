#include "Receptionist.h"
#include <iostream>

#include "ReservationsManagement.h"



Receptionist::Receptionist(const char* username, const char* password, const Role& role) : Employee(username, password, Role::Receptionist) {
};

Receptionist::Receptionist(const char* name) {};

void Receptionist::showPermissions() const {
    std::cout << "Receptionist can access information about Rooms, Reservations, Guests, ReservationsManagement" << std::endl;
};




void Receptionist::visitGuest(const Guest* g) {
    std::cout << "Guest information:\n";
    std::cout << "Name: " << g->getName() << "\n";
    std::cout << "Email: " << g->getEmail() << "\n";
    std::cout << "Guest Number: " << g->getGuestNum() << "\n";

    std::cout << "Phone Number: ";
    const int* phone = g->getPhoneNum();
    for (int i = 0; i < EnumClasses::MAX_NUMBERS; ++i) {
        std::cout << phone[i];
    }
    std::cout << "\n";

    std::cout << "Reservations Count: " << g->getReservationsCount() << "\n";
    std::cout << "Guest Status: " << g->getGuestStatus() << "\n";
}
void Receptionist::visitReservation(const Reservation* res) {
    std::cout << "Reservation Details:\n";
    std::cout << "Reservation ID: " << res->getReservationID() << "\n";

    std::cout << "Check-In Date: ";
    std::cout << res->getCheckInDate().toString();
    std::cout << "\n";

    std::cout << "Check-Out Date: ";
    std::cout << res->getCheckOutDate().toString();
    std::cout << "\n";

    std::cout << "Number of Nights: " << res->getNumNights() << "\n";
    std::cout << "Total Price: " << res->getTotalPrice() << " BGN\n";

    std::cout << "Active Status: " << (res->getIsActive() ? "Active" : "Inactive") << "\n";

    if (res->getGuest()) {
        std::cout << "Guest Name: " << res->getGuest()->getName() << "\n";
    }


}

void Receptionist::visitReservationsManagement(const ReservationsManagement* rm) {
    std::cout << "Reservations Overview:\n";
    int total = rm->getResCounter();
    std::cout << "Total Reservations: " << total << "\n";

    for (int i = 0; i < total; ++i) {
        Reservation* res = rm->getReservationAt(i);
        if (res != nullptr && res->getIsActive()) {
            std::cout << "Reservation #" << (i + 1) << ":\n";
            res->print();
            std::cout << "\n";
        }
    }
}

void Receptionist::visitRoom(const Room* room) {
    std::cout << "Room #" << room->getRoomNum() << "\n";
    std::cout << "Type: " << room->getRoomType() << "\n";
    std::cout << "Status: " << room->getStatusType() << "\n";
    std::cout << "Base Price: " << room->getBasePrice() << " BGN\n";
    std::cout << "Price with Strategy: " << room->getCalculatedPrice() << " BGN\n";
}

Employee* Receptionist::clone() const {
    return new Receptionist(*this);

};
