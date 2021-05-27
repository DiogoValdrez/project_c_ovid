#include "select.h"

/** \Função que faz a seleção de dados
 *
 * \param CountryHead -> ponteiro para a head da lista de países
 * \param select_data -> Argumento dado pelo utilizador para o tipo de seleção de dados
 * \return
 *
 */

void select_d(Country* CountryHead, char select_data[12])
{
    Country* country = CountryHead;
    Week* Change_week = CountryHead->week_head;

    while (country != NULL)
    {
        Change_week = country->week_head;
        Week* Save_week = (Week*)calloc(1, sizeof(Week));

        while (Change_week != NULL)
        {
            if (Change_week->week_cases > Save_week->week_cases && strcmp(select_data, "inf") == 0)
            {
                strcpy(Save_week->n_week, Change_week->n_week);
                Save_week->total_cases = Change_week->total_cases;
                Save_week->week_cases = Change_week->week_cases;
                Save_week->week_cases_ratio = Change_week->week_cases_ratio;
            }else if (Change_week->week_cases_ratio > Save_week->week_cases_ratio && strcmp(select_data, "racioinf") == 0)
            {
                strcpy(Save_week->n_week, Change_week->n_week);
                Save_week->total_cases = Change_week->total_cases;
                Save_week->week_cases = Change_week->week_cases;
                Save_week->week_cases_ratio = Change_week->week_cases_ratio;
            }else if (Change_week->week_deaths > Save_week->week_deaths && strcmp(select_data, "dea") == 0)
            {
                strcpy(Save_week->n_week, Change_week->n_week);
                Save_week->total_deaths = Change_week->total_deaths;
                Save_week->week_deaths = Change_week->week_deaths;
                Save_week->week_deaths_ratio = Change_week->week_deaths_ratio;
            }else if (Change_week->week_deaths_ratio > Save_week->week_deaths_ratio && strcmp(select_data, "raciodea") == 0)
            {
                strcpy(Save_week->n_week, Change_week->n_week);
                Save_week->total_deaths = Change_week->total_deaths;
                Save_week->week_deaths = Change_week->week_deaths;
                Save_week->week_deaths_ratio = Change_week->week_deaths_ratio;
            }
            Change_week = Change_week->next_week;
        }
        Change_week = country->week_head;
        remove_country_weeks(Change_week);
        country->week_head = (Week*)calloc(1, sizeof(Week));
        if (strcmp(select_data, "inf") == 0 || strcmp(select_data, "racioinf") == 0)
        {
            strcpy(country->week_head->n_week, Save_week->n_week);
            country->week_head->total_cases = Save_week->total_cases;
            country->week_head->week_cases =Save_week->week_cases;
            country->week_head->week_cases_ratio = Save_week->week_cases_ratio;
            country->week_head->indicator = 1;
        }else if (strcmp(select_data, "dea") == 0 || strcmp(select_data, "raciodea") == 0)
        {
            strcpy(country->week_head->n_week, Save_week->n_week);
            country->week_head->total_deaths = Save_week->total_deaths;
            country->week_head->week_deaths =Save_week->week_deaths;
            country->week_head->week_deaths_ratio = Save_week->week_deaths_ratio;
            country->week_head->indicator = 2;
        }
        country = country->next_country;
        free(Save_week);
    }
}
