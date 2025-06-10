#pragma once
#include "Guest.h"
#include "Date.h"
#include "Room.h"
#include "Receptionist.h"
#include "Manager.h"
#include <fstream> 
#include <iostream>

class Guest;
class Room;
class ReceptionistAccess;
class ManagerAccess;

class Reservation
{
    Date checkInDate;
    Date checkOutDate;
    int reservationID;
    Guest* guest;
    Room* room;

    bool isActive;

    void free();
    void copyFrom(const Reservation& other);
    void moveFrom(Reservation&& other) noexcept;

    int numNights;

    double totalPrice;

    friend class Manager;
    friend class Receptionist;

public:


    Reservation();
    Reservation(const Guest& g, const Date& checkIn, const Date& checkOut, const Room& room);

    Reservation(const Reservation& other);
    Reservation(Reservation&& other) noexcept;
    Reservation& operator=(const Reservation& other);
    Reservation& operator=(Reservation&& other) noexcept;

    int getReservationID() const;
    Guest* getGuest() const;
    Date getCheckInDate() const;
    Date getCheckOutDate() const;


    bool getIsActive() const;
    Room* getRoom() const;
    void setRoom(const Room& room);
    void setReservationID(int id);
    void setGuest(Guest* g);
    void setCheckInDate(const Date& d);
    void setCheckOutDate(const Date& d);
    void setIsActive(bool active);

    void setNumNights(int nights);

    int calculateNumNights() const;
    void updateNumNights();
    void calculatePrice();
    double getTotalPrice() const;
    int getNumNights() const;

    void print() const;


    void saveToFile(std::ofstream& out) const;
    void loadFromFile(std::ifstream& in);


    void accept(ReceptionistAccess* visitor) const;
    void accept(ManagerAccess* visitor) const;

    void updatePrice(double newPrice);
    void setActive(bool active);
};


