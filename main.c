#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "make_list.h"

int main()
{
    Country *CountryHead = NULL;
    
    char country[64], continent[16], country_code[3];
    unsigned long int population;

    char n_week[8] = "2020-13";
    int week_cases = 10, week_cases_ratio = 0,  total_cases = 12;//pode vaer aqui uma verificação se é maior que os casos da semana
    int week_deaths = 11, week_deaths_ratio = 1, total_deaths = 13;

    printf("Insere o primeiro pais:\n");
    scanf("%s", country);
    scanf("%s", country_code);
    scanf("%s", continent);
    scanf("%lu", &population);

    //atenção ao tamanho das strings
    //Testar
    //atenção que o valgrind queixa se que estamos a ir a valores não inicializados a seguir a cada print dos nodes

    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_cases, week_cases_ratio, total_cases, "cases");
    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_deaths, week_deaths_ratio, total_deaths, "deaths");
    //printf("%p\n", CountryHead);
    /*printf("Insere o segundo pais:\n");

    scanf("%s", country);
    scanf("%s", country_code);
    scanf("%s", continent);
    scanf("%lu", &population);

    NewCountry = create_country(country, country_code, continent, population);
    CountryHead = add_CEL(CountryHead, NewCountry);

    printf("Insere o terceiro pais, que vai para o inicio:\n");

    scanf("%s", country);
    scanf("%s", country_code);
    scanf("%s", continent);
    scanf("%lu", &population);

    NewCountry = create_country(country, country_code, continent, population);
    CountryHead = add_CEL(CountryHead, NewCountry);
    //CountryHead = switch_countries(NewCountry, NewCountry3);*/

    print_nodes(CountryHead);
    free_nodes(CountryHead);
    return 0;
}