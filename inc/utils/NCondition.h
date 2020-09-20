#ifndef _NCONDITION_H
#define _NCONDITION_H
#include <limits.h>
#include <stdint.h>
#include <sys/types.h>
#include <time.h>

#include <pthread.h>

#include "NMutex.h"
#include "NError.h"

class NCondition {
public:
    enum {
        PRIVATE = 0,
        SHARED = 1
    };

    enum WakeUpType {
        WAKE_UP_ONE = 0,
        WAKE_UP_ALL = 1
    };
    NCondition();
    explicit NCondition(INT32 type);
    ~Condition();
    // Wait on the condition variable.  Lock the mutex before calling.
    // Note that spurious wake-ups may happen.
    STATUS wait(NMutex& mutex);
    // same with relative timeout
    STATUS waitRelative(Mutex& mutex, NSECS reltime);
    // Signal the condition variable, allowing one thread to continue.
    VOID signal();
    // Signal the condition variable, allowing one or all threads to continue.
    VOID signal(WakeUpType type) {
        if (type == WAKE_UP_ONE) {
            signal();
        } else {
            broadcast();
        }
    }
    // Signal the condition variable, allowing all threads to continue.
    VOID broadcast();
private:
    pthread_cond_t mCond;
    
};

inline NCondition::NCondition() : NCondition(PRIVATE) {
}

inline NCondition::NCondition(INT32 type) {
    pthread_condattr_t attr;
    pthread_condattr_init(&attr);

    pthread_condattr_setclock(&attr, CLOCK_MONOTONIC);

    if (type == SHARED) {
        pthread_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    }

    pthread_cond_init(&mCond, &attr);
    pthread_condattr_destroy(&attr);

}

inline NCondition::~NCondition() {
    pthread_cond_destroy(&mCond);
}

inline STATUS NCondition::wait(NMutex& mutex) {
    return -pthread_cond_wait(&mCond, &mutex.mMutex);
}

inline STATUS NCondition::waitRelative(NMutex& mutex, NSECS reltime) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    // On 32-bit devices, tv_sec is 32-bit, but `reltime` is 64-bit.
    INT64 reltime_sec = reltime/1000000000;

    ts.tv_nsec += static_cast<INT64>(reltime%1000000000);
    if (reltime_sec < INT64_MAX && ts.tv_nsec >= 1000000000) {
        ts.tv_nsec -= 1000000000;
        ++reltime_sec;
    }

    INT64 time_sec = ts.tv_sec;
    if (time_sec > INT64_MAX - reltime_sec) {
        time_sec = INT64_MAX;
    } else {
        time_sec += reltime_sec;
    }

    ts.tv_sec = (time_sec > LONG_MAX) ? LONG_MAX : static_cast<long>(time_sec);

    return -pthread_cond_timedwait(&mCond, &mutex.mMutex, &ts);
}

inline VOID NCondition::signal() {
    pthread_cond_signal(&mCond);
}

inline VOID NCondition::broadcast() {
    pthread_cond_broadcast(&mCond);
}


#endif
