#include "Room.h"
#include<cstring>
#define _CRT_SECURE_NO_WARNINGS
#include "PricingStrategyFactory.h"
#include "ReceptionistAccess.h"


Room::Room(int num, double price, EnumClasses::RoomType type, EnumClasses::Status stat, PricingStrategy* strat)
    : roomNum(num), basePrice(price), roomType(type), status(stat), strategy(strat) {
    if (price <= 0) {
        switch (roomType) {
        case EnumClasses::RoomType::Single: basePrice = 70.0; break;
        case EnumClasses::RoomType::Double: basePrice = 100.0; break;
        case EnumClasses::RoomType::Apartment: basePrice = 130.0; break;
        case EnumClasses::RoomType::Deluxe: basePrice = 200.0; break;
        case EnumClasses::RoomType::Conference: basePrice = 500.0; break;
        default: basePrice = 50.0; break;
        }
    }
    else {
        basePrice = price;
    }
};

void Room::setRoomNum(int num) {
    if (num < 0 || num>500) {
        std::cout << "invalid room number";
    }
    else {
        roomNum = num;
    }

}

int Room::getRoomNum() const {
    return roomNum;
}

void Room::setBasePrice(double price) {
    if (price < 0) {
        throw std::invalid_argument("Price cannot be negative");
    }


    if (basePrice == 0) {
        switch (roomType) {
        case EnumClasses::RoomType::Single:
            basePrice = 70.0;
            break;
        case EnumClasses::RoomType::Double:
            basePrice = 100.0;
            break;
        case EnumClasses::RoomType::Apartment:
            basePrice = 130.0;
            break;
        case EnumClasses::RoomType::Deluxe:
            basePrice = 200.0;
            break;
        case EnumClasses::RoomType::Conference:
            basePrice = 500.0;
            break;
        default:
            std::cout << "Unknown room type." << std::endl;
            break;
        }
    }
    else {

        basePrice = price;
    }
}


double Room::getBasePrice() const {
    return basePrice;
}

void Room::setStatus(const char* statusType) {
    if (strcmp(statusType, "Available") == 0) {
        status = EnumClasses::Status::Available;

    }
    else if (strcmp(statusType, "Reserved") == 0) {
        status = EnumClasses::Status::Reserved;

    }
    else if (strcmp(statusType, "underRenovation") == 0) {
        status = EnumClasses::Status::underRenovation;

    }
    else {
        std::cout << "Invalid status type: " << statusType << std::endl;
        return;
    }


}

void Room::setRoomType(const char* type) {

    if (strcmp(type, "Single") == 0) {
        roomType = EnumClasses::RoomType::Single;
    }

    else if (strcmp(type, "Double") == 0) {
        roomType = EnumClasses::RoomType::Double;
    }

    else if (strcmp(type, "Apartment") == 0) {
        roomType = EnumClasses::RoomType::Apartment;
    }

    else if (strcmp(type, "Deluxe") == 0) {
        roomType = EnumClasses::RoomType::Deluxe;
    }

    else if (strcmp(type, "Conference") == 0) {
        roomType = EnumClasses::RoomType::Conference;
    }

    else {
        std::cout << "Invalid room type: " << type << std::endl;
        return;
    }

}
const char* Room::getStatusType() const {

    switch (status) {

    case EnumClasses::Status::Available: return "Available";

    case EnumClasses::Status::Reserved: return "Reserved";

    case EnumClasses::Status::underRenovation: return "underRenovation";


    default: return "Unknown";
    }
}

void Room::setStrategy(PricingStrategy* newStrategy) {

    if (strategy == newStrategy) {
        return;
    }
    delete strategy;
    strategy = (newStrategy != nullptr) ? newStrategy->clone() : nullptr;
}

PricingStrategy* Room::getStrategy() const {
    return strategy;
}

const char* Room::getRoomType() const {

    switch (roomType) {

    case EnumClasses::RoomType::Single: return "Single";

    case EnumClasses::RoomType::Double: return "Double";

    case EnumClasses::RoomType::Apartment: return "Apartment";

    case EnumClasses::RoomType::Deluxe: return "Deluxe";

    case EnumClasses::RoomType::Conference: return "Conference";

    default: return "Unknown";
    }
}

double Room::getCalculatedPrice() const {

    return strategy ? strategy->calculatePrice(basePrice) : basePrice;


}


Room::Room(const Room& other) {
    copyFrom(other);
};


Room& Room::operator=(const Room& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
};


Room::Room(Room&& other) noexcept {

    moveFrom(std::move(other));

};


Room& Room::operator=(Room&& other) noexcept {

    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;

};

void Room::moveFrom(Room&& other) {
    this->roomNum = other.roomNum;
    this->roomType = other.roomType;
    this->status = other.status;
    this->basePrice = other.basePrice;


    this->strategy = other.strategy;
    other.strategy = nullptr;
}


void Room::copyFrom(const Room& other) {
    this->roomNum = other.roomNum;
    this->roomType = other.roomType;
    this->status = other.status;
    this->basePrice = other.basePrice;
    this->strategy = other.strategy ? other.strategy->clone() : nullptr;

};

void Room::free() {
    delete strategy;

};




Room::~Room() {
    free();
}

void Room::setStrategyByName(const char* name, const char* parameter) {
    PricingStrategy* strat = PricingStrategyFactory::createStrategy(name, parameter);
    if (strat) {
        setStrategy(strat);
    }
    else {
        std::cout << "Invalid strategy or parameter: " << name;
        if (parameter) {
            std::cout << " (" << parameter << ")";
        }
        std::cout << std::endl;
    }
}

void Room::accept(ReceptionistAccess* visitor) const {

    visitor->visitRoom(this);

};

void Room::accept(ManagerAccess* visitor) const {

    visitor->visitRoom(this);
};

void Room::saveToFile(std::ostream& out) const {
    out << roomNum << ' '
        << basePrice << ' '
        << static_cast<int>(roomType) << ' '
        << static_cast<int>(status) << ' ';

    if (strategy) {
        out << strategy->getName() << ' ' << strategy->getParameter();
    }
    else {
        out << "null null";
    }


    out << '\n';
}

void Room::loadFromFile(std::istream& in) {
    int typeInt, statusInt;
    std::string strategyName, strategyParam;

    in >> roomNum >> basePrice >> typeInt >> statusInt >> strategyName >> strategyParam;

    roomType = static_cast<EnumClasses::RoomType>(typeInt);
    status = static_cast<EnumClasses::Status>(statusInt);

    if (strategyName != "null") {
        PricingStrategy* strat = PricingStrategyFactory::createStrategy(strategyName.c_str(), strategyParam.c_str());
        setStrategy(strat);

    }
    else {
        setStrategy(nullptr);
    }
}


