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
    int indicator;
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

Country *create_node(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population, char n_week[8],int week_values,int week_ratio,int total, char cindicator[7]);
Week *create_week(Country *Country,char n_week[8],int week_values,int week_ratio,int total, char cindicator[7]);
Country *create_country(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population);
Country *add_CEL(Country *CountryHead, Country *NewCountry);
Week *add_WEL(Country *Country, Week *NewWeek);
//Country *switch_countries(Country *Country1, Country *Country2);//returns list head
Country *look_for_country(char country[64], Country *CountryHead);
Week *look_for_week(Country *Country, char n_week[8]);

void print_nodes(Country *CountryHead);
void free_nodes(Country *CountryHead);


#endif