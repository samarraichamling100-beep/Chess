
#pragma once
#include "../Assets\piecesSrc.h"



class BOARD{
    private:
    float XaxiesOffset = 100;
    float YaxiesOffset = 100;
    float cellsize     = 40;
    const char * rowNames[8] = {"h","g","f","e","d","c","b","a"};
    Vector2Int AttemptedToMovePos{};
    //So the mouse doesnt get detected twice
    int movecooldown{};

    public:
    std::string ChessGrid[8][8] = 
    {
        {"wr","wk","wb","wK","wq","wb","wk","wr"},
        {"wp","wp","wp","wp","wp","wp","wp","wp"},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"bp","bp","bp","bp","bp","bp","bp","bp"},
        {"br","bk","bb","bK","bq","bb","bk","br"}
    };
    void draw_board(){
        ClearBackground(SKYBLUE);
        for(unsigned int col = 1;col < 9;col++){
            for(unsigned int row = 1;row < 9;row++){
                Color CellColor;

                if(col == 1){
                    DrawText(rowNames[row - 1],XaxiesOffset + (row - 1) * cellsize,YaxiesOffset - 10,15,YELLOW);
                    if((col + row) % 2 == 1){
                        CellColor = BLACK;
                    }
                    else {
                        CellColor = WHITE;
                    }
                }
                else if((col + row) % 2 == 1){
                    CellColor = BLACK;
                }
                else {
                    CellColor = WHITE;
                }
                Rectangle CellRect = {XaxiesOffset + (row - 1) * cellsize,YaxiesOffset + (col - 1) * cellsize ,cellsize,cellsize};
                DrawRectangleRec(CellRect,CellColor);
            }
        DrawText(TextFormat("%i",col),XaxiesOffset - 10,YaxiesOffset + (col - 1) * cellsize,15,YELLOW);
        }
    }
    void DrawHightLightOfSelection(std::vector<PieceData> &PiecesList){
        for(PieceData Piece : PiecesList){
            point TextureLeft = {
                XaxiesOffset + Piece.BoardPosition.x * cellsize,
                YaxiesOffset + Piece.BoardPosition.y * cellsize,
                XaxiesOffset + Piece.BoardPosition.x * cellsize,
                YaxiesOffset + Piece.BoardPosition.y * cellsize + cellsize
            };
            point TextureRight = {
                XaxiesOffset + Piece.BoardPosition.x * cellsize + cellsize,
                YaxiesOffset + Piece.BoardPosition.y * cellsize ,
                XaxiesOffset + Piece.BoardPosition.x * cellsize + cellsize,
                YaxiesOffset + Piece.BoardPosition.y * cellsize + cellsize
            };
            point TextureTop = {
                XaxiesOffset + Piece.BoardPosition.x * cellsize,
                YaxiesOffset + Piece.BoardPosition.y * cellsize,
                XaxiesOffset + Piece.BoardPosition.x * cellsize + cellsize,
                YaxiesOffset + Piece.BoardPosition.y * cellsize
            };
            point TextureDown = {
                XaxiesOffset + Piece.BoardPosition.x * cellsize,
                YaxiesOffset + Piece.BoardPosition.y * cellsize + cellsize,
                XaxiesOffset + Piece.BoardPosition.x * cellsize + cellsize,
                YaxiesOffset + Piece.BoardPosition.y * cellsize + cellsize
            };
            if(Piece.selected){
                DrawLineEx({TextureLeft.x,TextureLeft.y},{TextureLeft.EndPointX,TextureLeft.EndPointY},4,RED);
                DrawLineEx({TextureRight.x,TextureRight.y},{TextureRight.EndPointX,TextureRight.EndPointY},4,RED);
                DrawLineEx({TextureTop.x,TextureTop.y},{TextureTop.EndPointX,TextureTop.EndPointY},4,RED);
                DrawLineEx({TextureDown.x,TextureDown.y},{TextureDown.EndPointX,TextureDown.EndPointY},4,RED);
            }
        }
    }
    bool IsValidWhitePawnMove(PieceData & Piece,Vector2Int AttemptedMove){
        if(AttemptedMove.y == Piece.BoardPosition.y + 1){
            return true;
        }
        if(Piece.has_moved == false && AttemptedMove.y == Piece.BoardPosition.y + 2){
            Piece.has_moved = true;
            return true;
        }
        else{
            std::cout << "That White Pawn Move is not valid" << std::endl;
            return false;
        }
    }
    bool IsValidBlackPawnMove(PieceData & Piece,Vector2Int AttemptedMove){
        if(AttemptedMove.y == Piece.BoardPosition.y - 1){
            return true;
        }
        if(Piece.has_moved == false && AttemptedMove.y == Piece.BoardPosition.y - 2){
            Piece.has_moved = true;
            return true;
        }
        else{
            std::cout << "That Black Pawn Move is not valid" << std::endl;
            return false;
        }
    }
    bool IsValidWhiteKnightMove(PieceData & Piece,Vector2Int AttemptedMove){
        if(AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0){
            std::cout << "The white move is not valid" << std::endl;

            return false;
        }
        else if(
            AttemptedMove.y == Piece.BoardPosition.y + 2 && AttemptedMove.x == Piece.BoardPosition.x + 1 
        ){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.y == Piece.BoardPosition.y + 2 && AttemptedMove.x == Piece.BoardPosition.x - 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.y == Piece.BoardPosition.y - 2 && AttemptedMove.x == Piece.BoardPosition.x - 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.y == Piece.BoardPosition.y - 2 && AttemptedMove.x == Piece.BoardPosition.x + 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.x == Piece.BoardPosition.x - 2 && AttemptedMove.y == Piece.BoardPosition.y + 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.x == Piece.BoardPosition.x - 2 && AttemptedMove.y == Piece.BoardPosition.y - 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.x == Piece.BoardPosition.x + 2 && AttemptedMove.y == Piece.BoardPosition.y + 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.x == Piece.BoardPosition.x + 2 && AttemptedMove.y == Piece.BoardPosition.y - 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else{
            std::cout << "The white knight move is not valid" << std::endl;
            return false;
        }
    }
    bool IsValidBlackKnightMove(PieceData & Piece,Vector2Int AttemptedMove){
        if(AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0){
            std::cout << "The white move is not valid" << std::endl;

            return false;
        }
        else if(
            AttemptedMove.y == Piece.BoardPosition.y + 2 && AttemptedMove.x == Piece.BoardPosition.x + 1 
        ){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.y == Piece.BoardPosition.y + 2 && AttemptedMove.x == Piece.BoardPosition.x - 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.y == Piece.BoardPosition.y - 2 && AttemptedMove.x == Piece.BoardPosition.x - 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.y == Piece.BoardPosition.y - 2 && AttemptedMove.x == Piece.BoardPosition.x + 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.x == Piece.BoardPosition.x - 2 && AttemptedMove.y == Piece.BoardPosition.y + 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.x == Piece.BoardPosition.x - 2 && AttemptedMove.y == Piece.BoardPosition.y - 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.x == Piece.BoardPosition.x + 2 && AttemptedMove.y == Piece.BoardPosition.y + 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else if(AttemptedMove.x == Piece.BoardPosition.x + 2 && AttemptedMove.y == Piece.BoardPosition.y - 1){
            std::cout << "The knight move is valid" << std::endl;
            return true;
        }
        else{
            std::cout << "The white knight move is not valid" << std::endl;
            return false;
        }
    }
    bool IsValidWhiteBishopMove(PieceData & Piece,Vector2Int AttemptedMove){
        if(AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0){
            std::cout << "The white move is not valid" << std::endl;
            return false;
        }
        int diffX = abs(AttemptedMove.x - Piece.BoardPosition.x);
        int diffY = abs(AttemptedMove.y - Piece.BoardPosition.y);

        if (diffX == 0) {
            return false; 
        }
        if (diffX == diffY) {
            std::cout << "Valid White Bishop Move" << std::endl;
            return true;
        }
            return false;
        }
    void MovePiece(std::vector<PieceData> & PiecesList,Vector2 Pointer){
        for(PieceData & piece : PiecesList){
            if(piece.selected){
                movecooldown ++;
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && movecooldown > 15)
                {
                    AttemptedToMovePos.x = int((Pointer.x - XaxiesOffset)/ cellsize);
                    AttemptedToMovePos.y = int((Pointer.y - XaxiesOffset) / cellsize);
                    std::cout << "piece.BoardPosition.x : " <<  piece.BoardPosition.x << "piece.BoardPosition.y : " << piece.BoardPosition.y << '\n';
                    if(piece.str_value == "wp"){
                        std::cout << "White pawm is found "<< std::endl;
                        if(IsValidWhitePawnMove(piece,AttemptedToMovePos)){
                            std::cout << "The White pawn move is vaild" << std::endl;
                            piece.BoardPosition.x = AttemptedToMovePos.x;
                            piece.BoardPosition.y = AttemptedToMovePos.y;
                            piece.selected = false;
                            std::cout << "Piece has been unselected" << std::endl;
                            movecooldown = 0;
                        }
                        else{
                            std::cout << "Piece has been unselected" << std::endl;
                            piece.selected = false;
                            movecooldown = 0;
                        }
                    }
                    if(piece.str_value == "bp"){
                        std::cout << "Black pawm is found "<< std::endl;
                        if(IsValidBlackPawnMove(piece,AttemptedToMovePos)){
                            std::cout << "The Black pawn move is vaild" << std::endl;
                            piece.BoardPosition.x = AttemptedToMovePos.x;
                            piece.BoardPosition.y = AttemptedToMovePos.y;
                            piece.selected = false;
                            std::cout << "Piece has been unselected" << std::endl;
                            movecooldown = 0;
                        }
                        else{
                            piece.selected = false;
                            movecooldown = 0;
                            std::cout << "Piece has been unselected" << std::endl;
                        }
                    }
                    if(piece.str_value == "bk"){
                        std::cout << "White Kinght is found " << '\n';
                        if(IsValidBlackKnightMove(piece,AttemptedToMovePos)){
                            std::cout << "The White Knight move is valid " << '\n';
                            piece.BoardPosition.x = AttemptedToMovePos.x;
                            piece.BoardPosition.y = AttemptedToMovePos.y;
                            piece.selected = false;
                            std::cout << "Piece has been unselected" << std::endl;
                            movecooldown = 0;
                        }
                        else{
                            piece.selected = false;
                            movecooldown = 0;
                            std::cout << "Piece has been unselected" << std::endl;
                        }
                    }
                    if(piece.str_value == "wb"){
                        std::cout << "White Bishop is found" << '\n';
                        if(IsValidWhiteBishopMove(piece,AttemptedToMovePos)){
                            std::cout << "The White bishop move is valid " << '\n';
                            piece.BoardPosition.x = AttemptedToMovePos.x;
                            piece.BoardPosition.y = AttemptedToMovePos.y;
                            piece.selected = false;
                            std::cout << "Piece has been unselected" << std::endl;
                            movecooldown = 0;
                        }
                        else{
                            piece.selected = false;
                            movecooldown = 0;
                            std::cout << "Piece has been unselected" << std::endl;
                        }
                    }
                }

            }
        }
    }
};