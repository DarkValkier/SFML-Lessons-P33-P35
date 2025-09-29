#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// Специфічний колір
Color MAIN_COLOR(209, 134, 29, 0);

// Відстань між двома точками
float distance(Vector2f p1, Vector2f p2)
{
 return (p1 - p2).length();
}

// Відстань між двома колами
float distance(CircleShape c1, CircleShape c2)
{
 return (c1.getPosition() - c2.getPosition()).length() 
  - (c1.getRadius() + c2.getRadius());
}

int main() {
 // Створення вікна
 RenderWindow window(VideoMode({1200, 800}), "SFML");

 // Створення шестикутника
 Vertex figure[] =
 {
  {{100, 100}, Color::Red, {0,0}},
  {{100, 0}, Color::Red, {0,0}},
  {{0, 50}, Color::Red, {0,0}},

  {{100, 100}, Color::Green, {0,0}},
  {{0, 50}, Color::Green, {0,0}},
  {{0, 150}, Color::Green, {0,0}},

  {{100, 100}, Color::Blue, {0,0}},
  {{0, 150}, Color::Blue, {0,0}},
  {{100, 200}, Color::Blue, {0,0}},

  {{100, 100}, Color::Yellow, {0,0}},
  {{100, 200}, Color::Yellow, {0,0}},
  {{200, 150}, Color::Yellow, {0,0}},

  {{100, 100}, Color::Magenta, {0,0}},
  {{200, 50}, Color::Magenta, {0,0}},
  {{200, 150}, Color::Magenta, {0,0}},

  {{100, 100}, Color::Cyan, {0,0}},
  {{200, 50}, Color::Cyan, {0,0}},
  {{100, 0}, Color::Cyan, {0,0}},
 };

 // Створення кола
 CircleShape circle(100.f);
 circle.setOrigin({ 100.f, 100.f });
 circle.setFillColor(Color::Green);
 circle.setOutlineColor(Color::Red);
 circle.setOutlineThickness(10.f);

 float speed = 100.f;
 Vector2f direction(1, 0);


 float timer1 = 0.f;
 Clock clock;

 // Нескіченний цикл, який підтимує роботу вікна
 while (window.isOpen())
 {
  // Розрахунок часу, що пройшов з останнього кадру (в секундах)
  auto time = clock.restart().asMilliseconds() / 1000.f;

  // Виведення FPS
  system("cls");
  cout << 1 / time << " FPS" << endl;
  // Обробка подій
  while (const std::optional event = window.pollEvent())
  {
   // Close window: exit
   if (event->is<sf::Event::Closed>())
    window.close();
  }

  // Таймер на 3 секунди
  timer1 += time;
  if (timer1 > 3) {
   circle.setFillColor(Color::Red);
   timer1 -= 3;
  }

  window.clear(MAIN_COLOR);
  // window.draw(figure, 18, PrimitiveType::Triangles);
  circle.setPosition(
   circle.getPosition() + direction * speed * time
  );

  window.draw(circle);
  
  // Оновлення вікна
  window.display();
 }
  
 return 0;
}
