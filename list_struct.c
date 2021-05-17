#include "list_struct.h"

WEEK *addweek(WEEK *week_head, char n_week_ar[8], char indicator[8],  int week_numbers, int week_ratio, int total_numbers)
{
    WEEK *temp;
    WEEK *new_week;
    int help = 0, aux = 0;
    temp = week_head;
    
    if (temp != NULL)
    {
        printf("S:%d",strcmp(week_head->n_week, n_week_ar) );
        do{
            aux = 1;
            printf("%d",strcmp(temp->n_week, n_week_ar) );
            if(strcmp(temp->n_week, n_week_ar) == 0)
            {
                printf("hi");
                help = 1;
                break;
            }
            if (temp->next_week != NULL)
            {
                temp = temp->next_week;
            }
        }while (temp->next_week !=NULL);
        
        
    }
    
    if (help == 0)
    {
        new_week = (WEEK*)malloc(sizeof(WEEK));
        if (aux == 1)
        {
            temp->next_week = new_week;

        }else if (aux == 0)
        {
            week_head = new_week;
        }
        
    }
    //printf("%d", strcmp(temp->n_week, n_week_ar));
    strcpy(new_week->n_week, n_week_ar);
    if (strcmp(week_head->n_week, n_week_ar) == 0)
    {
        printf("ola");
    }
    
    if (strcmp(indicator, "cases") == 0)
    {
        new_week->week_cases = week_numbers;
        new_week->week_cases_ratio = week_ratio;
        new_week->total_cases = total_numbers;
    }
    if (strcmp(indicator, "deaths") == 0)
    {
        new_week->week_deaths = week_numbers;
        new_week->week_deaths_ratio = week_ratio;
        new_week->total_deaths = total_numbers;
    }
    new_week->next_week = NULL;

    printf("%d%d\n", aux, help);
    if (help == 0 && aux == 0){
        week_head = new_week;
    }
    return week_head;

    



    /*if (week_head == NULL)
    {
        printf("hi");
    }
    /*if (week_head == NULL)//If it is the first week
    {
        new_week = (WEEK*)malloc(sizeof(WEEK));
        week_head = new_week;
        temp = week_head;
        
    }else{
        temp = week_head;
        do
        {
            
            if(strcmp(temp->n_week, n_week_ar) != 0)
            {
                printf("hi");
                break;
            } 
            temp = temp->next_week;
        }while (temp != NULL);
        if (temp == NULL) 
        {
            new_week = (WEEK*)malloc(sizeof(WEEK));
            temp = new_week;
             while (aux->next_week != NULL)    
        {
            aux = aux->next_week;
        }
        aux->next_week = new_week;
        }
        
        
    } 

    if (strcmp(indicator, "cases") == 0)
    {
        new_week->week_cases = week_numbers;
        new_week->week_cases_ratio = week_ratio;
        new_week->total_cases = total_numbers;
    }
    if (strcmp(indicator, "deaths") == 0)
    {
        new_week->week_deaths = week_numbers;
        new_week->week_deaths_ratio = week_ratio;
        new_week->total_deaths = total_numbers;
    }
    return week_head;
    /*WEEK *temp;
    WEEK *new_week;
    temp = week_head;
    if (week_head == NULL)
    {
        new_week = (WEEK*)malloc(sizeof(WEEK));
    }else{
        while (temp->next_week != NULL)
        {
            temp = temp->next_week;
        }
        
    }
    new_week = (WEEK*)malloc(sizeof(WEEK));
    strcpy(new_week->n_week, n_week_ar);
    if (strcmp(indicator, "cases"))
    {
        new_week->week_cases = week_numbers;
        new_week->week_cases_ratio = week_ratio;
        new_week->total_cases = total_numbers;
    }
    if (strcmp(indicator, "deaths"))
    {
        new_week->week_deaths = week_numbers;
        new_week->week_deaths_ratio = week_ratio;
        new_week->total_deaths = total_numbers;
    }
    new_week->next_week = NULL;
    if (week_head == NULL)
    {
        week_head = new_week;
        return week_head;
    }
    while (temp->next_week != NULL)    
    {
        temp = temp->next_week;
    }
    temp->next_week = new_week;*/
    return week_head;
}

Country *addcountry( Country *head, char name[32], char continent[16], char acronym[4], int population )
{
    Country *country;
    Country *new_country;
    country = head;
    //WEEK *week;
    //week = (WEEK*)malloc(sizeof(WEEK));
    new_country = (Country*)malloc(sizeof(Country));
    strcpy(new_country->name, name);
    strcpy(new_country->continent, continent);
    strcpy(new_country->acronym, acronym);
    new_country->population = population;
    new_country->next_country = NULL;
    //new_country->week_head = week;
    if (head == NULL)
    {
        return new_country;
    }
    while (country->next_country != NULL)
    {
        country = country->next_country;
    }
    country->next_country = new_country;
    return head;
}