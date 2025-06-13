#pragma once
#include "EnumClasses.h"


class Employee
{
	char* name = nullptr;
	char* username = nullptr;
	char* password = nullptr;
	int employeeId = 0;
	Role role = Role::Receptionist;


	void free();
	void moveFrom(Employee&& other) noexcept;
	void copyFrom(const Employee& other);

public:
	const char* getRole() const;
	const char* getUserName() const;

	void setRole(const char* role);
	void setUserName(const char* username);

	int getId() const;

	Employee() = default;
	Employee(const char* name);
	Employee(const char* username, const char* password, const Role& role);
	Employee(const Employee& other);
	Employee& operator=(const Employee& other);

	Employee(Employee&& other) noexcept;
	Employee& operator=(Employee&& other) noexcept;

	virtual void showPermissions() const = 0;

	virtual ~Employee();

	virtual Employee* clone() const = 0;



};


