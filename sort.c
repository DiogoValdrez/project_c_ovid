#include "sort.h"
int find_cases_week(Country* country, char sort_week[8])
{
    Week* look_week;
    look_week = country->week_head;
    while (look_week->next_week != NULL && strcmp(sort_week, look_week->n_week) != 0)
    {
        look_week = look_week->next_week;
    }
    if (strcmp(sort_week, look_week->n_week) != 0)
    {
        return 0;
    }else
    {
        return look_week->total_cases;
    }
}

int find_deaths_week(Country* country, char sort_week[8])
{
    Week* look_week;
    look_week = country->week_head;
    while (look_week->next_week != NULL && strcmp(sort_week, look_week->n_week) != 0)
    {
        look_week = look_week->next_week;
    }
    if (strcmp(sort_week, look_week->n_week) != 0)
    {
        return 0;
    }else
    {
        return look_week->total_deaths;
    }
}

Country *sortposition(Country *head,char country1[64], char country2[64]){  
    Country *prevNode1 = NULL, *prevNode2 = NULL, *node1 = head, *node2 = head, *temp = NULL;  
      
    //Checks if list is empty  
    if(head == NULL) {  
        return head;  
    }  
          
    //If n1 and n2 are equal, then list will remain the same  
    //printf("%s:%s\n\n", country1, country2);
    if(strcmp(country1, country2) == 0)
    {
          
        return head;;  
    } 

    //Search for node1  
    while(node1 != NULL && strcmp(node1->country, country1) != 0){  
        prevNode1 = node1;  
        node1 = node1->next_country;  
    }  
      
    //Search for node2  
    while(node2 != NULL && strcmp(node2->country, country2) != 0){  
        prevNode2 = node2;  
        node2 = node2->next_country;  
    }  
    if(node1 != NULL && node2 != NULL) {  
          
        //If previous node to node1 is not null then, it will point to node2  
        if(prevNode1 != NULL)  
            prevNode1->next_country = node2;          
        else  
            head  = node2;  
          
        //If previous node to node2 is not null then, it will point to node1  
        if(prevNode2 != NULL)  
            prevNode2->next_country = node1;  
        else  
            head  = node1;  
          
        //Swaps the next nodes of node1 and node2  
        temp = node1->next_country;   
        node1->next_country = node2->next_country;   
        node2->next_country = temp;       
    }      
    else{  
        printf("Swapping is not possible\n");  
    }  
    return head;
}  
// Given a list, change it to be in sorted order (using `sortedInsert()`).
void sort(Country** head, char sort_type[8], char sort_week[8])
{
    Country* some_country = *head;  
    Country* current_country = *head;   
    Country* right_country;
    int swaps = 1;
    while (swaps == 1)
    {
        swaps = 0;
        current_country = some_country;
        while (current_country->next_country != NULL)
        {
            // Guardar a posição do país seguinte
            right_country = current_country->next_country;

            //Caso odernação seja alfabética
            if (strcmp(current_country->country, right_country->country) > 0 && strcmp(sort_type, "alfa") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->country, right_country->country);
                }else{
                    sortposition(some_country, current_country->country, right_country->country);
                }
                swaps = 1;
            }
            if (current_country->population < right_country->population && strcmp(sort_type, "pop") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->country, right_country->country);
                }else{
                    sortposition(some_country, current_country->country, right_country->country);
                }
                swaps = 1;
            }else if(strcmp(current_country->country, right_country->country) > 0 && (current_country->population == right_country->population) && strcmp(sort_type, "pop") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->country, right_country->country);
                }else{
                    sortposition(some_country, current_country->country, right_country->country);
                }
                swaps = 1;
            }
            if (find_cases_week(current_country, sort_week) < find_cases_week(right_country, sort_week) && strcmp(sort_type, "inf") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->country, right_country->country);
                }else{
                    sortposition(some_country, current_country->country, right_country->country);
                }
                swaps = 1;
            }else if(strcmp(current_country->country, right_country->country) > 0 && find_cases_week(current_country, sort_week) == find_cases_week(right_country, sort_week) && strcmp(sort_type, "inf") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->country, right_country->country);
                }else{
                    sortposition(some_country, current_country->country, right_country->country);
                }
                swaps = 1;
            }
            if (find_deaths_week(current_country, sort_week) < find_deaths_week(right_country, sort_week) && strcmp(sort_type, "dea") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->country, right_country->country);
                }else{
                    sortposition(some_country, current_country->country, right_country->country);
                }
                swaps = 1;
            }else if(strcmp(current_country->country, right_country->country) > 0 && find_deaths_week(current_country, sort_week) == find_deaths_week(right_country, sort_week) && strcmp(sort_type, "dea") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->country, right_country->country);
                }else{
                    sortposition(some_country, current_country->country, right_country->country);
                }
                swaps = 1;
            }
            printf("%s--%s\n", current_country->country, right_country->country);
            
            current_country = right_country;
            
        }
    }

    *head = some_country;
}

