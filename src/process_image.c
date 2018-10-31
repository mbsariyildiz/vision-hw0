#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

int _get_index(image im, int x, int y, int c){
    int _x = min(max(x, 0), im.w - 1);
    int _y = min(max(y, 0), im.h - 1);
    int area = im.w * im.h;
    int ix = area * c + _y * im.w + _x;
    return ix;
}

float get_pixel(image im, int x, int y, int c)
{
    int ix = _get_index(im, x, y, c);
    return im.data[ix];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    int ix = _get_index(im, x, y, c);
    im.data[ix] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    memcpy(im.data, copy.data, im.w * im.h * im.c * sizeof(float)); // im.data is a float array
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    
    int area = im.w * im.h;
    int ix_r, ix_g, ix_b;
    float gray_val;
    
    for (int y=0; y < im.h; y++){
        for (int x=0; x < im.w; x++){
            //red index, it is also same for gray-scale index
            ix_r = y * im.w + x;
            // green index
            ix_g = area + y * im.w + x;
            // blue index
            ix_b = area * 2 + y * im.w + x;

            gray_val = 0.299 * im.data[ix_r] + 0.587 * im.data[ix_g] + 0.114 * im.data[ix_b];
            gray.data[ix_r] = gray_val;
        }
    }

    return gray;
}

void shift_image(image im, int c, float v)
{   
    int offset = im.w * im.h * c;
    int ix;

    for (int y=0; y < im.h; y++){
        for (int x=0; x < im.w; x++){
            ix = offset + y * im.w + x;
            im.data[ix] = im.data[ix] + v;
        }
    }
}

void clamp_image(image im)
{
    int size = im.w * im.h * im.c;
    for (int i=0; i < size; i++)
        im.data[i] = min(max(im.data[i], 0.), 1.);
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
