#include"headers.hpp"
#include"level.hpp"
#include"brush.hpp"
#include"system.hpp"
#include"button.hpp"
#include"console.hpp"

void mang(Brush &brush, Level &level, Button &button, sf::RenderWindow &Wind, sf::Event &event, sf::Font &system_Font, Console &console, sf::Image &tile)
{

    console.update(event);
    string temp;
    //if mouse clicks...
    if(Wind.GetInput().IsMouseButtonDown(sf::Mouse::Left))
    {
        //if in range of a button...
        if(Wind.GetInput().GetMouseX() > button.x && Wind.GetInput().GetMouseX() < button.x + button.w
                && Wind.GetInput().GetMouseY() > button.y && Wind.GetInput().GetMouseY() < button.y + button.h)
        {
            temp = button.name;
        }

        for(int a = 0; a < level.z; a++)
        {
            for(int b = 0; b < level.x; b++)
            {
                for(int c = 0; c < level.y; c++)
                {
                    if(Wind.GetInput().GetMouseX() > level.tile[a][b][c].x + level.ofs_x
                            && Wind.GetInput().GetMouseX() < level.tile[a][b][c].x + level.ofs_x + level.tile[a][b][c].w
                            && Wind.GetInput().GetMouseY() > level.tile[a][b][c].y + level.ofs_y
                            && Wind.GetInput().GetMouseY() < level.tile[a][b][c].y + level.ofs_y + level.tile[a][b][c].h)
                    {
                        if(level.layer != -1)
                        {
                            level.tile[level.layer][b][c].s_x = brush.Tile * 32;
                            level.tile[level.layer][b][c].rendered = true;
                        }
                        else
                        {
                            level.tile[2][b][c].s_x = brush.Tile * 32;
                            level.tile[2][b][c].rendered = true;
                        }
                    }
                }
            }
        }
    }

    //moving map
    if(Wind.GetInput().IsKeyDown(sf::Key::Left))
    {
        level.ofs_x+= 5;
    }
    if(Wind.GetInput().IsKeyDown(sf::Key::Right))
    {
        level.ofs_x-=5;
    }
    if(Wind.GetInput().IsKeyDown(sf::Key::Up))
    {
        level.ofs_y+=5;
    }
    if(Wind.GetInput().IsKeyDown(sf::Key::Down))
    {
        level.ofs_y-=5;
    }
    if(Wind.GetInput().IsKeyDown(sf::Key::Num1))
    {
        brush.Tile = 0;
        level.SetFlag(0);
    }

    if(Wind.GetInput().IsKeyDown(sf::Key::Num2))
    {
        brush.Tile = 1;
        level.SetFlag(0);
    }
    if(Wind.GetInput().IsKeyDown(sf::Key::Num3))
    {
        brush.Tile = 2;
        level.SetFlag(1);
    }
    if(Wind.GetInput().IsKeyDown(sf::Key::Num4))
    {
        brush.Tile = 3;
        level.SetFlag(1);
    }

    if(Wind.GetInput().IsKeyDown(sf::Key::Num5))
    {
        brush.Tile = 4;
        level.SetFlag(0);
    }

    if(Wind.GetInput().IsKeyDown(sf::Key::Num6))
    {
        brush.Tile = 5;
    }

    if(temp == "Exit")
    {
        Wind.Close();
    }

    if(temp == "Save")
    {
#ifndef Debug
        console.set_entering(true);
        while(console.is_entering())
        {
            while(Wind.GetEvent(event))
            {
                console.update(event);
            }
            Wind.Clear();
            level.Draw(tile, Wind);
            console.Draw(Wind);
            Wind.Display();
        }

#endif
        //cout<<"saving to "<<console.entered<<"\n";
        level.Save_Map(console.get_text(),32,32); // maby make a create new function so when you save you have the vars from the
        // new map and this would be save as but the map would have a w and h
        console.set_entering(false);
        console.clear();
    }

    if(temp == "Load")
    {
#ifndef Debug
        console.set_entering(true);
        while(console.is_entering())
        {
            while(Wind.GetEvent(event))
            {
                console.update(event);
            }
            Wind.Clear();
            level.Draw(tile, Wind);
            console.Draw(Wind);
            Wind.Display();
        }
#endif
        cout << console.get_text()<<endl;
        cout << "loading from " << console.get_text() << endl;
        level.Load_Map(console.get_text());
        console.set_entering(false);
        console.clear();
    }
    if(temp == "Layer1")
    {
        level.layer = 0;
    }
    if(temp == "Layer2")
    {
        level.layer = 1;
    }
    if(temp == "Layer3")
    {
        level.layer = 2;
    }
    if(temp == "All")
    {
        level.layer = -1;
    }
}



int main(void)
{
    Brush main_brush;
    Level Edit;

#ifndef Debug
    System Game("System.ini");
#endif

#ifdef Debug
    System Game("Debug.ini");
#endif
    //x, y, z
    Edit.Create_Tiles(Game.amt_xtiles,Game.amt_ytiles,3);
    Edit.ofs_y = 50;
    Edit.ofs_x = 32;
    sf::Font System_Font;

    System_Font.LoadFromFile("system.ttf");

    sf::RenderWindow
    App(sf::VideoMode(Game.screen_width, Game.screen_height),Game.window_title.c_str() );

    sf::Input Input;

    App.SetFramerateLimit(Game.fps);

    sf::Image Tile_Set;
    Tile_Set.LoadFromFile("tiles.png");

    Console console(8, 10,20,20,250,System_Font);
    sf::Sprite sprite;
    sprite.SetImage(Tile_Set);
    sprite.SetSubRect(sf::IntRect(0,0,32,32));
    sprite.Resize(16,16);
    sprite.SetPosition(App.GetInput().GetMouseX(),App.GetInput().GetMouseY() );

    Button Exit_Button(10,10,10,30,sf::Color(255,0,0),System_Font,8,"Exit");
    Button Save_Button(60,10,10,30,sf::Color(0,255,0),System_Font,8,"Save");
    Button Load_Button(100,10,10,30,sf::Color(0,255,0),System_Font,8,"Load");

    Button Layer1_Button(10,30,10,35,sf::Color(0,255,0),System_Font,8,"Layer1");
    Button Layer2_Button(60,30,10,35,sf::Color(0,255,0),System_Font,8,"Layer2");
    Button Layer3_Button(100,30,10,35,sf::Color(0,255,0),System_Font,8,"Layer3");
    Button All_Button(140,30,10,30,sf::Color(0,255,0),System_Font,8,"All");


    sf::Event Event;

    while(App.IsOpened())
    {
        while(App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
            {
                App.Close();
            }

            mang(main_brush,Edit,Exit_Button,App,Event,System_Font,console, Tile_Set);
            mang(main_brush,Edit,Save_Button,App,Event,System_Font,console, Tile_Set);
            mang(main_brush,Edit,Load_Button,App,Event,System_Font,console, Tile_Set);
            mang(main_brush,Edit,Layer1_Button,App,Event,System_Font,console, Tile_Set);
            mang(main_brush,Edit,Layer2_Button,App,Event,System_Font,console, Tile_Set);
            mang(main_brush,Edit,Layer3_Button,App,Event,System_Font,console, Tile_Set);
            mang(main_brush,Edit,All_Button,App,Event,System_Font,console, Tile_Set);
            if(!App.IsOpened())
            {
                break;
            }

        }
        sprite.SetSubRect(sf::IntRect(main_brush.Tile * 32,0,main_brush.Tile * 32 + 32,32));
        sprite.SetPosition(App.GetInput().GetMouseX(),App.GetInput().GetMouseY() );
        sprite.Rotate(-5.f);

        App.Clear();

        Edit.Draw(Tile_Set,App); //level

        //buttons
        Save_Button.Draw(App);
        Exit_Button.Draw(App);
        Load_Button.Draw(App);
        Layer1_Button.Draw(App);
        Layer2_Button.Draw(App);
        Layer3_Button.Draw(App);
        All_Button.Draw(App);

        console.Draw(App);

        App.Draw(sprite);
        App.Display();
    }
    return 0;
}
