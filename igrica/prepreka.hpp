#ifndef PREPREKA_HPP_INCLUDED
#define PREPREKA_HPP_INCLUDED

class Prepreka{
protected:
    SDL_Rect r; //ova klasa predstaclja 4 atributa, x, y, sirinu, visinu
    SDL_Texture* image;
public:

    virtual void update(SDL_Event event) = 0;
    virtual void render(SDL_Renderer * renderer) = 0;

    virtual bool sudar(const Automobil* automobil) {

        SDL_Rect r1 = automobil->getRect();
        return SDL_HasIntersection(&r1, &r);


    }

};


class PravougaonikPrepreka : public Prepreka {
private:

public:
    PravougaonikPrepreka(double xx, double yy, double ss, double vv, SDL_Texture* texture) {

        r.x = xx;
        r.y = yy;
        r.w = ss;
        r.h = vv;
        image = texture;
    }

    void update(SDL_Event event) {
        r.y += 1; ///isto kao za novcic
    }


    void render(SDL_Renderer * renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderCopy(renderer, image, NULL, &r);  //iscrtava novcic
    }
};
#endif // PREPREKA_HPP_INCLUDED
