/*
 * Name: Tuerxun Kuerban
 * ID: 301326447
 * Piece.h: Specifing all the pieces with colors, and possible movements
*/
#ifndef PIECE_H
#define PIECE_H
#include <GL/glew.h>
#include "GL/gl.h"
#include <GL/freeglut.h>
#include "Angel.h"
namespace Piece {
    const int NUMOFSHAPES  = 7; // total 7 different shapes
    const int NUMOFCOLORS  = 7; // total 7 different colors
    const int POINTS = 4; // technically I can use one constant for 4
    const int CELLS  = 4; // but I do not want to confuse myself later
    const vec2 MOVELEFT(-1, 0); // moving left
    const vec2 MOVERIGHT(1, 0); // moving right
    const vec2 MOVEDOWN(0, -1); // moving down
    const int ROTATE =  1; // rotate the piece
    /*
     * Location of the piece
     */
    const int INSIDE =  0;
    const int UP = -1;
    const int DOWN = -2;
    const int LEFT = -3;
    const int RIGHT = -4;
    const int COLLAPSE = -5;
    /*
     * Default two famous color I used frequently in the other program
     */
    const int BLACK  = 0;
    const int WHITE  = 1;
    // 7 different colors
    const vec4 differentColors[NUMOFCOLORS] = {
            vec4(1.0, 1.0, 1.0, 1.0),  // White
            vec4(0.0, 0.0, 0.0, 1.0),  // Black
            vec4(1.0, 0.0, 0.0, 1.0),  // Red
            vec4(0.0, 1.0, 0.0, 1.0),  // Green
            vec4(0.0, 0.0, 1.0, 0.0),  // Blue
            vec4(1.0, 0.5, 0.0, 1.0),  // Orange
            vec4(1.0, 1.0, 0.0, 1.0),  // Yellow
    };
    // 7 different pieces
    const vec2 differentPieces[NUMOFSHAPES][POINTS][CELLS] = {
            // O Shape
            {
                    {vec2(0, -1), vec2(0, 0), vec2(-1, 0), vec2(-1, -1)},
                    {vec2(0, 0), vec2(-1, 0), vec2(-1, -1), vec2(0, -1)},
                    {vec2(-1, 0), vec2(-1, -1), vec2(0, -1), vec2(0, 0)},
                    {vec2(-1, -1), vec2(0, -1), vec2(0, 0), vec2(-1, 0)},
            },
            // I Shape
            {
                    {vec2(-2, 0), vec2(-1,  0), vec2(0, 0), vec2(1, 0)},
                    {vec2(0, -2), vec2(0, -1), vec2(0, 0), vec2(0, 1)},
                    {vec2(1, 0), vec2(0,  0), vec2(-1, 0), vec2(-2, 0)},
                    {vec2(0, 1), vec2(0,  0), vec2(0, -1), vec2(0, -2)}
            },
            // Z Shape
            {
                    {vec2(-1, -1), vec2(0, -1), vec2(0, 0), vec2(1, 0)},
                    {vec2(1, -1), vec2(1, 0), vec2(0, 0), vec2(0, 1)},
                    {vec2(1, 0), vec2(0, 0), vec2(0, -1), vec2(-1, -1)},
                    {vec2(0, 1), vec2(0, 0), vec2(1, 0), vec2(1, -1)}
            },
            // S Shape
            {
                    {vec2(1, -1), vec2(0, -1), vec2(0, 0), vec2(-1, 0)},
                    {vec2(1, 1), vec2(1, 0), vec2(0, 0), vec2(0, -1)},
                    {vec2(-1, 0), vec2(0, 0), vec2(0, -1), vec2(1, -1)},
                    {vec2(0, -1), vec2(0, 0), vec2(1, 0), vec2(1, 1)}
            },
            // J Shape
            {
                    {vec2(-1, -1), vec2(-1, 0), vec2(0, 0), vec2(1, 0)},
                    {vec2(1, -1), vec2(0, -1), vec2(0, 0), vec2(0, 1)},
                    {vec2(1, 1), vec2(1, 0), vec2(0, 0), vec2(-1, 0)},
                    {vec2(-1, 1), vec2(0, 1), vec2(0, 0), vec2(0, -1)}
            },
            // L Shape
            {
                    {vec2(-1, 1), vec2(-1, 0), vec2(0, 0), vec2(1, 0)},
                    {vec2(-1, -1), vec2(0, -1), vec2(0, 0), vec2(0, 1)},
                    {vec2(1, -1), vec2(1, 0), vec2(0, 0), vec2(-1, 0)},
                    {vec2(1,  1), vec2(0, 1), vec2(0, 0), vec2(0, -1)}
            },
            // T Shape
            {
                    {vec2(0, -1), vec2(-1, 0), vec2(0, 0), vec2(1, 0)},
                    {vec2(1, 0), vec2(0, -1), vec2(0, 0), vec2(0, 1)},
                    {vec2(0, 1), vec2(1, 0), vec2(0, 0), vec2(-1, 0)},
                    {vec2(-1, 0), vec2(0, 1), vec2(0, 0), vec2(0, -1)}
            }
    };
}
#endif

