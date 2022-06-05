class Punkt{
    float x, y;
public:
    Punkt(float x = 0, float y = 0){
        this->x = x;
        this->y = y;
    }
    void przesun(float a, float b);
    void przesun(Punkt P);
    void odbij();
    void wypisz();
    float getX();
    float getY();
};