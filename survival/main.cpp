#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>


sf::Vector2f NormalizeVector(sf::Vector2f vector)
{
	float m = sqrt(vector.x * vector.x + vector.y * vector.y);
	sf::Vector2f normalizedVector; 
    normalizedVector.x = vector.x / m; 
	normalizedVector.y = vector.y / m; 
	

    return normalizedVector;
}

int main()
{


    //---------------------------INITIALIZE---------------------------------
    //anti-aliasing
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    //create the window
    sf::RenderWindow window(sf::VideoMode({ 990, 540 }), "survival", sf::Style::Default, sf::State::Windowed, settings);
    window.setFramerateLimit(144);

    //-------------------------- - INITIALIZE---------------------------------
    

    //--------------------------------LOAD------------------------------------

    int XIndex = 0;
    int YIndex = 0;
    //player
    XIndex = 2;
    YIndex = 2;
    sf::Texture playerTexture("Assets/Player/Textures/SpriteSheet.png");
    sf::Sprite playerSprite(playerTexture);

	playerSprite.setPosition({ 825, 450 });
    playerSprite.setTextureRect(sf::IntRect({ XIndex * 64 , YIndex * 64 }, { 64, 64 }));
    playerSprite.setScale({ 1, 1 });


    //Skeleton
    XIndex = 0;
    YIndex = 0;
	sf::Texture SkeletonTexture("Assets/Skeleton/Textures/SpriteSheet.png");
	sf::Sprite SkeletonSprite(SkeletonTexture);

	SkeletonSprite.setPosition({ 200, 200 });
    SkeletonSprite.setTextureRect(sf::IntRect({ XIndex * 64 , YIndex * 64 }, { 64, 64 })); 
	SkeletonSprite.setScale({ 1, 1 });


    //creating bullet
	std::vector<sf::RectangleShape> bullets;
	float bulletSpeed = 5;  
    //--------------------------------LOAD------------------------------------
	
 
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


		//get the current position of the player
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
        
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{			
			bullets.push_back(sf::RectangleShape(sf::Vector2f(25, 10)));
			
            int i = bullets.size() - 1;
            bullets[i].setPosition(playerSprite.getPosition()); 
			bullets[i].setFillColor(sf::Color::Red); 
            

		}
        for (size_t i = 0; i < bullets.size(); i++) {
            sf::Vector2f bulletDirection = SkeletonSprite.getPosition() - bullets[i].getPosition(); 
            bulletDirection = NormalizeVector(bulletDirection);
            bullets[i].setPosition(bullets[i].getPosition() + bulletDirection * bulletSpeed);
        }

		//-------------------------------UPDATE--------------------------------


		//-------------------------------DRAW----------------------------------
        window.clear(sf::Color::Black);
        window.clear();
		window.draw(playerSprite);
		window.draw(SkeletonSprite);


		for (size_t i = 0; i < bullets.size(); i++) {
		    window.draw(bullets[i]);
        }

		//end the current frame
        window.display();
		//-------------------------------DRAW----------------------------------
    }
}

