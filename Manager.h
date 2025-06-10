#pragma once
#include "ManagerAccess.h"

#include "Employee.h"

class Guest;
class Reservation;
class Room;
class ReservationsManagement;
class RevenueInfo;
class Accommodation;

class ReservationsManagement;

class Manager : public Employee, public ManagerAccess
{

public:

	Manager() = default;
	Manager(const char* name);
	Manager(const char* username, const char* password, const Role& role);

	void visitRevenueInfo(const RevenueInfo* rInfo)  override;
	void visitGuest(const Guest* g) override;
	void visitReservation(const Reservation* res) override;
	void visitReservationsManagement(const ReservationsManagement* rm) override;
	void visitRoom(const Room* room)override;
	void visitAccommodation(const Accommodation* acc)override;

	void showPermissions() const override;
	Employee* clone() const override;
};
