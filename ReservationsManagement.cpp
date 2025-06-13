#include "ReservationsManagement.h"


void ReservationsManagement::free() {
	for (int i = 0; i < capacity; i++) {
		delete reservations[i];
	}
	delete[] reservations;
	capacity = 0;
	resCounter = 0;

};
void ReservationsManagement::copyFrom(const ReservationsManagement& other) {
	this->capacity = other.capacity;
	this->resCounter = other.resCounter;

	this->reservations = new Reservation * [capacity];

	for (int i = 0; i < capacity; i++) {
		this->reservations[i] = new Reservation(*other.reservations[i]);
	}

};
void ReservationsManagement::moveFrom(ReservationsManagement&& other) noexcept {
	this->resCounter = other.resCounter;
	other.resCounter = 0;

	this->capacity = other.capacity;
	other.capacity = 0;

	this->reservations = other.reservations;
	other.reservations = nullptr;

};

ReservationsManagement::ReservationsManagement() :capacity(EnumClasses::MAX_CAPACITY), resCounter(0) {
	reservations = new Reservation * [capacity];
	for (int i = 0; i < capacity; i++) {
		reservations[i] = nullptr;
	}

};
ReservationsManagement::ReservationsManagement(int capacity) {
	this->capacity = capacity;
	resCounter = 0;
	reservations = new Reservation * [capacity];
	for (int i = 0; i < capacity; i++) {
		reservations[i] = nullptr;
	}

};

void ReservationsManagement::resize(int newCap) {
	Reservation** tem = new Reservation * [newCap];
	for (int i = 0; i < capacity; i++) {
		if (reservations[i] != nullptr) {
			tem[i] = new Reservation(*reservations[i]);
		}
		else {
			tem[i] = nullptr;
		}

	}
	for (int i = 0; i < capacity; i++) {
		delete reservations[i];
	}

	delete[] reservations;
	reservations = tem;
	capacity = newCap;

}
int ReservationsManagement::getFirstFreeIndex() const {
	for (int i = 0; i < capacity; i++) {
		if (reservations[i] == nullptr) {
			return i;
		}
	}
	return -1;
}
void ReservationsManagement::insertAt(int index, const Guest& guest, const Date& checkIn, const Date& checkOut, const Room& room) {
	if (index >= 0 && index < capacity) {
		if (reservations[index] != nullptr) {
			delete reservations[index];
		}
		else {
			resCounter++;
		}
		reservations[index] = new Reservation(guest, checkIn, checkOut, room);
	}

}
void ReservationsManagement::addReservation(const Guest& guest, const Date& checkIn, const Date& checkOut, const Room& room) {
	int index = getFirstFreeIndex();

	if (index == -1) {
		resize(capacity * 2);
		index = getFirstFreeIndex();
	}

	insertAt(index, guest, checkIn, checkOut, room);
}

void ReservationsManagement::removeReservation(const Guest& gest, const Date& checkIn, const Date& checkOut, const Room& room) {


};
ReservationsManagement::ReservationsManagement(const Reservation* activeRes, int resCounter) {
	this->capacity = resCounter * 2;
	this->resCounter = resCounter;
	reservations = new Reservation * [capacity];

	for (int i = 0; i < resCounter; i++) {
		reservations[i] = new Reservation(activeRes[i]);
	}

	for (int i = resCounter; i < capacity; i++) {
		reservations[i] = nullptr;
	}
}




ReservationsManagement::ReservationsManagement(const ReservationsManagement& other) {
	copyFrom(other);
};
ReservationsManagement::ReservationsManagement(ReservationsManagement&& other)  noexcept {
	moveFrom(std::move(other));
};

ReservationsManagement& ReservationsManagement::operator=(const ReservationsManagement& other) {
	if (this != &other) {
		free();
		copyFrom(other);

	}
	return *this;
};
ReservationsManagement& ReservationsManagement::operator=(ReservationsManagement&& other)noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));

	}
	return *this;
};

ReservationsManagement::~ReservationsManagement() {
	free();
};

void ReservationsManagement::printActiveReservations() const {
	for (int i = 0; i < capacity; ++i) {
		if (reservations[i] != nullptr && reservations[i]->getIsActive()) {
			reservations[i]->print();
		}
	}
}
double  ReservationsManagement::getTotalAccommodationPrice(const Reservation& res) {

	return res.getTotalPrice();

};

bool ReservationsManagement::isThisRoomAvailable(const Reservation& res) const {
	return res.getIsActive();

};

bool ReservationsManagement::AreDatesValid(const Reservation& res)const {
	return res.getCheckInDate() < res.getCheckOutDate();

};
int  ReservationsManagement::getResCounter()const {
	return resCounter;

};
Reservation* ReservationsManagement::getReservationAt(int index) const {
	if (index < 0 || index >= resCounter || reservations[index] == nullptr) {
		return nullptr;
	}
	return reservations[index];
}


void ReservationsManagement::accept(ReceptionistAccess* visitor) const {
	visitor->visitReservationsManagement(this);

};

void ReservationsManagement::accept(ManagerAccess* visitor) const {
	visitor->visitReservationsManagement(this);

};

