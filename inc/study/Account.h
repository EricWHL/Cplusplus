#ifndef _ACCOUNT_H
#define _ACCOUNT_H
#include <string>
class Account {
public:

    void calculate() { amount += amount * interestRate; }
    static double rate() { return interestRate; }
    static void rate(double) ;

    
private:
    std::string owner;
    double amount;
    static constexpr int period = 30;
    double daily_tbl[period];
    static double interestRate;
    static double initRate();
};
#endif
