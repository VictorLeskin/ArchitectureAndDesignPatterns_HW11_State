///************************* OUTS HOMEWORK ****************************************
#ifndef CTHREADSAFECOMMANDSDEQUE_HPP
#define CTHREADSAFECOMMANDSDEQUE_HPP

#include "cThreadSafeDeque.hpp"
class iCommand;

class cThreadSafeCommandsDeque : public TThreadSafeDeque<std::shared_ptr<iCommand>>
{
public:
};

#endif //#ifndef CTHREADSAFECOMMANDSDEQUE_HPP
