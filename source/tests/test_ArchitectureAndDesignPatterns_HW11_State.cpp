///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "ArchitectureAndDesignPatterns_HW11_State.hpp"

// gTest grouping class
class test_ArchitectureAndDesignPatterns_HW11_State : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_ArchitectureAndDesignPatterns_HW11_State : public ArchitectureAndDesignPatterns_HW11_State
  {
  public:
    // add here members for free access.
    using ArchitectureAndDesignPatterns_HW11_State::ArchitectureAndDesignPatterns_HW11_State; // delegate constructors
  };

};
 
TEST_F(test_ArchitectureAndDesignPatterns_HW11_State, test_ctor )
{
  Test_ArchitectureAndDesignPatterns_HW11_State t;
}

