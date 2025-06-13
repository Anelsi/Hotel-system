#pragma once
#include "Manager.h"
#include <iostream>
#include <fstream>
#include "ReservationsManagement.h"

#include "Accountant.h"

class AccountantAccess;
class ManagerAccess;

struct RoomRevenueInfo {
    int roomNumber;
    double totalRevenue;
    int reservationCount;
    int occupiedNights;
};

class Date;

class RevenueInfo
{
    const ReservationsManagement& reservationsManagement;

    friend class Manager;

    friend class Accountant;

public:
    RevenueInfo(const ReservationsManagement& rm);

    double getTotalRevenuePerDay(const Date& date) const;
    double getTotalRevenuePerMonth(int month, int year) const;
    double getTotalRevenuePerYear(int year) const;

    int getRevenueByRoomType(RoomRevenueInfo* result, int maxSize) const;
    RoomRevenueInfo getMostProfitableRoom() const;

    void generateSummaryReport(std::ostream& os) const;
    void saveReportToFile(const char* fileName) const;


    void loadReportFromFile(const char* fileName);

    void accept(AccountantAccess* visitor) const;
    void accept(ManagerAccess* visitor) const;
};


