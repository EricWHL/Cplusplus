#include <iostream>
#include <string>

#include "com.h"
#include "NLog.h"

/*
 *   Study content  *
 */

#include "Study.h"

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


    Screen myscr(5,3,'A');
    cout<<"----------------"<<endl;
    char ch = myscr.get();
    ch = myscr.get(0,0);
    myscr.move(4,0).set('#');
    cout<<"----------------"<<endl;
    myscr.display(cout).set('*');
    cout<<"----------------"<<endl;
    myscr.move(4,0).set('#');
    cout<<"----------------"<<endl;
    Screen tmp = myscr.move(4,0);
    tmp.set('#');
    cout<<"----------------"<<endl;
    myscr.set('#').display(cout);
    cout<<"----------------"<<endl;
    
    constexpr Debug io_sub(false, true, false);
    if(io_sub.any())
        cerr << "print appropriate error messages" << endl;

    constexpr Debug prod(false);
    if(prod.any())
        cerr << "print an error messager" << endl;






    cout<<"Main Function OUT"<<endl;
    return 0;
}
