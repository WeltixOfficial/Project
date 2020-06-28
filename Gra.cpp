#include "Gra.h"

using namespace sf;
using namespace std;

void Gra::okno()
{
    this->window=new RenderWindow(VideoMode(800, 600), "Gra",Style::Close | Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void Gra::tekstury()
{
    this->textury["BULLET"]=new Texture();
    this->textury["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Gra::gui()
{
    if (!this->font.loadFromFile("Fonts/czcionka.ttf"))
        cout<<"ERROR"<<endl;

    this->tekst.setPosition(700.f, 25.f);
    this->tekst.setFont(this->font);
    this->tekst.setCharacterSize(20);
    this->tekst.setFillColor(Color::White);
    this->tekst.setString("test");

    this->tekstKoniec.setFont(this->font);
    this->tekstKoniec.setCharacterSize(60);
    this->tekstKoniec.setFillColor(Color::Red);
    this->tekstKoniec.setString("Przegrales!");
    this->tekstKoniec.setPosition(
        this->window->getSize().x/2.f-this->tekstKoniec.getGlobalBounds().width/2.f,
        this->window->getSize().y/2.f-this->tekstKoniec.getGlobalBounds().height/2.f);

    this->pasekZycia.setSize(Vector2f(300.f, 25.f));
    this->pasekZycia.setFillColor(Color::Red);
    this->pasekZycia.setPosition(Vector2f(20.f, 20.f));

    this->pasekZycia2=this->pasekZycia;
    this->pasekZycia2.setFillColor(Color(25,25,25,200));
}

void Gra::swiat()
{
    if (!this->teksturaSwiata.loadFromFile("Textures/background1.jpg"))
        cout<<"ERROR"<<endl;

    this->tloSwiata.setTexture(this->teksturaSwiata);
    this->tloSwiata.setScale(1.f, 1.f);
}

void Gra::system()
{
    this->punkty=0;
}

void Gra::gracz1()
{
    this->gracz=new Gracz();
}

void Gra::przeciwnicy()
{
    this->spawnCzasMax=50.f;
    this->spawnCzas=this->spawnCzasMax;
}

Gra::Gra()
{
    this->tekstury();
    this->gui();
    this->swiat();
    this->system();
    this->gracz1();
    this->przeciwnicy();
}

Gra::~Gra()
{
    delete this->window;
    delete this->gracz;

    for (auto *i : this->textury)
        delete i;
    for (auto *i : this->pociski)
        delete i;
    for (auto *i : this->vprzeciwnicy)
        delete i;
}

void Gra::uruchom()
{
    while (this->window->isOpen())
    {
        this->zdarzenia();
        if (this->gracz->getHp()>0)
            this->update();
        this->render();
    }
}

void Gra::zdarzenia()
{
    Event e;
    while (this->window->pollEvent(e))
    {
        if (e.Event::type==Event::Closed)
            this->window->close();
        if (e.Event::KeyPressed && e.Event::key.code==Keyboard::Escape)
            this->window->close();
    }
}

void Gra::wprowadzanie()
{
    if (Keyboard::isKeyPressed(Keyboard::A))
        this->gracz->move(-1.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::D))
        this->gracz->move(1.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::W))
        this->gracz->move(0.f, -1.f);
    if (Keyboard::isKeyPressed(Keyboard::S))
        this->gracz->move(0.f, 1.f);

    if (Mouse::isButtonPressed(Mouse::Left) && this->gracz->czyAtak())
    {
        this->pociski.push_back(
            new Pocisk(
                this->textury["BULLET"],
                this->gracz->getPos().x+this->gracz->getBounds().width/2.f,
                this->gracz->getPos().y,
                0.f,
                -1.f,
                5.f
                )
        );
    }
}

void Gra::updateGui()
{
    stringstream ss;
    ss<<"Punkty: "<<this->punkty;

    this->tekst.setString(ss.str());

    float procentHp=static_cast<float>(this->gracz->getHp())/this->gracz->getHpMax();
    this->pasekZycia.setSize(Vector2f(300.f*procentHp, this->pasekZycia.getSize().y));
}

void Gra::pozycjaSwiata()
{
    ///?????
}

void Gra::kolizja()
{
    if (this->gracz->getBounds().left<0.f)
        this->gracz->setPosition(0.f, this->gracz->getBounds().top);
    else if (this->gracz->getBounds().left+this->gracz->getBounds().width>=this->window->getSize().x)
        this->gracz->setPosition(this->window->getSize().x-this->gracz->getBounds().width, this->gracz->getBounds().top);
    if (this->gracz->getBounds().top<0.f)
        this->gracz->setPosition(this->gracz->getBounds().left, 0.f);
    else if (this->gracz->getBounds().top+this->gracz->getBounds().height>=this->window->getSize().y)
        this->gracz->setPosition(this->gracz->getBounds().left, this->window->getSize().y-this->gracz->getBounds().height);
}

void Gra::pozycjaPociskow()
{
    unsigned licznik=0;
    for (auto *pocisk : this->pociski)
    {
        pocisk->update();

        if (pocisk->getBounds().top+pocisk->getBounds().height<0.f)
        {
            delete this->pociski.at(licznik);
            this->pociski.erase(this->pociski.begin()+licznik);
        }
    }
}

void Gra::pozycjaPrzeciwnikow()
{
    this->spawnCzas+=0.5f;
    if (this->spawnCzas>=this->spawnCzasMax)
    {
        this->vprzeciwnicy.push_back(new Przeciwnik(rand()%this->window->getSize().x-20.f, -100.f));
        this->spawnCzas=0.f;
    }

    unsigned licznik=0;
    for (auto *enemy : this->vprzeciwnicy)
    {
        enemy->update();

        if (enemy->getBounds().top>this->window->getSize().y)
        {
            delete this->vprzeciwnicy.at(licznik);
            this->vprzeciwnicy.erase(this->vprzeciwnicy.begin()+licznik);
        }
        else if (enemy->getBounds().intersects(this->gracz->getBounds()))
        {
            this->gracz->utrataHp(this->vprzeciwnicy.at(licznik)->getObrazenia());
            delete this->vprzeciwnicy.at(licznik);
            this->vprzeciwnicy.erase(this->vprzeciwnicy.begin()+licznik);
        }
        licznik++;
    }
}

void Gra::updateWalka()
{
    for (int i=0; i<this->vprzeciwnicy.size(); i++)
    {
        bool usunieci=false;
        for (size_t j=0; j<this->pociski.size(); j++)
        {
            if (this->vprzeciwnicy[i]->getBounds().intersects(this->pociski[j]->getBounds()))
            {
                this->punkty+=this->vprzeciwnicy[i]->getPunkty();
                delete this->vprzeciwnicy[i];
                this->vprzeciwnicy.erase(this->vprzeciwnicy.begin()+j);
                delete this->pociski[j];
                this->pociski.erase(this->pociski.begin()+i);
            }
        }
    }
}

void Gra::update()
{
    this->wprowadzanie();
    this->gracz.update();
    this->kolizja();
    this->pozycjaPrzeciwnikow();
    this->updateWalka();
    this->updateGui();
    this->pozycjaSwiata();
}

void Gra::renderGui()
{
    this->window->draw(this->tekst);
    this->window->draw(this->pasekZycia2);
    this->window->draw(this->pasekZycia);
}

void Gra::renderSwiat()
{
    this->window->draw(this->tloSwiata);
}

void Gra::render()
{
    this->renderSwiat();

    this->gracz->render(*this->window);

    for (auto *pocisk : this->pociski)
        pocisk->render(this->window);
    for (auto *enemy : this->vprzeciwnicy)
        enemy->render(this->window);

    this->renderGui();

    if (this->gracz->getHp()<=0)
        this->window->draw(this->tekstKoniec);

    this->window.display();
}






