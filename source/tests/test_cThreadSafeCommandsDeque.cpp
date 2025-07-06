///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cThreadSafeCommandsDeque.hpp"

// gTest grouping class
class test_cThreadSafeCommandsDeque : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cThreadSafeCommandsDeque : public cThreadSafeCommandsDeque
  {
  public:
    // add here members for free access.
    using cThreadSafeCommandsDeque::cThreadSafeCommandsDeque; // delegate constructors
  };

};
 
TEST_F(test_cThreadSafeCommandsDeque, test_ctor )
{
  Test_cThreadSafeCommandsDeque t;
}

