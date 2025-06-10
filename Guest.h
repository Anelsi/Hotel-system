#pragma once
#include "EnumClasses.h"
#include <cstring>
#include <iostream>
#include <fstream> 
#include "Receptionist.h"
#include "Manager.h"


class ManagerAccess;

class ReceptionistAccess;

class Reservation;


class Guest
{
    char* name;
    char* email;
    int guestNum;
    int phoneNum[EnumClasses::MAX_NUMBERS];

    int reservationsCount;

    Reservation* reservations;

    void free();
    void copyFrom(const Guest& other);
    void moveFrom(Guest&& other);
    EnumClasses::GuestStatus guestStatus;


    

    friend class Manager;
    friend class Receptionist;

public:

    void updateGuestStatus();

    void setName(const char* name);
    const char* getName() const;


    void setEmail(const char* email);
    const char* getEmail() const;

    void setGuestNum(int num);
    int getGuestNum() const;



    void setPhoneNum(const int* digits);
    const int* getPhoneNum() const;

    void setReservationsCount(int resCount);
    int getReservationsCount()const;

    Reservation* getReservations() const;

    void setReservations(Reservation* newReservations, int count);


    Guest();

    Guest(const char* name, const char* email, int guestNum, const int* phoneDigits, const char* status, int resCount);

    Guest(const Guest& other);
    Guest& operator=(const Guest& other);


    Guest(Guest&& other) noexcept;
    Guest& operator=(Guest&& other) noexcept;



    void printReservationHistory() const;

    double getDiscount() const;

    void addReservation(const Reservation& res);


    void saveToFile(std::ofstream& out) const;
    void loadFromFile(std::ifstream& in);

    int getTotalStays() const;
    double getTotalSpent() const;

    void analyzeGuests(Guest* guests, int guestCount);
    Guest findMostLoyalGuest(Guest* guests, int guestCount);

    ~Guest();
    const char* getGuestStatus() const;

    void accept(ReceptionistAccess* visitor) const;
    void accept(ManagerAccess* visitor) const;

};


