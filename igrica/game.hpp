#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "mapa.hpp"
#include "score.hpp"
#include <sstream>
#include <SDL2/SDL_image.h>
#include <SDL2/sdl.h>


using namespace std;

class Game
{

private:
    SDL_Window* window;
    SDL_Renderer * renderer;
    SDL_Event event; //registruje neku akciju, pritisak na dugme, moramo da dodelimo svim klasama
    TTF_Font* font;

    bool quit;

    Mapa* mapa;
    int score;
public:

    Game() ///postavljamo sve stvari potrebne za igru, velicinu ekrana, score na 0, i pravimo mapu
    {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Igrica",
                                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        int ret = TTF_Init();
        font = TTF_OpenFont("lazy.ttf", 24);

        mapa = new Mapa(renderer);
        score = 0;

        quit = false;
    }
    void startGame() /// ovo je metoda koja se izvrsava sve dok se ne sudarimo
    {

        while (!quit) //ovaj uslov ce kasnije biti promenjen na proveru da li se auto sudario
        {

            SDL_Delay(10); //ceka 10ms 0.01 sekundi
            SDL_PollEvent(&event); /// gleda da li smo stisnuli neko dugme
            update(event); //pozove se na 0.01 sek
            render();
        }
    }

    void update(SDL_Event event) /// ovde se rade svi proracuni, pomera se auto, novcic, gleda se da li smo se sudarili
    {
        //pomeramo, deo koji reaguje na strelice

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN: //SDL_KEYUP:
            switch( event.key.keysym.sym )
            {
            case SDLK_ESCAPE:
                quit = true;
                break;

            }
        }

        mapa->update(event, &quit, &score); //moram dodati score

    }
    void render(){


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); /// ovde biramo boju pozadine
        SDL_RenderClear(renderer); /// ovde obrisemo ekran

        drawScore(score, font, renderer);  //iscrtava rezultat
        mapa->render(renderer); //mapu


        SDL_Texture* img = IMG_LoadTexture(renderer, "auto.jpg");
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = 200;
        r.h = 200;

        SDL_RenderCopy(renderer, img, NULL, &r);

        SDL_RenderPresent(renderer);
    }

    void drawScore(int score, TTF_Font* font, SDL_Renderer* renderer){ //da mi prikaze rezultat
        SDL_Color white = {255, 255, 255};
        stringstream ss;
        ss << "Score: " << score;

        SDL_Surface* sm = TTF_RenderText_Solid(font, ss.str().c_str(), white);
        SDL_Texture* poruka = SDL_CreateTextureFromSurface(renderer, sm);

        SDL_Rect poruka_box; //create a rect
        poruka_box.x = 70; /// pozicija teksta
        poruka_box.y = 200;
        poruka_box.w = sm->w;
        poruka_box.h = sm->h;
        SDL_RenderCopy(renderer, poruka, NULL, &poruka_box);
    }

    ~Game()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }

};

#endif // GAME_HPP_INCLUDED
