#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "make_list.h"

int main()
{
    Country *CountryHead = NULL;
    
    char country[64] = "Portugal", continent[16] = "Euro", country_code[4] = "POR";
    unsigned long int population = 10000000;
    char n_week[8] = "2020-10";
    int week_cases = 10, week_cases_ratio = 0,  total_cases = 12;
    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_cases, week_cases_ratio, total_cases, "cases");

    strcpy(n_week, "2020-13");//pode haver verificação se é numero valido
    week_cases = 10;
    week_cases_ratio = 0; 
    total_cases = 12;//pode vaer aqui uma verificação se é maior que os casos da semana
    int week_deaths = 11, week_deaths_ratio = 1, total_deaths = 13;

    /*printf("Insere o primeiro pais:\n");
    scanf("%s", country);
    scanf("%s", country_code);
    scanf("%s", continent);
    scanf("%lu", &population);*/
    //tem de se fazer dados de semana default, para n ficar com dados anteriores
    //atenção ao tamanho das strings
    //atenção que o valgrind queixa se que estamos a ir a valores não inicializados a seguir a cada print dos nodes

    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_cases, week_cases_ratio, total_cases, "cases");
    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_deaths, week_deaths_ratio, total_deaths, "deaths");

    strcpy(n_week, "2020-11");
    week_cases = 10; 
    week_cases_ratio = 3; 
    total_cases = 12;
    week_deaths = 11;
    week_deaths_ratio = 1;
    total_deaths = 13;
    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_cases, week_cases_ratio, total_cases, "cases");
    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_deaths, week_deaths_ratio, total_deaths, "deaths");

    strcpy(country, "Espanha");
    strcpy(continent, "Euro");
    strcpy(country_code, "Esp");
    population = 11000000;
    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_cases, week_cases_ratio, total_cases, "cases");
    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_deaths, week_deaths_ratio, total_deaths, "deaths");



    //printf("%p\n", CountryHead);

    print_nodes(CountryHead);
    free_nodes(CountryHead);
    return 0;
}