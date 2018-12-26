#include "spdlog/spdlog.h"
#include <iostream>
#include <CppUTest/TestHarness.h>

TEST_GROUP(spdlog_test)
{
    void setup() {
        MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    }
    void teardown() {
        MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
    }
};
TEST(spdlog_test, logging_test)
{
    try {
        auto console = spdlog::stdout_logger_mt("console");
        console->info("Welcome to spdlog!");
        console->info("An info message example {} ..", 1);

        auto my_logger = spdlog::basic_logger_mt("basic_logger", "basic.txt");
        my_logger->info("Some log message");
        console->flush();
        spdlog::drop_all();
    }

    catch (const spdlog::spdlog_ex& ex) {

        FAIL("Log init failed");
    }
}
