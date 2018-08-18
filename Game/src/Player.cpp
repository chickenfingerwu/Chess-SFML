#include "Player.h"
#include "Piece.h"
#include "Board.h"
#include "Game.h"
Player::Player()
{
}
void Player::setColor(Color color){
    this->color = color;
}

void Player::getAllyPiece(){
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            if(*game->board.BoardPiece[i][j]->m_player == *this){
                AllyPieces.push_back(game->board.BoardPiece[i][j]);
            }
        }
    }
}

bool Player::operator==(const Player& player2){
    if(this->color == player2.color)
        return true;
    else
        return false;
}

bool Player::operator!=(const Player& player2){
    if(this->color == player2.color)
        return false;
    else
        return true;
}

void Player::getEnemyPiece(){
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            if(*game->board.BoardPiece[i][j]->m_player == *this){
                EnemyPieces.push_back(game->board.BoardPiece[i][j]);
            }
        }
    }
}
