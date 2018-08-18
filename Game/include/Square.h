#pragma once

/*Board's square*/
class Square
{
    public:
        //square's coordinate
        int x;
        int y;
        //if this square has a piece then set to true
        bool hasPiece = false;
        //this function is used in another function to
        //get the piece occupying this square if there is one
        bool operator==(const Square& otherSquare);
        Square(int x,int y);
        ~Square();
};
