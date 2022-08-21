#include "../inc/header.h"

SDL_Texture *background;
SDL_Texture *sprite_gg;
SDL_Texture *loading;
SDL_Texture *loading1;
SDL_Texture *cat_menu;
SDL_Texture *cat_load;
SDL_Event event;

typedef struct 
{
    SDL_Rect draw_rect;    // dimensions of button
    SDL_Texture *texture;

    bool pressed;
} button_t;


static void button_process_event(button_t *btn, const SDL_Event *ev) {
    // react on mouse click within button rectangle by setting 'pressed'
    if(ev->type == SDL_MOUSEBUTTONDOWN) {
        if(ev->button.button == SDL_BUTTON_LEFT &&
                ev->button.x >= btn->draw_rect.x &&
                ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w) &&
                ev->button.y >= btn->draw_rect.y &&
                ev->button.y <= (btn->draw_rect.y + btn->draw_rect.h)) {
            btn->pressed = true;
        }
    }
}

static bool button(SDL_Renderer *r, button_t *btn) {
    // draw button
    SDL_RenderCopy(r, btn->texture, NULL, &btn->draw_rect);

    // if button press detected - reset it so it wouldn't trigger twice
    if(btn->pressed) {
        btn->pressed = false;
        return true;
    }
    return false;
}

void menu_call(SDL_Window *window, SDL_Renderer *renderer, int lives)
{
    int i = 1;
    Mix_OpenAudio(44100, AUDIO_S16, 2, 4096);
    Mix_Music *music = Mix_LoadMUS("resource/soundtrack/menu.mp3");
    Mix_Music *button_sound = Mix_LoadMUS("resource/soundtrack/start_button.ogg");
    background = load_sprite("resource/images/menu.png", renderer);
    cat_menu = load_sprite("resource/images/cat_kachaet_golovoi1.png", renderer);
    
    if ( Mix_PlayMusic( music, -1) == -1 )
        return ;

    button_t start_button = 
    {
        .texture = load_sprite("resource/images/exit.png", renderer),
        .draw_rect = { .x =WINDOW_WIDTH/2-150 , .y = 500, .w = 300, .h = 150 },
    };

    button_t start_button2 = 
    {
        .texture = load_sprite("resource/images/play.png", renderer),
        .draw_rect = { .x =WINDOW_WIDTH/2-130 , .y = 200, .w = 260, .h = 200 },
    };

    enum 
    {
        STATE_IN_MENU,
        STATE_LEVEL1,
        STATE_EXIT
    } state = 0;

    bool quit = false;

    // animation loop
    while (1)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        
        // clear the window
        SDL_RenderClear(renderer);

        button_process_event(&start_button, &event);
        button_process_event(&start_button2, &event);
        
        if(state == STATE_IN_MENU) {
            if(button(renderer, &start_button)) {
                Mix_PlayMusic(button_sound, 1);
                state = STATE_EXIT;   // state change - button will not be drawn anymore
            }
            if(button(renderer, &start_button2)) {
                Mix_PlayMusic(button_sound, 1);
                state = STATE_LEVEL1;
            }
        } else if(state == STATE_LEVEL1) {
            SDL_DestroyTexture(start_button.texture);
            SDL_DestroyTexture(start_button2.texture);
            SDL_DestroyTexture(background);
            SDL_RenderClear(renderer);
            cat_load = load_sprite("resource/images/cat_load1.png", renderer);
            loading = load_sprite("resource/images/menu.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, cat_load, NULL, NULL);
            loading1 = load_sprite("resource/images/LoADing.png", renderer);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_RenderClear(renderer);
            loading1 = load_sprite("resource/images/LoADing!.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, cat_load, NULL, NULL);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_RenderClear(renderer);
            loading1 = load_sprite("resource/images/LoADing!!.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, cat_load, NULL, NULL);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_RenderClear(renderer);
            loading1 = load_sprite("resource/images/LoADing!!!.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, cat_load, NULL, NULL);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_RenderClear(renderer);
            loading1 = load_sprite("resource/images/LoADing.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, cat_load, NULL, NULL);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_DestroyTexture(cat_load);
            SDL_DestroyTexture(loading);
            SDL_DestroyTexture(loading1);

            // Stop music
            
            Mix_FreeMusic(button_sound);
            Mix_FreeMusic(music);
            Mix_CloseAudio();

            // level2_call(window, renderer, lives);
            level1_call(window, renderer, lives);
            quit = true;
            break;
        } else if (state == STATE_EXIT) {
            break;
        }

        SDL_RenderCopy(renderer, background, NULL, NULL);
        if (i % 49 == 0)
        {
            cat_menu = load_sprite("resource/images/cat_kachaet_golovoi1.png", renderer);
        }
        else if (i % 101 == 0)
        {
            cat_menu = load_sprite("resource/images/cat_kachaet_golovoi2.png", renderer);
        }
        else if (i % 152 == 0)
        {
            cat_menu = load_sprite("resource/images/cat_kachaet_golovoi3.png", renderer);
            i = 0;
        }
        i++;

        SDL_RenderCopy(renderer, cat_menu, NULL, NULL);
        SDL_RenderCopy(renderer, start_button.texture, NULL, &start_button.draw_rect);
        SDL_RenderCopy(renderer, start_button2.texture, NULL, &start_button2.draw_rect);

        SDL_RenderPresent(renderer);

        SDL_Delay(1000/60);
    }

    if (!quit)
    {
        SDL_DestroyTexture(cat_menu);
        SDL_DestroyTexture(start_button.texture);
        SDL_DestroyTexture(start_button2.texture);
        SDL_DestroyTexture(background);

    }
}

