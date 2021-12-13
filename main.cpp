#include <iostream>
#include "Mission/Mission.h"
#include <SFML/Graphics.hpp>
int main() {

    std::string st = "type A";
    std::string st1 = "type B";
    double number = 1;

    std::map<std::string, double> :: const_iterator it;
    const std::map<std::string, double> *mp;

    Ships::Ship *a = new Ships::Ship(st, st, number, number, number);
    Ships::Transport_ship *b = new Ships::Transport_ship(st, st, number, number, number, number, number);
    Ships::Military_transport_ship *d = new Ships::Military_transport_ship(st, st, number, number, number, number, number);
    Ships::Security_ship *c = new Ships::Security_ship(st, st, number, number, number);
    Ships::Security_ship *c2 = new Ships::Security_ship(st1, st1, number, number, number);

    Menu::Basic_config *b_conf = new Menu::Basic_config;
    b_conf->add_ship(c);
    b_conf->add_ship(c2);

    Pattern::Table <std::string, Pattern::Info> *conv = new Pattern::Table <std::string, Pattern::Info>;
    Pattern::Table <std::string, Pattern::Info> *pirates = new Pattern::Table <std::string, Pattern::Info>;

    Menu::Mission mission(b_conf, conv, pirates);
    mission.set_properties("max money", 100);
    mission.set_properties("max count convoy", 100);
    mission.set_properties("max count pirates", 100);
    mission.set_properties("size A", 5);
    mission.set_properties("size B", 3);
    mission.set_coord_A_B(0, 4, 5);
    mission.set_coord_A_B(1, 30, 20);

    //mission.buy_ship(0, c->get_name());
    mission.buy_ship(0, c2->get_name());
    mission.buy_ship(1, c->get_name());
   // mission.buy_ship(1, c2->get_name());
   // mission.buy_ship(1, c->get_name());
   // mission.buy_ship(1, c2->get_name());

    mission.add_pirates_coordinate(34, 25);
    mission.add_pirates_coordinate(25, 6);
    mission.add_pirates_coordinate(14, 19);
    mission.add_pirates_coordinate(17, 6);

    mission.distribution_pirates();
    mission.start_coord();

    mission.draw();
    delete b_conf;
    delete a;
    delete b;
    delete c;
    delete d;
    /*
    Menu::Basic_config b;
    FILE *fd;
    std::string fname = "Type B";
    std::string new_type = "rocket";
    double damage = 2, rate = 0.3, range = 2, max_ammunition = 20, cost = 9000;
    double error = 0.01;
    Basic::Armament a(new_type, damage, rate, range, max_ammunition, cost);
    Basic::Armament *bbb = new Basic::Armament;
    fd = fopen(fname.c_str(), "r+b");

    if (fd == nullptr) {
        fd = fopen(fname.c_str(), "w+b");
        b.safe_armament(fd, &a);
    }
    else{
        b.load_armament(fd, bbb);
    }

    std::cout << *bbb;
    delete bbb;
    bbb = nullptr;
    std::string st = "type A";
    double number = 100;

    std::map<std::string, double> :: const_iterator it;
    const std::map<std::string, double> *mp;

    Ships::Ship a1 = Ships::Ship(st, st, number, number, number);
    Ships::Transport_ship b1 = Ships::Transport_ship(st, st, number, number, number, number, number);
    Ships::Military_transport_ship d1 = Ships::Military_transport_ship(st, st, number, number, number, number, number);
    Ships::Security_ship c1 = Ships::Security_ship(st, st, number, number, number);

    b.ship[a1.get_name()] = a1;

    fd = fopen(fname.c_str(), "r+b");

    if (fd == nullptr) {
        fd = fopen(fname.c_str(), "w+b");
        b.safe_b(fd);
    }
    else{
        b.load_b(fd);
    }

    */
/*
    int x, y;
    x = 50;
    y = 50;
    sf::RenderWindow window(sf::VideoMode(x * 64, y * 64), "Convoy");
    sf::Sprite sprite;
    sf::Image water_image;
    water_image.loadFromFile("../Mission/Imagine/water.png");
    sf::Texture water_texture;
    water_texture.loadFromImage(water_image);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < 50; i ++){
            for (int j = 0; j < 50; j ++){
                sprite.setTexture(water_texture);
                sprite.setPosition(j * 64, i * 64);
                window.draw(sprite);
            }
        }
        window.display();
    }
*/
    return 0;
}
