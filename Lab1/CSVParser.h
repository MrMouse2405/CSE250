#pragma once

#include <string>
#include <iostream>

/**
 *
 * CSV Parser
 *
 * Utility class for parsing CSV Files
 *
 */

#define DELIMETER ","

namespace Lab1
{

    /**
     *
     * CSV Parser
     *
     * This class consumes a line of CSV,
     * and returns substrings of original
     * string as parsed by the parser.
     *
     */
    class CSVParser
    {
    public:
        /**
         *
         * CSVParser()
         *
         * @param source: string to consume
         *
         */
        CSVParser(std::string source) : source(source) {}

        /**
         *
         * getWord()
         *
         * @returns std::string, parsed "word" from csv line
         *
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
         *
         * getDouble()
         *
         * @returns double, parsed "double" from csv line
         *
         */
        double getDouble()
        {
            return std::stod(this->getWord());
        }

    private:
        // string source
        mutable std::string source;
        // index of cursor
        std::size_t index = 0;
    };
}