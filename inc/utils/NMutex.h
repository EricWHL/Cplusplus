#ifndef _NMUTEX_H
#define _NMUTEX_H

#include <stdint.h>
#include <sys/types.h>
#include <time.h>

#include <pthread.h>

#include "com.h"
#include "NError.h"

#define THREAD_ANNOTATION_ATTRIBUTE__(x) __attribute__((x))
#define CAPABILITY(x) THREAD_ANNOTATION_ATTRIBUTE__(capability(x))

#define SCOPED_CAPABILITY THREAD_ANNOTATION_ATTRIBUTE__(scoped_lockable)

#define GUARDED_BY(x) THREAD_ANNOTATION_ATTRIBUTE__(guarded_by(x))

#define PT_GUARDED_BY(x) THREAD_ANNOTATION_ATTRIBUTE__(pt_guarded_by(x))

#define ACQUIRED_BEFORE(...) THREAD_ANNOTATION_ATTRIBUTE__(acquired_before(__VA_ARGS__))

#define ACQUIRED_AFTER(...) THREAD_ANNOTATION_ATTRIBUTE__(acquired_after(__VA_ARGS__))

#define REQUIRES(...) THREAD_ANNOTATION_ATTRIBUTE__(requires_capability(__VA_ARGS__))

#define REQUIRES_SHARED(...) THREAD_ANNOTATION_ATTRIBUTE__(requires_shared_capability(__VA_ARGS__))

#define ACQUIRE(...) THREAD_ANNOTATION_ATTRIBUTE__(acquire_capability(__VA_ARGS__))

#define ACQUIRE_SHARED(...) THREAD_ANNOTATION_ATTRIBUTE__(acquire_shared_capability(__VA_ARGS__))

#define RELEASE(...) THREAD_ANNOTATION_ATTRIBUTE__(release_capability(__VA_ARGS__))

#define RELEASE_SHARED(...) THREAD_ANNOTATION_ATTRIBUTE__(release_shared_capability(__VA_ARGS__))

#define TRY_ACQUIRE(...) THREAD_ANNOTATION_ATTRIBUTE__(try_acquire_capability(__VA_ARGS__))

#define TRY_ACQUIRE_SHARED(...) \
    THREAD_ANNOTATION_ATTRIBUTE__(try_acquire_shared_capability(__VA_ARGS__))

#define EXCLUDES(...) THREAD_ANNOTATION_ATTRIBUTE__(locks_excluded(__VA_ARGS__))

#define ASSERT_CAPABILITY(x) THREAD_ANNOTATION_ATTRIBUTE__(assert_capability(x))

#define ASSERT_SHARED_CAPABILITY(x) THREAD_ANNOTATION_ATTRIBUTE__(assert_shared_capability(x))

#define RETURN_CAPABILITY(x) THREAD_ANNOTATION_ATTRIBUTE__(lock_returned(x))

#define NO_THREAD_SAFETY_ANALYSIS THREAD_ANNOTATION_ATTRIBUTE__(no_thread_safety_analysis)

class NCondition;

class CAPABILITY("nmutex") NMutex {
  public:
    enum {
        PRIVATE = 0,
        SHARED = 1
    };

    NMutex();
    explicit NMutex(const UBYTE* name);
    explicit NMutex(INT32 type, const UBYTE* name = NULL);
    ~Mutex();

    // lock or unlock the mutex
    STATUS lock() ACQUIRE();
    VOID unlock() RELEASE();

    // lock if possible; returns 0 on success, error otherwise
    STATUS tryLock() TRY_ACQUIRE(true);
    STATUS timedLock(NSECS timeoutNs) TRY_ACQUIRE(true);


    class SCOPED_CAPABILITY Autolock {
    public:
        inline explicit Autolock(Mutex& mutex) ACQUIRE(mutex) : mLock(mutex) { mLock.lock(); }
        inline explicit Autolock(NMutex* mutex) ACQUIRE(mutex) : mLock(*mutex) { mLock.lock(); }
        inline ~Autolock() RELEASE() { mLock.unlock(); }

    private:
        NMutex& mLock;
        // Cannot be copied or moved - declarations only
        Autolock(const Autolock&);
        Autolock& operator=(const Autolock&);
    };
  private:
    friend class NCondition;

    // A mutex cannot be copied
    NMutex(const NMutex&);
    NMutex& operator=(const NMutex&);

    pthread_mutex_t mMutex;
    void _init();
    void* mState;

};

inline NMutex::NMutex() {
    pthread_mutex_init(&mMutex, NULL);
}

inline NMutex::NMutex(__attribute__((unused)) const UBYTE* name) {
    pthread_mutex_init(&mMutex, NULL);
}

inline NMutex::NMutex(INT32 type, __attribute__((unused)) const BYTE* name) {
    if (type == SHARED) {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
        pthread_mutex_init(&mMutex, &attr);
        pthread_mutexattr_destroy(&attr);
    } else {
        pthread_mutex_init(&mMutex, NULL);
    }
}

inline NMutex::~NMutex() {
    pthread_mutex_destroy(&mMutex);
}

inline STATUS NMutex::lock() {
    return -pthread_mutex_lock(&mMutex);
}

inline VOID NMutex::unlock() {
    pthread_mutex_unlock(&mMutex);
}

inline STATUS NMutex::tryLock() {
    return -pthread_mutex_trylock(&mMutex);
}

inline STATUS NMutex::timedLock(NSECS timeoutNs) {
    timeoutNs += systemTime(SYSTEM_TIME_REALTIME);
    const struct timespec ts = {
        /* .tv_sec = */ static_cast<time_t>(timeoutNs / 1000000000),
        /* .tv_nsec = */ static_cast<INT64>(timeoutNs % 1000000000),
    };
    return -pthread_mutex_timedlock(&mMutex, &ts);
}

typedef NNMutex::Autolock AutoMutex;


#endif
