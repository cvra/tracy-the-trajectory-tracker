
#include "CppUTest/TestHarness.h"
#include <cmath>

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

TEST_GROUP(ErrorTransformationTest)
{

};

TEST(ErrorTransformationTest, ErrorCanBeTransformed)
{
    struct tracking_error err;
    err.x_error = 1.;
    err.y_error = 0.;

    tracy_global_error_to_local(&err, M_PI_2);
    DOUBLES_EQUAL(0., err.x_error, 1e-3);
    DOUBLES_EQUAL(-1., err.y_error, 1e-3);
}

