#include "Przeciwnik.h"

void Przeciwnik::zmienne()
{
    this->licznikPunktow=rand()%8+3;
    this->typ=0;
    this->speed=static_cast<float>(this->licznikPunktow/3);
    this->hpMax=static_cast<int>(this->licznikPunktow);
    this->hp=this->hpMax;
    this->obrazenia=this->licznikPunktow;
    this->punkty=this->licznikPunktow;
}

void Przeciwnik::ksztalt()
{
    this->shape.setRadius(this->licznikPunktow*5);
    this->shape.setPointCount(this->licznikPunktow);
    this->shape.setFillColor(Color(rand()%255+1, rand()%255+1, rand()%255+1, 255));
}

Przeciwnik::Przeciwnik(float posX, float posY)
{
    this->zmienne();
    this->ksztalt();
    this->shape.setPosition(posX, posY);
}

Przeciwnik::~Przeciwnik()
{

}

const FloatRect Przeciwnik::getBounds() const
{
    return this->shape.getGlobalBounds();
}

const int & Przeciwnik::getPunkty() const
{
    return this->punkty;
}

const int & Przeciwnik::getObrazenia() const
{
    return this->obrazenia;
}

void Przeciwnik::update()
{
    this->shape.move(0.f, this->speed);
}

void Przeciwnik::render(RenderTarget *target)
{
    target->draw(this->shape);
}







