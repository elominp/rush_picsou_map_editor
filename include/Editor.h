#ifndef EDITOR_H
#define EDITOR_H
#define SPRITE_SIZE 32

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "MapFile.h"

class Editor
{
    public:
        Editor();
        void loadSprites(std::string bckground_path, std::string items_path);
        void draw_tile(int x, int y, int bcktile, int itmtile);
        void draw_map();
        void draw_icons();
        void render();
        void run();
        void click_event(int button, int x, int y);
        void kbd_event(int key);
        void savemap();
        virtual ~Editor();
    protected:
    private:
        Map lvl;
        MapFile *file;
        SDL_Window *window;
        SDL_Renderer *renderer;
        int win_width;
        int win_height;
        std::string win_title;
        SDL_Texture *bck_sprites;
        SDL_Texture *itm_sprites;
        int nb_bck_sprites;
        int nb_itm_sprites;
        SDL_Rect *bck_tab;
        SDL_Rect *itm_tab;
        bool error;
        int act_bck_sprite;
        int act_itm_sprite;
};

#endif // EDITOR_H
