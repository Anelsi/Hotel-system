#pragma once
#include "Employee.h"
#include "ReceptionistAccess.h"

class Guest;
class Reservation;
class Room;
class ReservationsManagement;

class Receptionist : public Employee, public ReceptionistAccess
{
public:
	Receptionist() = default;
	Receptionist(const char* name);
	Receptionist(const char* username, const char* password, const Role& role);

	void showPermissions() const override;

	virtual void visitGuest(const Guest* g) override;
	virtual void visitReservation(const Reservation* res) override;
	virtual void visitReservationsManagement(const ReservationsManagement* rm) override;
	virtual void visitRoom(const Room* room) override;

	Employee* clone() const override;
};

