///************************* OUTS HOMEWORK ****************************************
#ifndef CSTOPCOMMAND_HPP
#define CSTOPCOMMAND_HPP

#include "iCommand.hpp"
#include <typeinfo>
#include <deque>
#include <memory>

class cServerThread;

// stop after deque empty
class cSoftStopCommand : public iCommand
{
public:
	cSoftStopCommand(cServerThread* s) : s(s) {}

	void Execute() override;

	const char* Type() const override { return typeid(*this).name(); }

protected:
	cServerThread* s;
};

// stop after execution of this command
class cHardStopCommand : public iCommand
{
public:
	cHardStopCommand(cServerThread* s) : s(s) {}

	void Execute() override;

	const char* Type() const override { return typeid(*this).name(); }

protected:
	cServerThread* s;
};

// stop after execution of this command
class cMoveToCommand : public iCommand
{
	friend class cServerThread;
public:
	cMoveToCommand(cServerThread* s) : s(s) {}

	void Execute() override;

	const char* Type() const override { return typeid(*this).name(); }

protected:
	cServerThread* s;
};

// stop after execution of this command
class cRunCommand : public iCommand
{
	friend class cServerThread;
public:
	cRunCommand(cServerThread* s) : s(s) {}

	void Execute() override;

	const char* Type() const override { return typeid(*this).name(); }

protected:
	cServerThread* s;
};


// stop after execution of this command
class cCommandCounter : public iCommand
{
public:
	cCommandCounter(cServerThread* s) : s(s) {}

	void Execute() override;

	const char* Type() const override { return typeid(*this).name(); }

protected:
	cServerThread* s;
};




#endif //#ifndef CSTOPCOMMAND_HPP
