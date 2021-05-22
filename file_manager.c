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


    char n_week[8];
    int week_values = 0;//ter de tirar 0
    int week_ratio = 0;//ter de tirar 0
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
                printf("%s,", country);
                break;
            case 2:
                strcpy(country_code, token);
                printf("%s,", country_code);
                break;
            case 3:
                strcpy(continent, token);
                printf("%s,", continent);
                break;
            case 4:
                population = atoll(token);
                printf("%lu,", population);
                break;
            case 5:
                strcpy(cindicator, token);
                printf("%s,", cindicator);
                break;
            case 6:
                week_values = atoi(token);
                printf("%d,", week_values);
                break;
            case 7:
                strcpy(n_week, token);
                printf("%s,", n_week);
                break;
            case 8:
                week_ratio = atoi(token);
                printf("%d,", week_ratio);
                break;
            case 9:
                total = atoi(token);
                printf("%d\n", total);
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