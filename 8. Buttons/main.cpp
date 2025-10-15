#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
#include "Button.h"

using namespace sf;

void btn0_onclick(Button& btn) { btn.setFillColor(Color::Blue); }

int main()
{
    RenderWindow window(VideoMode({ 800, 600 }), "Buttons");
    std::vector<Button> buttons =
    {
        Button({100.f, 100.f}, {200.f, 200.f}),
        Button({100.f, 400.f}, {200.f, 200.f})
    };

    buttons[0].onclick = btn0_onclick; // <-- Звичайна функція
    buttons[1].onclick = [](Button& btn) { // <-- Лямбда-вираз
        btn.setFillColor(Color::Yellow);
        btn.setSize(btn.getSize() + Vector2f({ 10.f, 0.f }));
    };

    Clock clock;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            // Обробка натискання миші
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto button = event->getIf<sf::Event::MouseButtonPressed>()->button;
                auto position = (Vector2f)event->getIf<sf::Event::MouseButtonPressed>()->position;
                // Якщо натиснуто ліву кнопку миші
                if (button == Mouse::Button::Left)
                {
                    // for (auto button : buttons)
                    for(int i = 0; i < buttons.size(); i++)
                    {
                        if (buttons[i].getGlobalBounds().contains(position))
                        {
                            // Викликаємо метод onclick класу Button 
                            // (для кожної кнопки буде свій)
                            buttons[i].onclick(buttons[i]);
                        }
                    }
                }
            }
        }
        float time = clock.restart().asSeconds();

        window.clear();
        for (int i = 0; i < buttons.size(); i++)
        {
            window.draw(buttons[i]);
        }        
        window.display();
    }
}
