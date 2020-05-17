#ifndef AUTOMOBIL_HPP_INCLUDED
#define AUTOMOBIL_HPP_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Automobil {
private:
     SDL_Rect r;
     double levaIvicaPuta;
     double desnaIvicaPuta;
     SDL_Texture* image;

public:
    Automobil(double xx, double yy, double s, double d, double leva, double desna, SDL_Texture* texture): levaIvicaPuta(leva), desnaIvicaPuta(desna) {
        r.x = xx;
        r.y = yy;
        r.w = s;
        r.h = d;
        image = texture;

    }

    SDL_Rect getRect() const {
        return r;
    }

    void update(SDL_Event event) { //ovde pomeramo sve, deo koji reaguje na strelice

        switch (event.type){
            case SDL_KEYDOWN: //SDL_KEYUP:
                switch(event.key.keysym.sym ){
                    case SDLK_LEFT:
                        if(r.x > levaIvicaPuta)
                            r.x -= 1;
                        break;
                    case SDLK_RIGHT:
                        if (r.x + r.w < desnaIvicaPuta)
                            r.x += 1;
                        break;
            }
        }
    }
    void render(SDL_Renderer * renderer) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderCopy(renderer, image, NULL, &r);  //iscrtava pravugaonik tj put
    }

};

#endif // AUTOMOBIL_HPP_INCLUDED
