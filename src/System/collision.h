

class CollisionManager{
    public:
    float cellsize = 40.0f;
    float XaxiesOffset = 100.0f;
    float YaxiesOffset = 100.0f;
    int cooldown       = 0;
    void check_collision_piece(PieceData & piece,Vector2 Pointer,auto & MainPiece){
        Vector2Int OldWhitePawn = piece.BoardPosition;
        if(MainPiece.selected){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                piece.BoardPosition.x = int((Pointer.x - XaxiesOffset)/ cellsize);
                piece.BoardPosition.y = int((Pointer.y - XaxiesOffset) / cellsize);
                std::cout << "piece.BoardPosition.x : " <<  piece.BoardPosition.x << "piece.BoardPosition.y : " << piece.BoardPosition.y << '\n';
                MainPiece.BoardPosition.x = piece.BoardPosition.x;
                MainPiece.BoardPosition.y = piece.BoardPosition.y;
                MainPiece.selected = false;
            }
            else{
                if(piece.BoardPosition.x > 7 
                    || piece.BoardPosition.x < 0
                    || piece.BoardPosition.y > 7 
                    || piece.BoardPosition.y < 0){
                    piece.BoardPosition.x = OldWhitePawn.x;
                    piece.BoardPosition.y = OldWhitePawn.y;
                }
            }
        }
    }
};