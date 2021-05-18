#ifndef MAKE_LIST_HPP
#define MAKE_LIST_HPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//adicionar addCBL
typedef struct Week//corrigir nomes
{
    char n_week[8];
    int week_cases;
    int week_cases_ratio;
    int total_cases;
    int week_deaths;
    int week_deaths_ratio;
    int total_deaths;
    struct Week *next_week;
}Week;


typedef struct Country
{
    char country[64];
    char country_code[4];
    char continent[16]; 
    unsigned long int population;
    Week *week_head;
    struct Country *next_country;
}Country;


//Week *addWeek(Week *week_head, char n_week_arg[8], char indicator[8],  int week_numbers, int week_ratio, int total_numbers);
Country *create_country(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population);
Country *add_CEL(Country *CountryHead, Country *NewCountry);
//Country *switch_countries(Country *Country1, Country *Country2);//returns list head
Country *look_for_country(char country[64], Country *CountryHead);

void print_countries(Country *CountryHead);
void free_countries(Country *CountryHead);


#endif