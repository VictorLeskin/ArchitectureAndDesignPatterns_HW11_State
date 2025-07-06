///************************* OUTS HOMEWORK ****************************************
#ifndef CSERVERTHREAD_HPP
#define CSERVERTHREAD_HPP

#include <functional>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

class cThreadSafeCommandsDeque;
class cExceptionsHandler;


class cServerThread
{
public:
    cServerThread(cThreadSafeCommandsDeque *deque);

    void join() 
    {
        t.join();
    }

    void detach()
    {
      t.detach();
    }

    int SleptTimeMs() const { return sleepTimeMs;  };

    void Execute(const class cSoftStopCommand&) { iSoftStop = true; }
    void Execute(const class cHardStopCommand&) { iStop = true; }
    void Execute(const class cCommandCounter&);

protected:
    cThreadSafeCommandsDeque* deque;
    cExceptionsHandler* handler;
    std::thread t;
    std::function<void(cServerThread &)> behaviour;
    std::atomic_int iStop = false, iSoftStop = false;

    std::mutex m;
    std::condition_variable cv;
    bool bEnableStart = false;

    int sleepTimeMs = 0;
    int iCommandCounter = 0;
};

#endif //#ifndef CSERVERTHREAD_HPP
