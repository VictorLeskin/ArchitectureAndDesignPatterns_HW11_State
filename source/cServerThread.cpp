///************************* OUTS HOMEWORK ****************************************

#include "cServerThread.hpp"
#include "cCommandsDeque.hpp"
#include "cExceptionsHandler.hpp"
#include "cException.hpp"
#include "cThreadSafeCommandsDeque.hpp"

#include <thread>
#include <chrono>

using namespace std::chrono_literals;

cServerThread::cServerThread(cThreadSafeCommandsDeque* deque) : deque(deque)
{
    behaviour = [](cServerThread& s)
        {
            std::shared_ptr<iCommand> cmd;
            
            try 
            {
                if( true == s.deque->pop_front(cmd) )
                  cmd->Execute();

                if (true == s.deque->empty())
                {
                  if (false == s.iSoftStop)
                  {
                    std::this_thread::sleep_for(200ms);
                    s.sleepTimeMs += 200;
                  }
                  else
                    s.iStop = true;
                }
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

            while (!s.iStop)
            {
                s.behaviour(s);
            }
        },
        std::ref(*this)
    );
}

void cServerThread::Execute(const cCommandCounter&)
{
  iCommandCounter++;
}
