class Board{

    
    public :
    int bg[16];

    Board(void);
    ~Board();
    void add_random(void);
    void display(int status);
    int checker(void);

    bool move_up(void);
    bool move_down(void);
    bool move_right(void);
    bool move_left(void);
};