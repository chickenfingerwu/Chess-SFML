#include "Square.h"

Square::Square(int x,int y)
{
    this->x = x;
    this->y = y;
    hasPiece = false;
}

bool Square::operator==(const Square& otherSquare){
    if(this->x == otherSquare.x && this->y == otherSquare.y)
        return true;
    return false;
}

Square::~Square()
{
    //dtor
}
