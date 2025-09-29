#include <SFML/Graphics.hpp>

using namespace sf;

// Специфічний колір
Color MAIN_COLOR(209, 134, 29, 0);

int main() {
 // Створення вікна
 RenderWindow window(VideoMode({200, 200}), "SFML");

 Vertex figure[] =
 {
  {{100, 100}, Color::Red, {0,0}},
  {{120, 120}, Color::Red, {0,0}},
  {{110, 130}, Color::Red, {0,0}},
  {{110, 130}, Color::Red, {0,0}},
  {{80, 120}, Color::Red, {0,0}},
  {{100, 100}, Color::Red, {0,0}}
 };
 // Створення та налаштування кола
 CircleShape circle(50);
 circle.setPosition({ 0, 0 });
 circle.setFillColor(Color::Black);
 // Змінні для руху кола
 // Швидкість
 float speed = 0.1f;
 // Вектор руху
 Vector2f direction(1, 0);


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

  window.clear(MAIN_COLOR);

  window.draw(figure, 6, PrimitiveType::Triangles);
  // Рух кола (зміна позиції)
  circle.setPosition(
   // Додаємо до поточної позиції кола вектор руху, помножений на швидкість
   circle.getPosition() + direction * speed
  );

  if (circle.getPosition().x >= (window.getSize().x - circle.getRadius() * 2))
  {
   direction.x = -1;
  }
  // Виведення кола на екран
  window.draw(circle);

  // Оновлення вікна
  window.display();
 }
  
 return 0;
}
