///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "VerticalScalingAndSynchronization.hpp"
#include "cServerThread.hpp"
#include "cCommandsDeque.hpp"
#include "cStopCommand.hpp"
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

// gTest grouping class
class test_VerticalScalingAndSynchronization : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_VerticalScalingAndSynchronization : public VerticalScalingAndSynchronization
  {
  public:
    // add here members for free access.
    using VerticalScalingAndSynchronization::VerticalScalingAndSynchronization; // delegate constructors
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
 

TEST_F(test_VerticalScalingAndSynchronization, test_thread_start)
{
  cThreadSafeCommandsDeque deque1;

  Test_cServerThread t1(&deque1);

  for (int i = 0; i < 10; ++i)
  {
    std::unique_ptr<iCommand> t8(new cCommandCounter(&t1));
    deque1.push_back(t8);
  }
  

  t1.detach();

  std::this_thread::sleep_for(1000ms);

  EXPECT_EQ(0, t1.iCommandCounter);
  EXPECT_EQ(0, t1.SleptTimeMs());

  {
    std::lock_guard<std::mutex> lock(t1.m);
    t1.bEnableStart = true;
    t1.cv.notify_one(); // Сигнализация о готовности данных
  }
  
  std::this_thread::sleep_for(1000ms);
  EXPECT_EQ(10, t1.iCommandCounter);
  EXPECT_NEAR(1000, t1.SleptTimeMs(), 201 );

  std::unique_ptr<iCommand> softStopCmd1(new cSoftStopCommand(&t1));
  deque1.push_back(softStopCmd1);
}


TEST_F(test_VerticalScalingAndSynchronization, test_thread_hardStop)
{
  cThreadSafeCommandsDeque deque1;

  Test_cServerThread t1(&deque1);
  
  std::unique_ptr<iCommand> hardStopCmd1(new cHardStopCommand(&t1));

  for( int i = 0; i < 10; ++i )
  {
    std::unique_ptr<iCommand> t8(new cCommandCounter(&t1));
    deque1.push_back(t8);
  }
  deque1.push_back(hardStopCmd1);
  for (int i = 0; i < 10; ++i)
  {
    std::unique_ptr<iCommand> t8(new cCommandCounter(&t1));
    deque1.push_back(t8);
  }

  t1.bEnableStart = true;
  t1.join();

 EXPECT_EQ(10, t1.iCommandCounter );
  EXPECT_EQ(true, t1.iStop);
}

TEST_F(test_VerticalScalingAndSynchronization, test_thread_softStop)
{
  cThreadSafeCommandsDeque deque1;

  Test_cServerThread t1(&deque1);

  std::unique_ptr<iCommand> softStopCmd1(new cSoftStopCommand(&t1));

  for (int i = 0; i < 10; ++i)
  {
    std::unique_ptr<iCommand> t8(new cCommandCounter(&t1));
    deque1.push_back(t8);
  }
  deque1.push_back(softStopCmd1);
  for (int i = 0; i < 10; ++i)
  {
    std::unique_ptr<iCommand> t8(new cCommandCounter(&t1));
    deque1.push_back(t8);
  }

  t1.bEnableStart = true;
  t1.join();

  EXPECT_EQ(20, t1.iCommandCounter);
  EXPECT_EQ(true, t1.iStop);
  EXPECT_EQ(true, t1.iSoftStop);
}
