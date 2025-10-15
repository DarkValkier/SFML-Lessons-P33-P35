#include <SFML/Graphics.hpp>

using namespace sf;

const Color BG_COLOR = Color(196, 215, 245, 0);

// Отримати найближчу точку прямокутника rectangle до точки point 
Vector2f getNearestPoint(Vector2f point, RectangleShape rectangle)
{
 float left = rectangle.getPosition().x;
 float right = rectangle.getPosition().x + rectangle.getSize().x;
 float top = rectangle.getPosition().y;
 float bottom = rectangle.getPosition().y + rectangle.getSize().y;
 return {
  std::clamp(point.x, left, right),
  std::clamp(point.y, top, bottom)
 };
}

// Чи стикається коло circle з точкою point
bool isCollide(CircleShape circle, Vector2f point)
{
 return (point - circle.getPosition()).length() - circle.getRadius() <= 0;
}

// Чи стикається коло circle з прямокутником rectangle
bool isCollide(CircleShape circle, RectangleShape rectangle)
{
 return isCollide(
  circle,
  getNearestPoint(circle.getPosition(), rectangle)
 );
}

// Виштовхування кола з прямокутника
void pushOutCircleFromRectangle(CircleShape &circle, RectangleShape rectangle)
{
 Vector2f push = circle.getPosition() - getNearestPoint(circle.getPosition(), rectangle);
 push = (push / push.length()) * std::max(circle.getRadius() - push.length(), 0.f);
 circle.move(push);
}

int main()
{
 RenderWindow window(VideoMode({ 800, 600 }), "SFML");

 // Створення зеленого кола
 CircleShape circle(50.f);
 circle.setFillColor(Color::Green);
 circle.setOrigin({
  circle.getRadius(),
  circle.getRadius()
  });

 // Створення синього прямокутника
 RectangleShape rectangle({ 100.f, 100.f });
 rectangle.setFillColor(Color::Blue);
 rectangle.setPosition((Vector2f)window.getSize() / 2.f - rectangle.getSize() / 2.f);

 // Створення індикатору найближчої точки на прямокутнику
 // до кола (червоне коло)
 CircleShape indicator(5.f);
 indicator.setFillColor(Color::Red);
 indicator.setOrigin({
  indicator.getRadius(),
  indicator.getRadius()
  });

 // Змінна для постійного збереження позиції мищі
 Vector2f mousePosition({ 0.f, 0.f });
 while (window.isOpen())
 {
  // Process events
  while (const std::optional event = window.pollEvent())
  {
   // Close window: exit
   if (event->is<sf::Event::Closed>())
    window.close();
   // Якщо мишка рухалась - записуємо її нові координати
   if (event->is<Event::MouseMoved>())
    mousePosition = (Vector2f)event->getIf<Event::MouseMoved>()->position;
  }
  window.clear(BG_COLOR);
  // Малюємо прямокутник
  window.draw(rectangle);
  // Знаходимо найближчу точку прямокутника до центру кола
  Vector2f nearestPoint = getNearestPoint(circle.getPosition(), rectangle);
  // Розраховуємо вектор руху для кола
  Vector2f direction = (mousePosition - circle.getPosition()) / 100.f;
  // Переміщуємо коло в сторону миші
  circle.move(direction);
  // Якщо коло стикнулося з прямокутником — відміняємо
  // останній рух
  if (isCollide(circle, rectangle)) {
   pushOutCircleFromRectangle(circle, rectangle);
  }

  // У разі зіткнення кола з прямокутником переформбовуємо його в рожевий колір
  if (isCollide(circle, rectangle))
   circle.setFillColor(Color::Magenta);
  else
   circle.setFillColor(Color::Green);
  // Малюємо зелене коло
  window.draw(circle);
  // Переміщуємо індикатор (червоне коло) до найближчої точки
  indicator.setPosition(nearestPoint);
  // Малюємо індикатор (червону точку)
  window.draw(indicator);

  window.display();
 }
 return 0;
}
