#ifndef PUT_HPP_INCLUDED
#define PUT_HPP_INCLUDED
#include <vector>
#include "automobil.hpp"
#include "novcic.hpp"
#include "prepreka.hpp"
using namespace std;
class Put{
private:
    SDL_Rect r; //posebna, ima i sirinu i duzinu u sebi, pa onda ne pisem posebno int sirina, duzina
    SDL_Renderer* renderer;
    Automobil* automobil;
    vector<Novcic*> novcici;
    vector<Prepreka*> prepreke;
    int brojac;
    int vremeStvaranja;

    int brojacZaNovcic;
    int vremeStvaranjaNovcica;

    SDL_Texture* image;

public:

    Put(int duzina, int sirina, SDL_Renderer* re)  {
    r.x = 200;
    r.y = 0;
    r.w = sirina;
    r.h = duzina;

    renderer = re;

    automobil = new Automobil(250,400,30,40, r.x, r.x + r.w, IMG_LoadTexture(renderer, "slike/auto.png"));

    brojac = 0;
    vremeStvaranja = 100;

    brojacZaNovcic = 0;
    vremeStvaranjaNovcica = 150;

    image = IMG_LoadTexture(renderer, "slike/put.png");

    }


    void update(SDL_Event event, bool * quit, int* score) { //izadje i ovo int doda poen

        brojac++;
        if (brojac > vremeStvaranja){  //vreme stvaranja * 0.01 sek // > je zbog zelenih, da bi se cesce pojavljivali, umesto ==
            stvoriPrepreku( 25, 15);
            brojac=0;
            vremeStvaranja = rand() % 300 + 100;
        }

        brojacZaNovcic++;
        if(brojacZaNovcic == vremeStvaranjaNovcica) {
            stvoriNovcic(15,15);
            brojacZaNovcic = 0;
            vremeStvaranja = rand() % 500 + 100;
        }

        for (int i = 0; i < novcici.size(); i++){
            novcici[i]->update(event);
        }

        for (int i=novcici.size() -1; i>=0; i--) {
            if(novcici[i] ->pokupio(automobil))  {
                *score +=1; //dodajemo poen, dovde smo samo namestili, ali nismo rekli da pokupi
                novcici.erase(novcici.begin() + i); //da obrisem novcic iz vektora, sa i-te pozicije
            }
        }


        for (int i = 0; i < prepreke.size(); i++){
            prepreke[i]->update(event);
            if (prepreke[i]->sudar(automobil)) {
                *quit = true;
            }
        }

        automobil->update(event);
    }

    void render(SDL_Renderer * renderer) {

        SDL_RenderCopy(renderer, image, NULL, &r);  //iscrtava pravugaonik tj put

        for (int i = 0; i < novcici.size(); i++){
            novcici[i]->render(renderer);
        }

        for (int i = 0; i < prepreke.size(); i++){
            prepreke[i]->render(renderer);
        }

        automobil->render(renderer);
    }

        void stvoriPrepreku( double s, double v) {
            //random broj izmedju 0 do 100
            int x = rand() % r.w + r.x; // % 100 + 250 , w sirina puta, x leva ivica puta
            Prepreka * p = new PravougaonikPrepreka(x, 0, s, v, IMG_LoadTexture(renderer, "slike/rock.png"));
            prepreke.push_back(p);
        }


         void stvoriNovcic( double s, double v) {
            //random broj izmedju 0 do 100
            int x = rand() % r.w + r.x; // % 100 + 250 , w sirina puta, x leva ivica puta
            Novcic * n = new Novcic(x, 0, s, v, IMG_LoadTexture(renderer, "slike/novcic.png"));
            novcici.push_back(n);
        }
};

#endif // PUT_HPP_INCLUDED
