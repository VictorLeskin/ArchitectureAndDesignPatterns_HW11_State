///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cThreadSafeDeque.hpp"

// gTest grouping class
class test_cThreadSafeDeque : public ::testing::Test
{
    using cThreadSafeDeque = TThreadSafeDeque<int>;
public:
  // additional class to access to member of tested class
  class Test_cThreadSafeDeque : public cThreadSafeDeque
  {
  public:
    // add here members for free access.
    using cThreadSafeDeque::cThreadSafeDeque; // delegate constructors
  };

};
 
TEST_F(test_cThreadSafeDeque, test_ctor )
{
  Test_cThreadSafeDeque t;
}

