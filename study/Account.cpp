#include "Account.h"

double Account::interestRate = initRate();
constexpr int Account::period;

void Account::rate(double newRate)
{
    Account::interestRate = newRate;
}

double Account::initRate()
{
    return 0.0;
}
