
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
    Sound MoveSound = setup_sound();
    public:

    Sound setup_sound(){
        Wave moveSound = LoadWave(R"(../GameGraphics\Sound\chessTakes.mp3)");
        float StartingSecond = 0.9f;
        float EndingSecond   = 1.3f;
        int StartFrame = (int)(StartingSecond * moveSound.sampleRate);
        int EndFrame = (int)(EndingSecond * moveSound.sampleRate);
        WaveCrop(&moveSound,StartFrame,EndFrame);
        Sound sound = LoadSoundFromWave(moveSound);
        return sound;
    }
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
                        CellColor = { 118, 150, 86, 255 }; ;
                    }
                    else {
                        CellColor = { 238, 238, 210, 255 };
                    }
                }
                else if((col + row) % 2 == 1){
                    CellColor = { 118, 150, 86, 255 }; ;
                }
                else {
                    CellColor = { 238, 238, 210, 255 };
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
                DrawLineEx({TextureLeft.x,TextureLeft.y},{TextureLeft.EndPointX,TextureLeft.EndPointY},4,BLUE);
                DrawLineEx({TextureRight.x,TextureRight.y},{TextureRight.EndPointX,TextureRight.EndPointY},4,BLUE);
                DrawLineEx({TextureTop.x,TextureTop.y},{TextureTop.EndPointX,TextureTop.EndPointY},4,BLUE);
                DrawLineEx({TextureDown.x,TextureDown.y},{TextureDown.EndPointX,TextureDown.EndPointY},4,BLUE);
            }
        }
    }
    bool IsValidPawnMove(PieceData & Piece,Vector2Int AttemptedMove,std::string (&ChessGrid)[8][8],PIECES & pieces,std::vector<PieceData> & PieceList){
        if(Piece.str_value == "wp"){
            if (AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0) {
                std::cout << "The white move is not valid (Out of bounds)" << std::endl;
                return false;
            }
            else if (Piece.BoardPosition.x == AttemptedMove.x && Piece.BoardPosition.y == AttemptedMove.y) {
                std::cout << "The white move is not valid (Cannot stay on the same square)" << std::endl;
                return false;
            }
            else if(AttemptedMove.y == Piece.BoardPosition.y + 1 && AttemptedMove.x == Piece.BoardPosition.x){
                return true;
            }
            //Why is this not working
            //Capture move
            //if right diagonal side the str_value of that square is not empty 
            else if(
                AttemptedMove.y == Piece.BoardPosition.y + 1 && 
                AttemptedMove.x == Piece.BoardPosition.x + 1 && 
                ChessGrid[Piece.BoardPosition.y + 1][Piece.BoardPosition.x + 1] != ""
            ){
            }
            else if(Piece.has_moved == false && AttemptedMove.y == Piece.BoardPosition.y + 2 && AttemptedMove.x == Piece.BoardPosition.x){
                Piece.has_moved = true;
                return true;
            }
            else{
                std::cout << "That White Pawn Move is not valid" << std::endl;
                return false;
            }
        }
        else if(Piece.str_value == "bp"){
            if (AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0) {
                std::cout << "The white move is not valid (Out of bounds)" << std::endl;
                return false;
            }
            else if (Piece.BoardPosition.x == AttemptedMove.x && Piece.BoardPosition.y == AttemptedMove.y) {
                std::cout << "The white move is not valid (Cannot stay on the same square)" << std::endl;
                return false;
            }
            else if(AttemptedMove.y == Piece.BoardPosition.y - 1 && AttemptedMove.x == Piece.BoardPosition.x){
                return true;
            }
            else if(Piece.has_moved == false && AttemptedMove.y == Piece.BoardPosition.y - 2 && AttemptedMove.x == Piece.BoardPosition.x){
                Piece.has_moved = true;
                return true;
            }
            else{
                std::cout << "That White Pawn Move is not valid" << std::endl;
                return false;
            }
        }
        return false;
    }
    bool IsValidKnightMove(PieceData & Piece,Vector2Int AttemptedMove){
        if(AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0){
            std::cout << "The white move is not valid" << std::endl;

            return false;
        }
        if(Piece.str_value == "wk"|| Piece.str_value == "bk")
        {
            if(AttemptedMove.y == Piece.BoardPosition.y + 2 && AttemptedMove.x == Piece.BoardPosition.x + 1 
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
        }

        return false;
    }

    bool IsValidBishopMove(PieceData &Piece, Vector2Int AttemptedMove) {
        if (AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0) {
            std::cout << "The white move is not valid (Out of bounds)" << std::endl;
            return false;
        }
        else if (Piece.BoardPosition.x == AttemptedMove.x && Piece.BoardPosition.y == AttemptedMove.y) {
            std::cout << "The white move is not valid (Cannot stay on the same square)" << std::endl;
            return false;
        }
        else if(Piece.str_value == "wb"|| Piece.str_value == "bb"){
            int dx = AttemptedMove.x - Piece.BoardPosition.x;
            int dy = AttemptedMove.y - Piece.BoardPosition.y;
            if (std::abs(dx) == std::abs(dy)) {
                std::cout << "The white move is not valid (Not a diagonal line)" << std::endl;
                return true;
            }
        }

        return false;
    }
    bool IsValidRookMove(PieceData &Piece, Vector2Int AttemptedMove){
        //used AI on movement
        if (AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0) {
            std::cout << "The white move is not valid (Out of bounds)" << std::endl;
            return false;
        }
        else if (Piece.BoardPosition.x == AttemptedMove.x && Piece.BoardPosition.y == AttemptedMove.y) {
            std::cout << "The white move is not valid (Cannot stay on the same square)" << std::endl;
            return false;
        }
        else if(Piece.str_value == "wr"|| Piece.str_value == "br"){
            if(Piece.BoardPosition.x == AttemptedMove.x || Piece.BoardPosition.y == AttemptedMove.y){
                return true;
            }
        }
        return false;
    }
    bool IsValidQueenMove(PieceData &Piece, Vector2Int AttemptedMove){
        //directly added rook and bishop movement
        if (AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0) {
            std::cout << "The white move is not valid (Out of bounds)" << std::endl;
            return false;
        }
        else if (Piece.BoardPosition.x == AttemptedMove.x && Piece.BoardPosition.y == AttemptedMove.y) {
            std::cout << "The white move is not valid (Cannot stay on the same square)" << std::endl;
            return false;
        }
        else if(Piece.str_value == "wq"|| Piece.str_value == "bq"){
            int dx = AttemptedMove.x - Piece.BoardPosition.x;
            int dy = AttemptedMove.y - Piece.BoardPosition.y;

            if(std::abs(dx) == std::abs(dy)){
                return true;
            }
            else if (Piece.BoardPosition.x == AttemptedMove.x || Piece.BoardPosition.y == AttemptedMove.y){
                return true;
            }

        }
        return false;
    }
    bool IsValidKingMove(PieceData &Piece, Vector2Int AttemptedMove){
        if(Piece.str_value == "wK"|| Piece.str_value == "bK"){
            if (AttemptedMove.y > 7 || AttemptedMove.y < 0 || AttemptedMove.x > 7 || AttemptedMove.x < 0) {
                std::cout << "The white move is not valid (Out of bounds)" << std::endl;
                return false;
            }
            else if (Piece.BoardPosition.x == AttemptedMove.x && Piece.BoardPosition.y == AttemptedMove.y) {
                std::cout << "The white move is not valid (Cannot stay on the same square)" << std::endl;
                return false;
            }
            else if(AttemptedMove.x == Piece.BoardPosition.x + 1 && AttemptedMove.y == Piece.BoardPosition.y){
                return true;      
            }
            else if(AttemptedMove.x == Piece.BoardPosition.x - 1 && AttemptedMove.y == Piece.BoardPosition.y){
                return true;      
            }
            else if(AttemptedMove.x == Piece.BoardPosition.x  && AttemptedMove.y == Piece.BoardPosition.y + 1){
                return true;      
            }
            else if(AttemptedMove.x == Piece.BoardPosition.x  && AttemptedMove.y == Piece.BoardPosition.y - 1){
                return true;      
            }
            else if(AttemptedMove.x == Piece.BoardPosition.x + 1  && AttemptedMove.y == Piece.BoardPosition.y + 1){
                return true;      
            }
            else if(AttemptedMove.x == Piece.BoardPosition.x - 1  && AttemptedMove.y == Piece.BoardPosition.y - 1){
                return true;      
            }
            else if(AttemptedMove.x == Piece.BoardPosition.x - 1  && AttemptedMove.y == Piece.BoardPosition.y + 1){
                return true;      
            }
            else if(AttemptedMove.x == Piece.BoardPosition.x + 1 && AttemptedMove.y == Piece.BoardPosition.y - 1){
                return true;      
            }
        }

        return false;
    }
    void MovePiece(std::vector<PieceData> & PiecesList,Vector2 Pointer,std::string( & ChessGrid)[8][8],PIECES & pieces,std::vector<PieceData>PieceList){
        for(PieceData & piece : PiecesList){
            if(piece.selected){
                movecooldown ++;
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && movecooldown > 15)
                {

                    AttemptedToMovePos.x = int((Pointer.x - XaxiesOffset)/ cellsize);
                    AttemptedToMovePos.y = int((Pointer.y - XaxiesOffset) / cellsize);

                    std::cout << "piece.BoardPosition.x : " <<  piece.BoardPosition.x << "piece.BoardPosition.y : " << piece.BoardPosition.y << '\n';
                    if(IsValidPawnMove(piece,AttemptedToMovePos,ChessGrid,pieces,PieceList)){
                        PlaySound(MoveSound);
                        std::cout << "The White pawn move is vaild" << std::endl;
                        ChessGrid[piece.BoardPosition.y][piece.BoardPosition.x] = "";
                        piece.BoardPosition.x = AttemptedToMovePos.x;
                        piece.BoardPosition.y = AttemptedToMovePos.y;
                        ChessGrid[ AttemptedToMovePos.y][ AttemptedToMovePos.x] = piece.str_value;
                        piece.selected = false;
                        std::cout << "Piece has been unselected" << std::endl;
                        movecooldown = 0;
                    }
                    else{
                        std::cout << "Piece has been unselected" << std::endl;
                        piece.selected = false;
                        movecooldown = 0;
                    }
                    
                    if(IsValidKnightMove(piece,AttemptedToMovePos)){
                        PlaySound(MoveSound);
                        std::cout << "The White king move is vaild" << std::endl;
                        ChessGrid[piece.BoardPosition.y][piece.BoardPosition.x] = "";
                        piece.BoardPosition.x = AttemptedToMovePos.x;
                        piece.BoardPosition.y = AttemptedToMovePos.y;
                        ChessGrid[ AttemptedToMovePos.y][ AttemptedToMovePos.x] = piece.str_value;
                        piece.selected = false;
                        std::cout << "Piece has been unselected" << std::endl;
                        movecooldown = 0;
                    }
                    else{
                        piece.selected = false;
                        movecooldown = 0;
                        std::cout << "Piece has been unselected" << std::endl;

                    }
                    if(IsValidBishopMove(piece,AttemptedToMovePos)){
                        PlaySound(MoveSound);
                        std::cout << "The White king move is vaild" << std::endl;
                        ChessGrid[piece.BoardPosition.y][piece.BoardPosition.x] = "";
                        piece.BoardPosition.x = AttemptedToMovePos.x;
                        piece.BoardPosition.y = AttemptedToMovePos.y;
                        ChessGrid[ AttemptedToMovePos.y][ AttemptedToMovePos.x] = piece.str_value;
                        piece.selected = false;
                        std::cout << "Piece has been unselected" << std::endl;
                        movecooldown = 0;
                    }
                    else{
                        piece.selected = false;
                        movecooldown = 0;
                        std::cout << "Piece has been unselected" << std::endl;

                    }
                    if(IsValidRookMove(piece,AttemptedToMovePos)){
                        PlaySound(MoveSound);
                        std::cout << "The White king move is vaild" << std::endl;
                        ChessGrid[piece.BoardPosition.y][piece.BoardPosition.x] = "";
                        piece.BoardPosition.x = AttemptedToMovePos.x;
                        piece.BoardPosition.y = AttemptedToMovePos.y;
                        ChessGrid[ AttemptedToMovePos.y][ AttemptedToMovePos.x] = piece.str_value;
                        piece.selected = false;
                        std::cout << "Piece has been unselected" << std::endl;
                        movecooldown = 0;
                    }
                    else{
                        piece.selected = false;
                        movecooldown = 0;
                        std::cout << "Piece has been unselected" << std::endl;

                    }
                    if(IsValidQueenMove(piece,AttemptedToMovePos)){
                        PlaySound(MoveSound);
                        std::cout << "The White king move is vaild" << std::endl;
                        ChessGrid[piece.BoardPosition.y][piece.BoardPosition.x] = "";
                        piece.BoardPosition.x = AttemptedToMovePos.x;
                        piece.BoardPosition.y = AttemptedToMovePos.y;
                        ChessGrid[ AttemptedToMovePos.y][ AttemptedToMovePos.x] = piece.str_value;
                        piece.selected = false;
                        std::cout << "Piece has been unselected" << std::endl;
                        movecooldown = 0;
                    }
                    else{
                        piece.selected = false;
                        movecooldown = 0;
                        std::cout << "Piece has been unselected" << std::endl;

                    }
                    if(IsValidKingMove(piece,AttemptedToMovePos)){
                        PlaySound(MoveSound);
                        std::cout << "The White king move is vaild" << std::endl;
                        ChessGrid[piece.BoardPosition.y][piece.BoardPosition.x] = "";
                        piece.BoardPosition.x = AttemptedToMovePos.x;
                        piece.BoardPosition.y = AttemptedToMovePos.y;
                        ChessGrid[ AttemptedToMovePos.y][ AttemptedToMovePos.x] = piece.str_value;
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
};