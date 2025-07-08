///************************* OUTS HOMEWORK ****************************************
#ifndef CSERVERTHREAD_HPP
#define CSERVERTHREAD_HPP

#include <functional>
#include <atomic>
#include <thread>
#include <deque>
#include <mutex>
#include <condition_variable>

class cThreadSafeCommandsDeque;
class cExceptionsHandler;

class cState;
class iCommand;
class cWaitForSoftStop;
class cMoveToState;

class cServerThread
{
  friend class cWaitForSoftStop;
  friend class cMoveToState;

public:
    cServerThread(cThreadSafeCommandsDeque *deque, std::deque<std::shared_ptr<iCommand>>* storage = nullptr );

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
    void Execute(const class cHardStopCommand&) { state = nullptr; }
    void Execute(const class cCommandCounter&);
    void Execute(const class cMoveToCommand&);
    void Execute(const class cRunCommand&);

    void sleep();

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

    cState* state;
    std::shared_ptr<cWaitForSoftStop> stateWaitForSoftStop;
    std::shared_ptr<cMoveToState> stateMoveTo;

};

#endif //#ifndef CSERVERTHREAD_HPP
