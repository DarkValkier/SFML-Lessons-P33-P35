#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <map>
#include "Player.h"
#include "Map.h"

using namespace sf;
using namespace std;

const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 5;
const int MAP_TILE_SIZE = 70;
char MAP[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "          ",
    "         L",
    "GGGBBG    ",
    "          ",
    "      GGGG",
};

int main() {
    // Створення вікна
    RenderWindow window(VideoMode({ 1200, 800 }), "SFML");

    Player player("skeletonBase.png");
    player.setScale({ 2.f, 2.f });
    Map location(
        Vector2i({ MAP_WIDTH+1 , MAP_HEIGHT }),
        Vector2i({ MAP_TILE_SIZE , MAP_TILE_SIZE }),
        (char*)MAP);
    Clock clock;
    // Нескіченний цикл, який підтимує роботу вікна
    while (window.isOpen())
    {
        // Обробка подій
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float time = clock.restart().asSeconds();

        window.clear(Color::Black);
        location.draw(window);

        player.update(time);
        location.checkCollisions(player.sprite);
        player.draw(window);

        window.display();
    }
    return 0;
}

void drawMap(RenderWindow& window, map<char, Sprite>& spriteSheet)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            auto spriteIt = spriteSheet.find(MAP[y][x]);
            if (spriteIt != spriteSheet.end())
            {
                spriteIt->second.setPosition({ (float)(x * MAP_TILE_SIZE), (float)(y * MAP_TILE_SIZE) });
                window.draw(spriteIt->second);
            }
        }
}