#include "Accommodation.h"
#include "EnumClasses.h"

#include <exception>
#define _CRT_SECURE_NO_WARNINGS


void Accommodation::resize(int newCap) {
	Room** tem = new Room * [newCap];
	for (int i = 0; i < newCap; ++i) {
		tem[i] = nullptr;
	}

	for (int i = 0; i < used; ++i) {
		if (rooms[i] != nullptr) {
			tem[i] = new Room(*rooms[i]);
		}
	}

	for (int i = 0; i < used; ++i) {
		delete rooms[i];
	}
	delete[] rooms;

	rooms = tem;
	capacity = newCap;

};

void Accommodation::free() {

	for (int i = 0; i < capacity; i++) {
		delete rooms[i];
	}
	delete[] rooms;

	rooms = nullptr;
	used = 0;
	capacity = 0;

};
void Accommodation::copyFrom(const Accommodation& other) {
	this->capacity = other.capacity;
	this->used = other.used;
	this->rooms = new Room * [this->capacity] {nullptr};
	for (int i = 0; i < other.capacity; i++) {
		if (other.rooms[i]) {
			this->rooms[i] = new Room(*other.rooms[i]);
		}
	}

};
void Accommodation::moveFrom(Accommodation&& other) noexcept {
	this->capacity = other.capacity;
	other.capacity = 0;

	this->rooms = other.rooms;
	other.rooms = nullptr;

	this->used = other.capacity;
	other.used = 0;


};

Accommodation::Accommodation(int capacity) : capacity(EnumClasses::MAX_CAPACITY) {

	rooms = new Room * [EnumClasses::MAX_CAPACITY];


};
Accommodation::Accommodation(const Accommodation& other) {
	copyFrom(other);


};
Accommodation::Accommodation(Accommodation&& other) noexcept {
	moveFrom(std::move(other));

};
Accommodation& Accommodation::operator=(const Accommodation& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;

};
Accommodation& Accommodation::operator=(Accommodation&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;

};

//da syzdam li oshte edin addnewRoom(const Room& r)

void Accommodation::addNewRoom(const Room& room) {
	if (used >= capacity) {
		resize(capacity + 50);
	}
	int index = findFirstFreeIndex();
	insertAt(room, index);


};

void Accommodation::insertAt(const Room& room, int index) {
	if (rooms[index] == nullptr) {
		rooms[index] = new Room(room);
		used++;

	}
	else {
		*rooms[index] = room;
	}

};

int Accommodation::findFirstFreeIndex() const {
	for (int i = 0; i < capacity; i++) {
		if (rooms[i] == nullptr) {
			return i;
		}
	}

	throw std::exception("no more capacity");

}


//void Accommodation::addNewRoom(Room&& newRoom) {
//	if (used >= capacity) {
//		resize(capacity + 10);
//	}
//	rooms[used++] = std::move(newRoom);
//	
//
//
//};

Accommodation::~Accommodation() {
	free();

};

void Accommodation::accept(ManagerAccess* visitor) const {
	visitor->visitAccommodation(this);

}
int Accommodation::getUsed() const {

	return used;

};