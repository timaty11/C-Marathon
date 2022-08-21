#include "../inc/header.h"

Uint32 getPixel(SDL_Surface *loadingSurface, int x, int y)
{
    Uint32 *pixels = (Uint32*)loadingSurface->pixels;
    return pixels[(y * loadingSurface->pitch / 4) + x];
}

bool check_color(SDL_Surface *surface, int x, int y, Uint8 red_forbid, Uint8 green_forbid, Uint8 blue_forbid)
{
    // Uint8 red_forbid = 100, green_forbid = 168, blue_forbid = 103;
    // Uint8 red_forbid = 0, green_forbid = 0, blue_forbid = 0, alpha_forbid = 255;

    SDL_PixelFormat *fmt;
    Uint32 temp;
    Uint32 pixel = getPixel(surface, x, y);
    Uint8 red, green, blue, alpha;

    fmt = surface->format;
    SDL_LockSurface(surface);
    SDL_UnlockSurface(surface);

    /* Get Red component */
    temp = pixel & fmt->Rmask;  /* Isolate red component */
    temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
    temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
    red = (Uint8)temp;

    /* Get Green component */
    temp = pixel & fmt->Gmask;  /* Isolate green component */
    temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
    temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
    green = (Uint8)temp;

    /* Get Blue component */
    temp = pixel & fmt->Bmask;  /* Isolate blue component */
    temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
    temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
    blue = (Uint8)temp;

    /* Get Alpha component */
    temp = pixel & fmt->Amask;  /* Isolate alpha component */
    temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
    temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
    alpha = (Uint8)temp;



    if (red == red_forbid && green == green_forbid && blue == blue_forbid)
    {
        return true;
    }
    else
    {
        return false;
    }
}

