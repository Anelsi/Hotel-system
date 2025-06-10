#include "Reservation.h"
#include <stdexcept>  
#define _CRT_SECURE_NO_WARNINGS



int Reservation::getReservationID() const
{
    return reservationID;
}

Guest* Reservation::getGuest() const {
    return guest;
}

void Reservation::setRoom(const Room& r) {

    delete room;
    room = new Room(r);
}

Room* Reservation::getRoom() const {
    return room;
}

Date Reservation::getCheckInDate() const
{
    return checkInDate;
}

Date Reservation::getCheckOutDate() const
{
    return checkOutDate;

}





bool Reservation::getIsActive() const {
    return isActive;
}


void Reservation::setReservationID(int id) {

    if (id > 0) {
        reservationID = id;
    }
    else {
        throw std::invalid_argument("not valid reservation id");
    }
}

void Reservation::setGuest(Guest* g) {
    if (g != nullptr) {
        guest = g;
    }
    else {
        throw std::invalid_argument("not valid guest");
    }
}



void Reservation::setCheckInDate(const Date& d) {
    checkInDate = d;
}

void Reservation::setCheckOutDate(const Date& d) {
    if (d.getYear() > checkInDate.getYear() ||
        (d.getYear() == checkInDate.getYear() && d.getMonth() > checkInDate.getMonth()) ||
        (d.getYear() == checkInDate.getYear() && d.getMonth() == checkInDate.getMonth() &&
            d.getDay() > checkInDate.getDay())) {
        checkOutDate = d;
    }
    else {
        throw std::invalid_argument("not valid date");
    }
}




void Reservation::setIsActive(bool active) {
    isActive = active;
}





void Reservation::free() {
    delete guest;
    delete room;
    guest = nullptr;
    room = nullptr;
}

void Reservation::copyFrom(const Reservation& other) {
    checkInDate = other.checkInDate;
    checkOutDate = other.checkOutDate;
    reservationID = other.reservationID;
    isActive = other.isActive;

    guest = (other.guest != nullptr) ? new Guest(*other.guest) : nullptr;
    room = (other.room != nullptr) ? new Room(*other.room) : nullptr;



    numNights = other.numNights;
    totalPrice = other.totalPrice;
}

void Reservation::moveFrom(Reservation&& other)  noexcept {
    checkInDate = other.checkInDate;
    other.checkInDate = Date();

    checkOutDate = other.checkOutDate;
    other.checkOutDate = Date();

    reservationID = other.reservationID;
    other.reservationID = 0;
    isActive = other.isActive;
    other.isActive = false;

    guest = other.guest;
    other.guest = nullptr;

    room = other.room;
    other.room = nullptr;

}
Reservation::Reservation()
    : checkInDate(Date::Date()), checkOutDate(Date::Date()), reservationID(0),
    guest(nullptr), room(nullptr), isActive(false) {

}

Reservation::Reservation(const Guest& g, const Date& checkIn, const Date& checkOut, const Room& r)
    : checkInDate(checkIn),
    checkOutDate(checkOut),
    guest(new Guest(g)),
    room(new Room(r)),
    isActive(true) {

    static int nextID = 1;
    reservationID = nextID++;
    updateNumNights();
    calculatePrice();
};


Reservation::Reservation(const Reservation& other) {

    copyFrom(other);
};


Reservation::Reservation(Reservation&& other) noexcept {
    moveFrom(std::move(other));

};

Reservation& Reservation::operator=(const Reservation& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
};
Reservation& Reservation::operator=(Reservation&& other) noexcept {

    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
};

int Reservation::calculateNumNights() const {
    int diff = checkOutDate.getDifferenceInDays(checkInDate);
    return diff > 0 ? diff : 0;

}

void Reservation::updateNumNights() {
    numNights = calculateNumNights();
}

void Reservation::calculatePrice() {
    updateNumNights();
    if (room != nullptr) {
        totalPrice = numNights * room->getBasePrice();
    }
    else {
        totalPrice = 0.0;
    }
}

double Reservation::getTotalPrice() const {
    return totalPrice;
}

int Reservation::getNumNights() const {
    return numNights;
}

void Reservation::setNumNights(int nights) {
    if (nights >= 0)
        numNights = nights;
    else
        throw std::invalid_argument("Number of nights cannot be negative.");
}


void Reservation::print() const {
    std::cout << "Reservation #" << reservationID << "\n";
    std::cout << "Guest: " << (guest ? guest->getName() : "None") << "\n";
    std::cout << "Check-in: " << checkInDate.toString() << "\n";
    std::cout << "Check-out: " << checkOutDate.toString() << "\n";
    std::cout << "Nights: " << numNights << ", Total: " << totalPrice << " BGN\n";
    std::cout << "Status: " << (isActive ? "Active" : "Inactive") << "\n";
}
void Reservation::accept(ReceptionistAccess* visitor) const {
    visitor->visitReservation(this);

};
void Reservation::accept(ManagerAccess* visitor) const {

    visitor->visitReservation(this);

};

void Reservation::saveToFile(std::ofstream& out) const {
    out.write((char*)&reservationID, sizeof(reservationID));
    out.write((char*)&isActive, sizeof(isActive));
    out.write((char*)&numNights, sizeof(numNights));
    out.write((char*)&totalPrice, sizeof(totalPrice));

    checkInDate.saveToFile(out);
    checkOutDate.saveToFile(out);

    if (guest)
        guest->saveToFile(out);
    else
        throw std::runtime_error("Cannot save null guest");

    if (room)
        room->saveToFile(out);
    else
        throw std::runtime_error("Cannot save null room");
}
void Reservation::loadFromFile(std::ifstream& in) {
    free();

    in.read((char*)&reservationID, sizeof(reservationID));
    in.read((char*)&isActive, sizeof(isActive));
    in.read((char*)&numNights, sizeof(numNights));
    in.read((char*)&totalPrice, sizeof(totalPrice));

    checkInDate.loadFromFile(in);
    checkOutDate.loadFromFile(in);

    guest = new Guest();
    guest->loadFromFile(in);

    room = new Room();
    room->loadFromFile(in);
}
void Reservation::updatePrice(double newPrice)
{
    totalPrice = newPrice;
};
void Reservation::setActive(bool active)
{
    isActive = active;
};