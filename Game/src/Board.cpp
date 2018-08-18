#include "Board.h"
#include "Player.h"
#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include <iostream>

Board::Board(int width,int height){
    m_height = height;
    m_width = width;
    m_board = new Square**[m_height];
    for(int i=0;i<m_height;i++)
        m_board[i] = new Square*[m_width];
    for(int i=0;i<m_height;i++){
        for(int j=0;j<m_width;j++)
            m_board[i][j] = new Square(i,j);
    }
    BoardPiece = new Piece**[4];
    for(int i=0;i<4;i++)
        BoardPiece[i] = new Piece*[8];
}
void Board::setupPieces(Player* player1,Player* player2){
    setupPlayer1pieces(player1);
    setupPlayer2pieces(player2);
    setupPieceVector();
}
void Board::setupPieceVector(){
    for(int i=0;i<m_width;i++){
        whitePieces.push_back(BoardPiece[0][i]);
        whitePieces.push_back(BoardPiece[1][i]);
        blackPieces.push_back(BoardPiece[2][i]);
        blackPieces.push_back(BoardPiece[3][i]);
    }
}
void Board::setupPlayer2pieces(Player* player){
    for(int i=0;i<m_width;i++){
        if(i==0 || i==7)
            BoardPiece[0][i] = new Rook(player,m_board[0][i]);
        if(i==1 || i==6)
            BoardPiece[0][i] = new Bishop(player,m_board[0][i]);
        if(i==2 || i==5)
            BoardPiece[0][i] = new Knight(player,m_board[0][i]);
        if(i==3)
            BoardPiece[0][i] = new King(player,m_board[0][i]);
        if(i==4)
            BoardPiece[0][i] = new Queen(player,m_board[0][i]);
        BoardPiece[1][i] = new Pawn(player,m_board[1][i]);
        m_board[0][i]->hasPiece = true;
        m_board[1][i]->hasPiece = true;
    }
}
void Board::setupPlayer1pieces(Player* player){
    for(int i=0;i<m_width;i++){
        if(i==0 || i==7)
            BoardPiece[3][i] = new Rook(player,m_board[7][i]);
        if(i==1 || i==6)
            BoardPiece[3][i] = new Bishop(player,m_board[7][i]);
        if(i==2 || i==5)
            BoardPiece[3][i] = new Knight(player,m_board[7][i]);
        if(i==3)
            BoardPiece[3][i] = new King(player,m_board[7][i]);
        if(i==4)
            BoardPiece[3][i] = new Queen(player,m_board[7][i]);
        BoardPiece[2][i] = new Pawn(player,m_board[6][i]);
        m_board[6][i]->hasPiece = true;
        m_board[7][i]->hasPiece = true;
    }
}
bool Board::isValidMove(Piece* piece,int finalX,int finalY){
    piece->drawPath(finalX,finalY);
    if(isWithinBoard(finalX,finalY) && isNotOrigin(piece->PieceSquare,finalX,finalY) && PathIsNotObscured(piece->path)){
        if(m_board[finalX][finalY]->hasPiece){
            Piece* capture_piece = getPiece(m_board[finalX][finalY]);
            if(piece->canCapture(capture_piece)){
                if(capture_piece->m_type == KING)
                    capture_piece->m_player->isLoser = true;
                return true;
            }
            return false;
        }
        if(piece->isValidPath(finalX,finalY)){
            return true;
        }
        return false;
    }
    return false;
}

Piece* Board::getPiece(Square* square){
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            if(!BoardPiece[i][j]->isCaptured && *BoardPiece[i][j]->PieceSquare == *square)
                return BoardPiece[i][j];
        }
    }
    return 0;
}

bool Board::PathIsNotObscured(vector<vector<int>> &path){
    if(path[0].size() == 0){
        return true;
    }
    for(int i=0;i<path[0].size()-1;i++){
        if(m_board[path[0][i]][path[1][i]]->hasPiece)
        {
            return false;
        }
    }
    return true;
}

void Board::SetPiece(Piece* piece,Square* newSquare){
    if(newSquare->hasPiece){
        Piece* capturedPiece = getPiece(newSquare);
        capturedPiece->isCaptured = true;
    }
    piece->PieceSquare->hasPiece = false;
    piece->PieceSquare = newSquare;
    newSquare->hasPiece = true;
}

void Board::MovePiece(int finalX,int finalY,Piece* piece){
    SetPiece(piece,m_board[finalX][finalY]);
}
bool Board::validLeaping(Piece* piece,int** path){
    for(int i=0;i<sizeof(path[0]);i++){
        if(m_board[path[0][i]][path[1][i]]!=NULL)
            return false;
    }
    if(piece->m_type == KNIGHT)
        return true;
    if(piece->m_type == PAWN || piece->m_type == KING)
        return true;
    return false;
}
bool Board::isWithinBoard(int finalX, int finalY){
    if((finalX<m_width && finalX>=0) && (finalY>=0 && finalY<m_height)){
        return true;
    }
    return false;
}
bool Board::isNotOrigin(Square* piecesquare,int finalX,int finalY){
    if((finalX-piecesquare->x)!=0 || (finalY-piecesquare->y)!=0){
        return true;
    }
    return false;
}

Board::~Board(){
    for(int i=0;i<m_height;i++){
        for(int j=0;j<m_width;j++)
            delete m_board[i][j];
    }
    for(int i=0;i<m_height;i++)
        delete [] m_board[i];
    delete [] m_board;
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++)
            delete BoardPiece[i][j];
    }
    for(int i=0;i<4;i++)
        delete [] BoardPiece[i];
    delete [] BoardPiece;
}
