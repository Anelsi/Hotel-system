#pragma once
#include "Reservation.h"
#include "Receptionist.h"
#include "EnumClasses.h"
#include "Manager.h"

class ReceptionistAccess;
class Guest;
class Date;
class Room;

class ManagerAccess;

class ReservationsManagement
{
	Reservation** reservations = nullptr;
	int capacity;
	int resCounter;

	void free();
	void copyFrom(const ReservationsManagement& other);
	void moveFrom(ReservationsManagement&& other)noexcept;

	void resize(int newCap);
	int getFirstFreeIndex() const;

	friend class Manager;
	friend class Receptionist;




public:

	ReservationsManagement();
	ReservationsManagement(int capacity);

	ReservationsManagement(const Reservation* activeRes, int resCounter);
	ReservationsManagement(const ReservationsManagement& other);
	ReservationsManagement(ReservationsManagement&& other)  noexcept;

	ReservationsManagement& operator=(const ReservationsManagement& other);
	ReservationsManagement& operator=(ReservationsManagement&& other)noexcept;

	~ReservationsManagement();

	Reservation* getReservationAt(int index) const;

	void addReservation(const Guest& gest, const Date& checkIn, const Date& checkOut, const Room& room);
	void removeReservation(const Guest& gest, const Date& checkIn, const Date& checkOut, const Room& room);

	double getTotalAccommodationPrice(const Reservation& res);

	bool isThisRoomAvailable(const Reservation& res) const;

	bool AreDatesValid(const Reservation& res)const;

	void printActiveReservations() const;

	void insertAt(int index, const Guest& guest, const Date& checkIn, const Date& checkOut, const Room& room);
	int getResCounter()const;

	void accept(ReceptionistAccess* visitor) const;
	void accept(ManagerAccess* visitor) const;
};


