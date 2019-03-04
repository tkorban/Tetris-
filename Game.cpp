/*
 * Name: Tuerxun Kuerban
 * ID: 301326447
*/
#include "Game.h"

/*
 * initializing the game
 */
void Game::initialize(int width, int height) {
    sizes.x = width; // column of the game
    sizes.y = height; // row of the game
    vecColor = std::vector<std::vector<int> >(width, std::vector<int>(height, 0));
    while (!gameInfo.empty()) {
        gameInfo.pop();
    }
    gameInfo.push(Status::RUN);
    timeGap = SPEED;
}

/*
 * add a new piece to the game
 */
void Game::add() {
    newLocation.x = rand() % (int)sizes.getX();
    newLocation.y = (int)sizes.getY() - 1;
    piece = rand() % Piece::NUMOFSHAPES; // generating random piece
    location = rand() % Piece::POINTS;
    int value = rand() % (Piece::NUMOFCOLORS - 2) + 2; // generating random color except the black and white
    for (int i = 0; i < Piece::CELLS; i++) { // filling the piece
        color[i] = value;
    }
    // check the location of the piece
    int boundary = checkBoundary();
    while(boundary != Piece::INSIDE) {
        switch(boundary) {
            // move right
            case Piece::LEFT:
                newLocation += Piece::MOVERIGHT;
                break;
                // move left
            case Piece::RIGHT:
                newLocation += Piece::MOVELEFT;
                break;
                // move down
            case Piece::UP:
                newLocation += Piece::MOVEDOWN;
                break;
        }
        // recheck the boundary
        boundary = checkBoundary();
    }
    if (checkCollapse())
        gameInfo.push(Status::END);
}

/*
 * running the game
 */
void Game::run() {
    if (getState() != Status::END ) {
        int drop = dropRow();
        if (drop== Piece::COLLAPSE || drop == Piece::DOWN) {
            fillPieces();
            checkRemove();
            add();
        }
    }
}

/*
 * restart the game
 */
void Game::restart() {
    initialize((int)sizes.getX(), (int)sizes.getY());
    add();
}

/*
 * get the timeGap
 */
int Game::getTimeGap() const {
    return timeGap;
}

/*
 *  get the piece
 */
int Game::getPiece() const {
    return piece;
}

/*
 * get the location
 */
int Game::getLocation() const {
    return location;
}

/*
 * get the new location
 */
vec2 Game::getNewLocation() const {
    return newLocation;
}

/*
 * get the color
 */
int* Game::getColor() {
    return color;
}

/*
 * get game state
 */
Status Game::getState() const {
    if(!gameInfo.empty())
        return gameInfo.top();
    else
        return Status::EMPTY;
}

/*
 * get the size of vec2
 */
vec2 Game::getSize() const {
    return sizes;
}

/*
 * get the vec color
 */
std::vector<std::vector<int> >& Game:: getVecColor() {
    return vecColor;
}

/*
 * move piece based on the point
 */
int Game::movePiece(vec2 direction) {
    newLocation += direction;
    if (checkCollapse()) {
        newLocation -= direction;
        return Piece::COLLAPSE;
    }
    int boundary = checkBoundary();
    if (boundary != Piece::INSIDE) {
        newLocation -= direction;
        return boundary;
    }
}


/*
 * rotate the piece
 */
int Game::rotatePiece(int direction) {
    if (getState() != Status::END ) {
        location += direction;
        location %= Piece::POINTS;
        if (checkCollapse()) {
            location -= direction;
            if (location < 0)
                location = Piece::POINTS - 1;
            location %= Piece::POINTS;
            return Piece::COLLAPSE;
        }
        int boundary = checkBoundary();
        if (boundary != Piece::INSIDE) {
            location -= direction;
            if (location < 0)
                location = Piece::POINTS - 1;
            location %= Piece::POINTS;
            return boundary;
        }
    }
    return Piece::INSIDE;
}

/*
 * fill the piece
 */
void Game::fillPieces(){
    for (int i = 0; i < Piece::CELLS; i++) {
        int x = newLocation.x + Piece::differentPieces[piece][location][i].x;
        int y = newLocation.y + Piece::differentPieces[piece][location][i].y;
        if (x >= 0 && x < sizes.getX() && y >= 0 && y < sizes.getY()) {
            vecColor[x][y] = color[i];
        }
    }
}

/*
 * check whether can destroy any line
 */
void Game::checkRemove() {
    bool remove;
    do {
        remove = false;
        for (int i = 0; i < sizes.getY(); i++) {
            bool removeLine = true;
            for (int j = 0; j < sizes.getX(); j++) {
                if (vecColor[j][i] == Piece::BLACK) // whether it is empty or not
                    removeLine = false;
            }
            if (removeLine) { // if any row is full
                remove = true;
                removeRow(i);
                break;
            }
        }
    }
    while (remove);
}

/*
 * remove the specific row
 */
void Game::removeRow(int row) {
    std::vector<int>::iterator it;
    for (int i = 0; i < sizes.getX(); i++) {
        it = vecColor[i].begin();
        vecColor[i].erase(it + row, it + row + 1); // delete piece
        vecColor[i].push_back(Piece::BLACK); // put black on it
    }
}


int Game::dropRow() {
    if (getState() != Status::END ) {
        return movePiece(Piece::MOVEDOWN);
    }
    return Piece::INSIDE;
}

int Game::checkBoundary() {
    for (int i = 0; i < Piece::CELLS; i++) {
        int x = newLocation.x + Piece::differentPieces[piece][location][i].x;
        int y = newLocation.y + Piece::differentPieces[piece][location][i].y;
        if (y < 0)
            return Piece::DOWN;
        if (y >= sizes.getY())
            return Piece::UP;
        if (x < 0)
            return Piece::LEFT;
        if (x >= sizes.getX())
            return Piece::RIGHT;
    }
    return Piece::INSIDE;
}


bool Game::checkCollapse() {
    for (int i = 0; i < Piece::CELLS; i++) {
        int x = newLocation.x + Piece::differentPieces[piece][location][i].x;
        int y = newLocation.y + Piece::differentPieces[piece][location][i].y;
        if (x >= 0 && x < sizes.getX() && y >= 0 && y < sizes.getY() && vecColor[x][y])
            return true;
    }
    return false;
}