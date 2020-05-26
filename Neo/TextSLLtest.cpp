#include"textSLL.h"
using namespace sf;
int main()
{
    Textbox t;
    sf::RenderWindow window(VideoMode(450,450),"Test",Style::Default);
    sf::Font font;;
    font.loadFromFile("resources/fonts/consolas.ttf");
    t.setFont(font);
    t.setCharacterSize(20);
    int i;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                window.close();
                break;
                case Event::TextEntered:
                i=t.takeInput(event);
                break;
            }
        }
        window.clear(Color::Black);
        t.draw(window);
        window.display();
    }
    std::cout<<"Done";
    return 0;
}