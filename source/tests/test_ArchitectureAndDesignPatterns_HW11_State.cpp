///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "ArchitectureAndDesignPatterns_HW11_State.hpp"
#include "cServerThread.hpp"
#include "cCommandsDeque.hpp"
#include "cStopCommand.hpp"
#include "cState.hpp"
#include "cThreadSafeCommandsDeque.hpp"
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

// gTest grouping class
class test_cState : public ::testing::Test
{
public:
    // additional class to access to member of tested class
    class Test_cState : public cState
    {
    public:
        // add here members for free access.
        using cState::cState; // delegate constructors
    };

    // additional class to access to member of tested class
    class Test_cServerThread : public cServerThread
    {
    public:
        // add here members for free access.
        using cServerThread::cServerThread; // delegate constructors
        using cServerThread::iCommandCounter; // delegate constructors
        using cServerThread::iStop;
        using cServerThread::iSoftStop;

        using cServerThread::m;
        using cServerThread::cv;
        using cServerThread::bEnableStart;

    };
};

using test_ArchitectureAndDesignPatterns_HW11_State = test_cState;

TEST_F(test_ArchitectureAndDesignPatterns_HW11_State, test_thread_start)
{
    cThreadSafeCommandsDeque deque1;

    Test_cServerThread t1(&deque1);

    for (int i = 0; i < 10; ++i)
    {
        std::shared_ptr<iCommand> t8(new cCommandCounter(&t1));
        deque1.push_back(t8);
    }


    t1.detach();

    std::this_thread::sleep_for(1000ms);

    EXPECT_EQ(0, t1.iCommandCounter);
    EXPECT_EQ(0, t1.SleptTimeMs());

    {
        std::lock_guard<std::mutex> lock(t1.m);
        t1.bEnableStart = true;
        t1.cv.notify_one(); // ������������ � ���������� ������
    }

    std::this_thread::sleep_for(1000ms);
    EXPECT_EQ(10, t1.iCommandCounter);
    EXPECT_NEAR(1000, t1.SleptTimeMs(), 201);

    std::shared_ptr<iCommand> softStopCmd1(new cSoftStopCommand(&t1));
    deque1.push_back(softStopCmd1);
}


TEST_F(test_ArchitectureAndDesignPatterns_HW11_State, test_thread_hardStop)
{
    cThreadSafeCommandsDeque deque1;

    Test_cServerThread t1(&deque1);

    std::shared_ptr<iCommand> hardStopCmd1(new cHardStopCommand(&t1));

    for (int i = 0; i < 10; ++i)
    {
        std::shared_ptr<iCommand> t8(new cCommandCounter(&t1));
        deque1.push_back(t8);
    }
    deque1.push_back(hardStopCmd1);
    for (int i = 0; i < 10; ++i)
    {
        std::shared_ptr<iCommand> t8(new cCommandCounter(&t1));
        deque1.push_back(t8);
    }

    t1.bEnableStart = true;
    t1.join();

    EXPECT_EQ(10, t1.iCommandCounter);
    EXPECT_EQ(true, t1.iStop);
}

TEST_F(test_ArchitectureAndDesignPatterns_HW11_State, test_thread_softStop)
{
    cThreadSafeCommandsDeque deque1;

    Test_cServerThread t1(&deque1);

    std::shared_ptr<iCommand> softStopCmd1(new cSoftStopCommand(&t1));

    for (int i = 0; i < 10; ++i)
    {
        std::shared_ptr<iCommand> t8(new cCommandCounter(&t1));
        deque1.push_back(t8);
    }
    deque1.push_back(softStopCmd1);
    for (int i = 0; i < 10; ++i)
    {
        std::shared_ptr<iCommand> t8(new cCommandCounter(&t1));
        deque1.push_back(t8);
    }

    t1.bEnableStart = true;
    t1.join();

    EXPECT_EQ(20, t1.iCommandCounter);
    EXPECT_EQ(true, t1.iStop);
    EXPECT_EQ(true, t1.iSoftStop);
}

TEST_F(test_ArchitectureAndDesignPatterns_HW11_State, test_thread_MoveTo )
{
  cThreadSafeCommandsDeque deque1;
  std::deque<std::shared_ptr<iCommand>> storage;

  Test_cServerThread t1(&deque1, &storage);

  std::shared_ptr<iCommand> softStopCmd1(new cSoftStopCommand(&t1));
  std::shared_ptr <iCommand> moveToCmd1(new cMoveToCommand(&t1));
  std::shared_ptr <iCommand> runCmd1(new cRunCommand(&t1));

  for (int i = 0; i < 10; ++i)
  {
    std::shared_ptr<iCommand> t8(new cCommandCounter(&t1));
    deque1.push_back(t8);
  }
  deque1.push_back(moveToCmd1);
  for (int i = 0; i < 10; ++i)
  {
    std::shared_ptr<iCommand> t8(new cCommandCounter(&t1));
    deque1.push_back(t8);
  }

  deque1.push_back(runCmd1);
  deque1.push_back(softStopCmd1);
  for (int i = 0; i < 10; ++i)
  {
    std::shared_ptr<iCommand> t8(new cCommandCounter(&t1));
    deque1.push_back(t8);
  }

  t1.bEnableStart = true;
  t1.join();

  EXPECT_EQ(20, t1.iCommandCounter);
  EXPECT_EQ(10, storage.size() );
  EXPECT_EQ(true, t1.iStop);
  EXPECT_EQ(true, t1.iSoftStop);
}

