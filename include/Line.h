class Line{
    public :
    int* line[4];

    Line(int* a, int* b, int* c, int* d);
    ~Line();
    bool evolve(void);
    void show(void);
    int elt(int indice);
};