#include "Pocisk.h"

using namespace std;
using namespace sf;

Pocisk::Pocisk()
{

}

Pocisk::Pocisk(Texture *texture, float posX, float posY, float dirX, float dirY, float szybkosc)
{
    this->ksztalt.setTexture(&texture);
    this->ksztalt.setPosition(posX, posY);
    this->kierunek.x=dirX;
    this->kierunek.y=dirY;
    this->szybkosc1=szybkosc;
    this->ksztalt.setScale(0.5f, 0.5f);
}

Pocisk::~Pocisk()
{

}

const FloatRect Pocisk::getBounds() const
{
    return this->ksztalt.getGlobalBounds();
}

void Pocisk::update()
{
    this->ksztalt.move(this->szybkosc1*this->kierunek);
}

void Pocisk::render(RenderTarget &target)
{
    target->draw(this->ksztalt);
}




