class Display{
    private :
    int bg[36];
    const char* cmd_clear;
    int status;

    public :
    Display(int* board, int status);
    ~Display();
    void backgroundClear(void);
    void printBoard(void);
};