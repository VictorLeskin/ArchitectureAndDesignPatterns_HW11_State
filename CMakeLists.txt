cmake_minimum_required(VERSION 3.14)
project(ArchitectureAndDesignPatterns_HW11_State)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
  State

  source/ArchitectureAndDesignPatterns_HW11_State.cpp
  source/ArchitectureAndDesignPatterns_HW11_State.hpp
  source/cCommandsDeque.cpp
  source/cCommandsDeque.hpp
  source/cException.cpp
  source/cException.hpp
  source/cExceptionsHandler.cpp
  source/cExceptionsHandler.hpp
  source/cServerThread.cpp
  source/cServerThread.hpp
  source/cStopCommand.cpp
  source/cStopCommand.hpp
  source/iCommand.cpp
  source/iCommand.hpp
  source/cState.hpp
  source/cState.cpp
  source/cThreadSafeDeque.hpp
  source/cThreadSafeDeque.cpp
  source/cThreadSafeCommandsDeque.hpp
  source/cThreadSafeCommandsDeque.cpp
#add source file here
  source/tests/test_ArchitectureAndDesignPatterns_HW11_State.cpp
  source/tests/test_cCommandsDeque.cpp
  source/tests/test_cExceptionsHandler.cpp
  source/tests/test_cServerThread.cpp
  source/tests/test_cStopCommand.cpp
  source/tests/test_iCommand.cpp
  source/tests/test_cState.cpp
  source/tests/test_cThreadSafeDeque.cpp
  source/tests/test_cThreadSafeCommandsDeque.cpp
#add test file here
)

target_include_directories(
   State PRIVATE 
   source
)

target_link_libraries(
  State
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest GoogleMock)
gtest_discover_tests(State)