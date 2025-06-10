#pragma once

#include <iostream>

class ReservationsManagement;
class Guest;
class Reservation;
class Room;

class ReceptionistAccess
{
public:


	virtual void visitGuest(const Guest* g) = 0;
	virtual void visitReservation(const Reservation* res) = 0;
	virtual void visitReservationsManagement(const ReservationsManagement* rm) = 0;
	virtual void visitRoom(const Room* room) = 0;

	virtual ~ReceptionistAccess() = default;
};