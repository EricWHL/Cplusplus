#include <iostream>
#include <string>

#include "com.h"
#include "NLog.h"

/*
 *   Study content  *
 */
#include "Sales_data.h"
#include "Screen.h"

using namespace std;

int main ()
{
    cout<<"Main Function IN"<<endl;

#if FUNC_DEBUG
    NLog *ins = NLog::getInstance();
    NLog *ins1 = NLog::getInstance();
    NLog *ins2 = NLog::getInstance();
    NLog *ins3 = NLog::getInstance();
    NLog *ins4 = NLog::getInstance();
#endif
    
    struct Sales_data total = {
        .bookNo = "100-sws",
        .units_sold = 1,
        .revenue = 41.2,
    };


    cout << total.isbn() << endl;
    Sales_data trans;


    Screen myscr;
    char ch = myscr.get();
    
    cout<<"Main Function OUT"<<endl;
    return 0;
}
