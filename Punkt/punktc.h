class Punkt{
    float x, y;
public:
    Punkt(float x = 0, float y = 0){
        this->x = x;
        this->y = y;
    }
    Punkt przesun(float a, float b);
    Punkt przesun(Punkt P);
    Punkt odbij();
    void wypisz();
};