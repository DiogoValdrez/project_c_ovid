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
    int i;
    char *token = NULL;
    char *aux = NULL;
    char *aux2 = NULL;
    char n_week[8];
    char n_helper[8] = "\0";
    int n_help;
    int week_values = 0;
    char week_value_char[20];
    float week_ratio = 0;
    char week_ratio_char[20];
    int total = 0;
    char total_char[20];
    char country[64];
    char country_code[4];
    char continent[16];
    unsigned long int population = 0;
    char population_char[20];
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
                strcpy(population_char, token);
                break;
            case 5:
                strcpy(cindicator, token);
                break;
            case 6:
                strcpy(week_value_char, token);
                break;
            case 7:
                strcpy(n_week, token);
                break;
            case 8:
                strcpy(week_ratio_char, token);
                week_ratio = atof(token);
                break;
            case 9:
                strcpy(total_char, token);
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

        //Verificar os dados lidos
        //Nome do país
        i = 0;
        while (country[i] != '\0')
        {
            if((country[i] < 65 && country[i] != 32 )|| country[i] >122 || (country[i] < 97 && country[i] > 90))
            {
                free_nodes(CountryHead);
                fprintf(stderr, "-1 Erro de Leitura: dados na coluna 1 incompativeis\n");
                fclose(fp);
                free(aux2);
                exit(0);
            }
            i++;
        }
        //Código do País
        i = 0;
        while (country_code[i] != '\0')
        {
            if(country_code[i] < 65 || country_code[i] > 90)
            {
                free_nodes(CountryHead);
                fprintf(stderr, "-1 Erro de Leitura: dados na coluna 2 incompativeis\n");
                fclose(fp);
                free(aux2);
                exit(0);
            }
            i++;
        }
        //Caso o código do país tenha mais de 3 letras
        if (i > 3)
        {
            free_nodes(CountryHead);
            fprintf(stderr, "-1 Erro de Leitura: dados na coluna 2 incompativeis\n");
            fclose(fp);
            free(aux2);
            exit(0);
        }
        //Continente
        if (strcmp(continent, "Africa") && strcmp(continent, "Oceania") && strcmp(continent, "Europe") && strcmp(continent, "America") && strcmp(continent, "Asia"))
        {
            free_nodes(CountryHead);
            fprintf(stderr, "-1 Erro de Leitura: dados na coluna 3 incompativeis\n");
            fclose(fp);
            free(aux2);
            exit(0);
        }
        //Population
        i = 0;
        while (population_char[i] != '\0')
        {
            if(isdigit(population_char[i]) == 0)
            {
                free_nodes(CountryHead);
                fprintf(stderr, "-1 Erro de Leitura: dados na coluna 4 incompativeis\n");
                fclose(fp);
                free(aux2);
                exit(0);
            }
            i++;
        }
        population = atoll(population_char);
        if (population < 0)
        {
            free_nodes(CountryHead);
            fprintf(stderr, "-1 Erro de Leitura: dados na coluna 4 incompativeis\n");
            fclose(fp);
            free(aux2);
            exit(0);
        }
        //Indicator
        if (strcmp(cindicator, "cases") && strcmp(cindicator, "deaths"))
        {
            free_nodes(CountryHead);
            fprintf(stderr, "-1 Erro de Leitura: dados na coluna 5 incompativeis\n");
            fclose(fp);
            free(aux2);
            exit(0);
        }

        //N_week
        if (n_week[4] != '-')
        {
            free_nodes(CountryHead);
            fprintf(stderr, "-1 Erro de Leitura: dados na coluna 7 incompativeis\n");
            fclose(fp);
            free(aux2);
            exit(0);
        }
        i = 0;
        while (n_week[i] != '\0')
        {
            if(isdigit(n_week[i]) == 0 && i != 4)
            {
                free_nodes(CountryHead);
                fprintf(stderr, "-1 Erro de Leitura: dados na coluna 7 incompativeis\n");
                fclose(fp);
                free(aux2);
                exit(0);
            }
            i++;
        }
        n_helper[0] = n_week[5];
        n_helper[1] = n_week[6];
        n_help = atoi(n_helper);
        if (n_help > 53)
        {
            free_nodes(CountryHead);
            fprintf(stderr, "-1 Erro de Leitura: dados na coluna 7 incompativeis\n");
            fclose(fp);
            free(aux2);
            exit(0);
        }
        //Week_values
        i = 0;
        while (week_value_char[i] != '\0')
        {
            if(isdigit(week_value_char[i]) == 0)
            {
                free_nodes(CountryHead);
                fprintf(stderr, "-1 Erro de Leitura: dados na coluna 6 incompativeis\n");
                fclose(fp);
                free(aux2);
                exit(0);
            }
            i++;
        }
        week_values = atoi(week_value_char);
        if (week_values < 0)
        {
            free_nodes(CountryHead);
            fprintf(stderr, "-1 Erro de Leitura: dados na coluna 6 incompativeis\n");
            fclose(fp);
            free(aux2);
            exit(0);
        }
        //Total
        i = 0;
        while (total_char[i] != '\0')
        {
            if((total_char[i] < 48 || total_char[i] > 57 ) && total_char[i] != 13 && total_char[i] != 10)
            {
                free_nodes(CountryHead);
                fprintf(stderr, "-1 Erro de Leitura: dados na coluna 9 incompativeis\n");
                fclose(fp);
                free(aux2);
                exit(0);
            }
            i++;
        }
        total = atoi(total_char);
        if (total < 0)
        {
            free_nodes(CountryHead);
            fprintf(stderr, "-1 Erro de Leitura: dados na coluna 9 incompativeis\n");
            fclose(fp);
            free(aux2);
            exit(0);
        }
        //week_ratio
         i = 0;
        while (week_ratio_char[i] != '\0')
        {
            if(isdigit(week_ratio_char[i]) == 0 && week_ratio_char[i] != '.')
            {
                free_nodes(CountryHead);
                fprintf(stderr, "-1 Erro de Leitura: dados na coluna 8 incompativeis\n");
                fclose(fp);
                free(aux2);
                exit(0);
            }
            i++;
        }
        if (week_ratio < 0)
        {
            free_nodes(CountryHead);
            fprintf(stderr, "-1 Erro de Leitura: dados na coluna 8 incompativeis\n");
            fclose(fp);
            free(aux2);
            exit(0);
        }



        free(aux2);
        CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_values, week_ratio, total, cindicator, fp);
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
                        fclose(fp);
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
                fclose(fp);
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
                        fclose(fp);
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
            fclose(fp);
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
