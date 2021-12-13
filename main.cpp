#include <iostream>
#include "Mission/Mission.h"
#include <string>
#include <SFML/Graphics.hpp>
int main() {
    FILE *fd;
    std::string fname;
    std::string new_type = "rocket";
    double damage = 2, rate = 0.3, range = 2, max_ammunition = 20, cost = 9000;
    double error = 0.01;
    Basic::Armament a(new_type, damage, rate, range, max_ammunition, cost);
    fd = fopen(fname.c_str(), "r+b");

    if (fd == nullptr) fd = fopen(fname.c_str(), "w+b");


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
