#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Car race");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Texture txBg("background.jpg");
    Sprite background(txBg);

    Texture txCar;
    Sprite car(txCar);
    Vector2f carPosition = { 100.f, 100.f };

    Vector2f camera({ 0.f, 0.f });
    Vector2f cameraOrigin((Vector2f)window.getSize() / 2.f);
    

    car.setTextureRect(IntRect({ 0, 0 }, { 100, 50 }));
    car.setOrigin({ 50.f, 25.f });
    car.setPosition(carPosition);

    Vector2f direction = { 1.f, 0.f };
    float speed = 100.f;
    float rotationSpeed = 90.f;

    Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float time = clock.restart().asSeconds();

        // camera += {0.f, 20 * time};
        camera = carPosition;

        if (Keyboard::isKeyPressed(Keyboard::Key::A)) car.rotate(degrees(-rotationSpeed * time));
        if (Keyboard::isKeyPressed(Keyboard::Key::D)) car.rotate(degrees(rotationSpeed * time));

        direction = Vector2f({ 1.f, 0.f }).rotatedBy(car.getRotation());
        carPosition += direction * speed * time;

        car.setPosition(carPosition - camera + cameraOrigin);
        window.clear();
        background.setPosition(-camera + cameraOrigin);
        window.draw(background);
        window.draw(car);
        window.display();
    }
}
