#include <iostream>
#include "GUI.h"
#include "Game.h"
#include <stdlib.h>
/*update the game state and GUI (which sprite should be drawn) and print to console*/

void GUI::update(){
    //update the piece sprite state, if a piece is captured, we don't need to draw it
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            if(ChessGame.board.BoardPiece[i][j]->isCaptured)
                ToDrawOrNotToDraw[i][j] = false;
        }
    }
    //update the board state and print to console
    std::cout<<std::endl;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(ChessGame.board.m_board[i][j]->hasPiece){
                Piece* piece = ChessGame.board.getPiece(ChessGame.board.m_board[i][j]);
                std::cout<<piece->m_type<<" ";
            }
            else
                std::cout<<"e ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    //check if the game is over
    ChessGame.EndGame();
}

/*GUI constructor, the main game loop*/

GUI::GUI():window(sf::VideoMode(60*8,60*8),"Chess")
{
    window.setFramerateLimit(60);
    //Load game texture
    LoadGameTexture();
    //update game state and GUI
    update();
    //initialize all piece sprites state
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++)
            ToDrawOrNotToDraw[i][j]=true;
    }
    //pointer to the current player
    Player* current_player;
    //board's square original color
    sf::Color pre_square_color;
    //flag to check if the player has select a piece or not
    bool selected = false;
    //position of the selected piece's sprite
    int sprite_posX,sprite_posY;
    //the selected piece's square position
    int selected_posX,selected_posY;
    //SFML vector class to store mouse position
    sf::Vector2i mouse_pos;
    //player's selected piece for each turn
    Piece* selected_piece;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || ChessGame.quit)
                window.close();
            //if a mouse button is pressed and no piece has been selected
            if(!selected && event.type == sf::Event::MouseButtonPressed){
                //handle mouse input and see if any piece is selected
                selectPiece(event,selected_posX,selected_posY,sprite_posX,sprite_posY,selected);
                //if there is a piece where the player clicked:
                //- get the piece
                //- if the selected piece is not of the current player then continue
                //  else we make the selected piece's square red and continue
                if(ChessGame.board.m_board[selected_posX][selected_posY]->hasPiece){
                    selected_piece = ChessGame.board.getPiece(ChessGame.board.m_board[selected_posX][selected_posY]);
                    if(*selected_piece->m_player != *current_player){
                        std::cout<<"wrong piece dude!"<<std::endl;
                        selected = false;
                        continue;
                    }
                    fillSquareRed(pre_square_color,selected_posX,selected_posY);
                    continue;
                }
                //if there isn't a piece then continue
                else
                    continue;
            }
            //determine each player's turn
            switch(ChessGame.turn){
            case 0:
                current_player = &ChessGame.player1;
                break;
            case 1:
                current_player = &ChessGame.player2;
                break;
            }
            /*the player clicked at a position on the board:
            - if the destination has another piece then see if we can move the piece there
            - else we move the piece*/
            if(selected && event.type == sf::Event::MouseButtonPressed){
                mouse_pos = sf::Mouse::getPosition(window);
                /* if there is a piece*/
                if(ChessGame.board.m_board[mouse_pos.y/60][mouse_pos.x/60]->hasPiece){
                    //get the destination's piece
                    Piece* clicked_piece = ChessGame.board.getPiece(ChessGame.board.m_board[mouse_pos.y/60][mouse_pos.x/60]);
                    //if it's an ally piece then that piece becomes the selected piece and continue
                    if(*clicked_piece->m_player == *current_player){
                        selected = false;
                        ChessBoard[selected_posY][selected_posX].setFillColor(pre_square_color);
                        selectPiece(event,selected_posX,selected_posY,sprite_posX,sprite_posY,selected);
                        fillSquareRed(pre_square_color,selected_posX,selected_posY);
                        continue;
                    }
                }
                /*else we check if the move is valid or not*/
                if(ChessGame.board.isValidMove(selected_piece,mouse_pos.y/60,mouse_pos.x/60)){
                    //if the move is valid, we move the piece's sprite first and the actual piece next
                    moveSpriteToMouse(PieceSprite[sprite_posX][sprite_posY],mouse_pos);
                    ChessGame.board.MovePiece(mouse_pos.y/60,mouse_pos.x/60,selected_piece);
                    //bc the move is valid, we change player's turn
                    switch(ChessGame.turn){
                    case 1:
                        ChessGame.turn = 0;
                        break;
                    case 0:
                        ChessGame.turn = 1;
                        break;
                    }
                    update();
                }
                //return the red colored square back to its original color
                ChessBoard[selected_posY][selected_posX].setFillColor(pre_square_color);
                //after the player choose the move,
                //there is no longer a selected piece until the player select again
                selected = false;
            }
        }
        //drawing the game's graphics, basic SFML rendering
        window.clear();
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                window.draw(ChessBoard[i][j]);
            }
        }
        for(int i=0;i<4;i++){
            for(int j=0;j<8;j++){
                if(ToDrawOrNotToDraw[i][j]){
                    window.draw(PieceSprite[i][j]);
                }
            }
        }
        window.display();
    }
}

/*this function set the color of the selected piece's square on the board to red
to indicate a piece has been selected*/

void GUI::fillSquareRed(sf::Color &pre_square_color,int &x,int &y){
    pre_square_color = ChessBoard[y][x].getFillColor();
    ChessBoard[y][x].setFillColor(sf::Color(255,50,50));
}

/*handle mouse input to see if the player clicked on any piece*/

void GUI::selectPiece(sf::Event& event,int& selected_posX,int& selected_posY, int& sprite_posX,int& sprite_posY, bool &selected){
    //position on the board where the player clicked, we divide by 60 because it's the
    //length of each piece's sprite, this will convert the mouse position to the correct
    //coordinate on the board.
    selected_posX = sf::Mouse::getPosition(window).y/60;
    selected_posY = sf::Mouse::getPosition(window).x/60;
    //Go through all the piece's sprite
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            //if a piece's sprite is clicked and the piece hasn't been captured
            //then set the sprite position and the selected flag to true, then return
            if(ToDrawOrNotToDraw[i][j] && IsSpritePressed(PieceSprite[i][j],window) && !ChessGame.board.BoardPiece[i][j]->isCaptured)
            {
                sprite_posX = i;
                sprite_posY = j;
                selected = true;
                return;
            }
        }
    }
}

/*function to check if a sprite is pressed*/

bool GUI::IsSpritePressed(sf::Sprite &sprite,sf::RenderWindow &window){
    sf::IntRect temprect(sprite.getPosition().x,sprite.getPosition().y,sprite.getGlobalBounds().width,
                        sprite.getGlobalBounds().height);
    if(temprect.contains(sf::Mouse::getPosition(window))){
        return true;
    }
    return false;
}

/*function to move the sprite to where the player clicked*/

void GUI::moveSpriteToMouse(sf::Sprite &sprite,sf::Vector2i &mouse_pos){
    //coordinate of where we will move the sprite to
    //we minus mouse_pos.x%60 to get the position that
    //will coincide with the board's square.
    int x = mouse_pos.x - mouse_pos.x%60;
    int y = mouse_pos.y - mouse_pos.y%60;
    sprite.setPosition(x,y);
}

/*Load the game texture*/

void GUI::LoadGameTexture(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            ChessBoard[i][j].setSize(sf::Vector2f(60.0,60.0));
            ChessBoard[i][j].setPosition(60.0*i,60.0*j);
            if(i%2==0){
                if(j%2==0)
                    ChessBoard[i][j].setFillColor(sf::Color(100,100,255));
                else
                    ChessBoard[i][j].setFillColor(sf::Color::White);
            }
            if(i%2!=0){
                if(j%2!=0)
                    ChessBoard[i][j].setFillColor(sf::Color(100,100,255));
                else
                    ChessBoard[i][j].setFillColor(sf::Color::White);
            }
        }
    }
    for(int i=0;i<2;i++){
        for(int j=0;j<6;j++){
            if(i==0){
                if(j==0)
                    PieceTexture[i][j].loadFromFile("images/Rook.png");
                if(j==1)
                    PieceTexture[i][j].loadFromFile("images/Bishop.png");
                if(j==2)
                    PieceTexture[i][j].loadFromFile("images/Knight.png");
                if(j==3)
                    PieceTexture[i][j].loadFromFile("images/Queen.png");
                if(j==4)
                    PieceTexture[i][j].loadFromFile("images/King.png");
                if(j==5)
                    PieceTexture[i][j].loadFromFile("images/Pawn.png");
            }
            else if(i==1){
                if(j==0)
                    PieceTexture[i][j].loadFromFile("images/W_Rook.png");
                if(j==1)
                    PieceTexture[i][j].loadFromFile("images/W_Bishop.png");
                if(j==2)
                    PieceTexture[i][j].loadFromFile("images/W_Knight.png");
                if(j==3)
                    PieceTexture[i][j].loadFromFile("images/W_Queen.png");
                if(j==4)
                    PieceTexture[i][j].loadFromFile("images/W_King.png");
                if(j==5)
                    PieceTexture[i][j].loadFromFile("images/W_Pawn.png");
            }
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            if(i==0){
                if(j<3){
                    PieceSprite[i][j].setTexture(PieceTexture[0][j]);
                }
                if(j>=5&&j<8){
                    PieceSprite[i][j].setTexture(PieceTexture[0][7-j]);
                }
                if(j==3 || j==4){
                    PieceSprite[i][j].setTexture(PieceTexture[0][j]);
                }
                PieceSprite[i][j].setPosition(60.0*j,0.0);
            }
            if(i==1){
                PieceSprite[i][j].setTexture(PieceTexture[0][5]);
                PieceSprite[i][j].setPosition(60.0*j,60.0);
            }
            if(i==2){
                PieceSprite[i][j].setTexture(PieceTexture[1][5]);
                PieceSprite[i][j].setPosition(60.0*j,60.0*6);
            }
            if(i==3){
                if(j<3){
                    PieceSprite[i][j].setTexture(PieceTexture[1][j]);
                }
                if(j>=5&&j<8){
                    PieceSprite[i][j].setTexture(PieceTexture[1][7-j]);
                }
                if(j==3 || j==4){
                    PieceSprite[i][j].setTexture(PieceTexture[1][j]);
                }
                PieceSprite[i][j].setPosition(60.0*j,60.0*7);
            }
        }
    }
}

GUI::~GUI()
{
}
