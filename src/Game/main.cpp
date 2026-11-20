
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include "..\System\board.h"
#include "..\System\collision.h"
#include "..\Assets\debugPanel.h"
int main()
{
    InitAudioDevice();
    const int screenWidth  = 520;
    const int screenHeight = 520;
    const int fps          = 60;
    PIECES pieces;
    BOARD board;
    Data  Data;
    InitWindow(screenWidth, screenHeight, "Chess");
    SetTargetFPS(fps);
    pieces.LoadPieces(board.ChessGrid);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        Data.check_data();
        if(Data.can_show_data){
            Data.draw_data(board.ChessGrid);
        }
        else{
            board.draw_board();
            pieces.Draw_Pieces();
            pieces.Check_SelectiomOfPieces();
            board.DrawHightLightOfSelection(pieces.PiecesList);
            board.MovePiece(pieces.PiecesList,pieces.MousePos,board.ChessGrid);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
