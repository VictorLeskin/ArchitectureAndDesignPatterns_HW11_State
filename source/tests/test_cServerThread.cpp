///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cServerThread.hpp"

// gTest grouping class
class test_cServerThread : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cServerThread : public cServerThread
  {
  public:
    // add here members for free access.
    using cServerThread::cServerThread; // delegate constructors
  };

};
 
TEST_F(test_cServerThread, test_ctor )
{
  //Test_cServerThread t(nullptr);
}

