#pragma once
#include "Employee.h"
#include "AccountantAccess.h"

class Accountant : public Employee, public AccountantAccess
{
public:
    Accountant() = default;
    Accountant(const char* name);
    Accountant(const char* username, const char* password, const Role& role);


    void showPermissions()const override;
    void visitRevenueInfo(const RevenueInfo* info)override;

    Employee* clone() const override;
};


