#pragma once

#include <string>

#pragma once

#include <string>

/**
 * @file FlightData.h
 * @brief Defines the FlightData structure for storing flight information.
 *
 * This file contains the definition of the FlightData structure, which represents
 * a row of flight data including departure city, arrival city, flight code, and cost.
 */

namespace Lab2
{
    /**
     * @struct FlightData
     * @brief Represents a row of flight data.
     *
     * This structure stores information about a flight, including the departure city,
     * arrival city, flight code, and cost.
     */
    struct FlightData
    {
        std::string departure; ///< The name of the departure city.
        std::string arrival;   ///< The name of the arrival city.
        std::string code;      ///< The flight code.
        double cost;           ///< The cost of the flight.
    };
}