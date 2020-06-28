#ifndef POCISK_H
#define POCISK_H

#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;

class Pocisk
{
    private:

    Sprite ksztalt;
    Vector2f kierunek;
    float szybkosc1;

    public:

    Pocisk();
    Pocisk(Texture *texture, float posX, float posY, float dirX, float dirY, float szybkosc);
    virtual ~Pocisk();

    const FloatRect getBounds() const;

    void update();
    void render(RenderTarget *target);
};

#endif
