
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include "..\System\board.h"
#include "..\System\collision.h"
int main()
{
    const int screenWidth  = 520;
    const int screenHeight = 520;
    const int fps          = 60;
    PIECES pieces;
    BOARD board;
    InitWindow(screenWidth, screenHeight, "Chess");
    SetTargetFPS(fps);
    pieces.LoadPieces(board.ChessGrid);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        board.draw_board();
        pieces.Draw_Pieces();
        pieces.Check_SelectiomOfPieces();
        board.DrawHightLightOfSelection(pieces.PiecesList);
        board.MovePiece(pieces.PiecesList,pieces.MousePos);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
