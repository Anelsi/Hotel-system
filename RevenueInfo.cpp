#include "RevenueInfo.h"

#include <fstream>

#include <string>

RevenueInfo::RevenueInfo(const ReservationsManagement& rm)
    : reservationsManagement(rm) {}

double RevenueInfo::getTotalRevenuePerDay(const Date& date) const {
    double total = 0.0;
    for (int i = 0; i < reservationsManagement.getResCounter(); ++i) {
        const Reservation* res = reservationsManagement.getReservationAt(i);
        if (!res || !res->getIsActive()) continue;

        Date in = res->getCheckInDate();
        Date out = res->getCheckOutDate();

        if (!(date < in) && (date < out)) {

            int totalNights = res->getNumNights();
            if (totalNights <= 0) {
                throw std::runtime_error("Invalid reservation: zero or negative nights");
            }
            total += res->getTotalPrice() / totalNights;
        }
    }
    return total;

}

double RevenueInfo::getTotalRevenuePerMonth(int month, int year) const {
    double total = 0.0;
    for (int i = 0; i < reservationsManagement.getResCounter(); ++i) {
        const Reservation* res = reservationsManagement.getReservationAt(i);
        if (!res || !res->getIsActive()) continue;

        Date in = res->getCheckInDate();
        Date out = res->getCheckOutDate();

        for (Date d = in; d < out; ++d) {
            if (d.getMonth() == month && d.getYear() == year) {
                total += res->getTotalPrice() / res->getNumNights();
            }
        }
    }
    return total;
}

double RevenueInfo::getTotalRevenuePerYear(int year) const {
    double total = 0.0;
    for (int i = 0; i < reservationsManagement.getResCounter(); ++i) {
        const Reservation* res = reservationsManagement.getReservationAt(i);
        if (!res || !res->getIsActive()) continue;

        Date in = res->getCheckInDate();
        Date out = res->getCheckOutDate();

        for (Date d = in; d < out; ++d) {
            if (d.getYear() == year) {
                total += res->getTotalPrice() / res->getNumNights();
            }
        }
    }
    return total;
}

int RevenueInfo::getRevenueByRoomType(RoomRevenueInfo* result, int maxSize) const {
    int count = 0;

    for (int i = 0; i < reservationsManagement.getResCounter(); ++i) {
        const Reservation* res = reservationsManagement.getReservationAt(i);
        if (!res || !res->getIsActive()) continue;

        Room* room = res->getRoom();
        if (!room) continue;

        int roomNum = room->getRoomNum();
        bool found = false;

        for (int j = 0; j < count; ++j) {
            if (result[j].roomNumber == roomNum) {
                result[j].totalRevenue += res->getTotalPrice();
                result[j].reservationCount++;
                result[j].occupiedNights += res->getNumNights();
                found = true;
                break;
            }
        }

        if (!found && count < maxSize) {
            result[count].roomNumber = roomNum;
            result[count].totalRevenue = res->getTotalPrice();
            result[count].reservationCount = 1;
            result[count].occupiedNights = res->getNumNights();
            count++;
        }
    }

    return count;
}

RoomRevenueInfo RevenueInfo::getMostProfitableRoom() const {
    RoomRevenueInfo best = { 0, 0.0, 0, 0 };
    RoomRevenueInfo buffer[100];
    int count = getRevenueByRoomType(buffer, 100);

    for (int i = 0; i < count; ++i) {
        if (buffer[i].totalRevenue > best.totalRevenue)
            best = buffer[i];
    }

    return best;
}

void RevenueInfo::generateSummaryReport(std::ostream& os) const {
    os << "Room revenue report:\n\n";

    RoomRevenueInfo rooms[100];
    int count = getRevenueByRoomType(rooms, 1000);

    for (int i = 0; i < count; ++i) {
        os << "Room: " << rooms[i].roomNumber
            << " | Revenue: " << rooms[i].totalRevenue
            << " | Reservations: " << rooms[i].reservationCount
            << " | Nights: " << rooms[i].occupiedNights << "\n";
    }

    RoomRevenueInfo top = getMostProfitableRoom();
    os << "\nMost profitable room: " << top.roomNumber
        << " with revenue of: " << top.totalRevenue << "\n";
}

void RevenueInfo::saveReportToFile(const char* fileName) const {
    
        
        std::ofstream ofs(fileName, std::ios::binary);
        if (!ofs) {
            throw std::runtime_error("Failed to open the save file.");
        }

        
        const unsigned char bom[] = { 0xEF, 0xBB, 0xBF };
        ofs.write(reinterpret_cast<const char*>(bom), sizeof(bom));

        
        generateSummaryReport(ofs);

        ofs.close();
   
}

void RevenueInfo::accept(AccountantAccess* visitor)const {

    visitor->visitRevenueInfo(this);
};

void RevenueInfo::accept(ManagerAccess* visitor) const {

    visitor->visitRevenueInfo(this);

}

void RevenueInfo::loadReportFromFile(const char* fileName) {
    std::ifstream ifs(fileName);
    if (!ifs) {
        throw std::runtime_error("Failed to open file for reading.");
    }

    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << '\n';
    }

    ifs.close();
}
