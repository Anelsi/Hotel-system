#include "Accountant.h"
#include <iostream>
#include "RevenueInfo.h"

//Accountant::Accountant():Employee("accountant","accountant123",Role::Accountant) {
//
//
//};

Accountant::Accountant(const char* username, const char* password, const Role& role) :Employee(username, password, Role::Accountant) {
};

Accountant::Accountant(const char* name) : Employee(name) {};


void Accountant::showPermissions()const {
    //изчисляване и пеглед на приходи

    std::cout << "1. Review and analysis of revenues\n";


};



void Accountant::visitRevenueInfo(const RevenueInfo* info) {

    std::cout << "\n Revenue Review and Analysis Report\n";
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
    std::cout << "Revenue for " << sampleDate.toString() << ": " << revenueForDay << " лв.\n";


    int monthh, yearr;
    std::cout << "Enter month: ";
    std::cin >> monthh;
    std::cout << "Enter year: ";
    std::cin >> yearr;


    double revenueForMonth = info->getTotalRevenuePerMonth(month, year);
    std::cout << "Revenue for month " << month << "/" << year << ": " << revenueForMonth << " лв.\n";


    int yearT;
    std::cout << "Enter year" << std::endl;
    std::cin >> yearT;
    double revenueForYear = info->getTotalRevenuePerYear(yearT);
    std::cout << "Revenue for year  " << yearT << ": " << revenueForYear << " лв.\n";


    RoomRevenueInfo buffer[100];
    int roomCount = info->getRevenueByRoomType(buffer, 100);
    std::cout << "\n Revenue by rooms:\n";
    for (int i = 0; i < roomCount; ++i) {
        std::cout << "Room: " << buffer[i].roomNumber
            << ", Revenue: " << buffer[i].totalRevenue
            << ", Reservations: " << buffer[i].reservationCount
            << ", Nights: " << buffer[i].occupiedNights << "\n";
    }


    RoomRevenueInfo topRoom = info->getMostProfitableRoom();
    std::cout << "\n Most profitable room: " << topRoom.roomNumber
        << "with total Revenue of: " << topRoom.totalRevenue << " leva.\n";


    try {
        info->saveReportToFile("Revenue_Report.txt");
        std::cout << "Revenue Report Successfully Saved in Revenue_Report.txt\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error writing to file: " << ex.what() << "\n";
    }
}

Employee* Accountant::clone() const {
    return new Accountant(*this);


};
