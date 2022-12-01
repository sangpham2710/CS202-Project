/*!
 * \file    main.cpp
 * \brief   move a sprite with the keyboard (https://www.lucidarme.me/?p=6127)
 * \author  Philippe Lucidarme
 * \version 1.0
 * \date    12/18/2016
 */

 // SFML libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

// Sprite speed (high values = high speed)
#define         SPRITE_SPEED        5

int main()
{
    // _____________________
    // ::: Create window :::

    // Create a window with the same pixel depth as the desktop
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(sf::VideoMode(600,
        600),
        "SFML part 3");

    // Enable vertical sync. (vsync)
    window.setVerticalSyncEnabled(true);
    // When a key is pressed, sf::Event::KeyPressed will be true only once
    window.setKeyRepeatEnabled(false);

    // ____________________
    // ::: Load texture :::

    // Create texture from PNG file
    sf::Texture textureCar;
    if (!textureCar.loadFromFile("E:/CS202/project/pixel/yellow_car.png"))
    {
        std::cerr << "Error while loading texture" << std::endl;
        return -1;
    }
    // Enable the smooth filter. The texture appears smoother so that pixels are less noticeable.


    // _______________________________________
    // ::: Create sprite and apply texture :::

    // Create the sprite and apply the texture
    sf::Sprite spriteCar;
    spriteCar.setTexture(textureCar);
    sf::FloatRect spriteSize = spriteCar.getGlobalBounds();
    spriteCar.setOrigin(spriteSize.width / 2., spriteSize.height / 2.);


    // _________________
// ::: Main loop :::

// Sprite coordinates
    int x = window.getSize().x / 2.;
    int y = window.getSize().y / 2.;

    // Flags for key pressed
    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;

    sf::Clock timer;
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the window if a key is pressed or if requested
            if (event.type == sf::Event::Closed) window.close();

            //// If a key is pressed
            //if (event.type == sf::Event::KeyPressed)
            //{
            //    switch (event.key.code)
            //    {
            //        // If escape is pressed, close the application
            //    case  sf::Keyboard::Escape: window.close(); break;

            //        // Process the up, down, left and right keys
            //    case sf::Keyboard::Up:     upFlag = true; break;
            //    case sf::Keyboard::Down:    downFlag = true; break;
            //    case sf::Keyboard::Left:    leftFlag = true; break;
            //    case sf::Keyboard::Right:   rightFlag = true; break;
            //    default: break;
            //    }
            //}

            //// If a key is released
            //if (event.type == sf::Event::KeyReleased)
            //{
            //    switch (event.key.code)
            //    {
            //        // Process the up, down, left and right keys
            //    case sf::Keyboard::Up:     upFlag = false; break;
            //    case sf::Keyboard::Down:    downFlag = false; break;
            //    case sf::Keyboard::Left:    leftFlag = false; break;
            //    case sf::Keyboard::Right:   rightFlag = false; break;
            //    default: break;
            //    }
            //}
        }

        // Update coordinates
        if (leftFlag) x -= SPRITE_SPEED;
        if (rightFlag) x += SPRITE_SPEED;
        if (upFlag) y -= SPRITE_SPEED;
        if (downFlag) y += SPRITE_SPEED;

        // Check screen boundaries
        if (x < 0) x = window.getSize().x;
        if (x > (int)window.getSize().x + sprite.getTexture()->getSize().x) x = 0;
        if (y < 0) y = 0;
        if (y > (int)window.getSize().y) y = window.getSize().y;

        // Clear the window and apply grey background
        window.clear(sf::Color(127, 127, 127));
        
        x += 10;
        // Rotate and draw the sprite
        sprite.setPosition(x, y);
        //sprite.setRotation(timer.getElapsedTime().asSeconds() / M_PI * 90.f);
        window.draw(sprite);

        // Update display and wait for vsync
        window.display();
    }
    return 0;
}
