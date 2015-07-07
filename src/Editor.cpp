#include "Editor.h"

Editor::Editor()
{
    error = false;
    win_width = 1920;
    win_height = 960;
    win_title = "Picsou map creator";
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if ((window = SDL_CreateWindow(win_title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, win_width, win_height,
                                   SDL_WINDOW_SHOWN)) == NULL)
        {
            error = true;
            return;
        }
    if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE)) == NULL)
    {
        error = true;
        return;
    }
    if ((file = new MapFile("out.map")) == NULL)
        return;
    nb_bck_sprites = 2;
    nb_itm_sprites = 4;
    act_bck_sprite = 1;
    act_itm_sprite = 1;
    loadSprites("img/sheet1.bmp", "img/sheet2.bmp");
    //ctor
}

void Editor::loadSprites(std::string bckground_path, std::string items_path)
{
    SDL_Surface *img_bck, *img_itm;

    if ((img_bck = SDL_LoadBMP(bckground_path.c_str())) == NULL ||
        (img_itm = SDL_LoadBMP(items_path.c_str())) == NULL)
        {
            error = true;
            std::cerr << "Impossible to load sprite files" << std::endl;
            return;
        }
    if ((bck_sprites = SDL_CreateTextureFromSurface(renderer, img_bck)) == NULL ||
        (itm_sprites = SDL_CreateTextureFromSurface(renderer, img_itm)) == NULL)
        {
            error = true;
            std::cerr << "Impossible to create textures" << std::endl;
            return;
        }
    if ((bck_tab = (SDL_Rect *)malloc(sizeof(SDL_Rect) * nb_bck_sprites)) == NULL ||
        (itm_tab = (SDL_Rect *)malloc(sizeof(SDL_Rect) * nb_itm_sprites)) == NULL)
        {
            error = true;
            std::cerr << "Impossible to allocate rect arrays" << std::endl;
            return;
        }
    for (int i = 0; i < nb_bck_sprites; i++)
    {
        bck_tab[i].x = i * SPRITE_SIZE;
        bck_tab[i].y = 0;
        bck_tab[i].w = SPRITE_SIZE;
        bck_tab[i].h = SPRITE_SIZE;
    }
    for (int i = 0; i < nb_itm_sprites; i++)
    {
        itm_tab[i].x = i * SPRITE_SIZE;
        itm_tab[i].y = 0;
        itm_tab[i].w = SPRITE_SIZE;
        itm_tab[i].h = SPRITE_SIZE;
    }
}

void Editor::draw_tile(int x, int y, int bcktile, int itmtile)
{
    SDL_Rect dest;

    if (x < 0 || x > 49 || y < 0 || y > 29 || bcktile < 0 ||
        bcktile > nb_bck_sprites || itmtile > nb_itm_sprites || itmtile < 0)
        return;
    dest.w = SPRITE_SIZE;
    dest.h = SPRITE_SIZE;
    dest.x = x * 32;
    dest.y = y * 32;
    SDL_RenderCopy(renderer, bck_sprites, &bck_tab[bcktile], &dest);
    dest.w = SPRITE_SIZE;
    dest.h = SPRITE_SIZE;
    dest.x = x * 32;
    dest.y = y * 32;
    if (itmtile != 0)
        SDL_RenderCopy(renderer, itm_sprites, &itm_tab[itmtile - 1], &dest);
}

void Editor::draw_map()
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 50; j++)
            draw_tile(j, i, lvl.get_casemap(j, i), lvl.get_caseitem(j, i));
    }
}

void Editor::draw_icons()
{
    SDL_Rect dest;

    dest.w = SPRITE_SIZE;
    dest.h = SPRITE_SIZE;
    for (int i = 0; i < nb_itm_sprites; i++)
    {
        dest.x = 1600 + (i * 32) + 32;
        dest.y = 0;
        SDL_RenderCopy(renderer, itm_sprites, &itm_tab[i], &dest);
    }
    for (int i = 0; i < nb_bck_sprites; i++)
    {
        dest.x = 1600 + (i * 32) + 32;
        dest.y = 32;
        SDL_RenderCopy(renderer, bck_sprites, &bck_tab[i], &dest);
    }
}

void Editor::render()
{
    SDL_RenderClear(renderer);
    draw_map();
    draw_icons();
    SDL_RenderPresent(renderer);
}

void Editor::run()
{
    bool running = true;
    SDL_Event event;

    render();
    while (running && !error)
    {
        SDL_RenderPresent(renderer);
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
            running = false;
        else if (event.type == SDL_MOUSEBUTTONDOWN)
            click_event(event.button.button, event.button.x, event.button.y);
        else if (event.type == SDL_KEYDOWN)
            kbd_event(event.key.keysym.sym);
    }
}

void Editor::click_event(int button, int x, int y)
{
    if (button == SDL_BUTTON_RIGHT && x < 1600)
    {
        lvl.set_map(x / 32, y / 32, act_bck_sprite);
        draw_tile(x / 32, y / 32, lvl.get_casemap(x / 32, y / 32), lvl.get_caseitem(x / 32, y / 32));
    }
    else if (button == SDL_BUTTON_LEFT && x < 1600)
    {
        lvl.set_item(x / 32, y / 32, act_itm_sprite);
        draw_tile(x / 32, y / 32, lvl.get_casemap(x / 32, y / 32), lvl.get_caseitem(x / 32, y / 32));
    }
    else
    {
        if (y < 32 && x < (1600 + 32 * (nb_itm_sprites + 1)))
            act_itm_sprite = ((x - 1600) / 32);
        else if (y >= 32 && y < 64 && x < (1600 + 32 * (nb_bck_sprites + 1)))
            act_bck_sprite = ((x - 1600 - 32) / 32);
    }
}

void Editor::kbd_event(int key)
{
    if (key == SDLK_s)
    {
        file->append(&lvl);
        lvl.reset();
        render();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Status", "File recorded", NULL);
    }
}

Editor::~Editor()
{
    if (bck_sprites != NULL)
        SDL_DestroyTexture(bck_sprites);
    if (itm_sprites != NULL)
        SDL_DestroyTexture(itm_sprites);
    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if (window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    //dtor
}
