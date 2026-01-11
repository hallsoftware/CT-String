include(FetchContent)

FetchContent_Declare(
    doctest
    URL https://github.com/doctest/doctest/archive/v2.4.11.zip
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doctest
)

FetchContent_MakeAvailable(doctest)

file(GLOB CT_STR_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

if(CT_STR_TEST_SOURCES)
    add_executable(run_tests ${CT_STR_TEST_SOURCES})
endif()

target_compile_features(run_tests PRIVATE cxx_std_20)

target_include_directories(run_tests PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test/doctest
    ${CMAKE_SOURCE_DIR}/test/doctest/doctest
)

include(CTest)
add_test(NAME run_tests COMMAND run_tests)