#include "Guest.h"

#include "Reservation.h"

#include <fstream>
#define _CRT_SECURE_NO_WARNINGS

void Guest::setName(const char* name) {
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy_s(this->name, strlen(name) + 1, name);

}

void Guest::setEmail(const char* email) {
    delete[] this->email;
    this->email = new char[strlen(email) + 1];
    strcpy_s(this->email, strlen(email)+1,email);
}

void Guest::setGuestNum(int num) {
    guestNum = num;
}





const char* Guest::getName() const {
    return name;
}

const char* Guest::getEmail() const {
    return email;
}

int Guest::getGuestNum() const {
    return guestNum;
}

const int* Guest::getPhoneNum() const {
    return phoneNum;
}
void Guest::setPhoneNum(const int* digits) {
    for (int i = 0; i < EnumClasses::MAX_NUMBERS; ++i) {
        if (digits[i] < 0 || digits[i] > 9) {
            std::cout << "Invalid digit at position " << i << ": " << digits[i] << "\n";
            return;
        }
    }
    for (int i = 0; i < EnumClasses::MAX_NUMBERS; ++i) {
        phoneNum[i] = digits[i];
    }
}


const char* Guest::getGuestStatus() const {
    switch (guestStatus) {
    case EnumClasses::GuestStatus::Gold:return "Gold";
    case EnumClasses::GuestStatus::Platinium:return "Platinium";
    case EnumClasses::GuestStatus::Regular: return "Regular";
    default: return "not valid guest status";
    }

}
void Guest::free() {
    delete[] name;
    delete[] email;
    delete[]reservations;
    name = nullptr;
    email = nullptr;
    reservations = nullptr;
}

void Guest::copyFrom(const Guest& other) {
    this->name = new char[strlen(other.name) + 1];
    strcpy_s(name,strlen(name)+1, other.name);

    this->email = new char[strlen(other.email) + 1];
    strcpy_s(email,strlen(email)+1, other.email);

    guestNum = other.guestNum;
    guestStatus = other.guestStatus;
    for (int i = 0; i < EnumClasses::MAX_NUMBERS; i++) {
        phoneNum[i] = other.phoneNum[i];
    }
    this->reservationsCount = other.reservationsCount;
    this->reservations = new Reservation[reservationsCount];
    for (int i = 0; i < other.reservationsCount; i++) {
        this->reservations[i] = other.reservations[i];
    }
}

void Guest::moveFrom(Guest&& other) {
    this->name = other.name;
    other.name = nullptr;

    this->email = other.email;
    other.email = nullptr;

    this->guestNum = other.guestNum;
    other.guestNum = 0;

    this->guestStatus = other.guestStatus;

    for (int i = 0; i < EnumClasses::MAX_NUMBERS; ++i) {
        this->phoneNum[i] = other.phoneNum[i];
    }
    for (int i = 0; i < EnumClasses::MAX_NUMBERS; ++i) {
        other.phoneNum[i] = 0;
    }
    this->reservationsCount = other.reservationsCount;
    other.reservationsCount = 0;

    this->reservations = other.reservations;
    other.reservations = nullptr;
}
Guest::Guest()
    : name(nullptr), email(nullptr), reservations(nullptr), guestNum(0),
    reservationsCount(0), guestStatus(EnumClasses::GuestStatus::Regular) {
    for (int i = 0; i < EnumClasses::MAX_NUMBERS; ++i)
        phoneNum[i] = 0;
}


Guest::Guest(const char* name, const char* email, int guestNum, const int* phoneDigits, const char* status, int resCount)
    : name(nullptr), email(nullptr), reservations(nullptr)
{
    setName(name);
    setEmail(email);
    setGuestNum(guestNum);
    setPhoneNum(phoneDigits);

    setReservationsCount(resCount);

    reservations = new Reservation[resCount];
}



Guest::~Guest() {
    free();
}

Guest::Guest(const Guest& other) {
    copyFrom(other);
}

Guest& Guest::operator=(const Guest& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}


Guest::Guest(Guest&& other) noexcept {
    moveFrom(std::move(other));
}


Guest& Guest::operator=(Guest&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

double Guest::getDiscount() const {


    switch (guestStatus) {
    case EnumClasses::GuestStatus::Platinium: return 0.20;
    case EnumClasses::GuestStatus::Gold: return 0.10;
    default: return 0.0;
    }
}
void Guest::addReservation(const Reservation& res) {

    Reservation* newArray = new Reservation[reservationsCount + 1];
    for (int i = 0; i < reservationsCount; ++i) {
        newArray[i] = reservations[i];
    }
    newArray[reservationsCount] = res;

    delete[] reservations;
    reservations = newArray;
    ++reservationsCount;

}
void Guest::setReservationsCount(int resCount) {
    reservationsCount = resCount;
};
int Guest::getReservationsCount() const {
    return reservationsCount;

};

Reservation* Guest::getReservations() const {
    return reservations;
}

void Guest::setReservations(Reservation* newReservations, int count) {
    delete[] reservations;
    reservations = new Reservation[count];
    for (int i = 0; i < count; ++i) {
        reservations[i] = newReservations[i];
    }

    reservationsCount = count;
}

int Guest::getTotalStays() const {
    return reservationsCount;
}

double Guest::getTotalSpent() const {
    double total = 0.0;
    for (int i = 0; i < reservationsCount; ++i) {
        total += reservations[i].getTotalPrice();
    }
    return total;
}
void Guest::analyzeGuests(Guest* guests, int guestCount) {
    std::cout << "Guest Activity Report" << std::endl;
    for (int i = 0; i < guestCount; ++i) {
        int stays = guests[i].getReservationsCount();
        double spent = guests[i].getTotalSpent();

        std::cout << guests[i].getName() << ": "
            << stays << " stays, "
            << spent << " BGN spent" << std::endl;
    }
}

Guest Guest::findMostLoyalGuest(Guest* guests, int guestCount) {
    int maxStays = -1;
    int index = -1;

    for (int i = 0; i < guestCount; ++i) {
        if (guests[i].getReservationsCount() > maxStays) {
            maxStays = guests[i].getReservationsCount();
            index = i;
        }
    }

    return guests[index];
}


void Guest::updateGuestStatus() {
    if (reservationsCount >= 10) {
        guestStatus = EnumClasses::GuestStatus::Gold;
    }
    else if (reservationsCount >= 5) {
        guestStatus = EnumClasses::GuestStatus::Platinium;
    }
    else {
        guestStatus = EnumClasses::GuestStatus::Regular;
    }
}

void Guest::accept(ReceptionistAccess* visitor) const {
    visitor->visitGuest(this);

};
void Guest::accept(ManagerAccess* visitor) const {

    visitor->visitGuest(this);

};

void Guest::printReservationHistory() const {
    std::cout << "Reservation history for " << name << ":\n";
    for (int i = 0; i < reservationsCount; ++i) {
        std::cout << "Reservation " << (i + 1) << ":\n";
        reservations[i].print();
        std::cout << "---------------------\n";
    }
}
void Guest::saveToFile(std::ofstream& out) const {
    size_t nameLen = strlen(name);
    size_t emailLen = strlen(email);

    out.write((char*)&nameLen, sizeof(nameLen));
    out.write(name, nameLen);

    out.write((char*)&emailLen, sizeof(emailLen));
    out.write(email, emailLen);

    out.write((char*)&guestNum, sizeof(guestNum));
    out.write((char*)phoneNum, sizeof(int) * EnumClasses::MAX_NUMBERS);

    out.write((char*)&guestStatus, sizeof(guestStatus));

    out.write((char*)&reservationsCount, sizeof(reservationsCount));

    for (int i = 0; i < reservationsCount; ++i) {
        reservations[i].saveToFile(out);
    }
}

void Guest::loadFromFile(std::ifstream& in) {
    free();

    size_t nameLen = 0;
    in.read((char*)&nameLen, sizeof(nameLen));
    name = new char[nameLen + 1];
    in.read(name, nameLen);
    name[nameLen] = '\0';

    size_t emailLen = 0;
    in.read((char*)&emailLen, sizeof(emailLen));
    email = new char[emailLen + 1];
    in.read(email, emailLen);
    email[emailLen] = '\0';

    in.read((char*)&guestNum, sizeof(guestNum));
    in.read((char*)phoneNum, sizeof(int) * EnumClasses::MAX_NUMBERS);

    in.read((char*)&guestStatus, sizeof(guestStatus));

    in.read((char*)&reservationsCount, sizeof(reservationsCount));

    reservations = new Reservation[reservationsCount];
    for (int i = 0; i < reservationsCount; ++i) {
        reservations[i].loadFromFile(in);
    }
}

