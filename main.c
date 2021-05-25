#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include "make_list.h"
#include "file_manager.h"

#define LISTA_OPCOES "-:L:S:D:P:i:o:"

int main(int argc, char *argv[])
{
    int helper;
	int opt;
    //Variables to check whether or not the options were inputted
    int opt_L = 0, opt_S = 0, opt_D = 0, opt_P = 0, opt_i = 0, opt_o = 0;
    char *read_data;
    char sort_type[8], sort_week[8];
    char select_data[12];
    char restrict_data_type[8], restrict_data_week[8], restrict_data_interval_week[8];
    char *file_read;
    char *file_write;
    //FALTAM OS DEFAULTS
	opterr = 0;
	
	while((opt = getopt(argc, argv, LISTA_OPCOES)) != -1)  
	{
	  switch (opt)
      {
        case 'L': 
            read_data = optarg;
            if (strcmp(read_data, "all") && strcmp(read_data, "Africa") && strcmp(read_data, "Oceania") && strcmp(read_data, "Europe") && strcmp(read_data, "America") && strcmp(read_data, "Asia"))
            {
                printf("Argumento para opção -L incorreto\n");
                return EXIT_FAILURE;
            }
            opt_L = 1;
            break;
        case 'S':  
            optind--;
            helper = 0;
            for(;optind < argc && *argv[optind] != '-'; optind++)
            {
                if (helper == 0)
                {
                    strcpy(sort_type, argv[optind]);
                }
                if (helper == 1)
                {
                    strcpy(sort_week, argv[optind]);
                }
                helper++;
            }
            if (strcmp(sort_type, "alfa") && strcmp(sort_type, "pop") && strcmp(sort_type, "inf") && strcmp(sort_type, "dea"))
            {
                printf("Argumento para opção -S incorreto\n");
                return EXIT_FAILURE;
            }
            opt_S = 1;
            break;
        case 'D':
            strcpy(select_data, argv[optind-1]);
            if (strcmp(select_data, "inf") && strcmp(select_data, "dea") && strcmp(select_data, "racioinf") && strcmp(select_data, "raciodea"))
            {
                printf("Argumento para opção -D incorreto\n");
                return EXIT_FAILURE;
            }
            opt_D = 1;
            break;
        case 'P': // opção com argumentos obrigatórios
            optind--;
            helper = 0;
            for(;optind < argc && *argv[optind] != '-'; optind++)
            {
                if (helper == 0)
                {
                    strcpy(restrict_data_type, argv[optind]);
                }
                if (helper == 1)
                {
                    strcpy(restrict_data_week, argv[optind]);
                }
                if (helper == 2)
                {
                    strcpy(restrict_data_interval_week, argv[optind]);
                }
                helper++;
            }
            if (strcmp(restrict_data_type, "min") && strcmp(restrict_data_type, "max") && strcmp(restrict_data_type, "date") && strcmp(restrict_data_type, "dates"))
            {
                printf("Argumento para opção -P incorreto\n");
                return EXIT_FAILURE;
            }
            opt_P = 1;
            break;
        case 'i': 
            file_read = optarg;
            opt_i = 1;
            break;
        case 'o':  
            file_write = optarg;
            opt_o = 1;
            break;
        case '?':
            if (isprint (optopt))
            fprintf (stderr, "> opcao `-%c' desconhecida.\n", optopt);
            return EXIT_FAILURE;
      }
    }

    if (opt_i == 0 || opt_o == 0 || (opt_L == 0 && opt_S == 0 && opt_D == 0 && opt_P == 0 && opt_i == 0 && opt_o == 0))
    {
        printf("Opções Obrigatórias:\n\t-i: Opção de Leitura de Dados de Ficheiro\n\t-o: Opção de Escrita de Dados em Ficheiro\n");
        printf("Opções Não Obrigatórias:\n\t-L: Opção de Leitura de Dados\n\t-S: Opção de Ordenação de Dados\n\t");
        printf("-D: Opção de Seleção de Dados\n\t-P: Opção de Restrição de Dados\n");
        return EXIT_FAILURE;
    }



    Country *CountryHead = NULL;
    /*char country[64] = "Portugal", continent[16] = "Euro", country_code[4] = "POR";
    unsigned long int population = 10000000;
    char n_week[8] = "2020-10";
    int week_cases = 10, week_cases_ratio = 0,  total_cases = 12;
    CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_cases, week_cases_ratio, total_cases, "cases");

    strcpy(n_week, "2020-13");//pode haver verificação se é numero valido
    week_cases = 10;
    week_cases_ratio = 0; 
    total_cases = 12;//pode vaer aqui uma verificação se é maior que os casos da semana
    int week_deaths = 11, week_deaths_ratio = 1, total_deaths = 13;*/

    /*printf("Insere o primeiro pais:\n");
    scanf("%s", country);
    scanf("%s", country_code);
    scanf("%s", continent);
    scanf("%lu", &population);*/
    //tem de se fazer dados de semana default, para n ficar com dados anteriores
    //atenção ao tamanho das strings
    //atenção que o valgrind queixa se que estamos a ir a valores não inicializados a seguir a cada print dos nodes

    /*CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_cases, week_cases_ratio, total_cases, "cases");
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
*/
    CountryHead = getdat(CountryHead, file_read, read_data);
    print_nodes(CountryHead);
    expcsv(file_write, CountryHead);
    free_nodes(CountryHead);
    return 0;
}