#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <optional>

#include "FlightData.h"
#include "CSVParser.h"
#include "List.h"

using Lab1::CSVParser;
using Lab1::FlightData;
using Lab1::List;

/**
 *
 * CSE250 Lab1 Part 2
 * Author: OCdt Syed
 * Professor Rivest
 *
 * This file contains the code for Lab 1 Part 2 for aggregating the
 * flight data.
 */

// Data File
#define FILE_NAME "FlightsAll_Winter2025.dat" //"Flights10_Winter2025.dat"

/**
 *
 * readCSVFile
 *
 * @brief Reads input from csv file and populates data
 * array with values. Returns number of rows
 * read from the file.
 *
 * @param csv_file, std::ifstream&, input file to read from
 * @param data,  List< FlightData>, array to populate values into.
 */
void readCSVFile(std::ifstream &CSVFile, List<struct FlightData *> &data)
{
    std::string line;
    for (int i = 0; std::getline(CSVFile, line); i++)
    {
        CSVParser parser(line);
        data.add(new FlightData{
            /* departure: */ parser.getWord(),
            /* arrival:   */ parser.getWord(),
            /* code:      */ parser.getWord(),
            /* cost:      */ parser.getDouble()});
    }
}

/**
 *
 * findCheapestFlight
 *
 * Finds the cheapest flight from the list
 * and returns it.
 *
 * @param data,  List< FlightData>, array read values from.
 * @return  FlightData*, pointer to the cheapest flight
 */
FlightData *findCheapestFlight(List<FlightData *> &data)
{
    std::size_t cheapest = 0;
    for (std::size_t i = 1; i < data.getSize(); i++)
    {
        if (data[cheapest]->cost > data[i]->cost)
        {
            cheapest = i;
        }
    }
    return data[cheapest];
}

/**
 *
 * getFlightsForCity
 *
 * Gets the count for # of flights leaving the city.
 *
 * @param data,  List< FlightData>, aarray to read values from.
 * @return std::size_t, # of flights leaving the city.
 */
std::size_t getFlightsForCity(List<FlightData *> &data, std::string cityName)
{
    std::size_t count = 0;
    for (std::size_t i = 0; i < data.getSize(); i++)
    {
        if (!data[i]->arrival.compare(cityName) || !data[i]->departure.compare(cityName))
        {
            count += 1;
        }
    }
    return count;
}

/**
 *
 * calculateAverageDepartureCostForCity
 *
 * Computes the average flight cost for flights leaving the city.
 *
 * optional value will be empty IF there are no flights leaving the city.
 *
 * @param data,  List< FlightData>, aarray to read values from.
 * @return std::optional<double>, calculated average or absent value.
 */
std::optional<double> calculateAverageDepartureCostForCity(List<FlightData *> &data, std::string cityName)
{
    double count = 0;
    double sum = 0;
    for (std::size_t i = 0; i < data.getSize(); i++)
    {
        if (!data[i]->departure.compare(cityName))
        {
            count += 1;
            sum += data[i]->cost;
        }
    }

    if (count == 0)
    {
        return std::optional<double>();
    }

    return std::optional<double>(sum / count);
}

/**
 *
 * sortFlights
 *
 * uses selection sort to sort the flights lexicographically by the flight code.
 *
 * @param data,  List< FlightData>, array to sort values in.
 */
void sortFlights(List<FlightData *> &data)
{
    using std::size_t;
    const size_t len = data.getSize();
    for (size_t i = 0; i < len - 1; i++)
    {
        size_t min_idx = i;
        for (size_t j = i + 1; j < len; j++)
        {
            if (data[j]->code.compare(data[min_idx]->code) < 0)
            {
                min_idx = j;
            }
        }

        if (i != min_idx)
        {
            FlightData *temp = data[i];
            data[i] = data[min_idx];
            data[min_idx] = temp;
        }
    }
}

int main()
{
    auto flightsList = List<struct FlightData *>();

    // Open file, read data, close it.
    std::ifstream dataFile(FILE_NAME);
    if (!dataFile.is_open())
    {
        std::cout << "Failed to open file!" << std::endl;
        return -1;
    }
    readCSVFile(dataFile, flightsList);
    dataFile.close();

    /*

       Question 1

     */
    std::cout << flightsList.getSize() << " Flights Loaded.\n";

    std::cout << "The first 5 flights are: \n";
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << "Flight #" << flightsList[i]->code << " from " << flightsList[i]->departure << " to " << flightsList[i]->arrival << " costs " << flightsList[i]->cost << "$\n";
    }

    std::cout << "The last 5 flights are: \n";
    for (size_t i = flightsList.getSize() - 5; i < flightsList.getSize(); i++)
    {
        std::cout << "Flight #" << flightsList[i]->code << " from " << flightsList[i]->departure << " to " << flightsList[i]->arrival << " costs " << flightsList[i]->cost << "$\n";
    }

    std::cout << std::endl;

    /*

       Question 2

     */
    FlightData *cheapestFlight = findCheapestFlight(flightsList);
    std::cout << "The cheapest flight is ";
    std::cout << "Flight #" << cheapestFlight->code << " from " << cheapestFlight->departure << " to " << cheapestFlight->arrival << " costs " << cheapestFlight->cost << "$\n";
    std::cout << std::endl;

    /*

       Question 3

     */
    for (std::string city : {"Jacksonville", "Liverpool", "Amsterdam", "Kingston"})
    {
        std::size_t flightCount = getFlightsForCity(flightsList, city);
        std::string text;
        switch (flightCount)
        {
        case 0:
            text = "is no flights";
            break;
        case 1:
            text = "is 1 flight";
            break;
        default:
            text = "are " + std::to_string(flightCount) + " flights";
            break;
        }
        std::cout << "There " + text + " arriving or leaving from " + city << '\n';
    }
    std::cout << std::endl;

    /*

       Question 4

     */
    for (std::string city : {"Liverpool", "Jacksonville", "Kingston"})
    {
        std::optional<double> avg = calculateAverageDepartureCostForCity(flightsList, city);
        if (avg.has_value())
        {
            std::cout << "The average price to leave " << city << " is " << avg.value() << "$\n";
        }
        else
        {
            std::cout << "There is no flight leaving " << city << "\n";
        }
    }
    std::cout << std::endl;

    /*

       Question 5

     */
    sortFlights(flightsList);

    std::cout << "The first 10 flights are: \n";
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << "Flight #" << flightsList[i]->code << " from " << flightsList[i]->departure << " to " << flightsList[i]->arrival << " costs " << flightsList[i]->cost << "$\n";
    }

    std::cout << "The last 10 flights are: \n";
    for (size_t i = flightsList.getSize() - 10; i < flightsList.getSize(); i++)
    {
        std::cout << "Flight #" << flightsList[i]->code << " from " << flightsList[i]->departure << " to " << flightsList[i]->arrival << " costs " << flightsList[i]->cost << "$\n";
    }

    std::cout << std::endl;

    return 0;
}