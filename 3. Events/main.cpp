#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
 RenderWindow window(VideoMode({ 800, 600 }), "SFML");

 // Створення кола
 CircleShape circle(50.f);
 circle.setFillColor(Color::Green);
 circle.setOrigin({ circle.getRadius(), circle.getRadius() });

 // Швидкість руху кола
 float speed = 500.f;
 // Напрям руху кола
 Vector2f direction({ 0.f, 0.f });
 
 Clock clock;
 Color backgroundColor = Color::Black;

 while (window.isOpen())
 {
  auto time = clock.restart().asMilliseconds() / 1000.f;
  direction = { 0.f, 0.f };
  // Process events
  while (const std::optional event = window.pollEvent())
  {
   // Close window: exit
   if (event->is<sf::Event::Closed>())
    window.close();
   if (event->is<Event::KeyPressed>())
   {
    auto key = event->getIf<Event::KeyPressed>()->code;
    // Обробка натискання клавіш
    if (key == Keyboard::Key::Escape) window.close();
    if (key == Keyboard::Key::Num1) backgroundColor = Color::Color(240, 156, 110, 0);
    if (key == Keyboard::Key::Num0) backgroundColor = Color::Black;

   }
   // Подія натискання на кнопку миші
   if (event->is<Event::MouseButtonPressed>())
   {
    // Отримуємо кнопку, яка була натиснута
    auto button = event->getIf<Event::MouseButtonPressed>()->button;
    // Якщо натиснута ліва кнопка миші
    if (button == Mouse::Button::Left)
    {
     // Отримуємо позицію миші
     auto position = (Vector2f)event->getIf<Event::MouseButtonPressed>()->position;
     // Виводимо у консоль інформацію про натискання
     std::cout << "Mouse clicked in " << position.x << ", " << position.y << std::endl;
     // Переміщуємо коло у точку, куди було натиснуто мишею
     circle.setPosition(position);
    }
   }
  }
  
  window.clear(backgroundColor);

  if (Keyboard::isKeyPressed(Keyboard::Key::W)) direction.y = -1.f;
  if (Keyboard::isKeyPressed(Keyboard::Key::S)) direction.y = 1.f;
  if (Keyboard::isKeyPressed(Keyboard::Key::A)) direction.x = -1.f;
  if (Keyboard::isKeyPressed(Keyboard::Key::D)) direction.x = 1.f;

  // Рух кола в напрямку вектора direction зі швидкістю speed
  circle.setPosition(
   circle.getPosition() + direction * (speed * time)
  );

  window.draw(circle);
  window.display();
 }
 return 0;
}
 
