#include "make_list.h"

Country *create_country(Country *CountryHead, char country[64], char country_code[4], char continent[16], unsigned long int population)
{
    Country *NewCountry;
    //Looks for the country name to see if there is already a node with that name
    if(look_for_country(country, CountryHead) != NULL){
        return NULL;
    }
    if((NewCountry = (Country*)malloc(sizeof(Country)))==NULL){
        printf("Erro: Não foi possivel alocar o bloco de memória.[addCountry]");
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
    Country *Aux;
    /*if((NewCountry = look_for_country(NewCountry->country, CountryHead)) != NULL){
        printf("ao adicionar ja existia");
        return CountryHead;
    }*/
    //verifica se o coutry criado ja existia(ou seja ficou null)
    if(NewCountry == NULL){
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

Country *look_for_country(char country[64], Country *CountryHead){
    Country *Aux;
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



void print_countries(Country *CountryHead){//apagar no fim
    Country *Aux;

    for( Aux = CountryHead; Aux != NULL; Aux = Aux->next_country){
        printf("\n%s, %s, %s, %lu, %p\n", Aux->country, Aux->country_code, Aux->continent, Aux->population, Aux->next_country);
    }
    return;
}

void free_countries(Country *CountryHead){
    Country *Aux;

    Aux = CountryHead;
    while(CountryHead != NULL){
        Aux = CountryHead;
        CountryHead = CountryHead->next_country;
        free(Aux);
    }
    return;
}