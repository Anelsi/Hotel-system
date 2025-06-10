#include "Manager.h"
#include <iostream>


#include "ReservationsManagement.h"
#include "RevenueInfo.h"

Manager::Manager(const char* name) : Employee(name) {};

Manager::Manager(const char* username, const char* password, const Role& role)
    : Employee(username, password, Role::Manager)
{
}


void Manager::showPermissions() const {
    std::cout << "Manager can access information about Rooms, Guests, RevenueInfo, ReservationsManagement, Accommodation" << std::endl;
};



void Manager::visitRevenueInfo(const RevenueInfo* info) {

    std::cout << "\n Generated text report:\n";
    info->generateSummaryReport(std::cout);


    int day, month, year;

    std::cout << "\nEnter day: ";
    std::cin >> day;
    std::cout << "Enter month: ";
    std::cin >> month;
    std::cout << "Enter year: ";
    std::cin >> year;


    Date sampleDate(day, month, year);
    double revenueForDay = info->getTotalRevenuePerDay(sampleDate);
    std::cout << "Revenue for" << sampleDate.toString() << ": " << revenueForDay << " leva.\n";


    int monthh, yearr;
    std::cout << "Enter month: ";
    std::cin >> monthh;
    std::cout << "Enter year: ";
    std::cin >> yearr;


    double revenueForMonth = info->getTotalRevenuePerMonth(month, year);
    std::cout << "Revenue for month " << month << "/" << year << ": " << revenueForMonth << " leva.\n";


    int yearT;
    std::cout << "Enter year: ";
    std::cin >> yearT;

    double revenueForYear = info->getTotalRevenuePerYear(yearT);
    std::cout << "Revenue for year " << yearT << ": " << revenueForYear << " leva.\n";


    RoomRevenueInfo buffer[100];
    int roomCount = info->getRevenueByRoomType(buffer, 100);
    std::cout << "\n Revenue by rooms\n";
    for (int i = 0; i < roomCount; ++i) {
        std::cout << "Room: " << buffer[i].roomNumber
            << ", Revenue: " << buffer[i].totalRevenue
            << ", Reservations: " << buffer[i].reservationCount
            << ", Nights: " << buffer[i].occupiedNights << "\n";
    }


    RoomRevenueInfo topRoom = info->getMostProfitableRoom();
    std::cout << "\n Most profitable room: " << topRoom.roomNumber
        << " with revenue of: " << topRoom.totalRevenue << " leva.\n";


    try {
        info->saveReportToFile("Revenue_Report.txt");
        std::cout << "The report is saved in Revenue_Report.txt\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error writing to file: " << ex.what() << "\n";
    }
}




void Manager::visitGuest(const Guest* g) {
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



void Manager::visitReservation(const Reservation* res) {
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



void Manager::visitReservationsManagement(const ReservationsManagement* rm) {
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



void Manager::visitAccommodation(const Accommodation* acc) {

    std::cout << "As Manager you can access Accommodation's functionalities" << std::endl;
};

void Manager::visitRoom(const Room* room) {
    if (!room) {

        throw std::runtime_error("Invalid room pointer");


    }

    std::cout << "Room #" << room->getRoomNum() << "\n";
    std::cout << "Type: " << room->getRoomType() << "\n";
    std::cout << "Status: " << room->getStatusType() << "\n";
    std::cout << "Base Price: " << room->getBasePrice() << " BGN\n";
    std::cout << "Price with Strategy: " << room->getCalculatedPrice() << " BGN\n";
}

Employee* Manager::clone() const {
    return new Manager(*this);

};
