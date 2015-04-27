
#ifndef __TRACY__
#define __TRACY__

#include <stdint.h>

#define DEFAULT_PARAM_DAMPING_COEFF (0.7f)
#define DEFAULT_PARAM_G (60.0f)

/**
 * represents a tracking error: reference_pos - current_pos
 *
 */
struct tracking_error {
    float x_error;
    float y_error;
    float theta_error;
};

/**
 * robot velocity in polar robot coordinates
 *
 */
struct robot_velocity {
    float tangential_velocity;
    float angular_velocity;
};

/**
 * compute the linear controller output
 *
 * @param current_error error between where you want to be and where you are 
 *                      at this timestep
 * @param reference_velocity velocity you want to be at currently
 * @param output pointer to memory to store result
 *
 */
void tracy_linear_controller(const struct tracking_error * current_error,
                             const struct robot_velocity * reference_velocity,
                             struct robot_velocity * output);

/**
 * manually set parameters used by linear controller
 *
 * @param param_damping_coeff Must be between 0 and 1
 * @param param_g has to be > 0
 *
 * @return 0 on success, or something else on failure
 */
uint8_t tracy_set_controller_params(float param_damping_coeff, float param_g);

/** Converts an error struct from global frame to robot local (x and y only).
 * @param error The error structure to convert.
 * @param angle The heading of the robot, in radians.
 */
void tracy_global_error_to_local(struct tracking_error *error, float heading);

#endif
