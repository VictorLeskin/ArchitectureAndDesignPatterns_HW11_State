///************************* OUTS HOMEWORK ****************************************

#include "cStopCommand.hpp"
#include "cException.hpp"
#include "cServerThread.hpp"

void cSoftStopCommand::Execute()
{
	s->Execute(*this);
}

void cHardStopCommand::Execute()
{
	s->Execute(*this);
}

void cCommandCounter::Execute()
{
	s->Execute( *this );
}

void cMoveToCommand::Execute()
{
	s->Execute(*this);
}

void cRunCommand::Execute()
{
	s->Execute(*this);
}