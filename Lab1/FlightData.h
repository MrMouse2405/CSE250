#pragma once

#include <string>

/**
 *
 * Row structure for Flight Data
 *
 */

namespace Lab1
{
    struct FlightData
    {
        // departure city name
        std::string departure;
        // arrival city name
        std::string arrival;
        // flight code
        std::string code;
        // flight cost
        double cost;
    };
}