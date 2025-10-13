#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

const Font font("Roboto.ttf");
const Font fontHalloween("RubikWetPaint-Regular.ttf");

int main() {
 // Створення вікна
 RenderWindow window(VideoMode({1200, 800}), "SFML");

 int active_answer = 0;
 Text answers[4] = {
  Text(fontHalloween, "VARIANT 1"),
  Text(fontHalloween, "VARIANT 2"),
  Text(fontHalloween, "VARIANT 3"),
  Text(fontHalloween, "VARIANT 4"),
 };

 for (int i = 0; i < 4; i++)
 {
  if (i == active_answer)
   answers[i].setFillColor(Color::Red);
  answers[i].setPosition({ 50.f, 250.f + (float)(answers[i].getCharacterSize() * i * 2) });
 }


 // Нескіченний цикл, який підтимує роботу вікна
 while (window.isOpen())
 {
  // Обробка подій
  while (const std::optional event = window.pollEvent())
  {
   // Close window: exit
   if (event->is<sf::Event::Closed>())
    window.close();
   if (event->is<Event::KeyPressed>())
   {
    auto key = event->getIf<Event::KeyPressed>()->code;
    if (key == Keyboard::Key::Up)
    {
     active_answer = max(0, active_answer-1);
    }
    if (key == Keyboard::Key::Down)
    {
     active_answer = min(3, active_answer + 1);
    }
   }
  }
  
  window.clear(Color::Black);
  
  for (int i = 0; i < 4; i++)
  {
   if (i == active_answer)
    answers[i].setFillColor(Color::Red);
   else
    answers[i].setFillColor(Color::White);
   window.draw(answers[i]);
  }

  // Оновлення вікна
  window.display();
 }
 return 0;
}
 
