/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last entry in flight table
* @return True when is the last entry of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(LayoverTable a) {
  for (unsigned int hour = 0u; hour < HOURS; ++hour) {
    for (unsigned int type = 0u; type < TYPE; ++type) {
      Flight f = a[hour][type];
      fprintf(stdout, "%c: %s at %u:00 with %u passengers", f.code, f.type == 0 ? "arrives" : "departs", f.hour - 1, f.passengers_amount);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int passengers_amount_in_airport (LayoverTable a, unsigned int h) {
  unsigned int sum = 0;

  for(unsigned int i=0; i<HOURS; i++) {
    // If it's a previous hour, we add the passengers who arrived
    if(i+1 < h) {
      sum += a[i][arrival].passengers_amount;
    }
    // If it's the current hour, we add the passengers who arrived AND the ones about to leave
    else if(i+1 == h) {
      sum += a[i][arrival].passengers_amount;
      sum += a[i][departure].passengers_amount;
    }
  }

  return sum;
}


void array_from_file(LayoverTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  rewind(file);
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i=0;
  while (i < HOURS && !feof(file)) {
    int res = fscanf(file, "_%c_", &code);
    if (res != 1) {
      printf("last code: %c, res: %d\n", code, res);
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }

    // Assign flights for current hour
    array[i][arrival] = flight_from_file(file, code);
    array[i][departure] = flight_from_file(file, code);
    fscanf(file, "\n");
    i++;
  }
  fclose(file);
}
