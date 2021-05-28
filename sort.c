#include "sort.h"
/** \Função que retorna o número de infetados numa semana
 *
 * \param country -> ponteiro para o país em que queremos pesquisar
 * \param sort_week -> semana que se quer procurar
 * \return número de casos dessa semana
 *
 */

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
        return look_week->week_cases;
    }
}

/** \Função que retorna o número de mortes numa semana
 *
 * \param country -> ponteiro para o país em que queremos pesquisar
 * \param sort_week -> semana que se quer procurar
 * \return número de mortos dessa semana
 *
 */

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
        return look_week->week_deaths;
    }
}

/** \Função que troca a posição de dois países
 *
 * \param head-> ponteiro para o primeiro elemento da lista de países
 * \param country1 -> um dos países que se quer trocar
 * \param country2 -> um dos países que se quer trocar
 * \return head-> ponteiro para o primeiro elemento da lista de países pois pode ter de ser modificado dentro da função
 *
 */

Country *sortposition(Country *head,char country1[64], char country2[64]){
    Country *prevNode1 = NULL, *prevNode2 = NULL, *node1 = head, *node2 = head, *temp = NULL;

    //Verifica se a lista está vazia
    if(head == NULL) {
        return head;
    }

    //Verifica se são o mesmo país
    if(strcmp(country1, country2) == 0)
    {

        return head;;
    }

    //Pesquisa pelo nodo do country1
    while(node1 != NULL && strcmp(node1->country, country1) != 0)
    {
        prevNode1 = node1;
        node1 = node1->next_country;
    }

    //Pesquisa pelo nodo do country1
    while(node2 != NULL && strcmp(node2->country, country2) != 0)
    {
        prevNode2 = node2;
        node2 = node2->next_country;
    }
    if(node1 != NULL && node2 != NULL)
    {

        if(prevNode1 != NULL)
        {
            prevNode1->next_country = node2;
        }else
        {
            head  = node2;
        }
        if(prevNode2 != NULL)
        {
            prevNode2->next_country = node1;
        }else
        {
            head  = node1;
        }

        temp = node1->next_country;
        node1->next_country = node2->next_country;
        node2->next_country = temp;
    }
    else{
        printf("Swapping is not possible\n");
    }
    return head;
}

/** \Função que faz a ordenação da lista
 *
 * \param head -> duplo ponteiro para a head da lista de países
 * \param sort_type -> tipo de ordenação
 * \param sort_week -> dependendo do tipo de ordenacao representa a semana em relação à qual vai ser feita a ordenação
 * \return
 *
 */

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
            //Caso odernação seja por população
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
            //Caso odernação seja por casos numa semana
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
            //Caso odernação seja por mortes numa semana
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

            current_country = right_country;

        }
    }

    *head = some_country;
    return;
}

