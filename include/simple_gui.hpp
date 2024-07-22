#ifndef SIMPLE_GUI
#define SIMPLE_GUI

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

namespace Simple{
    extern SDL_Renderer *renderer;
    extern TTF_Font* font;
}

class Simple_GUI{
    private:
    unsigned int id;
    string tag = "root";
    public:

    string getTag();
    void setTag(string tag);

};


class Button : public Simple_GUI{
    private:
    SDL_Color textColor;
    string text;
    SDL_Color color;

    bool checkHover(SDL_Rect &rect);

    public:

    Button();
    Button(SDL_Color &textColor, SDL_Color &Color);

    void setText(string text);
    void setColor(SDL_Color &color);
    void setTextColor(SDL_Color &color);
    void render(SDL_Rect &rect);
};

#endif