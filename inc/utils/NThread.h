#ifndef _N_THREAD_H
#define _N_THREAD_H

#include <pthread.h>
#include "com.h"
#include "NError.h"

typedef UINT32 NThread_id_t;
typedef UINT32 (*NThread_Func)(POINTER);


class NThread {
    typedef enum _NTHREAD_PRIORITY{
        NTHREAD_PRIORITY_DEFAULT,
        NTHREAD_PRIORITY_LOW,
        NTHREAD_PRIORITY_MID,
        NTHREAD_PRIORITY_HIGH
    }NTHREAD_PRIORITY;
    
    NThread();
    virtual ~NThread();

    virtual STATUS Run(const UBYTE* name,
                         INT32 priority = NTHREAD_PRIORITY_DEFAULT,
                         INT32 stack = 0);

    virtual void        requestExit();

    
};






#endif
