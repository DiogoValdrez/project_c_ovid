#ifndef MAKE_LIST_HPP
#define MAKE_LIST_HPP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Week
{
    float week_cases_ratio;
    float week_deaths_ratio;
    int week_cases;
    int total_cases;
    int week_deaths;
    int total_deaths;
    int indicator;
    char n_week[8];
    struct Week *next_week;
}Week;


typedef struct Country
{
    unsigned long int population;
    char country[64];
    char country_code[4];
    char continent[16]; 
    Week *week_head;
    struct Country *next_country;
}Country;

Country *create_node(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population, char n_week[8],int week_values,float week_ratio,int total, char cindicator[7]);
Week *create_week(Country *Country,char n_week[8],int week_values,float week_ratio,int total, char cindicator[7]);
Country *create_country(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population);
Country *add_CEL(Country *CountryHead, Country *NewCountry);
Week *add_WEL(Country *Country, Week *NewWeek);
Country *look_for_country(char country[64], Country *CountryHead);
Week *look_for_week(Country *Country, char n_week[8]);

Country *remove_country(Country *CountryHead, Country *WantRemoved);
Week *remove_week(Country *Country, Week *WantRemoved);

void print_nodes(Country *CountryHead);
void free_nodes(Country *CountryHead);
void remove_country_weeks(Week* Week_head);


#endif