#include "../inc/header.h"

SDL_Texture *background;
SDL_Texture *sprite_gg;
SDL_Texture *background_wall;

SDL_Texture *dragon2;
SDL_Texture *truba;

SDL_Texture *endgame;
SDL_Texture *cat;

SDL_Texture *lives_img;

void level2_call(SDL_Window *window, SDL_Renderer *renderer, int lives)
{
    Mix_OpenAudio(44100, AUDIO_S16, 2, 4096);
    Mix_Music *music = Mix_LoadMUS("resource/soundtrack/level2.mp3");
    Mix_Music *yron = Mix_LoadMUS("resource/soundtrack/yron.mp3");
    Mix_Music *Quest_complete = Mix_LoadMUS("resource/soundtrack/Quest_complete.ogg");

    background = load_sprite("resource/images/menu.png", renderer);
    
    if (Mix_PlayMusic(music, -1) == -1)
        return ;

    // const int eath = 500;
    // bool eath1 = true;
    bool quit = true;
    background = load_sprite("resource/images/mario.png", renderer);
    sprite_gg = load_sprite("resource/images/stay.png", renderer);
    dragon2 = load_sprite("resource/images/dragon_left.png", renderer);
    truba = load_sprite("resource/images/truba.png", renderer);
    

    int close_requested = 0;

  // Walls - not displayed but needed for mechanic
    SDL_Surface *surface = IMG_Load("resource/images/background_wall_mario.png");
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
    SDL_Rect dest_background;
    SDL_Rect dest_background_wall;
   
    SDL_Rect dest_drag2;

    SDL_Rect dest_lives;

    SDL_QueryTexture(sprite_gg, NULL, NULL, &dest_gg.w, &dest_gg.h);
    SDL_QueryTexture(background, NULL, NULL, &dest_background.w, &dest_background.h);
    SDL_QueryTexture(background_wall, NULL, NULL, &dest_background_wall.w, &dest_background_wall.h);

    SDL_QueryTexture(dragon2, NULL, NULL, &dest_drag2.w, &dest_drag2.h);


    dest_drag2.x = 740;
    dest_drag2.y = 710;
    dest_drag2.w = 60;
    dest_drag2.h = 60;

    // Our character positions and size
    dest_gg.x = 0;
    dest_gg.y = 620;
    dest_gg.w = 70;
    dest_gg.h = 105;

    // Backgound positions and size
    dest_background.x = 0;
    dest_background.y = 0;
    dest_background.w = WINDOW_WIDTH;
    dest_background.h = WINDOW_HEIGHT;

    // Backgound walls positions and size
    dest_background_wall.x = 0;
    dest_background_wall.y = 0;
    dest_background_wall.w = WINDOW_WIDTH;
    dest_background_wall.h = WINDOW_HEIGHT;

    // start sprite in center of screen
    float x_pos = 0;
    float y_pos = 620;
    float x_vel = 0;
    float y_vel = 0;

    // keep track of which inputs are given
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;



    bool left_drag2 = true;
    bool right_drag2 = false;

    // int j = 0;
    int a = 0;
    int d = 0;
    int flag_for_jamp = 0;

    bool Chek_ennd_of_jump = true;
    while (!close_requested)
    {

        //ВТОРОЙ ДРАКОН!
        if(left_drag2)
        {
            dragon2 = load_sprite("resource/images/dragon_left.png", renderer);
            if (dest_drag2.x>420)
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
            dragon2 = load_sprite("resource/images/dragon_right.png", renderer);
            if (dest_drag2.x<740 )
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
                case SDL_SCANCODE_SPACE:
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
                case SDL_SCANCODE_SPACE:
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

        // Анимация jump +++++++++++++ 
        x_vel = y_vel = 0;

        //ПРЫЖОК НАХУЙ!
        int flag = 11;
        if (up && !down)
        {
            if (Chek_ennd_of_jump)
            {
                Chek_ennd_of_jump = false;
                
                for(int j = 0;j<flag;j++)
                {   
                    if (j < flag/2)
                    {
                        if (flag_for_jamp == 1)
                        {
                            x_vel-=90;
                            y_vel-=430;
                        }
                        else
                        {
                            x_vel+=90;
                            y_vel-=430;
                        }
                        



                        x_pos += x_vel / 60;
                        y_pos += y_vel / 60;

                        // collision detection with bounds
                        if (x_pos <= 0) x_pos = 0;
                        if (y_pos <= 0) y_pos = 0;
                        if (x_pos >= WINDOW_WIDTH - dest_gg.w) x_pos = WINDOW_WIDTH - dest_gg.w;
                        if (y_pos >= WINDOW_HEIGHT - dest_gg.h) y_pos = WINDOW_HEIGHT - dest_gg.h;

                        //ВТОРОЙ ДРАКОН!
                        if(left_drag2)
                        {
                            dragon2 = load_sprite("resource/images/dragon_left.png", renderer);
                            if (dest_drag2.x>420)
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
                            dragon2 = load_sprite("resource/images/dragon_right.png", renderer);
                            if (dest_drag2.x<740 )
                            {
                                dest_drag2.x++;
                            }
                            else 
                            {
                                left_drag2 = true;
                                right_drag2 = false;
                            }  

                        }

                        // set the positions in the struct
                        dest_gg.y = (int) y_pos;
                        dest_gg.x = (int) x_pos;
                        SDL_RenderClear(renderer);

                        // draw the image to the window
                        SDL_RenderCopy(renderer, background , NULL, NULL);
                        SDL_RenderCopy(renderer, sprite_gg, NULL, &dest_gg);
                        SDL_RenderCopy(renderer, truba, NULL, NULL);
                        // SDL_RenderCopy(renderer, dragon, NULL, &dest_drag);
                        SDL_RenderCopy(renderer, dragon2, NULL, &dest_drag2);
                        if (lives == 3) 
                        {
                            lives_img = load_sprite("resource/images/3_heart.gif", renderer);
                            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
                            dest_lives.x = 0;
                            dest_lives.y = 0;
                            dest_lives.w = 210;
                            dest_lives.h = 70;
                            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
                        } 
                        else if (lives == 2)
                        {
                            lives_img = load_sprite("resource/images/2_heart.gif", renderer);
                            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
                            dest_lives.x = 0;
                            dest_lives.y = 0;
                            dest_lives.w = 140;
                            dest_lives.h = 70;
                            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
                        }
                        else if (lives == 1) 
                        {
                            lives_img = load_sprite("resource/images/1_heart.gif", renderer);
                            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
                            dest_lives.x = 0;
                            dest_lives.y = 0;
                            dest_lives.w = 70;
                            dest_lives.h = 70;
                            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
                        }
                        SDL_RenderPresent(renderer);

                        // wait 1/60th of a second
                        SDL_Delay(1000/60);
                    }
                    else
                    {
                        if (flag_for_jamp == 1)
                        {
                            x_vel-=90;
                            y_vel+=631;
                        }
                        else
                        {
                            x_vel+=90;
                            y_vel+=632;
                        }
                        


                        
                        x_pos += x_vel / 60;
                        y_pos += y_vel / 60;

                        // collision detection with bounds
                        if (x_pos <= 0) x_pos = 0;
                        if (y_pos <= 0) y_pos = 0;
                        if (x_pos >= WINDOW_WIDTH - dest_gg.w) x_pos = WINDOW_WIDTH - dest_gg.w;
                        if (y_pos >= WINDOW_HEIGHT - dest_gg.h) y_pos = WINDOW_HEIGHT - dest_gg.h;

                        //ВТОРОЙ ДРАКОН!
                        if(left_drag2)
                        {
                            dragon2 = load_sprite("resource/images/dragon_left.png", renderer);
                            if (dest_drag2.x>420)
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
                            dragon2 = load_sprite("resource/images/dragon_right.png", renderer);
                            if (dest_drag2.x<740 )
                            {
                                dest_drag2.x++;
                            }
                            else 
                            {
                                left_drag2 = true;
                                right_drag2 = false;
                            }  

                        }
                        // set the positions in the struct
                        dest_gg.y = (int) y_pos;
                        dest_gg.x = (int) x_pos;

                        SDL_RenderClear(renderer);

                        // draw the image to the window

                        SDL_RenderCopy(renderer, background , NULL, NULL);
                        SDL_RenderCopy(renderer, sprite_gg, NULL, &dest_gg);
                        // SDL_RenderCopy(renderer, dragon, NULL, &dest_drag);
                        SDL_RenderCopy(renderer, truba, NULL, NULL);
                        SDL_RenderCopy(renderer, dragon2, NULL, &dest_drag2);
                        if (lives == 3) 
                        {
                            lives_img = load_sprite("resource/images/3_heart.gif", renderer);
                            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
                            dest_lives.x = 0;
                            dest_lives.y = 0;
                            dest_lives.w = 210;
                            dest_lives.h = 70;
                            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
                        } 
                        else if (lives == 2)
                        {
                            lives_img = load_sprite("resource/images/2_heart.gif", renderer);
                            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
                            dest_lives.x = 0;
                            dest_lives.y = 0;
                            dest_lives.w = 140;
                            dest_lives.h = 70;
                            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
                        }
                        else if (lives == 1) 
                        {
                            lives_img = load_sprite("resource/images/1_heart.gif", renderer);
                            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
                            dest_lives.x = 0;
                            dest_lives.y = 0;
                            dest_lives.w = 70;
                            dest_lives.h = 70;
                            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
                        }
                        SDL_RenderPresent(renderer);

                        // wait 1/60th of a second
                        SDL_Delay(1000/60);
                        usleep(6000);
                    }
                    
                }
            }
        }
        if (left && !right)
        {
            flag_for_jamp = 1;
            x_vel = -SPEED-100;

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
            x_vel = SPEED+100;

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
        y_vel+=800;
            
        if (dest_gg.y >= 850 && dest_gg.x >= 1100 && dest_gg.x <= 1560)
        {
            Mix_PlayMusic(yron, 1);
            SDL_Delay(500);
            lives--;
            if (lives == 0)
            {
                SDL_DestroyTexture(sprite_gg);
                SDL_DestroyTexture(background_wall);
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(truba);
                // SDL_DestroyTexture(dragon);
                SDL_DestroyTexture(dragon2);

                endgame = load_sprite("resource/images/GAME_OVER_Dragon.png", renderer);
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
                SDL_DestroyTexture(sprite_gg);
                SDL_DestroyTexture(background_wall);
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(truba);
                // SDL_DestroyTexture(dragon);
                SDL_DestroyTexture(dragon2);

                Mix_FreeMusic(yron);
                Mix_FreeMusic(music);
                Mix_CloseAudio();
                
                level2_call(window, renderer, lives);
                quit = true;
                break;
            }
        }
        else if (dest_gg.y >= 850 && dest_gg.x >= 1650 && dest_gg.x <= 1830)
        {
            Mix_PlayMusic(Quest_complete, 1);
            SDL_DestroyTexture(sprite_gg);
            SDL_DestroyTexture(background_wall);
            SDL_DestroyTexture(background);
            SDL_DestroyTexture(truba);
            // SDL_DestroyTexture(dragon);
            SDL_DestroyTexture(dragon2);

            endgame = load_sprite("resource/images/menu.png", renderer);
            cat = load_sprite("resource/images/end_cat.png", renderer);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, endgame, NULL, NULL);
            SDL_RenderCopy(renderer, cat, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(5000);
            SDL_DestroyTexture(cat);
            SDL_DestroyTexture(endgame);

            Mix_FreeMusic(Quest_complete);
            Mix_FreeMusic(yron);
            Mix_FreeMusic(music);
            Mix_CloseAudio();

            menu_call(window, renderer, 3);
            quit = true;
            break;
        }

        bool to_move = false;
        if (x_vel > 0)
        {   
            if (check_color(surface, dest_gg.x + (dest_gg.w / 2), dest_gg.y + dest_gg.h, 221, 25, 25))
            {
                Chek_ennd_of_jump = true;
                to_move = true;
                y_vel = 0;
            }
            else if (!check_color(surface, dest_gg.x + dest_gg.w + (x_vel / 60), dest_gg.y + (dest_gg.h), 100, 168, 103))
            {

                y_pos += y_vel / 60;
                x_pos += x_vel / 30;
            }
            if (check_color(surface, dest_gg.x + dest_gg.w + (x_vel / 60), dest_gg.y + (dest_gg.h), 100, 168, 103))
            {
                Chek_ennd_of_jump = true;
                x_pos += 0;
                y_vel = 0;
            }
        }
        else
        {
            if (check_color(surface, dest_gg.x, dest_gg.y + dest_gg.h, 221, 25, 25))
            {
                Chek_ennd_of_jump = true;
                to_move = true;
                y_vel = 0;
            }
            else if (!check_color(surface, dest_gg.x + dest_gg.w + (x_vel / 60), dest_gg.y + (dest_gg.h), 100, 168, 103))
            {
                y_pos += y_vel / 60;
            }
            if (check_color(surface, dest_gg.x + (x_vel / 60), dest_gg.y + dest_gg.h + (dest_gg.h), 100, 168, 103))
            {
                x_pos += 0;
                y_vel = 0;
            }
        }
        if (to_move)
        {
            x_pos += x_vel / 60;
        }
            

        
        

        // collision detection with bounds
        if (x_pos <= 0) x_pos = 0;
        if (y_pos <= 0) y_pos = 0;
        if (x_pos >= WINDOW_WIDTH - dest_gg.w) x_pos = WINDOW_WIDTH - dest_gg.w;
        if (y_pos >= WINDOW_HEIGHT - dest_gg.h) y_pos = WINDOW_HEIGHT - dest_gg.h;

        // set the positions in the struct
        dest_gg.y = (int) y_pos;
        dest_gg.x = (int) x_pos;
        
        if ((dest_gg.x >= dest_drag2.x && dest_gg.y <= dest_drag2.y && dest_gg.x <= dest_drag2.x + dest_drag2.w && dest_gg.y >= dest_drag2.y - dest_drag2.h) || 
            (dest_gg.x + dest_gg.w >= dest_drag2.x && dest_gg.x + dest_gg.w <= dest_drag2.x + dest_drag2.w && dest_gg.y >= dest_drag2.y && dest_gg.y <= dest_drag2.y + dest_drag2.h))
        {
            Mix_PlayMusic(yron, 1);
            SDL_Delay(500);
            lives--;
            if (lives == 0)
            {
                SDL_DestroyTexture(background_wall);
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(sprite_gg);
                SDL_DestroyTexture(dragon2);

                endgame = load_sprite("resource/images/GAME_OVER_Dragon.png", renderer);
                
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
                SDL_DestroyTexture(background_wall);
                SDL_DestroyTexture(background);
                SDL_DestroyTexture(sprite_gg);
                SDL_DestroyTexture(dragon2);

                Mix_FreeMusic(yron);
                Mix_FreeMusic(music);
                Mix_CloseAudio();
            
                level2_call(window, renderer, lives);
                quit = true;
                break;
            }
        }

        // clear the window
        SDL_RenderClear(renderer);

        // draw the image to the window
        SDL_RenderCopy(renderer, background_wall, NULL, &dest_background_wall);
        SDL_RenderCopy(renderer, background, NULL, NULL);
        // SERDE4ki
        if (lives == 3) 
        {
            lives_img = load_sprite("resource/images/3_heart.gif", renderer);
            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
            dest_lives.x = 0;
            dest_lives.y = 0;
            dest_lives.w = 210;
            dest_lives.h = 70;
            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
        } 
        else if (lives == 2)
        {
            lives_img = load_sprite("resource/images/2_heart.gif", renderer);
            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
            dest_lives.x = 0;
            dest_lives.y = 0;
            dest_lives.w = 140;
            dest_lives.h = 70;
            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
        }
        else if (lives == 1) 
        {
            lives_img = load_sprite("resource/images/1_heart.gif", renderer);
            SDL_QueryTexture(lives_img, NULL, NULL, &dest_lives.w, &dest_lives.h);
            dest_lives.x = 0;
            dest_lives.y = 0;
            dest_lives.w = 70;
            dest_lives.h = 70;
            SDL_RenderCopy(renderer, lives_img, NULL, &dest_lives);
        }
        SDL_RenderCopy(renderer, sprite_gg, NULL, &dest_gg);
        // SDL_RenderCopy(renderer, dragon, NULL, &dest_drag);
        SDL_RenderCopy(renderer, truba, NULL, NULL);
        SDL_RenderCopy(renderer, dragon2, NULL, &dest_drag2);
        SDL_RenderPresent(renderer);

        // wait 1/60th of a second
        SDL_Delay(1000/60);

        if (!quit)
        {
            // SDL_DestroyTexture(background);
            SDL_DestroyTexture(sprite_gg);
        }
    }
}
