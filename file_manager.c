#include "file_manager.h"
Country* getcsv(Country* CountryHead, char filename[32], char opLD[16]){//trocar retorno
    FILE *fp;
    char buffer[100000];//tamanho maximo de uma linha(pode se por um define)
    int line = 0;
    int column = 0;
    char *token = NULL;
    char *aux = NULL;
    char *aux2 = NULL;

    //o ratio tem de ser float
    //verificar valores
    //maybe alocação dinamica aqui + alocação dinamica valores variáveis?
    //dar reset as variáveis em todos os ciclos??
    //check se é uma linha vazia?


    char n_week[8];
    int week_values = 0;//ter de tirar 0
    float week_ratio = 0;//ter de tirar 0
    int total = 0;//ter de tirar 0
    char country[64];
    char country_code[4];
    char continent[16]; 
    unsigned long int population = 0;//ter de tirar 0
    char cindicator[7];

   

    fp  = fopen(filename, "r");
    if (fp == NULL)  {
        printf("Erro: o ficheiro %s não consegue ser aberto\n", filename);
        exit(0);
    }
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
                //printf("%s,", country);
                break;
            case 2:
                strcpy(country_code, token);
                //printf("%s,", country_code);
                break;
            case 3:
                strcpy(continent, token);
                //printf("%s,", continent);
                break;
            case 4:
                population = atoll(token);
                //printf("%lu,", population);
                break;
            case 5:
                strcpy(cindicator, token);
                //printf("%s,", cindicator);
                break;
            case 6:
                week_values = atoi(token);
                //printf("%d,", week_values);
                break;
            case 7:
                strcpy(n_week, token);
                //printf("%s,", n_week);
                break;
            case 8:
                week_ratio = atof(token);
                //printf("%d,", week_ratio);
                break;
            case 9:
                total = atoi(token);
                //printf("%d\n", total);
                break;
            }
        }
        if(strcmp(opLD, continent)!=0 && strcmp(opLD, "all")!=0){
            week_values = 0;//ter de tirar 0
            week_ratio = 0;//ter de tirar 0
            total = 0;//ter de tirar 0
            free(aux2);//temos de reiniciar os valores todos tambem
            continue;
        }
        CountryHead = create_node(CountryHead, country, country_code, continent, population, n_week, week_values, week_ratio, total, cindicator);
        free(aux2);               
    }
    fclose(fp);
    return CountryHead;
}

//exportar tudo o que esta na lista, pela ordem que esta na lista
//por no .h
//ver caso lista vazia
//ver comodistinguir se é csv ou dat ou nenhum(recortar a string e ver o fim)

//escrever indice
//dividir por casos e mortes
void expcsv(char filename[32], Country *CountryHead){
    Country *Aux = NULL;
    Week *AuxW = NULL;
    FILE *fp = NULL;
    fp = fopen(filename, "w");
    if(fp == NULL || CountryHead == NULL){//maybe retirar countryhead
        printf("Erro: exportação de fcheiro inválida");
        exit(0);
    }
    fprintf(fp, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");
    for(Aux = CountryHead; Aux != NULL; Aux = Aux->next_country){
        //avisar po para mudar o valor do indicador quando houver seleções
        //libertar memoria quando erro
        //corrigir rints de erro

        //verificar se é preciso por o output como o stor(ou pelo menos por para testar)
        for(AuxW = Aux->week_head; AuxW != NULL; AuxW = AuxW->next_week){
            if(AuxW->indicator != 2){
                fprintf(fp,"%s,%s,%s,%lu,%s,%d,%s,%g,%d\n", Aux->country, Aux->country_code, Aux->continent, Aux->population, "cases", AuxW->week_cases, AuxW->n_week, AuxW->week_cases_ratio, AuxW->total_cases);
            }
        }
        for(AuxW = Aux->week_head; AuxW != NULL; AuxW = AuxW->next_week){
            if(AuxW->indicator != 1){
                fprintf(fp,"%s,%s,%s,%lu,%s,%d,%s,%g,%d\n", Aux->country, Aux->country_code, Aux->continent, Aux->population, "deaths", AuxW->week_deaths, AuxW->n_week, AuxW->week_deaths_ratio, AuxW->total_deaths);
            }//colocar %f para testar e %g para commits
        }               
        
    }
    fclose(fp);
    return;
}