#include "Ruletka.h"

Ruletka::Ruletka(std::default_random_engine& engine)
{
    myEngine = engine;
}

Ruletka::~Ruletka() {}

Uczciwa::Uczciwa(std::default_random_engine& engine): Ruletka(engine) {}

Europejska::Europejska(std::default_random_engine& engine): Ruletka(engine) {}

Amerykanska::Amerykanska(std::default_random_engine& engine): Ruletka(engine) {}

int Uczciwa::zakrec()
{
    std::uniform_int_distribution<int> dist(1,36);
    int losowanie = dist(myEngine);
    return losowanie;
}

int Europejska::zakrec()
{
    std::uniform_int_distribution<int> dist(0,36);
    int losowanie = dist(myEngine);
    return losowanie;
}

int Amerykanska::zakrec()
{
    std::uniform_int_distribution<int> dist(0,37); // wartosc 37 jest polem 00
    int losowanie = dist(myEngine);
    if(losowanie==37){
        losowanie=0;
    }
    return losowanie;
}
