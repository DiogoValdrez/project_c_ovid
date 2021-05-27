#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include "make_list.h"
#include "file_manager.h"
#include "sort.h"
#include "restrict.h"
#include "select.h"

#define LISTA_OPCOES "-:L:S:D:P:i:o:"

/** \Pandemia
 * \Autores: Diogo Valdrez 99914, Pedro Raposo 100059
 *
 * \Descrição:  Projeto Pandemia
 * \            Realizado como projeto final para a UC Programação
 *
 */

int main(int argc, char *argv[])
{

    Country *CountryHead = NULL;
    int helper;
	int opt;
    //Variáveis que verificam se as opções foram ou não ativadas
    int opt_L = 0, opt_S = 0, opt_D = 0, opt_P = 0, opt_i = 0, opt_o = 0;
    char read_data[24] = "all";
    char sort_type[8] = "alfa", sort_week[8] = "";
    char select_data[12];
    char restrict_data_type[8], restrict_data_week[8], restrict_data_interval_week[8];
    char file_read[24];
    char file_write[24];
	opterr = 0;

	while((opt = getopt(argc, argv, LISTA_OPCOES)) != -1)
	{
	  switch (opt)
      {
        case 'L':
            strcpy(read_data, optarg);
            if (strcmp(read_data, "all") && strcmp(read_data, "Africa") && strcmp(read_data, "Oceania") && strcmp(read_data, "Europe") && strcmp(read_data, "America") && strcmp(read_data, "Asia"))
            {
                fprintf(stderr, "-1 Erro de Argumento: argumento para opção -L incorreto\n");
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
                fprintf(stderr, "-1 Erro de Argumento: argumento para opção -S incorreto\n");
                return EXIT_FAILURE;
            }
            opt_S = 1;
            break;
        case 'D':
            strcpy(select_data, argv[optind-1]);
            if (strcmp(select_data, "inf") && strcmp(select_data, "dea") && strcmp(select_data, "racioinf") && strcmp(select_data, "raciodea"))
            {
                fprintf(stderr, "-1 Erro de Argumento: argumento para opção -D incorreto\n");
                return EXIT_FAILURE;
            }
            opt_D = 1;
            break;
        case 'P':
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
                fprintf(stderr, "-1 Erro de Argumento: argumento para opção -P incorreto\n");
                return EXIT_FAILURE;
            }
            opt_P = 1;
            break;
        case 'i':
            strcpy(file_read, optarg);
            opt_i = 1;
            break;
        case 'o':
            strcpy(file_write, optarg);
            opt_o = 1;
            break;
        case '?':
            if (isprint (optopt))
            fprintf(stderr, "-1 Erro de Argumento: opcao '-%c' desconhecida.\n", optopt);
            return EXIT_FAILURE;
      }
    }

    //Verificação das opções
    if (opt_i == 0 || opt_o == 0 || (opt_L == 0 && opt_S == 0 && opt_D == 0 && opt_P == 0 && opt_i == 0 && opt_o == 0))
    {
        printf("Opções Obrigatórias:\n\t-i: Opção de Leitura de Dados de Ficheiro\n\t-o: Opção de Escrita de Dados em Ficheiro\n");
        printf("Opções Não Obrigatórias:\n\t-L: Opção de Leitura de Dados\n\t-S: Opção de Ordenação de Dados\n\t");
        printf("-D: Opção de Seleção de Dados\n\t-P: Opção de Restrição de Dados\n");
        return EXIT_FAILURE;
    }

    char *last4i = &file_read[strlen(file_read)-4];
    char *last4o = &file_write[strlen(file_write)-4];

    //Leitura de dados de um ficheiro
    if(strncmp(last4i, ".csv", -4) == 0){
        CountryHead = getcsv(CountryHead, file_read, read_data);
    }else if(strncmp(last4i, ".dat", -4) == 0){
        CountryHead = getdat(CountryHead, file_read, read_data);
    }else{
        fprintf(stderr, "-1 Erro de Leitura: o ficheiro de leitura tem de ser .dat ou.csv\n");
        exit(0);
    }

    //Realizar caso as opções tenham sido acionadas
    if (opt_D == 1)
    {
        select_d(CountryHead, select_data);
    }
    if (opt_P == 1)
    {
        CountryHead = do_restrict(CountryHead, restrict_data_type, restrict_data_week, restrict_data_interval_week);
    }

    sort(&CountryHead, sort_type, sort_week);

    //Escrita de dados num ficheiro
    if(strncmp(last4o, ".csv", -4) == 0){
        expcsv(file_write, CountryHead);
    }else if(strncmp(last4o, ".dat", -4) == 0){
        expdat(file_write, CountryHead);
    }else{
        fprintf(stderr, "-1 Erro de Leitura: o ficheiro exportado tem de ser .dat ou.csv\n");
        exit(0);
    }

    print_nodes(CountryHead);
    free_nodes(CountryHead);
    return 0;
}
