#define VERSION 3

class System
{
public:

    System(string location);
    void Init(bool defaults);

    float version;

    int
    amt_xtiles,
    amt_ytiles,
    screen_width,
    screen_height,
    fps;
    string language;
    string window_title;

    string font;
};
