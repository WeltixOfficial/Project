#include <SFML/Graphics.hpp>

using namespace sf;

class Przeciwnik
{
    private:

    unsigned licznikPunktow;
    CircleShape shape;
    int typ;
    float speed;
    int hp;
    int hpMax;
    int obrazenia;
    int punkty;

    void zmienne();
    void ksztalt();

    public:

    Przeciwnik(float pos_x, float pos_y);
    virtual ~Przeciwnik();

    const FloatRect getBounds() const;
    const int & getPunkty() const;
    const int & getObrazenia() const;

    void update();
    void render(RenderTarget *target);
};
