#ifndef MAPA_HPP_INCLUDED
#define MAPA_HPP_INCLUDED
#include "put.hpp"

class Mapa{

private:

Put*put;

public:

    Mapa(SDL_Renderer* renderer){
        put = new Put(1000, 250, renderer);
    }
    void update(SDL_Event event, bool * quit, int* score) {
    put->update(event, quit, score);

    }
    void render(SDL_Renderer * renderer) {
        put->render(renderer);
    }

};

#endif // MAPA_HPP_INCLUDED
