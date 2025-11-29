cmake_minimum_required(VERSION 3.10)
project(FiguresProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<CONFIG:Debug>" "MultiThreaded$<CONFIG:Release>")
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

# === Подключение GoogleTest ===
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

# === Основная программа ===
add_executable(main src/main.cpp)

# === Тесты ===
enable_testing()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp")
    add_executable(tests tests/test.cpp)
    target_link_libraries(tests PRIVATE gtest_main)
    
    add_test(NAME FiguresTests COMMAND tests)

    add_custom_command(TARGET tests
        POST_BUILD
        COMMAND tests
        COMMENT "Running unit tests after build"
    )
else()
    message(WARNING "Test file tests/test.cpp not found. Tests will not be built.")
endif()