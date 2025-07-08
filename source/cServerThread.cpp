///************************* OUTS HOMEWORK ****************************************

#include "cServerThread.hpp"
#include "cCommandsDeque.hpp"
#include "cExceptionsHandler.hpp"
#include "cException.hpp"
#include "cThreadSafeCommandsDeque.hpp"
#include "cStopCommand.hpp"
#include "cState.hpp"

#include <thread>
#include <chrono>

using namespace std::chrono_literals;

void cServerThread::sleep()
{
  std::this_thread::sleep_for(200ms);
  sleepTimeMs += 200;
}

cServerThread::cServerThread(cThreadSafeCommandsDeque* deque, std::deque<std::shared_ptr<iCommand>>* storage) : deque(deque)
{
  stateWaitForSoftStop = std::shared_ptr<cWaitForSoftStop>(new cWaitForSoftStop(this));
  stateMoveTo = std::shared_ptr<cMoveToState>(new cMoveToState(this, storage));

  state = stateWaitForSoftStop.get();

    behaviour = [](cServerThread& s)
        {
            std::shared_ptr<iCommand> cmd;
            
            try 
            {
              std::optional<std::shared_ptr<iCommand>> pcmd;
              if (true == s.deque->pop_front(cmd))
                pcmd = cmd;

              s.state->execute(pcmd);
            }
            catch (cException e)
            {
                s.handler->Handle(*cmd, e);
            }
        };

    t = std::thread(
        [](cServerThread& s)
        {
          {
            std::unique_lock<std::mutex> lock(s.m);
            s.cv.wait(lock, [&] { return s.bEnableStart; }); // Wait tille bEnableStart is false
          }

            while (s.state != nullptr )
            {
                s.behaviour(s);
            }

            s.iStop = true;
        },
        std::ref(*this)
    );
}

void cServerThread::Execute(const cCommandCounter&)
{
  iCommandCounter++;
}

void cServerThread::Execute(const cMoveToCommand& sc)
{
  state = stateMoveTo.get();
}

void cServerThread::Execute(const cRunCommand& sc)
{
  state = stateWaitForSoftStop.get();
}
