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
    text = "";
    textColor = {0, 0, 0, 255};
    color = {255, 255, 255, 255};
}

Button::Button(SDL_Color &textColor, SDL_Color &Color){
    setColor(color);
    setTextColor(textColor);
}

void Button::setText(string text){
    this->text = text;
}

void Button::setColor(SDL_Color &color){
    this->color = color;
}

void Button::setTextColor(SDL_Color &color){
    this->textColor = color;
}

void Button::render(SDL_Rect &rect){
    SDL_SetRenderDrawColor(Simple::renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(Simple::renderer, &rect);

    SDL_Surface* temp = TTF_RenderUTF8_Blended(Simple::font, text.c_str(), textColor);
    SDL_Texture* textImage = SDL_CreateTextureFromSurface(Simple::renderer, temp);
    SDL_RenderCopy(Simple::renderer, textImage, NULL, &rect);
    SDL_FreeSurface(temp);
    SDL_DestroyTexture(textImage);
}
