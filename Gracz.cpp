#include "Gracz.h"

using namespace std;
using namespace sf;

void Gracz::zmienne()
{
    this->szybkosc=2.f;

    this->cooldownAtakuMax=10.f;
    this->cooldownAtaku=this->cooldownAtakuMax;

    this->hpMax=100;
    this->hp=this->hpMax;
}

void Gracz::tekstury()
{
    if (!this->texture.loadFromFile("Textures/doge1.png"))
        cout<<"ERROR"<<endl;
    //this->sprite.setScale(1.5f, 1.5f);
}

void Gracz::uiSprite()
{
    this->sprite.setTexture(this->texture);
    this->sprite.scale(0.4f, 0.4f);
}

Gracz::Gracz()
{
    this->zmienne();
    this->tekstury();
    this->uiSprite();
}

Gracz::~Gracz()
{
    ///???
}

const Vector2f & Gracz::getPos() const
{
    return this->sprite.getPosition();
}

const FloatRect Gracz::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const int & Gracz::getHp() const
{
    return this->hp;
}

const int & Gracz::getHpMax() const
{
    return this->hpMax;
}

void Gracz::setPosition(const Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Gracz::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x,y);
}

void Gracz::ustawHp(const int hp)
{
    this->hp=hp;
}

void Gracz::utrataHp(const int wartosc)
{
    this->hp-=wartosc;
    if (this->hp<0)
        this->hp=0;
}

void Gracz::move(const float dX, const float dY)
{
    this->sprite.move(this->szybkosc*dX, this->szybkosc*dY);
}

const bool Gracz::czyAtak()
{
    if (this->cooldownAtaku>=this->cooldownAtakuMax)
    {
        this->cooldownAtaku=0.f;
        return true;
    }
    return false;
}

void Gracz::updateAtak()
{
    if (this->cooldownAtaku < this->cooldownAtakuMax)
        this->cooldownAtaku+=0.5f;
}

void Gracz::update()
{
    this->updateAtak();
}

void Gracz::render(RenderTarget &target)
{
    target.draw(this->sprite);
}


