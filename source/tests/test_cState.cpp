///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cState.hpp"

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

};
 
TEST_F(test_cState, test_ctor )
{
  Test_cState t(nullptr);
}

