#include "weather.h"
#include "array_helpers.h"

int min_min_temp(WeatherTable a) {
  int min;
  for (unsigned int year = 0; year < YEARS; year++) {
    for (t_month month = january; month <= december; ++month) {
      for(unsigned int day = 0u; day < DAYS; ++day){
        // Take the first and then compare it with the rest
        if(month==january && day==0){
          min = a[year][month][day]._min_temp;
        } else {
          // Update min if necessary
          if(min > a[year][month][day]._min_temp){
            min = a[year][month][day]._min_temp;
          }
        }
      }
    }
  }

  return min;
}

int max_temp_for_year(WeatherTable a, int year){
  int max;
  for (t_month month = january; month <= december; ++month) {
    for(unsigned int day = 0u; day < DAYS; ++day){
      // Take the first and then compare it with the rest
      if(month==january && day==0){
        max = a[year][month][day]._max_temp;
      } else {
        // Update max if necessary
        if(max < a[year][month][day]._max_temp){
          max = a[year][month][day]._max_temp;
        }
      }
    }
  }

  return max;
}


void max_per_year(WeatherTable a, int output[YEARS]) {
  for (unsigned int year = 0; year < YEARS; year++) {
    output[year] = max_temp_for_year(a, year);
  }
}

unsigned int total_rainfall_for_month(WeatherTable a, int year, t_month month) {
  unsigned int sum = 0u;
  for(unsigned int day=0; day<DAYS; ++day){
    sum += a[year][month][day]._rainfall;
  }
  return sum;
}

t_month month_of_max_rainfall_for_year(WeatherTable a, int year){
  unsigned int max;
  t_month max_month;
  for (t_month month = january; month <= december; ++month) {
      
    unsigned int total_rainfall = total_rainfall_for_month(a, year, month);

    // Take the first and then compare it with the rest
    if(month==january){
      max = total_rainfall;
      max_month = month;
    } else {
      // Update max if necessary
      if(max < total_rainfall){
        max = total_rainfall;
        max_month = month;
      }
    }
  }

  return max_month;
}

void month_of_max_rainfall_per_year(WeatherTable a, t_month output[YEARS]) {
  for (unsigned int year = 0; year < YEARS; year++) {
    output[year] = month_of_max_rainfall_for_year(a, year);
  }
}
