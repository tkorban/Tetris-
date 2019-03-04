/*
 * Name: Tuerxun Kuerban
 * ID: 301326447
*/
#include "Game.h"
#include "Angel.h"
#include <ctime>
#include <cstdlib>

// game object
Game game;
// screen size
int width = 500;
int height = 800;
const int TOTALPOINTS = 1200;
vec4 board_colors[TOTALPOINTS];
const double SIZE = 35.0;
const int ROW = 20;
const int COLUMN = 10;
// location of vertex, array object and buffer
GLuint position, color, locationX, locationY, vertexObject[3], vertexBuffer[6];


/*
 * update the color
 */
void updateColor() {
    // get color from color Piece
    vec4 colors[24];
    for (int i = 0; i < 24; i++) {
        colors[i] = Piece::differentColors[game.getColor()[i / 6]];
    }
    // update the color
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[5]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);
}

/*
 * update the position
 */
void updatePosition() {
    // location of the piece
    double topLeft = 35.0;
    double z = 0.5;
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[4]);
    // initializing the each piece
    for (int i = 0; i < Piece::CELLS; i++) {
        // calculate the coordinates
        GLfloat x = game.getNewLocation().x + Piece::differentPieces[game.getPiece()][game.getLocation()][i].x;
        GLfloat y = game.getNewLocation().y + Piece::differentPieces[game.getPiece()][game.getLocation()][i].y;
        // create the 4 corners of the box
        vec4 p1 = vec4(topLeft + (x * topLeft), topLeft + (y * topLeft), z, 1);
        vec4 p2 = vec4(topLeft + (x * topLeft), topLeft * 2 + (y * topLeft), z, 1);
        vec4 p3 = vec4(topLeft * 2 + (x * topLeft), topLeft + (y * topLeft), z, 1);
        vec4 p4 = vec4(topLeft * 2 + (x * topLeft), topLeft * 2 + (y * topLeft), z, 1);
        // two points are used by two triangles each
        vec4 new_points[6] = {p1, p2, p3, p2, p3, p4};
        // put new data
        glBufferSubData(GL_ARRAY_BUFFER, i * 6 * sizeof(vec4), 6 * sizeof(vec4), new_points);

    }
}

/*
 * update display
 */
void updateDisplay() {
    // update the geometry
    updatePosition();
    // update the color
    updateColor();
    // redisplay
    glutPostRedisplay();
}

/*
 * add new piece
 */
void addNewPiece() {
    // add a new tile
    game.add();
    // update tile display
    updateDisplay();
}

/*
 * initialize the board
 */
void bindBoard() {
    int size = 64;
    vec4 points[size]; // array containing the 64 points
    vec4 colors[size]; // each vertex color
    // vertical lines
    for (int i = 0; i <= COLUMN; i++){
        points[2 * i] = vec4((SIZE + (SIZE * i)), SIZE, 0, 1);
        points[2 * i + 1] = vec4((SIZE + (SIZE * i)), SIZE * 21, 0, 1);
    }
    // horizontal lines
    for (int i = 0; i <= ROW; i++){
        points[22 + 2 * i] = vec4(SIZE, (SIZE + (SIZE * i)), 0, 1);
        points[22 + 2 * i + 1] = vec4(SIZE * 11, (SIZE + (SIZE * i)), 0, 1);
    }
    // set lines to white
    for (int i = 0; i < size; i++)
        colors[i] = Piece::differentColors[Piece::WHITE];
    // bind the first object
    glBindVertexArray(vertexObject[0]);
    glGenBuffers(2, &vertexBuffer[0]);
    // vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(vec4), points, GL_STATIC_DRAW);
    glVertexAttribPointer(position, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position);
    // vertex colors
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[1]);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(vec4), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color);
}

/*
 * update the game
 */
void updateGame() {
    // get current vector color
    std::vector<std::vector<int>> &vecColor = game.getVecColor();
    // set cells to black
    for (int i = 0; i < TOTALPOINTS; i++) {
        int x = i / 6 / (int)game.getSize().getX();
        int y = i / 6 % (int)game.getSize().getX();
        board_colors[i] = Piece::differentColors[vecColor[y][x]];
    }
    // update cell vertex colors
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[3]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, TOTALPOINTS * sizeof(vec4), board_colors);
}


/*
 * bind the piece
 */
void bindPiece() {
    // piece buffer vertex array
    glBindVertexArray(vertexObject[2]);
    glGenBuffers(2, &vertexBuffer[4]);
    // piece vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[4]);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(position, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position);
    // piece vertex colors
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[5]);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color);
}

/*
 * initialize the game board
 */
void initializeGameBoard() {
    vec4 board_points[TOTALPOINTS];
    double z = 0.5;
    // each cell is a box
    // this part of code idea is coming from Stack Overflow
    // and google
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COLUMN; j++) {
            vec4 p1 = vec4(SIZE + (j * SIZE), SIZE + (i * SIZE), z, 1);
            vec4 p2 = vec4(SIZE + (j * SIZE), SIZE * 2 + (i * SIZE), z, 1);
            vec4 p3 = vec4(SIZE * 2 + (j * SIZE), SIZE + (i * SIZE), z, 1);
            vec4 p4 = vec4(SIZE * 2 + (j * SIZE), SIZE * 2 + (i * SIZE), z, 1);
            board_points[6 * (10 * i + j)] = p1;
            board_points[6 * (10 * i + j) + 1] = p2;
            board_points[6 * (10 * i + j) + 2] = p3;
            board_points[6 * (10 * i + j) + 3] = p2;
            board_points[6 * (10 * i + j) + 4] = p3;
            board_points[6 * (10 * i + j) + 5] = p4;
        }
    }
    // buffer objects
    glBindVertexArray(vertexObject[1]);
    glGenBuffers(2, &vertexBuffer[2]);

    // vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[2]);
    glBufferData(GL_ARRAY_BUFFER, TOTALPOINTS * sizeof(vec4), board_points, GL_STATIC_DRAW);
    glVertexAttribPointer(position, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position);

    // vertex colors
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[3]);
    glBufferData(GL_ARRAY_BUFFER, TOTALPOINTS * sizeof(vec4), NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(color, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color);
}

/*
 * initialize the all stuff
 */

void Init() {
    // make sure each time can generate random numbers
    srand(time(0));
    // initialize the game
    game.initialize(COLUMN, ROW);
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );
    position = glGetAttribLocation(program, "myPosition");
    color = glGetAttribLocation(program, "myColor");
    // create 3 array objects
    glGenVertexArrays(3, vertexObject);
    bindBoard();
    initializeGameBoard();
    bindPiece();
    locationX = glGetUniformLocation(program, "xCoordinate");
    locationY = glGetUniformLocation(program, "yCoordinate");
    addNewPiece();
}

/*
 * timer function
 */
void run(int) {
    game.run();
    updateGame();
    updateDisplay();
    glutTimerFunc(game.getTimeGap(), run, 0);
}

/*
 * reshape all
 */
void reshape(GLsizei width1, GLsizei height1) {
    width = width1;
    height = height1;
    glViewport(0, 0, width1, height1);
}

/*
 * Display all
 */
void Display() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUniform1i(locationX, width);
    glUniform1i(locationY, height);
    glBindVertexArray(vertexObject[1]);
    // draw the board
    glDrawArrays(GL_TRIANGLES, 0, TOTALPOINTS);
    if (game.getState() != Status::END) {
        glBindVertexArray(vertexObject[2]);
        // draw the piece
        glDrawArrays(GL_TRIANGLES, 0, 24);
    }
    glBindVertexArray(vertexObject[0]);
    glDrawArrays(GL_LINES, 0, 64);
    glutSwapBuffers();
}

/*
 * quit and restart function
 */
void Keyboard(unsigned char key, int, int) {
    switch (key) {
        // 'q' key exit the game
        case 'q':
            exit (EXIT_SUCCESS);
            // 'r' key restarts the game
        case 'r':
            game.restart();
            updateGame();
            updateDisplay();
            break;
    }
    glutPostRedisplay();
}

/*
 * special keyboard function
 */
void Special(int key, int, int) {
    switch (key) {
        // move left
        case GLUT_KEY_LEFT:
            game.movePiece(Piece::MOVELEFT);
            updateDisplay();
            break;
            // rotate
        case GLUT_KEY_UP:
            game.rotatePiece(Piece::ROTATE);
            updateDisplay();
            break;
            // drop fast
        case GLUT_KEY_DOWN:
            game.movePiece(Piece::MOVEDOWN);
            updateDisplay();
            break;
            // move right
        case GLUT_KEY_RIGHT:
            game.movePiece(Piece::MOVERIGHT);
            updateDisplay();
            break;
        default:
            break;
    }
}


/*
 * Idle function
 */
void Idle(void) {
    glutPostRedisplay();
}

/*
 * main function
 */
int main(int argc, char **argv) {
    // screen size
    const int WIDTH = 700;
    const int HEIGHT = 200;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(WIDTH, HEIGHT);
    glutCreateWindow("Tetris");
    glewInit();
    Init();
    glutDisplayFunc(Display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(Special);
    glutKeyboardFunc(Keyboard);
    glutIdleFunc(Idle);
    glutTimerFunc(Game::SPEED, run, 0);
    glutMainLoop();
    return 0;
}