#pragma once
#include <iostream>
#include <cstring> 
#include "EnumClasses.h"
#include "PricingStrategy.h"
#include "Manager.h"

class ReceptionistAccess;
class ManagerAccess;

class Room {

    EnumClasses::RoomType roomType;
    int roomNum;
    double basePrice;
    EnumClasses::Status status;
    PricingStrategy* strategy = nullptr;

    void moveFrom(Room&& other);
    void copyFrom(const Room& other);
    void free();

    friend class Manager;
    friend class Receptionist;


public:

    Room() = default;
    Room(int num, double price, EnumClasses::RoomType type, EnumClasses::Status stat, PricingStrategy* strat);

    void setRoomNum(int num);
    int getRoomNum() const;

    void setBasePrice(double price);
    double getBasePrice() const;


    void setStatus(const char* statusType);
    const char* getStatusType() const;

    void setRoomType(const char* type);
    const char* getRoomType() const;

    void setStrategy(PricingStrategy* newStrategy);
    PricingStrategy* getStrategy() const;

    void setStrategyByName(const char* name, const char* parameter);


    double getCalculatedPrice() const;


    Room(const Room& other);


    Room& operator=(const Room& other);


    Room(Room&& other) noexcept;


    Room& operator=(Room&& other) noexcept;


    void saveToFile(std::ostream& out) const;

    void loadFromFile(std::istream& in);

    ~Room();

    void accept(ReceptionistAccess* visitor) const;
    void accept(ManagerAccess* visitor) const;
};


