/**
 *
 *
 *
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <optional>

#include "FlightData.h"
#include "CSVParser.h"
#include "List.h"

#define FILE_NAME "FlightsAll_Winter2025.dat" //"Flights10_Winter2025.dat"

/**
 *
 * readCSVFile
 *
 * Reads input from csv file and populates data
 * array with values. Returns number of rows
 * read from the file.
 *
 * @param csv_file, std::ifstream&, input file to read from
 * @param data, Lab1::List<Lab1::FlightData>, array to populate values into.
 */
void readCSVFile(std::ifstream &CSVFile, Lab1::List<struct Lab1::FlightData> &data)
{
    std::string line;
    for (int i = 0; std::getline(CSVFile, line); i++)
    {
        Lab1::CSVParser parser(line);
        data.add({/* departure: */ parser.getWord(),
                  /* arrival:   */ parser.getWord(),
                  /* code:      */ parser.getWord(),
                  /* cost:      */ parser.getDouble()});
    }
}

std::size_t findCheapestFlight(Lab1::List<Lab1::FlightData> &data)
{
    std::size_t cheapest = 0;
    for (std::size_t i = 1; i < data.getSize(); i++)
    {
        if (data[cheapest].cost > data[i].cost)
        {
            cheapest = i;
        }
    }
    return cheapest;
}

std::size_t getFlightsForCity(Lab1::List<Lab1::FlightData> &data, std::string cityName)
{
    std::size_t count = 0;
    for (std::size_t i = 0; i < data.getSize(); i++)
    {
        if (!data[i].arrival.compare(cityName) || !data[i].departure.compare(cityName))
        {
            count += 1;
        }
    }
    return count;
}

void sortFlights(Lab1::List<Lab1::FlightData> &data)
{
    using std::size_t;
    const size_t len = data.getSize();
    for (size_t i = 0; i < len - 1; i++)
    {
        size_t min_idx = i;
        for (size_t j = i + 1; j < len; j++)
        {
            if (data[j].code.compare(data[min_idx].code) < 0)
            {
                min_idx = j;
            }
        }

        if (i != min_idx)
        {
            Lab1::FlightData temp = data[i];
            data[i] = data[min_idx];
            data[min_idx] = temp;
        }
    }
}

std::optional<double> calculateAverageDepartureFlightsForCity(Lab1::List<Lab1::FlightData> &data, std::string cityName)
{
    double count = 0;
    double sum = 0;
    for (std::size_t i = 0; i < data.getSize(); i++)
    {
        if (!data[i].departure.compare(cityName))
        {
            count += 1;
            sum += data[i].cost;
        }
    }

    if (count == 0)
    {
        return std::optional<double>();
    }

    return std::optional<double>(sum / count);
}

int main()
{
    auto flightsList = Lab1::List<struct Lab1::FlightData>();

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
        std::cout << "Flight #" << flightsList[i].code << " from " << flightsList[i].departure << " to " << flightsList[i].arrival << " costs " << flightsList[i].cost << "$\n";
    }

    std::cout << "The last 5 flights are: \n";
    for (size_t i = flightsList.getSize() - 5; i < flightsList.getSize(); i++)
    {
        std::cout << "Flight #" << flightsList[i].code << " from " << flightsList[i].departure << " to " << flightsList[i].arrival << " costs " << flightsList[i].cost << "$\n";
    }

    std::cout << std::endl;

    /*

       Question 2

     */
    std::size_t indexOfCheapestFlight = findCheapestFlight(flightsList);
    std::cout << "The cheapest flight is ";
    std::cout << "Flight #" << flightsList[indexOfCheapestFlight].code << " from " << flightsList[indexOfCheapestFlight].departure << " to " << flightsList[indexOfCheapestFlight].arrival << " costs " << flightsList[indexOfCheapestFlight].cost << "$\n";
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
        std::optional<double> avg = calculateAverageDepartureFlightsForCity(flightsList, city);
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
        std::cout << "Flight #" << flightsList[i].code << " from " << flightsList[i].departure << " to " << flightsList[i].arrival << " costs " << flightsList[i].cost << "$\n";
    }

    std::cout << "The last 10 flights are: \n";
    for (size_t i = flightsList.getSize() - 10; i < flightsList.getSize(); i++)
    {
        std::cout << "Flight #" << flightsList[i].code << " from " << flightsList[i].departure << " to " << flightsList[i].arrival << " costs " << flightsList[i].cost << "$\n";
    }

    std::cout << std::endl;

    return 0;
}