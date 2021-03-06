/*
* Kod z ćwiczeń
* z uzupełnioną funkcją zagraj
*/

#include <stdlib.h>
#include <iostream>
#include <random>
#include "Ruletka.h"

double zagraj(Ruletka* ruletka, int zaklad, int liczbaZakladow, double stawka);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << " obstaw liczbę od 1 do 36 " << std::endl;
        return 0;
    }
    int zaklad = atoi(argv[1]);
    if(zaklad < 1 || zaklad > 36)
    {
        std::cout << " do wyboru są liczby od 1 do 36 " << std::endl;
        return 0;        
    }
    int liczbaZakladow = 10000000;   
    double stawka = 1;
    
    std::random_device rd;
    std::default_random_engine engine(rd());
    Ruletka* ruletka = new Uczciwa(engine);  
    //Ruletka* ruletka = new Amerykanska(engine);  
    //Ruletka* ruletka = new Europejska(engine);
     
    double wygrana = zagraj(ruletka, zaklad, liczbaZakladow, stawka);

    std::cout << "Stopa zwrotu" << wygrana/(liczbaZakladow*stawka) * 100.  << " %" << std::endl;
    return 0;
}

double zagraj(Ruletka* ruletka, int zaklad, int liczbaZakladow, double stawka)
{
    double wygrana = 0;
    for(int i = 0; i != liczbaZakladow; ++i)
    {
        int wylosowanyNumerek = ruletka -> zakrec(); // operator "zakrec" z pliku Ruletka.h
        if(wylosowanyNumerek == zaklad)
            wygrana = wygrana + 36*stawka;
        else
            wygrana = wygrana - stawka;
    }
    return wygrana;
}
