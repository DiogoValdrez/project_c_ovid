#include "make_list.h"

//função que adiciona node, se ja existir adiciona apenas semana; retorna o countryhead(pode ser trocado o retorno)
Country *create_node(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population, char n_week[8],int week_values,float week_ratio,int total, char cindicator[7])
{
    Week *NewWeek = NULL;
    Country *Country = NULL;
    Country = create_country(CountryHead, country, country_code, continent, population);
    NewWeek = create_week(Country, n_week, week_values, week_ratio, total, cindicator);
    Country->week_head = add_WEL(Country, NewWeek);
    CountryHead = add_CEL(CountryHead, Country);
    return CountryHead;
}

Week *create_week(Country *Country,char n_week[8],int week_values,float week_ratio,int total,char cindicator[7]){
    Week *NewWeek = NULL;
    int ind_aux;

    if(strcmp("cases", cindicator)==0){
        ind_aux = 1;
    }else if(strcmp("deaths", cindicator)==0){
        ind_aux = 2;
    }else{
        printf("Erro: Indicador com valor inválido\n");//faltam \n nos erros
        exit(0);
    }
    NewWeek = look_for_week(Country, n_week);
    if(NewWeek != NULL){
        if(NewWeek->indicator == ind_aux || NewWeek->indicator == 3){
            printf("Erro: A semana pedida tem dados repetidos");
            exit(0);
        }
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
        printf("Erro: Não foi possivel alocar o bloco de memória.[create_week]");
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

//probelam desta função: se criarmos paises mas não os adicionarmos as listas dá problemas
Country *create_country(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population)
{
    Country *NewCountry = NULL;
    //Looks for the country name to see if there is already a node with that name
    if((NewCountry = look_for_country(country, CountryHead)) != NULL){
        return NewCountry;
    }
    if((NewCountry = (Country*)calloc(1, sizeof(Country)))==NULL){
        printf("Erro: Não foi possivel alocar o bloco de memória.[create_country]");
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


Country *add_CEL(Country *CountryHead, Country *NewCountry){
    Country *Aux = NULL;
    //verifica se ja existe na lista antes de adicionar
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

Week *look_for_week(Country *Country, char n_week[8]){
    Week *FoundWeek = NULL;
    Week *Aux = NULL;
    Aux = Country->week_head;;
    if(Aux == NULL){
        return FoundWeek;
    }
    do{
        //Conditional jump or move depends on uninitialised value(s) + segmentation fault!!!!
        if(strcmp(Aux->n_week, n_week) == 0){
            FoundWeek = Aux;
            break;
        }
        Aux = Aux->next_week;
    }while(Aux != NULL);//Conditional jump or move depends on uninitialised value(s)
    return FoundWeek;
}

void print_nodes(Country *CountryHead){//apagar no fim
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

Country *remove_country(Country *CountryHead, Country *WantRemoved){
    Country *Aux;
    Country *BAux = NULL;  
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

Week *remove_week(Country *Country, Week *WantRemoved){
    Week *AuxW;
    Week *BAuxW = NULL;
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
void remove_country_weeks(Week* Week_head)
{
    Week *Save_week = NULL;

    while (Week_head != NULL)
        {
            Save_week = Week_head;
            Week_head = Week_head->next_week;
            free(Save_week);
        }
}