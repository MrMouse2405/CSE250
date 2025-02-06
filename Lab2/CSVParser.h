#pragma once

#include <string>
#include <iostream>

/**
 * @file CSVParser.h
 * @brief Utility class for parsing CSV files.
 *
 * This file contains the definition of the CSVParser class, which is used to parse
 * lines of CSV data into individual words or doubles.
 */

#define DELIMETER "," ///< The delimiter used to separate values in the CSV file.

namespace Lab2
{
    /**
     * @class CSVParser
     * @brief A utility class for parsing lines of CSV data.
     *
     * This class consumes a line of CSV data and provides methods to extract individual
     * words or doubles from the line based on the specified delimiter.
     */
    class CSVParser
    {
    public:
        /**
         * @brief Constructs a new CSVParser object.
         *
         * @param source The CSV line to be parsed.
         */
        CSVParser(std::string source) : source(source) {}

        /**
         * @brief Extracts the next word from the CSV line.
         *
         * This method extracts the next word from the CSV line, starting from the current
         * cursor position, and updates the cursor position to the next delimiter.
         *
         * @return std::string The extracted word.
         */
        std::string getWord()
        {
            std::size_t found = source.find(DELIMETER, index);
            std::string result;
            if (found != std::string::npos)
            {
                result = source.substr(index, found - index);
                index = found + 1;
            }
            else
            {
                result = source.substr(index, source.length() - index);
            }

            return result;
        }

        /**
         * @brief Extracts the next double from the CSV line.
         *
         * This method extracts the next word from the CSV line and converts it to a double.
         *
         * @return double The extracted double value.
         */
        double getDouble()
        {
            return std::stod(this->getWord());
        }

    private:
        mutable std::string source; ///< The CSV line to be parsed.
        std::size_t index = 0;      ///< The current cursor position in the CSV line.
    };
}