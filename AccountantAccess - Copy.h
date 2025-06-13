#pragma once

#include <iostream>

class RevenueInfo;

class AccountantAccess
{
public:

    virtual void visitRevenueInfo(const RevenueInfo* rInfo) = 0;

    virtual ~AccountantAccess() = default;
};

