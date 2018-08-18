#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

/*GUI class to handle all the graphics and inputs from mouse stuff*/

class GUI
{
public:
    Game ChessGame;
    sf::Event event;
    sf::RenderWindow window;
    sf::Texture PieceTexture[2][6];
    sf::RectangleShape ChessBoard[8][8];
    sf::Sprite PieceSprite[4][8];
    //Sprite state: Decide which piece sprite should be drawn to screen
    bool ToDrawOrNotToDraw[4][8];
    GUI();
    ~GUI();
    //change a square's color to red to indicate the player's chosen piece
    void fillSquareRed(sf::Color &pre_square_color,int &x,int &y);
    void update();
    void selectPiece(sf::Event& event,int& selected_posX,int& selected_posY, int& sprite_posX,int& sprite_posY, bool &selected);
    bool IsSpritePressed(sf::Sprite &sprite,sf::RenderWindow &window);
    void moveSpriteToMouse(sf::Sprite &sprite,sf::Vector2i &mouse_pos);
    void LoadGameTexture();

};
