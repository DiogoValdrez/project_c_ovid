#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP
#define _SVID_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "make_list.h"

Country* getcsv(Country* CountryHead, char filename[32], char opLD[16]);


#endif