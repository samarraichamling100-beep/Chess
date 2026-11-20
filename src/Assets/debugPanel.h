


class Data{
    private:



    public:
    bool can_show_data = false;
    void draw_chess_grid(std::string( & ChessGrid)[8][8]){
        for(int col = 0;col < 8;col++){
            for(int row = 0;row < 8;row ++){
                DrawText(ChessGrid[col][row].c_str(),200 + row * 30,200 + col * 30,20,BLACK);
            }
        }
    }
    void check_data(){
        if (IsKeyDown(KEY_F5) && !can_show_data ){
            std::cout << "the data is being turned on " << std::endl;
            can_show_data = true;
            std::cout << can_show_data << std::endl;
        }
        if(IsKeyReleased(KEY_F5) && can_show_data){
            std::cout << "the data is being turned off " << std::endl;
            can_show_data = false;
            std::cout << can_show_data << std::endl;
        }
    }
    void draw_data(std::string( & ChessGrid)[8][8]){
        draw_chess_grid(ChessGrid);
    }  
};