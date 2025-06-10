#include "Employee.h"
#include <cstring>
#include <stdexcept>




void Employee::free() {
	delete[] this->name;
	delete[] this->username;
	delete[] this->password;
	name = username = password = nullptr;



};
void Employee::moveFrom(Employee&& other) noexcept {
	this->name = other.name;
	other.name = nullptr;

	this->username = other.username;
	other.username = nullptr;

	this->password = other.password;
	other.password = nullptr;

	this->employeeId = other.employeeId;
	other.employeeId = 0;

	this->role = other.role;


};
void Employee::copyFrom(const Employee& other) {
	this->name = new char[strlen(other.name) + 1];
	strcpy_s(this->name, strlen(other.name) + 1, other.name);

	this->username = new char[strlen(other.username) + 1];
	strcpy_s(this->username, strlen(other.username) + 1, other.username);

	this->password = new char[strlen(other.password) + 1];
	strcpy_s(this->password, strlen(other.password) + 1, other.password);

	this->employeeId = other.employeeId;
	this->role = other.role;

};

const char* Employee::getRole() const {
	switch (role) {

	case Role::Accountant: return "Accountant";

	case Role::Manager:return "Manager";

	case Role::Receptionist:return "Receptionist";

	default: return "Unknown";
	}



};

void Employee::setRole(const char* role) {
	if (strcmp(role, "Receptionist") == 0) {
		this->role = Role::Receptionist;

	}
	else if (strcmp(role, "Accountant") == 0) {
		this->role = Role::Accountant;
	}
	else if (strcmp(role, "Manager") == 0) {
		this->role = Role::Manager;
	}
	else {
		throw std::invalid_argument("Invalid role");

	}
};

const char* Employee::getUserName() const {
	return username;

};


void Employee::setUserName(const char* username) {
	delete[] this->username;
	this->username = new char[strlen(username) + 1];
	strcpy_s(this->username, strlen(username) + 1, username);


};


Employee::Employee(const char* name) {

	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);

	this->username = nullptr;
	this->password = nullptr;
};


Employee::Employee(const char* username, const char* password, const Role& role) {
	this->username = new char[strlen(username) + 1];
	strcpy_s(this->username, strlen(username) + 1, username);

	this->password = new char[strlen(password) + 1];
	strcpy_s(this->password, strlen(password) + 1, password);


	this->role = role;
	this->name = nullptr;

};
Employee::Employee(const Employee& other) {

	copyFrom(other);

};
Employee& Employee::operator=(const Employee& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;


};

Employee::Employee(Employee&& other) noexcept {

	moveFrom(std::move(other));

};
Employee& Employee::operator=(Employee&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;


};



Employee::~Employee() {
	free();

};
int Employee::getId() const { return employeeId; }

