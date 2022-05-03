/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 2;

Flight flight_from_file(FILE* file, char code, unsigned int arrival_hour)
{
    Flight flight;
    flight.code = code;
    flight.hour = arrival_hour;

    int res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT, &flight.type, &flight.items_amount);
    if(res != AMOUNT_OF_FLIGHT_VARS) {
      fprintf(stderr, "Invalid flight format. Code: %c", code);
    }


    return flight;
}
