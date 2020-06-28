#pragma once

#include <map>
#include <string>
#include <sstream>
#include "Gracz.h"
#include "Pocisk.h"
#include "Przeciwnik.h"

using namespace std;
using namespace sf;

class Gra
{
    private:

    RenderWindow *window;
    map<string, Texture*> textury;
    vector<Pocisk*> pociski;

    Font font;
    Text tekst;
    Text tekstKoniec;

    Texture teksturaSwiata;
    Sprite tloSwiata;

    unsigned punkty;

    Gracz *gracz;

    RectangleShape pasekZycia;
    RectangleShape pasekZycia2;

    float spawnCzas;
    float spawnCzasMax;
    vector<Przeciwnik*> vprzeciwnicy;


    void tekstury();
    void gui();
    void swiat();
    void system();

    void gracz1();
    void przeciwnicy();

    public:

    Gra();
    virtual ~Gra();

    void okno();
    void uruchom();
    void zdarzenia();
    void wprowadzanie();
    void updateGui();
    void pozycjaSwiata();
    void kolizja();
    void pozycjaPociskow();
    void pozycjaPrzeciwnikow();
    void updateWalka();
    void update();

    void renderGui();
    void renderSwiat();
    void render();
};
