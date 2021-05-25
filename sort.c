#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
int find_cases_week(Country* country, char sort_week[8])
{
    Week* look_week;
    look_week = country->week_head;
    while (look_week->next_week != NULL && strcmp(sort_week, look_week->n_week) != 0)
    {
        look_week = look_week->next_week;
    }
    //printf("%s:%s:%d\n", country->country, look_week->n_week, look_week->total_cases );
    return look_week->total_cases;
}

int find_deaths_week(Country* country, char sort_week[8])
{
    Week* look_week;
    look_week = country->week_head;
    while (look_week->next_week != NULL && strcmp(sort_week, look_week->n_week) != 0)
    {
        look_week = look_week->next_week;
    }
    //printf("%s:%s:%d\n", country->country, look_week->n_week, look_week->total_cases );
    return look_week->total_deaths;
}

Country *sortposition(Country *head,int n1, int n2){  
    Country *prevNode1 = NULL, *prevNode2 = NULL, *node1 = head, *node2 = head, *temp = NULL;  
      
    //Checks if list is empty  
    if(head == NULL) {  
        return head;  
    }  
          
    //If n1 and n2 are equal, then list will remain the same  
    if(n1 == n2)  
        return head;  
      
    //Search for node1  
    while(node1 != NULL && node1->population != n1){  
        prevNode1 = node1;  
        node1 = node1->next_country;  
    }  
      
    //Search for node2  
    while(node2 != NULL && node2->population != n2){  
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
    // Onde vai ser guardadas as mudanças da head
    Country* result_head = NULL;   
    //Para a iteração dos vários países da lista
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

            if (strcmp(current_country->country, right_country->country) > 0 && strcmp(sort_type, "alfa") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->population, right_country->population);
                }else{
                    sortposition(some_country, current_country->population, right_country->population);
                }
                swaps = 1;
            }
            if (current_country->population < right_country->population && strcmp(sort_type, "pop") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->population, right_country->population);
                }else{
                    sortposition(some_country, current_country->population, right_country->population);
                }
                
                swaps = 1;
            }

            if (find_cases_week(current_country, sort_week) < find_cases_week(right_country, sort_week) && strcmp(sort_type, "inf") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->population, right_country->population);
                }else{
                    sortposition(some_country, current_country->population, right_country->population);
                }
                swaps = 1;
            }
            if (find_deaths_week(current_country, sort_week) < find_deaths_week(right_country, sort_week) && strcmp(sort_type, "dea") == 0)
            {
                if (current_country == some_country)
                {
                    some_country = sortposition(some_country, current_country->population, right_country->population);
                }else{
                    sortposition(some_country, current_country->population, right_country->population);
                }
                swaps = 1;
            }

            
            current_country = right_country;
            
        }
    }

    *head = some_country;
}

// Não da pra usar este algoritmo nos dois ultimos.
/*
Country *sort(Country*head, char sort_type[8], char sort_week[8],Week* head_week)
{
    Country* left = NULL;
    Country* current = head;
    Country* save_right;
    Country* save_current;
    Country* save_left;
    int swaps = 0, helper = 0;
    if (head == NULL)
    {
        printf("hi");
        return head;
    }
    if (head->next_country == NULL)
    {
        return head;
    }
    Country* right = head->next_country;


    do
    {
        swaps = 0;
        left = NULL;
        current = head;
        right = head->next_country;
        save_current = current->next_country;
        save_right = right->next_country;
        save_left = current;
        if (helper == 0)
        {
            if (strcmp(current->country, right->country) < 0)
            {
                head = right;
                current->next_country = right->next_country;
                right->next_country = current;
                swaps = 1;
            }
        }
        printf("%s:%s,%s\n", left->country, current->country, right->country);
        helper = 3;
        left = save_left;
        current = save_current;
        right = save_right;
        printf("->>%s:%s,%s, %s\n", left->country, current->country, right->country, head->country);
        //return head;
        while (right->next_country != NULL)
        {
            save_current = current->next_country;
            save_right = right->next_country;
            save_left = current;
            if (strcmp(current->country, right->country) < 0)
            {
                printf("hi");
                //printf("%s : %s", current->country, right->country);
                left->next_country = right;
                current->next_country = right->next_country;
                right->next_country = current;
                swaps = 1;
            }
            left = save_left;
            current = save_current;
            right = save_right;
            
            
        }
        swaps ++;
    }while (swaps !=10 );
    return head;
    


}
*/

