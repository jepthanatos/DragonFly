set(BINARY ${CMAKE_PROJECT_NAME}_test)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})

add_executable(${BINARY} ${SOURCES})

target_include_directories(${BINARY} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(${BINARY} ${CMAKE_PROJECT_NAME}_lib sfml-system sfml-window sfml-graphics GTest::gtest_main spdlog::spdlog)

include(GoogleTest)
gtest_discover_tests(${BINARY})