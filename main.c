#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "make_list.h"

int main()
{
    Country *CountryHead = NULL;
    Country *NewCountry;
    char country[64], continent[16], country_code[3];
    unsigned long int population;

    printf("Insere o primeiro pais:\n");
    scanf("%s", country);
    scanf("%s", country_code);
    scanf("%s", continent);
    scanf("%lu", &population);

    //ja verifica se pais existe----agora é, (criar semana): procurar se pais ja existe, se sim, procurar se semana já existe, se não, adicionar nova semana
    //creat_coutry fica dentro de creat_week
    //free das semanas
    //printf("%p\n", CountryHead);
    NewCountry = create_country(CountryHead, country, country_code, continent, population);
    CountryHead = add_CEL(CountryHead, NewCountry);

    NewCountry = create_country(CountryHead, country, country_code, continent, population);
    CountryHead = add_CEL(CountryHead, NewCountry);

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

    print_countries(CountryHead);
    free_countries(CountryHead);
    return 0;
}