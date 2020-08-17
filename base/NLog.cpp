#include <cstddef>
#include <iostream>

#include "NLog.h"
using namespace std;

NLog* NLog::m_instance = NULL;

NLog::NLog()
    : m_type (NLOG_TYPE_UNKNOWN)
{
    cout<<"NLog() function in"<<endl;
    cout<<"NLog() function out"<<endl;
}

NLog* NLog::getInstance()
{
    
    cout<<"get instance IN"<<endl;
    if(NULL == m_instance) {
        cout<<"get new instance "<<endl;
        m_instance = new NLog();
    }
    cout<<"get instance OUT"<<endl;
    return m_instance;
}

NLOG_TYPE NLog::getLogType()
{
    return m_type;
}
