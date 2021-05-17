#include <stdlib.h>
#include <stdio.h>
#include "list_struct.h"

int main()
{
    Country *head = NULL;
    char name[32] = "name";
    char continent[16] = "cont";
    char acronym[4] = "fra";
    int population = 4534455;
    char n_week_ar[8] = "2012-01";
    /*int week_cases = 10;
    int week_cases_ratio = 9;
    int total_cases = 20;
    int week_deaths = 5;
    int week_deaths_ratio = 4;
    int total_deaths = 12;*/
    char indicator[8] = "cases";
    int week_numbers = 15;
    int week_ratio = 12;
    int total_numbers = 30;

    //scanf("%s", name);
    //scanf("%s", continent);
    //scanf("%s", acronym);
    //scanf("%d", &population);
    head = addcountry(head, name, continent, acronym, population );
    /*printf("Name: %s\n", head->name);
    printf("Continent: %s\n", head->continent);
    printf("Acron: %s\n", head->acronym);
    printf("Pop: %d\n", head->population);*/
    
    head->week_head = addweek(head->week_head,n_week_ar,indicator,week_numbers, week_ratio, total_numbers );
    
    strcpy(indicator, "deaths");
   
    //printf("%d", head->week_head->total_cases);
    //printf("%s\n", head->week_head->n_week);
    head->week_head = addweek(head->week_head,n_week_ar,indicator,week_numbers, week_ratio, total_numbers );
    printf("F:%d", strcmp(head->week_head->n_week, n_week_ar));
    strcpy(n_week_ar, "2012-05");
    head->week_head = addweek(head->week_head,n_week_ar,indicator,week_numbers, week_ratio, total_numbers );
    //strcpy(n_week_ar, "2012-08");
    head->week_head = addweek(head->week_head,n_week_ar,indicator,week_numbers, week_ratio, total_numbers );
    
    do
    {
        printf("%s", head->week_head->n_week);
        printf("Total cases: %d\n", head->week_head->total_cases);
        printf("Total deaths: %d\n", head->week_head->total_deaths);
        head->week_head = head->week_head->next_week;
    } while (head->week_head != NULL);
    
    //printf("Total cases: %d\n", head->week_head->total_cases);
    //printf("Total deaths: %d\n", head->week_head->total_deaths);
    //head->week_head = head->week_head->next_week;
    //printf("Total cases: %d\n", head->week_head->total_cases);
    //printf("Total deaths: %d\n", head->week_head->total_deaths);
    
    //head->week_head = head->week_head->next_week;
    return 0;
}