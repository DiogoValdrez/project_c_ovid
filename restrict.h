#ifndef RESTRICT_HPP
#define RESTRICT_HPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "make_list.h"

Country *do_restrict(Country *CountryHead, char restrict_data_type[8], char restrict_data_week[8], char restrict_data_interval_week[8]);
int compare_dates(char date1[8], char date2[8]);

#endif