#Setup CMake to run tests
enable_testing()

#Prep ourselves for compiling boost

include_directories (${STTProject_SOURCE_DIR}/src)
file(GLOB TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#Run through each source
#foreach(testSrc ${TEST_SRCS})
        #Extract the filename without an extension (NAME_WE)
        #get_filename_component(testName ${testSrc} NAME_WE)

        #Add compile target
        add_executable(test_main ${TEST_SRCS} test_main.cpp)

        #link to Boost libraries AND your targets and dependencies
        target_link_libraries(test_main ${STTProject_LIBRARIES})

        #I like to move testing binaries into a testBin directory
        set_target_properties(test_main PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

        #Finally add it to test execution - 
        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME test_main 
                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin 
                 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/test_main )
#endforeach(testSrc)
