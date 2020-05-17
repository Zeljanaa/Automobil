
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>
using namespace std;

class Shape{
  public:
    virtual void draw(SDL_Renderer* renderer){
      // SDL_RenderDrawLine(renderer, 20, 40, 60, 40);
      // SDL_RenderDrawLine(renderer, 40, 20, 40, 60);
    };

    virtual void move(int, int){};
};

class Line:public Shape{
  public:
    Line(int, int, int, int);
    int x1, y1, x2, y2;
    void draw(SDL_Renderer*);
    void move(int, int);
};

class Circle:public Shape{
public:
  Circle(int, int, int);
  int xc;
  int yc;
  int r;
  void draw(SDL_Renderer*);
  void move(int, int);
};

Line::Line(int aX1, int aY1, int aX2, int aY2){
  x1 = aX1;
  y1 = aY1;
  x2 = aX2;
  y2 = aY2;
}

void Line::draw(SDL_Renderer* renderer){
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Line::move(int dX, int dY){
  x1 += dX;
  x2 += dX;
  y1 += dY;
  y2 += dY;
}

class Reket:public Line{
  public:
    Reket(int x1, int y1, int x2, int y2):Line(x1, y1, x2, y2){};
    void draw(SDL_Renderer*);
};

void Reket::draw(SDL_Renderer* renderer){
  SDL_RenderDrawLine(renderer, x1, y1-1, x2, y2-1);
  SDL_RenderDrawLine(renderer, x1, y1+1, x2, y2+1);
}

Circle::Circle(int aXc, int aYc, int aR){
    xc = aXc;
    yc = aYc;
    r = aR;
}

void Circle::draw(SDL_Renderer* renderer){
  int s = 30;
  float d_a = 2*M_PI/s;
  float angle = d_a;

  float x0, y0;
  float x1, y1;
  x1 = xc+r;
  y1 = yc;
  for (int i=0; i<s; i++){
    x0 = x1;
    y0 = y1;
    x1 = xc + cos(angle) * r;
    y1 = yc + sin(angle) * r;
    angle += d_a;
    SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
  }
}

void Circle::move(int dX, int dY){
  xc += dX;
  yc += dY;
}

void drawScore(int score, int total, TTF_Font* font, SDL_Renderer* renderer){
  SDL_Color white = {255, 255, 255};
  stringstream ss;
  ss << "[" << score<<"/"<<total << "]";
  SDL_Surface* sm = TTF_RenderText_Solid(font, ss.str().c_str(), white);
  SDL_Texture* poruka = SDL_CreateTextureFromSurface(renderer, sm);
  SDL_Rect poruka_box; //create a rect
  poruka_box.x = 320-sm->w/2;
  poruka_box.y = 200-2-sm->h;
  poruka_box.w = sm->w;
  poruka_box.h = sm->h;
  SDL_RenderCopy(renderer, poruka, NULL, &poruka_box);
}

/*
int main(int argc, char ** argv) {
    bool quit = false;
    SDL_Event event;

    Reket* reket = new Reket(320-20, 240, 320+20, 240);

    vector<Shape*> lista;
    lista.push_back(new Line(50, 200, 640-50, 200));
    lista.push_back(new Circle(320, 240, 30));
    lista.push_back(new Line(50, 280, 640-50, 280));

    lista.push_back(new Line(0, 0, 640-50, 480-50));
    lista.push_back(new Line(640-50, 0, 0, 480-50));


    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Programiranje 2 - Singidunum",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

    int ret = TTF_Init();
    TTF_Font* font = TTF_OpenFont("lazy.ttf", 24);

    int dx = 1;
    int dy = 0;
    int sx = 0;

    int score = 0;
    int total = 0;

    // main loop
    while (!quit){
        SDL_Delay(2);
        SDL_PollEvent(&event);
        // event handling
        switch (event.type){
            case SDL_MOUSEBUTTONUP:
                cout<<event.button.x<<event.button.y<<'\n';
                break;
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN: //SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        dx = -1;
                        break;
                    case SDLK_RIGHT:
                        dx = 1;
                        break;
                    case SDLK_UP:
                        dy = -1;
                        break;
                    case SDLK_DOWN:
                        dy = 1;
                        break;
                    case SDLK_r:
                        total = 0;
                        score = 0;
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                        if(dx != 0){
                          sx = dx;
                          dx = 0;
                          total++;
                          if(reket->x1>320-30 && reket->x2<320+30){
                              score++;
                          }
                        }else{
                          dx = sx;
                        }
                        break;
                    default:
                        break;
                }
                break;
          }
        int n = lista.size();
        // move objects
        reket->move(dx, dy);
        if(reket->x1<0)
          dx = 1;

        if(reket->x2>640)
          dx = -1;

        // clear window
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);
        drawScore(score, total, font, renderer);

        // render objects
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for(int i=0; i<n; i++){
          lista[i]->draw(renderer);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 100);
        reket->draw(renderer);

        // render window
        SDL_RenderPresent(renderer);
    }

    // cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
*/
