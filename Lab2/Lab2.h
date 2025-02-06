#include <memory>

#include "FlightData.h"
#include "CSVParser.h"
#include "List.h"

using Lab2::CSVParser;
using Lab2::FlightData;
using Lab2::List;

// Data File
#define FILE_NAME "Flights10_Winter2025.dat"
// #define FILE_NAME "FlightsAll_Winter2025.dat"

typedef List<FlightData *> FlightsList;
typedef void (*SortFunction)(std::shared_ptr<FlightsList>);