#include "file_manager.h"
/** \brief Função que abre um ficheiro .csv e cria a lista relativa aos dados desse ficheiro
 *
 * \param CountryHead Country* - Ponteiro para o primeiro país
 * \param filename[32] char - Nome do ficheiro .csv
 * \param opLD[16] char - Opção de leitura de dados
 * \return Country* - Retorna o ponteiro para o primeiro país
 *
 */
Country* getcsv(Country* CountryHead, char filename[32], char opLD[16]){
    FILE *fp;
    char buffer[100000];
    int line = 0;
    int column = 0;
    char *token = NULL;
    char *aux = NULL;
    char *aux2 = NULL;
    char n_week[8];
    int week_values = 0;
    float week_ratio = 0;
    int total = 0;
    char country[64];
    char country_code[4];
    char continent[16];
    unsigned long int population = 0;
    char cindicator[7];

    // Abre o ficheior em modo de leitura e verifica se houve algum erro ao abri-lo
    fp  = fopen(filename, "r");
    if (fp == NULL)  {
        fprintf(stderr, "-1 Erro de Ficheiro: o ficheiro %s não consegue ser aberto\n", filename);
        exit(0);
    }
    // Lê as varias linhas, ignorando a primeira
    while(fgets(buffer, 1000, fp) != NULL){
        line++;
        column = 0;
        if(line == 1){
            continue;
        }
        aux = strdup(buffer);
        aux2 = aux;
        while((token = strsep(&aux, ",")) != NULL){
            column++;
            switch (column)
            {
            case 1:
                strcpy(country, token);
                break;
            case 2:
                strcpy(country_code, token);
                break;
            case 3:
                strcpy(continent, token);
                break;
            case 4:
                population = atoll(token);
                break;
            case 5:
                strcpy(cindicator, token);
                break;
            case 6:
                week_values = atoi(token);
                break;
            case 7:
                strcpy(n_week, token);
                break;
            case 8:
                week_ratio = atof(token);
                break;
            case 9:
                total = atoi(token);
                break;
            }
        }
        // Verifica as opções de leitura de dados
        if(strcmp(opLD, continent)!=0 && strcmp(opLD, "all")!=0){
            week_values = 0;
            week_ratio = 0;
            total = 0;
            free(aux2);
            continue;
        }
        CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_values, week_ratio, total, cindicator);
        free(aux2);
    }
    fclose(fp);
    return CountryHead;
}


/** \brief Função que abre um ficheiro .csv e exporta a lista para esse ficheiro
 *
 * \param CountryHead Country* - Ponteiro para o primeiro país
 * \param filename[32] char - Nome do ficheiro .csv
 *
 */
void expcsv(char filename[32], Country *CountryHead){
    Country *Aux = NULL;
    Week *AuxW = NULL;
    FILE *fp = NULL;

    // Abre o ficheior em modo de escrita e verifica se houve algum erro ao abri-lo
    fp = fopen(filename, "w");
    if(fp == NULL){
        fprintf(stderr, "-1 Erro de Ficheiro: não é possivel exportar para o ficheiro %s\n", filename);
        free_nodes(CountryHead);
        exit(0);
    }

    // Escreve a primeira linha
    fprintf(fp, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");
    for(Aux = CountryHead; Aux != NULL; Aux = Aux->next_country){
        for(AuxW = Aux->week_head; AuxW != NULL; AuxW = AuxW->next_week){
            if(AuxW->indicator != 2){
                fprintf(fp,"%s,%s,%s,%lu,%s,%d,%s,%g,%d\n", Aux->country, Aux->country_code, Aux->continent, Aux->population, "cases", AuxW->week_cases, AuxW->n_week, AuxW->week_cases_ratio, AuxW->total_cases);
            }
        }
        for(AuxW = Aux->week_head; AuxW != NULL; AuxW = AuxW->next_week){
            if(AuxW->indicator != 1){
                fprintf(fp,"%s,%s,%s,%lu,%s,%d,%s,%g,%d\n", Aux->country, Aux->country_code, Aux->continent, Aux->population, "deaths", AuxW->week_deaths, AuxW->n_week, AuxW->week_deaths_ratio, AuxW->total_deaths);
            }
        }

    }
    fclose(fp);
    return;
}

/** \brief Função que abre um ficheiro .dat e cria a lista relativa aos dados desse ficheiro
 *
 * \param CountryHead Country* - Ponteiro para o primeiro país
 * \param filename[32] char - Nome do ficheiro .dat
 * \param opLD[16] char - Opção de leitura de dados
 * \return Country* - Retorna o ponteiro para o primeiro país
 *
 */
Country* getdat(Country* CountryHead, char filename[32], char opLD[16]){
    FILE *fp = NULL;
    Country *NewCountry = NULL;
    Country *PAux = NULL;
    Week *WeekHead = NULL;
    Week *NewWeek = NULL;
    Week *AuxW = NULL;
    int number;
    int aux;

    // Abre o ficheior em modo de leitura em binario e verifica se houve algum erro ao abri-lo
    fp = fopen(filename, "rb");
    if((NewCountry = (Country*)calloc(1, sizeof(Country)))==NULL){
            fprintf(stderr, "-1 Erro de Alocação: não foi possivel alocar o bloco de memória.[getdat]\n");
            exit(0);
        }
    // Lê o primeiro pais
    fread(NewCountry, sizeof(Country), 1, fp);
    do{
        if(CountryHead == NULL){
            CountryHead = NewCountry;
            PAux = CountryHead;
            // Lê o número de semanas que irão haver
            fread(&number, sizeof(int), 1, fp);
            // Lê as semanas
            for(aux = number; aux != 0; aux--){
                if((NewWeek = (Week*)calloc(1, sizeof(Week)))==NULL){
                        fprintf(stderr, "-1 Erro de Alocação: não foi possivel alocar o bloco de memória.[getdat]\n");
                        free_nodes(CountryHead);
                        exit(0);
                }
                fread(NewWeek, sizeof(Week), 1, fp);
                if(WeekHead == NULL){
                    WeekHead = NewWeek;
                    AuxW = WeekHead;
                    PAux->week_head = WeekHead;
                    continue;
                }
                AuxW->next_week = NewWeek;
                AuxW = NewWeek;
            }
            WeekHead = NULL;
            if((NewCountry = (Country*)calloc(1, sizeof(Country)))==NULL){
                fprintf(stderr, "-1 Erro de Alocação: não foi possivel alocar o bloco de memória.[getdat]\n");
                free_nodes(CountryHead);
                exit(0);
            }
            continue;
        }
        PAux->next_country = NewCountry;
        PAux = NewCountry;
        fread(&number, sizeof(int), 1, fp);
        for(aux = number; aux != 0; aux--){
                if((NewWeek = (Week*)calloc(1, sizeof(Week)))==NULL){
                        fprintf(stderr, "-1 Erro de Alocação: não foi possivel alocar o bloco de memória.[getdat]\n");
                        free_nodes(CountryHead);
                        exit(0);
                }
                fread(NewWeek, sizeof(Week), 1, fp);
                if(WeekHead == NULL){
                    WeekHead = NewWeek;
                    AuxW = WeekHead;
                    NewCountry->week_head = WeekHead;
                    continue;
                }
                AuxW->next_week = NewWeek;
                AuxW = NewWeek;
        }
        WeekHead = NULL;
        if((NewCountry = (Country*)calloc(1, sizeof(Country)))==NULL){
            fprintf(stderr, "-1 Erro de Alocação: não foi possivel alocar o bloco de memória.[getdat]\n");
            free_nodes(CountryHead);
            exit(0);
        }
    }while(fread(NewCountry, sizeof(Country), 1, fp) == 1);// Verifica se já leu todos os países
    free(NewCountry);
    fclose(fp);
    return CountryHead;
}

/** \brief Função que abre um ficheiro .dat e exporta a lista para esse ficheiro
 *
 * \param CountryHead Country* - Ponteiro para o primeiro país
 * \param filename[32] char - Nome do ficheiro .dat
 *
 */
void expdat(char filename[32], Country *CountryHead){
    FILE *fp = NULL;
    Country *Aux = NULL;
    Week *AuxW = NULL;
    int number = 0;

    fp = fopen(filename, "wb");
    for(Aux = CountryHead; Aux != NULL; Aux = Aux->next_country){
        // Escreve um pais
        fwrite(Aux, sizeof(Country), 1, fp);
        // Conta o numero de semanas que o país tem
        for(AuxW = Aux->week_head; AuxW != NULL; AuxW =AuxW->next_week){
            number++;
        }
        // Escreve um int com o numero de semanas a escrever(para ser mais facil ler)
        fwrite(&number, sizeof(int), 1, fp);
        number = 0;
        // Escreve as semanas no ficheiro
        for(AuxW = Aux->week_head; AuxW != NULL; AuxW =AuxW->next_week){
            fwrite(AuxW, sizeof(Week), 1, fp);
        }
    }
    fclose(fp);
    return;
}
