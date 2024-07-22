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

SDL_Color Button::hover(){
    SDL_Color temp = color;
    if(color.b > 20 && color.g > 20 && color.r > 20){
        temp.b -= 15;
        temp.r -= 15;
        temp.g -= 15;
    }
    else{
        temp.b += 15;
        temp.r += 15;
        temp.g += 15;
    }
    return temp;
}

Button::Button(){
    is_hovering = false;
    text = "";
    textColor = {0, 0, 0, 255};
    color = {255, 255, 255, 255};
    rect = {0, 0, 100, 50};
}

Button::Button(SDL_Color &textColor, SDL_Color &Color){
    is_hovering = false;
    setColor(color);
    setTextColor(textColor);
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

    if(is_hovering){
        SDL_Color tcl = hover();
        SDL_SetRenderDrawColor(Simple::renderer, tcl.r, tcl.g, tcl.b, tcl.a);
    }
    else SDL_SetRenderDrawColor(Simple::renderer, color.r, color.g, color.b, color.a);
    SDL_Rect mrect = rect;
    mrect.w += 10;
    mrect.x -= 5;
    SDL_RenderFillRect(Simple::renderer, &mrect);

    temp = TTF_RenderUTF8_Blended(Simple::font, text.c_str(), textColor);
    textImage = SDL_CreateTextureFromSurface(Simple::renderer, temp);
    SDL_RenderCopy(Simple::renderer, textImage, NULL, &rect);
    is_hovering = false;
}

void Button::clear(){
    SDL_FreeSurface(temp);
    SDL_DestroyTexture(textImage);
}
