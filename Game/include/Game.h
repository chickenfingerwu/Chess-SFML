#pragma once
#include "Player.h"
#include "Board.h"
#include "Piece.h"

class Game
{
    public:
        //if either one player is loser then set this to true
        bool quit = false;
        //game's board
        Board board;
        //2 player
        Player player1,player2;
        Game();
        void setupGame();
        void EndGame();
        void update();
        void choose1stTurn();
        //current turn, right now white player will always goes first
        int turn = 0;
        virtual ~Game();
};
