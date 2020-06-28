#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

using namespace sf;
using namespace std;

class Gracz
{
    private:

    Sprite sprite;
    Texture texture;

    float szybkosc;

    float cooldownAtaku;
    float cooldownAtakuMax;

    int hp;
    int hpMax;

    void zmienne();
    void tekstury();
    void uiSprite();

    public:

    Gracz();
    virtual ~Gracz();

    const Vector2f getPos() const;
    const FloatRect getBounds() const;
    const int & getHp() const;
    const int & getHpMax() const;

    void setPosition(const Vector2f pos);
    void setPosition(const float x, const float y);
    void ustawHp(const int hp);
    void utrataHp(const int wartosc);

    void move(const float dX, const float dY);
    const bool czyAtak();

    void updateAtak();
    void update();
    void render(RenderTarget &target);
};








