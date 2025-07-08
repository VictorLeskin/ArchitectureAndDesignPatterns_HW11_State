///************************* OUTS HOMEWORK ****************************************

#include "cState.hpp"
#include "cServerThread.hpp"
#include "iCommand.hpp"

#include<optional>
#include<memory>

#include "cThreadSafeCommandsDeque.hpp"
#include <cStopCommand.hpp>

void cWaitForSoftStop::execute(std::optional<std::shared_ptr<iCommand>>& cmd)
{
  if (cmd.has_value() )
    cmd.value()->Execute();
  else  // deque is empty
  {
    if (false == s->iSoftStop)
      s->sleep();
    else
      s->state = nullptr;
  }
}

void cMoveToState::execute(std::optional<std::shared_ptr<iCommand>>& cmd)
{
  const static cRunCommand rc(nullptr); // out of mode command name

  if (cmd.has_value())
  {
    auto& c = cmd.value();
    if (std::string(rc.Type()) == c->Type())
    {
      c->Execute();
      return;
    }
    if( nullptr != storage )
      storage->push_back(c);
  }
  else
    s->sleep(); // do nothing
}

