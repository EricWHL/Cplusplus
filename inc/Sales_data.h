#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
using namespace std;

struct Sales_data {

    string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

#endif
