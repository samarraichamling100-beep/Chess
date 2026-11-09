



struct Vector2Int{
    int x;
    int y;
};

struct point{
    float x;
    float y;
    float EndPointX;
    float EndPointY;
};
struct PieceData{
    Texture textur;
    Vector2Int BoardPosition{};
    bool selected{};
    bool has_moved{};
    std::string str_value{};
};

class PIECES{
    private:
    float XaxiesOffset = 100;
    float YaxiesOffset = 100;
    float cellsize = 40;
    public:
    Vector2 MousePos;
    int SelectCooldown{};
    std::vector<PieceData>PiecesList{};
    bool CheckCollisionBetweenTextureAndPointer(PieceData P){
        point TextureLeft = {
            XaxiesOffset + P.BoardPosition.x * cellsize,
            YaxiesOffset + P.BoardPosition.y * cellsize,
            XaxiesOffset + P.BoardPosition.x * cellsize,
            YaxiesOffset + P.BoardPosition.y * cellsize + cellsize
        };
        point TextureRight = {
            XaxiesOffset + P.BoardPosition.x * cellsize + cellsize,
            YaxiesOffset + P.BoardPosition.y * cellsize ,
            XaxiesOffset + P.BoardPosition.x * cellsize + cellsize,
            YaxiesOffset + P.BoardPosition.y * cellsize + cellsize
        };
        point TextureTop = {
            XaxiesOffset + P.BoardPosition.x * cellsize,
            YaxiesOffset + P.BoardPosition.y * cellsize,
            XaxiesOffset + P.BoardPosition.x * cellsize + cellsize,
            YaxiesOffset + P.BoardPosition.y * cellsize
        };
        point TextureDown = {
            XaxiesOffset + P.BoardPosition.x * cellsize,
            YaxiesOffset + P.BoardPosition.y * cellsize + cellsize,
            XaxiesOffset + P.BoardPosition.x * cellsize + cellsize,
            YaxiesOffset + P.BoardPosition.y * cellsize + cellsize
        };

        if(TextureLeft.x < MousePos.x && TextureRight.x > MousePos.x && TextureTop.y < MousePos.y && TextureDown.y > MousePos.y ){
            return true;
        }
        else {
            return false;
        }
    }
    void LoadPieces(std::string (&ChessGrid)[8][8]){
        for (int col = 0;col < 8 ;col++){
            for(int row = 0;row < 8;row++){
                if(ChessGrid[col][row] == "wp"){
                    PieceData Whitepawn;
                    Image WhitePawnImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/white-pawn.png)");
                    ImageResize(&WhitePawnImage,cellsize,cellsize);
                    Whitepawn.textur = LoadTextureFromImage(WhitePawnImage);
                    Whitepawn.BoardPosition = {row,col};
                    Whitepawn.str_value = "wp";
                    PiecesList.push_back(Whitepawn);
                }
                if(ChessGrid[col][row] == "wk"){
                    PieceData WhiteKnight;
                    Image WhiteKinghtImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/white-knight.png)");
                    ImageResize(&WhiteKinghtImage,cellsize,cellsize);
                    WhiteKnight.textur = LoadTextureFromImage(WhiteKinghtImage);
                    WhiteKnight.BoardPosition = {row,col};
                    WhiteKnight.str_value = "wk";
                    PiecesList.push_back(WhiteKnight);
                }
                
                if(ChessGrid[col][row] == "wb"){
                    PieceData WhiteBishop;
                    Image WhiteBishopImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/white-bishop.png)");
                    ImageResize(&WhiteBishopImage,cellsize,cellsize);
                    WhiteBishop.textur = LoadTextureFromImage(WhiteBishopImage);
                    WhiteBishop.BoardPosition = {row,col};
                    WhiteBishop.str_value = "wp";
                    PiecesList.push_back(WhiteBishop);
                }
                if(ChessGrid[col][row] == "wq"){
                    PieceData WhiteQueen;
                    Image WhiteQueenImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/white-queen.png)");
                    ImageResize(&WhiteQueenImage,cellsize,cellsize);
                    WhiteQueen.textur = LoadTextureFromImage(WhiteQueenImage);
                    WhiteQueen.BoardPosition = {row,col};
                    PiecesList.push_back(WhiteQueen);
                }
                if(ChessGrid[col][row] == "wK"){
                    PieceData WhiteKing;
                    Image WhiteKingImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/white-king.png)");
                    ImageResize(&WhiteKingImage,cellsize,cellsize);
                    WhiteKing.textur = LoadTextureFromImage(WhiteKingImage);
                    WhiteKing.BoardPosition = {row,col};
                    PiecesList.push_back(WhiteKing);
                }
                if(ChessGrid[col][row] == "wr"){
                    PieceData WhiteRook;
                    Image WhiteRookImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/white-rook.png)");
                    ImageResize(&WhiteRookImage,cellsize,cellsize);
                    WhiteRook.textur = LoadTextureFromImage(WhiteRookImage);
                    WhiteRook.BoardPosition = {row,col};
                    PiecesList.push_back(WhiteRook);
                }
                if(ChessGrid[col][row] == "bp"){
                    PieceData Blackpawn;
                    Image WhitePawnImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/black-pawn.png)");
                    ImageResize(&WhitePawnImage,cellsize,cellsize);
                    Blackpawn.textur = LoadTextureFromImage(WhitePawnImage);
                    Blackpawn.BoardPosition = {row,col};
                    Blackpawn.str_value = "bp";
                    PiecesList.push_back(Blackpawn);
                }
                if(ChessGrid[col][row] == "bk"){
                    PieceData BlackKinght;
                    Image BlackKinghtImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/black-knight.png)");
                    ImageResize(&BlackKinghtImage,cellsize,cellsize);
                    BlackKinght.textur = LoadTextureFromImage(BlackKinghtImage);
                    BlackKinght.BoardPosition = {row,col};
                    BlackKinght.str_value = "bk";
                    PiecesList.push_back(BlackKinght);
                }
                
                if(ChessGrid[col][row] == "bb"){
                    PieceData BlackBishop;
                    Image BlackBishopImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/black-bishop.png)");
                    ImageResize(&BlackBishopImage,cellsize,cellsize);
                    BlackBishop.textur = LoadTextureFromImage(BlackBishopImage);
                    BlackBishop.BoardPosition = {row,col};
                    PiecesList.push_back(BlackBishop);
                }
                if(ChessGrid[col][row] == "bq"){
                    PieceData BlackQueen;
                    Image BlackQueenImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/black-queen.png)");
                    ImageResize(&BlackQueenImage,cellsize,cellsize);
                    BlackQueen.textur = LoadTextureFromImage(BlackQueenImage);
                    BlackQueen.BoardPosition = {row,col};
                    PiecesList.push_back(BlackQueen);
                }
                if(ChessGrid[col][row] == "bK"){
                    PieceData BlackKing;
                    Image BlackKingImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/black-king.png)");
                    ImageResize(&BlackKingImage,cellsize,cellsize);
                    BlackKing.textur = LoadTextureFromImage(BlackKingImage);
                    BlackKing.BoardPosition = {row,col};
                    PiecesList.push_back(BlackKing);
                }
                if(ChessGrid[col][row] == "br"){
                    PieceData BlackRook;
                    Image BlackRookImage = LoadImage(R"(../GameGraphics/PiecesSourceFolder/black-rook.png)");
                    ImageResize(&BlackRookImage,cellsize,cellsize);
                    BlackRook.textur = LoadTextureFromImage(BlackRookImage);
                    BlackRook.BoardPosition = {row,col};
                    PiecesList.push_back(BlackRook);
                }
            }
        }
    }
    void Draw_Pieces(){
        for(PieceData Piece : PiecesList){
            DrawTexture
            (
                Piece.textur,
                Piece.BoardPosition.x * cellsize + XaxiesOffset,
                YaxiesOffset + Piece.BoardPosition.y * cellsize,
                WHITE
            );
        }
    }
    void Check_SelectiomOfPieces(){
        MousePos = GetMousePosition();
        for(PieceData & Piece : PiecesList){
            if(CheckCollisionBetweenTextureAndPointer(Piece)){
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    Piece.selected = true;
                    std::cout << "Piece is selected" << std::endl;
                }
            }
        }
    }

};