#include "../inc/header.h"

SDL_Texture *background;
SDL_Texture *sprite_gg;
SDL_Texture *portal_key;
SDL_Texture *portal;
SDL_Texture *background_wall;
SDL_Texture *dragon;
SDL_Texture *dragon2;

SDL_Texture *loading;
SDL_Texture *loading1;
SDL_Texture *endgame;
SDL_Texture *load_cat;

SDL_Texture *lives_img;

SDL_Event event;


bool portal_open = false;

void level1_call(SDL_Window *window, SDL_Renderer *renderer, int lives)
{
    Mix_OpenAudio(44100, AUDIO_S16, 2, 4096);
    Mix_Music *music = Mix_LoadMUS("resource/soundtrack/level1.mp3");
    Mix_Music *yron = Mix_LoadMUS("resource/soundtrack/yron.mp3");
    Mix_Music *Quest_complete = Mix_LoadMUS("resource/soundtrack/Quest_complete.ogg");
    
    background = load_sprite("resource/images/menu.png", renderer);
    
    if ( Mix_PlayMusic( music, -1) == -1 )
        return ;

    sprite_gg = load_sprite("resource/images/stay.png", renderer);
    portal_key = load_sprite("resource/images/key.png", renderer);
    portal = load_sprite("resource/images/portal1.png", renderer);
    background = load_sprite("resource/images/labirint.png", renderer);
    dragon = load_sprite("resource/images/ghost.png", renderer);
    dragon2 = load_sprite("resource/images/ghost.png", renderer);
    
    // Walls - not displayed but needed for mechanic
    SDL_Surface *surface = IMG_Load("resource/images/background_wall_transparent.png");
    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        return ;
    }
    background_wall = SDL_CreateTextureFromSurface(renderer, surface);
    if (!background)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return ;
    }

    // Конструкция для добавления координат и задания размеров нашей текстуре
    SDL_Rect dest_gg;
    SDL_Rect dest_key;
    SDL_Rect dest_portal;
    SDL_Rect dest_background;
    SDL_Rect dest_background_wall;
    SDL_Rect dest_drag;
    SDL_Rect dest_drag2;

    SDL_Rect dest_lives;

    SDL_QueryTexture(sprite_gg, NULL, NULL, &dest_gg.w, &dest_gg.h);
    SDL_QueryTexture(portal_key, NULL, NULL, &dest_key.w, &dest_key.h);
    SDL_QueryTexture(portal, NULL, NULL, &dest_portal.w, &dest_portal.h);
    SDL_QueryTexture(background, NULL, NULL, &dest_background.w, &dest_background.h);
    SDL_QueryTexture(background_wall, NULL, NULL, &dest_background_wall.w, &dest_background_wall.h);
    SDL_QueryTexture(dragon, NULL, NULL, &dest_drag.w, &dest_drag.h);
    SDL_QueryTexture(dragon2, NULL, NULL, &dest_drag2.w, &dest_drag2.h);

    // Конструкция для добавления координат и задания размеров нашей текстуре

    dest_drag.x = 1370;
    dest_drag.y = 150;
    dest_drag.w = 60;
    dest_drag.h = 60;

    dest_drag2.x = 140;
    dest_drag2.y = 610;
    dest_drag2.w = 60;
    dest_drag2.h = 60;

    // Our character positions and size
    dest_gg.x = 0;
    dest_gg.y = 900;
    dest_gg.w = 40;
    dest_gg.h = 65;

    // Portal key positions and size
    dest_key.x = 835;
    dest_key.y = 575;
    dest_key.w = 30;
    dest_key.h = 60;

    // Portal positions and size
    dest_portal.x = 1775;
    dest_portal.y = 110;
    dest_portal.w = 100;
    dest_portal.h = 100;

    // Backgound positions and size
    dest_background.x = 0;
    dest_background.y = 0;
    dest_background.w = WINDOW_WIDTH + 40;
    dest_background.h = WINDOW_HEIGHT;

    // Backgound walls positions and size
    dest_background_wall.x = 0;
    dest_background_wall.y = 0;
    dest_background_wall.w = WINDOW_WIDTH;
    dest_background_wall.h = WINDOW_HEIGHT;

    // start sprite in center of screen
    float x_pos = 0;
    float y_pos = 900;
    float x_vel = 0;
    float y_vel = 0;

    // keep track of which inputs are given
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    // set to 1 when window close button is pressed
    int close_requested = 0;
    bool left_drag= true;
    bool right_drag = false;

    bool left_drag2 = true;
    bool right_drag2 = false;

    // gg animation flags
    // int Test_portal = 0;
    int Portal = 0;
    int w = 0;
    int s = 0;
    int a = 0;
    int d = 0;
    int flag_for_jamp = 0;

    bool quit = false;
    int delay = 0;
    
    // animation loop
    while (!close_requested)
    {
        Portal++;
        // ПЕРВЫЙ ДРАКОН !
        if(left_drag)
        {
            if (dest_drag.y>180)
            {
                dest_drag.y--;
            }
            else 
            {
                left_drag = false;
                right_drag = true;
            }   
        }
        
        else
        {
            if (dest_drag.y<900)
            {
                dest_drag.y++;
            }
            else 
            {
                left_drag = true;
                right_drag = false;
            }  

        }
        // ПЕРВЫЙ ДРАКОН !

        //ВТОРОЙ ДРАКОН!
        if(left_drag2)
        {
            if (dest_drag2.x>150)
            {
                dest_drag2.x--;
            }
            else 
            {
                left_drag2 = false;
                right_drag2 = true;
            }   
        }
        else
        {
            if (dest_drag2.x<540 )
            {
                dest_drag2.x++;
            }
            else 
            {
                left_drag2 = true;
                right_drag2 = false;
            }  

        }

        // process events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close_requested = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 1;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 1;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 1;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 1;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    up = 0;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    left = 0;
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    down = 0;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    right = 0;
                    break;
                }
                break;
            }
        }

        // determine velocity
        x_vel = y_vel = 0;
        if (up && !down)
        {
            y_vel = -SPEED;

            w++;
            // Анимация хотьбы в верх +++++++++++++ 
            a++;
            if (a % 3)
            {
                sprite_gg = load_sprite("resource/images/3Go_up_1.png", renderer);
            }
            else
            {
                sprite_gg = load_sprite("resource/images/3Go_up_2.png", renderer);
            }
        }

        // Движение в низ.
        if (down && !up)
        {
            y_vel = SPEED;

            // Анимация хотьбы в низ +++++++++++++ 
            s++;
            if (s % 3)
            {
                sprite_gg = load_sprite("resource/images/4Go_down_1.png", renderer);
            }
            else
            {
                sprite_gg = load_sprite("resource/images/4Go_down_2.png", renderer);
            }

        }
        // Движение в лево.
        if (left && !right)
        {
            flag_for_jamp = 1;
            x_vel = -SPEED;

            // Анимация хотьбы в лево +++++++++++++ 
            a++;
            if (a % 3)
            {
                sprite_gg = load_sprite("resource/images/1Go_left_1.png", renderer);
            }
            else
            {
                sprite_gg = load_sprite("resource/images/1Go_left_2.png", renderer);
            }
        } 
        // Движение в право.
        if (right && !left)
        {
            flag_for_jamp = 0;
            x_vel = SPEED;

            // Анимация хотьбы в право +++++++++++++ 
            d++;
            if (d % 3)
            {
                sprite_gg = load_sprite("resource/images/2Go_to_right_1.png", renderer);
            }
            else
            {
                sprite_gg = load_sprite("resource/images/2Go_to_right_2.png", renderer);
            }
        } 

        // update positions
        delay++;
        int good_to_go = 0;
        for (int i = 0; i <= 5; i++)
        {
            if (x_vel > 0 || y_vel > 0)
            {
                if (!check_color(surface, dest_gg.x + dest_gg.w + (x_vel / 60) - i, dest_gg.y + (y_vel / 60) - i, 100, 168, 103) &&
                    !check_color(surface, dest_gg.x + (x_vel / 60) - i, dest_gg.y + dest_gg.h + (y_vel / 60) - i, 100, 168, 103) &&
                    !check_color(surface, dest_gg.x + (dest_gg.w / 2) + (x_vel / 60) - i, dest_gg.y + (y_vel / 60) - i, 100, 168, 103) &&
                    !check_color(surface, dest_gg.x + (x_vel / 60) - i, dest_gg.y + (dest_gg.h / 2) + (y_vel / 60) - i, 100, 168, 103))
                {
                    good_to_go++;
                }
            }

            else
            {
                if (!check_color(surface, dest_gg.x + (x_vel / 60) - i, dest_gg.y + (y_vel / 60) - i, 100, 168, 103))
                {
                    good_to_go++;
                }
            }
        }
        if (good_to_go >= 4)
        {
            x_pos += x_vel / 60;
            y_pos += y_vel / 60;
        }        

        // collision detection with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest_gg.w) x_pos = WINDOW_WIDTH - dest_gg.w;
        if (y_pos >= WINDOW_HEIGHT - dest_gg.h) y_pos = WINDOW_HEIGHT - dest_gg.h;

        // set the positions in the struct
        dest_gg.y = (int) y_pos;
        dest_gg.x = (int) x_pos;

        // Check collision with ghost1
        if ((dest_gg.x >= dest_drag.x && dest_gg.y >= dest_drag.y && dest_gg.x <= dest_drag.x + dest_drag.w && dest_gg.y <= dest_drag.y + dest_drag.h) || 
            (dest_gg.x + dest_gg.w >= dest_drag.x && dest_gg.x + dest_gg.w <= dest_drag.x + dest_drag.w && dest_gg.y <= dest_drag.y && dest_gg.y >= dest_drag.y - dest_drag.h))
        {
            Mix_PlayMusic(yron, 1);
            SDL_Delay(500);
            lives--;
            if (lives == 0)
            {
                SDL_DestroyTexture(portal_key);
                SDL_DestroyTexture(portal);
                SDL_DestroyTexture(background_wall);
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(sprite_gg);
                SDL_DestroyTexture(dragon);
                SDL_DestroyTexture(dragon2);
                portal_open = false;

                endgame = load_sprite("resource/images/GAME_OVER_with_ghost.png", renderer);
                
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, endgame, NULL, NULL);
                SDL_RenderPresent(renderer);
                SDL_Delay(5000);
                SDL_DestroyTexture(endgame);

                Mix_FreeMusic(yron);
                Mix_FreeMusic(music);
                Mix_CloseAudio();

                menu_call(window, renderer, 3);
                quit = true;
                break;
            }
            else
            {
                SDL_DestroyTexture(portal_key);
                SDL_DestroyTexture(portal);
                SDL_DestroyTexture(background_wall);
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(sprite_gg);
                SDL_DestroyTexture(dragon);
                SDL_DestroyTexture(dragon2);
                portal_open = false;

                Mix_FreeMusic(yron);
                Mix_FreeMusic(music);
                Mix_CloseAudio();

                level1_call(window, renderer, lives);
                quit = true;
                break;
            }
        }

        // Check collision with ghost2
        if ((dest_gg.x >= dest_drag2.x && dest_gg.y <= dest_drag2.y && dest_gg.x <= dest_drag2.x + dest_drag2.w && dest_gg.y >= dest_drag2.y - dest_drag2.h) || 
            (dest_gg.x + dest_gg.w >= dest_drag2.x && dest_gg.x + dest_gg.w <= dest_drag2.x + dest_drag2.w && dest_gg.y >= dest_drag2.y && dest_gg.y <= dest_drag2.y + dest_drag2.h))
        {
            Mix_PlayMusic(yron, 1);
            SDL_Delay(500);
            lives--;
            if (lives == 0)
            {
                SDL_DestroyTexture(portal_key);
                SDL_DestroyTexture(portal);
                SDL_DestroyTexture(background_wall);
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(sprite_gg);
                SDL_DestroyTexture(dragon);
                SDL_DestroyTexture(dragon2);
                portal_open = false;

                endgame = load_sprite("resource/images/GAME_OVER_with_ghost.png", renderer);
                
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, endgame, NULL, NULL);
                SDL_RenderPresent(renderer);
                SDL_Delay(5000);
                SDL_DestroyTexture(endgame);

                Mix_FreeMusic(yron);
                Mix_FreeMusic(music);
                Mix_CloseAudio();

                menu_call(window, renderer, 3);
                quit = true;
                break;
            }
            else
            {
                SDL_DestroyTexture(portal_key);
                SDL_DestroyTexture(portal);
                SDL_DestroyTexture(background_wall);
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(sprite_gg);
                SDL_DestroyTexture(dragon);
                SDL_DestroyTexture(dragon2);
                portal_open = false;

                Mix_FreeMusic(yron);
                Mix_FreeMusic(music);
                Mix_CloseAudio();

                level1_call(window, renderer, lives);
                quit = true;
                break;
            }
        }

        // Check collision with key
        if (dest_gg.x >= dest_key.x && dest_gg.y >= dest_key.y && dest_gg.x <= dest_key.x + dest_key.w && dest_gg.y <= dest_key.y + dest_key.h)
        {
            portal_open = true;
        }

        // Check collision with portal
        if (dest_gg.x >= dest_portal.x && dest_gg.y >= dest_portal.y && dest_gg.x <= dest_portal.x + dest_portal.w && dest_gg.y <= dest_portal.y + dest_portal.h && portal_open)
        {   
            Mix_PlayMusic(Quest_complete, 1);
            SDL_DestroyTexture(portal_key);
            SDL_DestroyTexture(portal);
            SDL_DestroyTexture(background_wall);
            SDL_DestroyTexture(background);
            SDL_DestroyTexture(sprite_gg);
            SDL_DestroyTexture(dragon);
            SDL_DestroyTexture(dragon2);

            SDL_RenderClear(renderer);
            loading = load_sprite("resource/images/menu.png", renderer);
            load_cat = load_sprite("resource/images/cat_load2.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, load_cat, NULL, NULL);
            loading1 = load_sprite("resource/images/LoADing.png", renderer);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_RenderClear(renderer);
            loading1 = load_sprite("resource/images/LoADing!.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, load_cat, NULL, NULL);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_RenderClear(renderer);
            loading1 = load_sprite("resource/images/LoADing!!.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, load_cat, NULL, NULL);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_RenderClear(renderer);
            loading1 = load_sprite("resource/images/LoADing!!!.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, load_cat, NULL, NULL);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_RenderClear(renderer);
            loading1 = load_sprite("resource/images/LoADing.png", renderer);
            SDL_RenderCopy(renderer, loading, NULL, NULL);
            SDL_RenderCopy(renderer, load_cat, NULL, NULL);
            SDL_RenderCopy(renderer, loading1, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(500);

            SDL_DestroyTexture(load_cat);
            SDL_DestroyTexture(loading);
            SDL_DestroyTexture(loading1);

            Mix_FreeMusic(Quest_complete);
            Mix_FreeMusic(yron);
            Mix_FreeMusic(music);
            Mix_CloseAudio();

            level2_call(window, renderer, lives);
            quit = true;
            break;
        }
        
       

        // clear the window
        SDL_RenderClear(renderer);

        // draw the image to the window
        SDL_RenderCopy(renderer, background_wall, NULL, &dest_background_wall);
        SDL_RenderCopy(renderer, background, NULL, &dest_background);
        if (lives == 3) {
            lives_img = load_sprite("resource/images/3_heart.gif", renderer);
            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
            dest_lives.x = 0;
            dest_lives.y = 0;
            dest_lives.w = 210;
            dest_lives.h = 70;
            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
        } else if (lives == 2) {
            lives_img = load_sprite("resource/images/2_heart.gif", renderer);
            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
            dest_lives.x = 0;
            dest_lives.y = 0;
            dest_lives.w = 140;
            dest_lives.h = 70;
            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
        } else if (lives == 1) {
            lives_img = load_sprite("resource/images/1_heart.gif", renderer);
            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
            dest_lives.x = 0;
            dest_lives.y = 0;
            dest_lives.w = 70;
            dest_lives.h = 70;
            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
        }
        
        SDL_RenderCopy(renderer, dragon, NULL, &dest_drag);
        SDL_RenderCopy(renderer, dragon2, NULL, &dest_drag2);
        if (!portal_open)
        {
            SDL_RenderCopy(renderer, portal_key, NULL, &dest_key);
        }
        else
        {
            if (Portal % 6)
            {
                portal = load_sprite("resource/images/portal1.png", renderer);
            }
            else if (Portal % 10)
            {
                portal = load_sprite("resource/images/portal2.png", renderer);
                Portal = 0;
            }
            SDL_RenderCopy(renderer, portal, NULL, &dest_portal);
        }
        SDL_RenderCopy(renderer, sprite_gg, NULL, &dest_gg);
        SDL_RenderPresent(renderer);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }

    // SDL_DestroyTexture(start_button.texture);
    if (!quit)
    {
        SDL_DestroyTexture(portal_key);
        SDL_DestroyTexture(portal);
        SDL_DestroyTexture(background_wall);
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(sprite_gg);
        SDL_DestroyTexture(dragon);
        SDL_DestroyTexture(dragon2);
    }
}

