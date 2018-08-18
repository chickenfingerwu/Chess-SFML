#pragma once
#include "Color.h"
#include "SFML/Graphics.hpp"
#include <vector>
class Game;
class Piece;
class Player
{
    public:
        Player();
        Game* game;
        bool goesFirst = false;
        //player's piece's color
        Color color;
        int score = 0;
        //if king is captured then set this to true
        bool isLoser = false;
        //check if a piece's player is the same as another piece's player
        bool operator== (const Player& player2);
        bool operator!= (const Player& player2);
        void setColor(Color color);
        std::vector <Piece*> AllyPieces;
        std::vector <Piece*> EnemyPieces;
        void getAllyPiece();
        void getEnemyPiece();
};
