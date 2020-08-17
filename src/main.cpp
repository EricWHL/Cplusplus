#include <iostream>
#include <string>
#include "Sales_data.h"
#include "NLog.h"
using namespace std;

int main ()
{
    cout<<"Main Function IN"<<endl;

    NLog *ins = NLog::getInstance();
    NLog *ins1 = NLog::getInstance();
    NLog *ins2 = NLog::getInstance();
    NLog *ins3 = NLog::getInstance();
    NLog *ins4 = NLog::getInstance();
    cout<<"Main Function OUT"<<endl;
    return 0;
}
