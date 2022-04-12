#ifndef WEATHER_UTILS1
#define WEATHER_UTILS1
#include "weather.h"
#include "array_helpers.h"


// Menor temperatura minima registrada en todos los datos
int min_min_temp(WeatherTable a);

// Max temp per year in the given table
void max_per_year(WeatherTable a, int output[YEARS]);

// Month of max rainfall per year in the given table
void month_of_max_rainfall_per_year(WeatherTable a, t_month output[YEARS]);
#endif
