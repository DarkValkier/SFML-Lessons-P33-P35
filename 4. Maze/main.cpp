#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 7;
const char MAP[MAP_HEIGHT][MAP_WIDTH + 1] = {
 "XXXXXXXXXX",
 "X        X",
 "X   XX   X",
 "X   XX   X",
 "X   XX   X",
 "X        X",
 "XXXXXXXXXX",
};
const float TILE_SIZE = 100.f;


int main() {
 // Створення вікна
 RenderWindow window(VideoMode({ 1200, 800 }), "SFML");
 Color windowBGColor = Color::Black;

 CircleShape circle(50.f);
 circle.setFillColor(Color::Green);
 circle.setOrigin({
   circle.getRadius(),
   circle.getRadius()
  });
 circle.setPosition({ 100.f, 50.f });

 // Швидкість руху кола (пікселів на кадр)
 float speed = 500.f;
 // Напрям руху кола
 Vector2f direction(0.f, 0.f);
 // Точка, до якої рухається коло
 Vector2f targetPos = circle.getPosition();

 Clock clock;
 // Нескіченний цикл, який підтимує роботу вікна
 while (window.isOpen())
 {
  auto time = clock.restart().asMilliseconds() / 1000.f;
  // Обробка подій
  while (const std::optional event = window.pollEvent())
  {
   // Close window: exit
   if (event->is<sf::Event::Closed>())
    window.close();
   // При натисканні клавіші Esc
   if (event->is<Event::KeyPressed>()
    && event->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)
    window.close();
  }

  if (Keyboard::isKeyPressed(Keyboard::Key::W)) circle.move({ 0, -1 });
  if (Keyboard::isKeyPressed(Keyboard::Key::S)) circle.move({ 0, 1 });
  if (Keyboard::isKeyPressed(Keyboard::Key::A)) circle.move({ -1, 0 });
  if (Keyboard::isKeyPressed(Keyboard::Key::D)) circle.move({ 1, 0 });
  window.clear(windowBGColor);

  for(int y = 0; y < MAP_HEIGHT; y++)
   for (int x = 0; x < MAP_WIDTH; x++)
   {
    if (MAP[y][x] == ' ') continue;
    else if (MAP[y][x] == 'X')
    {
     RectangleShape tile({ TILE_SIZE, TILE_SIZE });
     tile.setFillColor(Color::Magenta);
     tile.setPosition({ x * TILE_SIZE, y * TILE_SIZE });
     window.draw(tile);
    }
   }

  // Малюємо коло
  window.draw(circle);
  // Оновлення вікна
  window.display();
 }
 return 0;
}
