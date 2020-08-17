#ifndef _NLOG_H
#define _NLOG_H
typedef enum _NLOG_TYPE {
    NLOG_TYPE_UNKNOWN = 0,
    NLOG_TYPE_DEBUG,
    NLOG_TYPE_ERROR,
    NLOG_TYPE_INFO,
    NLOG_TYPE_MAX
}NLOG_TYPE;

class NLog {
public:
    static NLog* getInstance();

private:
    
    NLog();
    virtual ~NLog(){}

    NLOG_TYPE getLogType();
    
    NLOG_TYPE m_type;
    static NLog* m_instance;
};
#endif
