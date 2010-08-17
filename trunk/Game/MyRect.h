#ifndef _MY_RECT_H_
#define _MY_RECT_H_


struct MyRect
{
    int x, y, w,  h;

    int right() { return x+w; }
    int bottom() { return y+h; }

    MyRect(): x(0), y(0), w(0), h(0){}
    MyRect(int _x, int _y, int _w, int _h)
    :
    x(_x), y(_y), w(_w), h(_h){}

    void set(int x, int y, int w, int h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    inline bool contains(int _x, int _y)
    {
        return ( _x >= x && _x <= x+w &&
                 _y >= y && _y <= y+h    );
    }

    inline bool intersects(const MyRect& rect)
    {
        return( (rect.x > x && rect.x < x+w && rect.y > y && rect.y < y+h)|| // top left
                (rect.x+rect.w < x+w && rect.x+rect.w > x && rect.y > y && rect.y < y+h)|| // top right
                (rect.x < x+w && rect.x > x && rect.y+rect.h > y && rect.y + rect.h < y+h)|| // bottom left
                (rect.x+rect.w < x+w && rect.x+rect.w > x && rect.y+rect.h > y && rect.y + rect.h < y+h)); // bottom right
    }
};

#endif
