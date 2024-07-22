#include <simple_gui.hpp>

namespace Simple{
    SDL_Renderer *renderer = NULL;
    TTF_Font* font = NULL;
}

string Simple_GUI::getTag(){
    return this->tag;
}

void Simple_GUI::setTag(string tag){
    this->tag = tag;
}

Button::Button(){
    is_pressable = true;
    text = "";
    textColor = {0, 0, 0, 255};
    color = {255, 255, 255, 255};
    rect = {0, 0, 100, 50};
}

Button::Button(SDL_Color &textColor, SDL_Color &Color, bool Press){
    setColor(color);
    setTextColor(textColor);
    is_pressable = Press;
    rect = {0, 0, 100, 50};
}

void Button::setRect(int x, int y, int w, int h){
    rect.h = h;
    rect.w = w;
    rect.x = x;
    rect.y = y;
}

void Button::setRect(SDL_Rect &rect){
    this->rect = rect;
}

void Button::setText(string text){
    this->text = text;
}

void Button::setColor(SDL_Color color){
    this->color = color;
}

void Button::setTextColor(SDL_Color color){
    this->textColor = color;
}

void Button::render(){
    SDL_SetRenderDrawColor(Simple::renderer, color.r, color.g, color.b, color.a);
    mrect = rect;
    mrect.w += 10;
    mrect.x -= 5;
    SDL_RenderFillRect(Simple::renderer, &mrect);

    SDL_Surface* temp = TTF_RenderUTF8_Blended(Simple::font, text.c_str(), textColor);
    SDL_Texture* textImage = SDL_CreateTextureFromSurface(Simple::renderer, temp);
    SDL_RenderCopy(Simple::renderer, textImage, NULL, &rect);
    SDL_FreeSurface(temp);
    SDL_DestroyTexture(textImage);
}
