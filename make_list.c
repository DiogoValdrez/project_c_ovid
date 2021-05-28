#include "make_list.h"

/** \brief Função geral que cria um nó da lista principal
 *
 * \param CountryHead Country* - Apontador para o primeiro país da lista
 * \param country[64] char - nome do país
 * \param country_code[4] char - sigla do país
 * \param continent[16] char - nome do continente
 * \param population unsigned longint - população do país
 * \param n_week[8] char - semana e ano
 * \param week_values int - valor de mortes/casos na semana
 * \param week_ratio float - racio de mortes/casos na semana
 * \param total int - numero total de mortes/casos
 * \param cindicator[7] char - indicador se os dados são relativos ás mortes ou casos
 * \return Country* - Apontador para o primeiro país da lista
 *
 */
Country *create_node(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population, char n_week[8],int week_values,float week_ratio,int total, char cindicator[7], FILE *fp)
{
    Week *NewWeek = NULL;
    Country *Country = NULL;
    Country = create_country(CountryHead, country, country_code, continent, population, fp);
    NewWeek = create_week(CountryHead, Country, n_week, week_values, week_ratio, total, cindicator, fp);
    Country->week_head = add_WEL(Country, NewWeek);
    CountryHead = add_CEL(CountryHead, Country);
    return CountryHead;
}

/** \brief Função que cria um nó da lista de semanas
 *
 * \param Country Country* - Apontador para o país
 * \param n_week[8] char - semana e ano
 * \param week_values int - valor de mortes/casos na semana
 * \param week_ratio float - racio de mortes/casos na semana
 * \param total int - numero total de mortes/casos
 * \param cindicator[7] char - indicador se os dados são relativos ás mortes ou casos
 * \return Week* - Apontador para a primeira semana desta lista
 *
 */
Week *create_week(Country *CountryHead, Country *Country,char n_week[8],int week_values,float week_ratio,int total,char cindicator[7], FILE *fp){
    Week *NewWeek = NULL;
    int ind_aux;

    // Torna o indicador em int, desta forma é amis facil saber que dados uma semana tem em cada país
    if(strcmp("cases", cindicator)==0){
        ind_aux = 1;
    }else if(strcmp("deaths", cindicator)==0){
        ind_aux = 2;
    }else{
        fprintf(stderr, "-1 Erro de Leitura: Indicador com valor inválido\n");
        free_nodes(CountryHead);
        fclose(fp);
        exit(0);
    }
    NewWeek = look_for_week(Country, n_week);
    if(NewWeek != NULL){
        if(NewWeek->indicator == ind_aux || NewWeek->indicator == 3){
            fprintf(stderr, "-1 Erro de Leitura: A semana pedida tem dados repetidos\n");
            free_nodes(CountryHead);
            fclose(fp);
            exit(0);
        }
        // Verifica o indicador
        if(ind_aux == 1){
            NewWeek->week_cases = week_values;
            NewWeek->week_cases_ratio = week_ratio;
            NewWeek->total_cases = total;
        }else{
            NewWeek->week_deaths = week_values;
            NewWeek->week_deaths_ratio = week_ratio;
            NewWeek->total_deaths  = total;
        }
        NewWeek->indicator = NewWeek->indicator + ind_aux;
        return NewWeek;
    }
    if((NewWeek = (Week*)calloc(1, sizeof(Week)))==NULL){
        fprintf(stderr, "-1 Erro de Alocação: Não foi possivel alocar o bloco de memória.[create_week]\n");
        free_nodes(CountryHead);
        fclose(fp);
        exit(0);
    }
    NewWeek->indicator = ind_aux;
    strcpy(NewWeek->n_week, n_week);
    if(ind_aux == 1){
        NewWeek->week_cases = week_values;
        NewWeek->week_cases_ratio = week_ratio;
        NewWeek->total_cases = total;
    }else{
        NewWeek->week_deaths = week_values;
        NewWeek->week_deaths_ratio = week_ratio;
        NewWeek->total_deaths  = total;
    }
    return NewWeek;
}

/** \brief Função qe cria um país
 *
 * \param CountryHead Country* - Apontador para o primeiro país da lista
 * \param country[64] char - nome do país
 * \param country_code[4] char - sigla do país
 * \param continent[16] char - nome do continente
 * \param population unsigned longint - população do país
 * \return Country* - Apontador para o primeiro país da lista
 *
 */
Country *create_country(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population, FILE *fp)
{
    Country *NewCountry = NULL;
    //Procura pelo país, para ver se ele já existe
    if((NewCountry = look_for_country(country, CountryHead)) != NULL){
        return NewCountry;
    }
    if((NewCountry = (Country*)calloc(1, sizeof(Country)))==NULL){
        fprintf(stderr, "-1 Erro de Alocação: Não foi possivel alocar o bloco de memória.[create_country]\n");
        free_nodes(CountryHead);
        fclose(fp);
        exit(0);
    }
    strcpy(NewCountry->country, country);
    strcpy(NewCountry->country_code, country_code);
    strcpy(NewCountry->continent, continent);
    NewCountry->population = population;
    NewCountry->week_head = NULL;
    NewCountry->next_country = NULL;

    return NewCountry;
}


/** \brief Função que adiciona um país ao fim da lista
 *
 * \param CountryHead Country* - Apontador para o primeiro país da lista
 * \param NewCountry Country* - Apontador para o novo país
 * \return Country* - Apontador para o primeiro país da lista
 *
 */
Country *add_CEL(Country *CountryHead, Country *NewCountry){
    Country *Aux = NULL;
    // Verifica se ja existe na lista antes de adicionar
    if(look_for_country(NewCountry->country, CountryHead) != NULL){
        return CountryHead;
    }
    if(CountryHead == NULL){
        CountryHead = NewCountry;
    }else{
        Aux = CountryHead;
        while(Aux->next_country != NULL){
            Aux = Aux->next_country;
        }
        Aux->next_country = NewCountry;
    }
    return CountryHead;
}

/** \brief Função que adiciona um país ao fim da lista
 *
 * \param Country Country* - Apontador para o país
 * \param NewWeek Week* - Apontador para a nova semana
 * \return Week* - Apontador para a primeira semana da lista
 *
 */
Week *add_WEL(Country *Country, Week *NewWeek){
    Week *Aux = NULL;
    //verifica se ja existe na lista antes de adicionar
    if(look_for_week(Country, NewWeek->n_week) != NULL){
        return Country->week_head;
    }
    if(Country->week_head == NULL){
        Country->week_head = NewWeek;
    }else{
        Aux = Country->week_head;
        while(Aux->next_week != NULL){
            Aux = Aux->next_week;
        }
        Aux->next_week = NewWeek;
    }
    return Country->week_head;
}

/** \brief Função que procura por um país
 *
 * \param country[64] char - nome do país
 * \param CountryHead Country* - Apontador para o primeiro país da lista
 * \return Country* - Apontador para o país, caso o encontre
 *
 */
Country *look_for_country(char country[64], Country *CountryHead){
    Country *Aux = NULL;
    Country *FoundCountry = NULL;

    Aux = CountryHead;
    if(Aux == NULL){
        return FoundCountry;
    }

    do{
        if(strcmp(Aux->country, country) == 0){
            FoundCountry = Aux;
            break;
        }
        Aux = Aux->next_country;
    }while(Aux != NULL);
    return FoundCountry;
}

/** \brief Função que procura por uma semana
 *
 * \param Country Country* - Apontador para o país
 * \param n_week[8] char - semana e ano
 * \return Week* - Apontador para a semana, caso a encontre
 *
 */
Week *look_for_week(Country *Country, char n_week[8]){
    Week *FoundWeek = NULL;
    Week *Aux = NULL;
    Aux = Country->week_head;;
    if(Aux == NULL){
        return FoundWeek;
    }
    do{
        if(strcmp(Aux->n_week, n_week) == 0){
            FoundWeek = Aux;
            break;
        }
        Aux = Aux->next_week;
    }while(Aux != NULL);
    return FoundWeek;
}

/** \brief Função usada para testar o código rapidamente
 *
 * \param CountryHead Country*
 * \return void
 *
 */
/*
void print_nodes(Country *CountryHead){
    Country *Aux = NULL;
    Week *AuxW = NULL;
    for(Aux = CountryHead; Aux != NULL; Aux = Aux->next_country){
        printf("\n%s, %s, %s, %lu, %p\n", Aux->country, Aux->country_code, Aux->continent, Aux->population, Aux->next_country);
        for(AuxW = Aux->week_head; AuxW != NULL; AuxW = AuxW->next_week){
            printf("\t%s, %d, %g, %d, %d, %g, %d, %d, %p\n", AuxW->n_week, AuxW->week_cases, AuxW->week_cases_ratio, AuxW->total_cases, AuxW->week_deaths, AuxW->week_deaths_ratio, AuxW->total_deaths, AuxW->indicator, AuxW->next_week);
        }
    }
    return;
}
*/


/** \brief Função que liberta a memória alocada para a lista
 *
 * \param CountryHead Country* - Apontador para o primeiro país da lista
 *
 */
void free_nodes(Country *CountryHead){
    Country *Aux = NULL;
    Week *AuxW = NULL;

    Aux = CountryHead;
    AuxW = CountryHead->week_head;
    while(CountryHead != NULL){
        while(CountryHead->week_head != NULL){
            AuxW = CountryHead->week_head;
            CountryHead->week_head = CountryHead->week_head->next_week;
            free(AuxW);
        }
        Aux = CountryHead;
        CountryHead = CountryHead->next_country;
        free(Aux);
    }
    return;
}

/** \brief Função que remove um país
 *
 * \param CountryHead Country* - Apontador para o primeiro país da lista
 * \param WantRemoved Country* - Apontador para o país que queremos remover
 * \return Country* - Apontador para o primeiro país da lista
 *
 */
Country *remove_country(Country *CountryHead, Country *WantRemoved){
    Country *Aux;
    Country *BAux = NULL;
    // Procura pelo país queremos remover, para podermos ter o país anterior e religar a lista toda
    for(Aux = CountryHead; Aux != NULL; Aux = Aux->next_country){
        if(Aux == WantRemoved){
            if(BAux == NULL){
                CountryHead = Aux->next_country;
                Aux->next_country = NULL;
                free_nodes(Aux);
                return CountryHead;
            }
            BAux->next_country = Aux->next_country;
            Aux->next_country = NULL;
            free_nodes(Aux);
            return CountryHead;
        }
        BAux = Aux;
    }
    return CountryHead;
}

/** \brief Função que remove uma semana
 *
 * \param Country Country* - Apontador para o país
 * \param WantRemoved Week* - Apontador para a semana que queremos remover
 * \return Week*- Apontador para a primeira semana da lista
 *
 */
Week *remove_week(Country *Country, Week *WantRemoved){
    Week *AuxW;
    Week *BAuxW = NULL;
    // Procura pela semana que queremos remover, para podermos ter a semana anterior e religar a lista toda
    for(AuxW = Country->week_head; AuxW != NULL; AuxW = AuxW->next_week){
        if(AuxW == WantRemoved){
            if(BAuxW == NULL){
                Country->week_head = Country->week_head->next_week;
                free(AuxW);
                return Country->week_head;
            }
            BAuxW->next_week = AuxW->next_week;
            free(AuxW);
            return Country->week_head;
        }
        BAuxW = AuxW;
    }
    return Country->week_head;
}

/** \brief Função que elimina todas as semanas de um país
 *
 * \param Week_head Week* - Apontador para a primeira semana
 *
 */
void remove_country_weeks(Week* Week_head){
    Week *Save_week = NULL;

    while (Week_head != NULL)
        {
            Save_week = Week_head;
            Week_head = Week_head->next_week;
            free(Save_week);
        }
}
