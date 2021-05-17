#ifndef LIST_STRUCT_HPP
#define LIST_STRUCT_HPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct week
{
    char n_week[8];
    int week_cases;
    int week_cases_ratio;
    int total_cases;
    int week_deaths;
    int week_deaths_ratio;
    int total_deaths;
    struct week *next_week;
}WEEK;


typedef struct country
{
    char name[32];
    char continent[16];
    char acronym[4];
    int population;
    WEEK *week_head;
    struct country *next_country;
}Country;


WEEK *addweek(WEEK *week_head, char n_week_ar[8], char indicator[8],  int week_numbers, int week_ratio, int total_numbers);
Country *addcountry(Country *head, char name[32], char continent[16], char acronym[4], int population );


#endif