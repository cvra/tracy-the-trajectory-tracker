
#include "CppUTest/TestHarness.h"

extern "C" {
#include "../src/trajectory_tracking.h"
}

TEST_GROUP(FaultyInput)
{
    void setup(void)
    {

    }

    void teardown(void)
    {

    }
};

TEST(FaultyInput, SetInvalidParams)
{
    CHECK(tracy_set_controller_params(0.6, -1.0f) != 0);
    CHECK(tracy_set_controller_params(0.6, 0.0f) != 0);
}

