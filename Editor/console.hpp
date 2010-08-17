class Console
{
    sf::Shape Rect;
    sf::Font Text_font;

    string buffer;
    int x, y, h, w;
    char get_typed(sf::Event &event);

    void delete_letter();

    void add_text(char l);

    void add_letter(char text);

public:

    sf::String Text;
    string entered;
    void set_text(string text);

    void clear();
    string get_text();
    bool is_entering();
    void set_entering(bool enter = true);
    bool entering, Cancel;
    void update(sf::Event &event);
    void Draw(sf::RenderWindow &Window);
    Console(int text_size,int o_x, int o_y, int o_h, int o_w, sf::Font &o_font);

    sf::String GetText();
};