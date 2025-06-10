
#pragma once
#include "Room.h"
#include "Manager.h"

class ManagerAccess;


class Accommodation
{
	Room** rooms = nullptr;
	int used = 0;
	int capacity = 0;

	void resize(int newCap);
	void free();
	void copyFrom(const Accommodation& other);
	void moveFrom(Accommodation&& other)  noexcept;
	int findFirstFreeIndex() const;

	friend class Manager;


public:
	Accommodation(int capacity);
	Accommodation(const Accommodation& other);
	Accommodation(Accommodation&& other) noexcept;
	Accommodation& operator=(const Accommodation& other);
	Accommodation& operator=(Accommodation&& other) noexcept;



	void insertAt(const Room& room, int index);
	void addNewRoom(const Room& newRoom);
	//void addNewRoom(Room&& newRoom);
	~Accommodation();

	void accept(ManagerAccess* visitor) const;

	int getUsed()const; 

};


