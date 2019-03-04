/*
 * Name: Tuerxun Kuerban
 * ID: 301326447
*/
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stack>
#include "Angel.h"
#include "Piece.h"

/*
 * controlling different stages of the game
 */
enum class Status {
    EMPTY,
    RUN,
    END
};

class Game {
private:
    std::stack<Status> gameInfo;     // stack
    std::vector<std::vector<int> > vecColor;     // color vector
    int timeGap;             // time
    int piece;        // piece
    int location;       // location of piece
    int color[Piece::CELLS];        // color of piece
    vec2 newLocation;       // new location of piece
    vec2 sizes; // size of the game(row, column)
    int dropRow();
    int checkBoundary(); // check the boundary for movement
    bool checkCollapse(); // check whether the piece is collapse
    void checkRemove();
    void removeRow(int);
    void fillPieces();
public:
    Game() {};
    void initialize(int width, int height);
    void add(); // generate new piece
    void run(); // run the game
    int rotatePiece(int); // rotate piece
    int movePiece(vec2); // move the piece
    void restart(); // restart the game
    /*
     * return each information for later user
     */
    int getTimeGap() const;
    int getPiece() const;
    int getLocation() const;
    vec2 getNewLocation() const;
    int* getColor();
    Status getState() const;
    vec2 getSize() const;
    std::vector<std::vector<int> >& getVecColor();
    static const int SPEED = 600; // falling speed of the piece
};
#endif