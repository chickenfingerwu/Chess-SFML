#include "Game.h"
#include "Board.h"
#include <stdlib.h>
#include <iostream>
Game::Game():board(8,8){
    setupGame();
}

void Game::setupGame(){
    player1.game = this;
    player2.game = this;
    player1.setColor(WHITE);
    player2.setColor(BLACK);
    board.setupPieces(&player1,&player2);
    player1.getAllyPiece();
    player1.getEnemyPiece();
    player2.getAllyPiece();
    player2.getEnemyPiece();
}

void Game::EndGame(){
    if(player1.isLoser || player2.isLoser)
        quit = true;
    if(quit){
        if(player2.isLoser)
            std::cout<<"Congrats! player 1 wins!! The other one, you suck at this game!!"<<std::endl;
        else
            std::cout<<"Congrats! player 2 wins!! The other one, you suck at this game!!"<<std::endl;
    }
}

void Game::choose1stTurn(){
    int seed = 0;
    srand(seed);
    int numb = rand() % 2 + 1;
    if(numb == 1)
        player1.goesFirst = true;
    else
        player2.goesFirst = true;
}
Game::~Game()
{
    //dtor
}
