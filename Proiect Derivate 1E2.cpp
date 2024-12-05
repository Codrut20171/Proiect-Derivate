#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

int main()
{
    // Creăm fereastra fullscreen în funcție de rezoluția ecranului
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Derivare formula", sf::Style::Fullscreen);

    // Setăm fontul pentru text
    sf::Font font;
    if (!font.loadFromFile("Font.otf")) {
        cout << "Nu am putut incarca fontul!" << endl;
        return -1;
    }

    // Creăm titlul
    sf::Text title("Derivare formula", font, 50);
    title.setFillColor(sf::Color::Red);

    // Creăm descrierea
    sf::Text description("1. Programul accepta ca operanzi numere\n"
        "   intregi si numere rationale (pentru cele\n"
        "   rationale se va folosi ':' ca separator),\n"
        "   iar ca si variabila, programul accepta 'x'.\n"
        "2. Notatia postfixata, derivata intai si\n"
        "   derivata de ordinul al doilea vor fi\n"
        "   salvate in fisierul proiecut.out.",
        font, 20);
    description.setFillColor(sf::Color::Red);

    // Creăm butoanele pentru meniu
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color(150, 50, 50)); // Culoare buton
    button.setOutlineColor(sf::Color::Red);
    button.setOutlineThickness(2);

    sf::Text buttonText("", font, 20);
    buttonText.setFillColor(sf::Color::White);

    // Setăm pozițiile pentru butoane (fixate în partea dreaptă)
    float buttonWidth = 200;
    float buttonHeight = 50;
    float offsetX = desktopMode.width - buttonWidth - 10; // 10 pixeli de la marginea dreaptă
    float startY = 100;

    // Butonul "Informatii"
    button.setPosition(offsetX, startY);
    buttonText.setPosition(offsetX + 20, startY + 15);
    buttonText.setString("Informatii");

    // Butonul "Preluati formula de la tastatura"
    startY += 70; // Distanță între butoane
    sf::RectangleShape button2(sf::Vector2f(buttonWidth, buttonHeight));
    button2.setFillColor(sf::Color(150, 50, 50));
    button2.setOutlineColor(sf::Color::Red);
    button2.setOutlineThickness(2);
    button2.setPosition(offsetX, startY);
    sf::Text buttonText2("Preluati formula de la tastatura", font, 20);
    buttonText2.setFillColor(sf::Color::White);
    buttonText2.setPosition(offsetX + 20, startY + 15);

    // Creăm butonul pentru comutarea modului fullscreen/windowed
    sf::RectangleShape fullscreenButton(sf::Vector2f(40, 40));  // Dimensiuni buton (corespunzătoare cu poza)
    fullscreenButton.setFillColor(sf::Color::Transparent);
    fullscreenButton.setOutlineColor(sf::Color::White);
    fullscreenButton.setOutlineThickness(2);
    fullscreenButton.setPosition(desktopMode.width - 50, desktopMode.height - 50); // Plasat în dreapta jos

    // Desenăm liniile care formează simbolul
    sf::VertexArray cross(sf::Lines, 4);
    cross[0].position = sf::Vector2f(desktopMode.width - 45, desktopMode.height - 40);
    cross[1].position = sf::Vector2f(desktopMode.width - 35, desktopMode.height - 40);
    cross[2].position = sf::Vector2f(desktopMode.width - 40, desktopMode.height - 45);
    cross[3].position = sf::Vector2f(desktopMode.width - 40, desktopMode.height - 35);

    // Loopul principal
    bool isFullscreen = true;  // Mod fullscreen activat la început
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Verificăm click-ul pe butonul fullscreen/windowed
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (fullscreenButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    if (isFullscreen)
                    {
                        // Comutăm în mod fereastră și permitem redimensionarea
                        window.create(sf::VideoMode(800, 600), "Derivare formula", sf::Style::Resize | sf::Style::Close);
                        isFullscreen = false;
                    }
                    else
                    {
                        // Comutăm în mod fullscreen
                        window.create(desktopMode, "Derivare formula", sf::Style::Fullscreen);
                        isFullscreen = true;
                    }
                }
            }
        }

        // Recalculez pozițiile elementelor
        // Poziția titlului va fi fixată, pentru a rămâne centrat oricum redimensionăm
        title.setPosition((window.getSize().x - title.getLocalBounds().width) / 2, 20);

        // Butoanele vor fi plasate mereu în partea dreaptă a ferestrei
        button.setPosition(window.getSize().x - buttonWidth - 10, 100);
        buttonText.setPosition(window.getSize().x - buttonWidth - 10 + 20, 100 + 15);

        button2.setPosition(window.getSize().x - buttonWidth - 10, 170);
        buttonText2.setPosition(window.getSize().x - buttonWidth - 10 + 20, 170 + 15);

        fullscreenButton.setPosition(window.getSize().x - 50, window.getSize().y - 50);
        cross[0].position = sf::Vector2f(window.getSize().x - 45, window.getSize().y - 40);
        cross[1].position = sf::Vector2f(window.getSize().x - 35, window.getSize().y - 40);
        cross[2].position = sf::Vector2f(window.getSize().x - 40, window.getSize().y - 45);
        cross[3].position = sf::Vector2f(window.getSize().x - 40, window.getSize().y - 35);

        // Poziționăm textul pentru descriere pentru a nu-l lărgi
        description.setPosition(20, 100);

        // Curățăm fereastra și desenăm elementele
        window.clear(sf::Color::Black);

        window.draw(title);          // Desenăm titlul
        window.draw(description);    // Desenăm descrierea

        window.draw(button);         // Desenăm butonul "Informatii"
        window.draw(buttonText);

        window.draw(button2);        // Desenăm butonul "Preluati formula de la tastatura"
        window.draw(buttonText2);

        // Desenăm butonul fullscreen/windowed
        window.draw(fullscreenButton);
        window.draw(cross);

        window.display();            // Actualizăm fereastra
    }

    return 0;
}
