/*
  @file layover.c
  @brief Implements flight structure and methods
*/
#include <stdlib.h>
#include "flight.h"

static const int AMOUNT_OF_FLIGHT_VARS = 2;

Flight flight_from_file(FILE* file, char code, item_t type)
{
    Flight flight;
    flight.code = code;
    flight.type = type;

    int res = fscanf(file, EXPECTED_FLIGHT_FILE_FORMAT, &flight.hour, &flight.items_amount);
    if(res < AMOUNT_OF_FLIGHT_VARS) {
      fprintf(stderr, "Invalid file format: flight code %c", code);
      exit(EXIT_FAILURE);
    }

    return flight;
}
