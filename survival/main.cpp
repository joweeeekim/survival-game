#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //---------------------------INITIALIZE---------------------------------
    //anti-aliasing
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    //create the window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "survival", sf::Style::Default, sf::State::Windowed, settings);

    //-------------------------- - INITIALIZE---------------------------------



    //--------------------------------LOAD------------------------------------

    sf::Texture playerTexture("Assets/Player/Textures/SpriteSheet.png");
    sf::Sprite playerSprite(playerTexture);

    int XIndex = 0;
	int YIndex = 0;
    playerSprite.setTextureRect(sf::IntRect({ XIndex * 64 , YIndex * 64 }, { 64, 64 }));
    playerSprite.setScale({ 1, 1 });
    
    //--------------------------------LOAD------------------------------------
	// run the program as long as the window is open
    while (window.isOpen())
    {   
		//-------------------------------UPDATE--------------------------------
		//check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
			//"close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();

        }
        
        
        sf::Vector2f position = playerSprite.getPosition(); 

        //going left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            playerSprite.setPosition(position + sf::Vector2f(1, 0));
        
        //going right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            playerSprite.setPosition(position + sf::Vector2f(-1, 0));
        
        //going up
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            playerSprite.setPosition(position + sf::Vector2f(0, -1));
        
        //going down
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            playerSprite.setPosition(position + sf::Vector2f(0, 1));
        


		//-------------------------------UPDATE--------------------------------


		//-------------------------------DRAW----------------------------------
        window.clear(sf::Color::Black);
        window.clear();
		window.draw(playerSprite);

		//end the current frame
        window.display();
		//-------------------------------DRAW----------------------------------
    }
}