///************************* OUTS HOMEWORK ****************************************
#ifndef CSTATE_HPP
#define CSTATE_HPP

#include <optional>
#include <memory>
#include <deque>

class cServerThread;
class iCommand;

class cState // interface class of states
{
public:
  virtual ~cState() = default;

  cState(cServerThread* s) : s(s) {}
  virtual void execute( std::optional<std::shared_ptr<iCommand>> &cmd) {}

 protected:
   cServerThread* s;
};

class cWaitForSoftStop : public cState
{
public:
  cWaitForSoftStop(cServerThread* s) : cState(s) {}

  void execute(std::optional<std::shared_ptr<iCommand>>& cmd) override;
};

class cMoveToState : public cState
{
public:
  cMoveToState(cServerThread* s, std::deque<std::shared_ptr<iCommand>>* storage) : cState(s), storage(storage) {}

  void execute(std::optional<std::shared_ptr<iCommand>>& cmd) override;

  protected:
    std::deque<std::shared_ptr<iCommand>>* storage;
};




#endif //#ifndef CSTATE_HPP
