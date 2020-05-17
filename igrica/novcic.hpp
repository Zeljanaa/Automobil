#ifndef NOVCIC_HPP_INCLUDED
#define NOVCIC_HPP_INCLUDED
class Novcic{
private:
    SDL_Rect r;
    SDL_Texture* image;
public:
    Novcic(double xx, double yy, double ss, double vv, SDL_Texture* texture)  {

        r.x = xx;
        r.y = yy;
        r.w = ss;
        r.h = vv;
        image = texture;

    }

    void update(SDL_Event event) {
        r.y += 1; ///plus ide ka dole, znaci novcici idu dole
    }
    virtual bool pokupio(const Automobil* automobil) {

        SDL_Rect r1 = automobil->getRect();
        return SDL_HasIntersection(&r1, &r);


    }


    void render(SDL_Renderer * renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderCopy(renderer, image, NULL, &r);  //iscrtava novcic

    }

};


#endif // NOVCIC_HPP_INCLUDED
