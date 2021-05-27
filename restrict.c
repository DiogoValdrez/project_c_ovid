#include "restrict.h"

/** \brief Função que trata das restrições
 *
 * \param CountryHead Country* - Apontador para o primeiro país da lista
 * \param restrict_data_type[8]
 * \param restrict_data_week[8] char
 * \param restrict_data_interval_week[8] char
 * \return Country*
 *
 */
Country *do_restrict(Country *CountryHead, char restrict_data_type[8], char restrict_data_week[8], char restrict_data_interval_week[8]){
    int aux = -1;//valor default
    unsigned long int aux2 = 0;
    Country *Aux = NULL;
    Country *Aux2 = NULL;
    Week *AuxW = NULL;
    Week *AuxW2 = NULL;

    if(strcmp(restrict_data_type, "min") == 0){
        aux = 0;
        // Transforma o char em unsigned long int e multiplica por 1000 para ficar igual aos valores que estão na lista
        aux2 = (unsigned long int)atoi(restrict_data_week)*1000;
    }else if(strcmp(restrict_data_type, "max") == 0){
        aux = 1;
        aux2 = (unsigned long int)atoi(restrict_data_week)*1000;
    }else if(strcmp(restrict_data_type, "date") == 0){
        aux = 2;
    }else{//verificação aqui seria redundante
        aux = 3;
    }

    switch (aux)//verificação seria redundante
    {
    case 0:
        for(Aux = CountryHead; Aux != NULL; Aux = Aux2){
            Aux2 = Aux->next_country;
            if(Aux->population <= aux2){
                CountryHead = remove_country(CountryHead, Aux);
            }
        }
        break;
    case 1:
        for(Aux = CountryHead; Aux != NULL; Aux = Aux2){
            Aux2 = Aux->next_country;
            if(Aux->population >= aux2){
                CountryHead = remove_country(CountryHead, Aux);
            }
        }
        break;
    case 2:
        for(Aux = CountryHead; Aux != NULL; Aux = Aux->next_country){
            for(AuxW = Aux->week_head; AuxW != NULL; AuxW = AuxW2){
                AuxW2 = AuxW->next_week;
                if(strcmp(AuxW->n_week, restrict_data_week) != 0){
                    remove_week(Aux, AuxW);
                }
            }
        }
        break;
    case 3:
        for(Aux = CountryHead; Aux != NULL; Aux = Aux->next_country){
            for(AuxW = Aux->week_head; AuxW != NULL; AuxW = AuxW2){
                AuxW2 = AuxW->next_week;
                if(compare_dates(AuxW->n_week, restrict_data_week) == 2 || compare_dates(AuxW->n_week, restrict_data_interval_week) == 1){
                    remove_week(Aux, AuxW);
                }
            }
        }
        break;
    }
    return CountryHead;
}

/** \brief Função que compara semanas
 *
 * \param date1[8] char
 * \param date2[8] char
 * \return int - retorna 1,2,0 se for maior, menor ou igual à primeira e à segunda data, respetivamente
 *
 */
int compare_dates(char date1[8], char date2[8]){
    int i;
    int comp = 0;
    for(i = 0; i < 8; i++){
        if(i == 4){
            continue;
        }
        if(date1[i]>date2[i]){
            comp = 1;
            return comp;
        }else if(date1[i]<date2[i]){
            comp = 2;
            return comp;
        }
    }
    return comp;
}
