#include "Com_Test.h"

#include <iostream>
using namespace std;

extern void Com_Test_Main()
{
    cout<< "Com_Test_Main IN"<<endl;
    
    cout << "UBYTE size is: " << sizeof(UBYTE)<<endl;

    cout << "UINT16 size is: " << sizeof(UINT16)<<endl;
    cout << "INT16 size is: " << sizeof(INT16)<<endl;

    cout << "UINT32 size is: " << sizeof(UINT32)<<endl;
    cout << "INT32 size is: " << sizeof(INT32)<<endl;

    cout << "UINT64 size is: " << sizeof(UINT64)<<endl;
    cout << "INT64 size is: " << sizeof(INT64)<<endl;

    cout<< "Com_Test_Main OUT"<<endl;
}
