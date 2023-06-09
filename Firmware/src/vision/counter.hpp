#ifndef COUNTER_H
#define COUNTER_H

#include "esp_camera.h"
#include "vision.hpp"
#include "FS.h"               
#include "SD_MMC.h"         

// Error codes
#define NO_ERROR 1
#define ERROR_NOT_CALIBRATED -1
#define ERROR_CAPTURE_FAILED -2
#define ERROR_MALLOC_FAILED -2
#define ERROR_MEMCPY_FAILED -3
#define ERROR_DETECTION_FAILED -4
#define ERROR_CAMERA_FAIL -5
#define ERROR_SD_FAIL -6

// The class
class counter
{
private:
    int difference_threshold;
    int people_threshold;
    uint8_t* base_buffer = NULL;
    uint16_t* compare_buffer = NULL;
    vision* detection;
    framesize_t resolution;
    fs::FS &fs = SD_MMC; 
public:
    /// @brief Constructor of counter
    counter(int width, int heigth, framesize_t resolution);

    /// @brief Begin starts the camera for measurements
    /// @return An error code or no error
    int begin();

    /// @brief Calibrate makes a base photo for the counter
    /// @param difference_threshold The minium difference needed
    /// @param people_threshold The minium blob size needed for human
    /// @return An error code or no error.
    int calibrate(int difference_threshold, int people_threshold);

    /// @brief Counts the people in the room
    /// @return The count result or one of the error codes
    int count();
};

#endif