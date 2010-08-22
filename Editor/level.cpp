#include"headers.hpp"
#include"level.hpp"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
Config::Config(string file)
{
    File = file;

    string temp;
    ifstream config;
    config.open( file.c_str() );

    if(!config.bad())
    {
        while(config>>temp)
        {
            if(temp == "Map_x")
            {
                config>>x;
            }
            if(temp == "Map_y")
            {
                config>>y;
            }
        }

    }
    config.close();
}

void Level::SetFlag(int f)
{
    for(int a = 0; a < z; a++)
    {
        for(int b = 0; b < x; b++)
        {
            for(int c = 0; c < y; c++)
            {
                tile[a][b][c].flag = f;
            }
        }
    }
}
void Level::Create_Tiles(int X, int Y, int Z)
{
    layer = -1;
    x = X;
    y = Y;
    z = Z;
    Clear_Tiles();
}



Level::~Level()
{
   // delete [] tile; // dont delete it unless its a pointer on the heap!!!!!
}

void Level::Clear_Tiles()
{
    cout<<"Clearinng tiles"<<endl;

    int counter = 1;
    for(int a = 0; a < z; a++)
    {
        for(int b = 0; b < x; b++)
        {
            for(int c = 0; c < y; c++)
            {
                tile[a][b][c].x = b * 32;
                tile[a][b][c].y = c * 32;
                tile[a][b][c].s_x = a * 32;
                tile[a][b][c].s_y = 0;
                tile[a][b][c].h = 32;
                tile[a][b][c].w = 32;
                tile[a][b][c].flag = 0;
                counter++;
            }
        }
    }
}

void Level::Save_Map(std::string buffer, int H, int W)
{



    cout<<"Is something wrong?"<<endl<<"converted sfml to string: "<<buffer<<endl;
#ifndef Debug
    cout<<"buffer: "<< buffer <<endl;
#endif

#ifdef Debug
    cout<<"debug mode. Please Enter Filename: "<<endl;
    cin>>buffer;
    cin.ignore();

#endif
    ofstream Save;
    Save.open(buffer.c_str());

    if(Save.good())
    {
         cout<<"Saving to: "<< buffer <<" Length: "<<buffer.size()<<endl;

        cout<<"File being created..."<<endl;
        Save<<"H "<< H <<" W "<< W <<"\n\n";

        Save<<"MapX "<< x <<" MapY "<< y<<"\n\n";

        for(int a = 0; a < z; a++)
        {
            for(int b = 0; b < x; b++)
            {
                for(int c = 0; c < y; c++)
                {
                    Save<<"Layer "<< a << " Tile "<< c;
                    Save<<" X "<< tile[a][b][c].x <<" Y " << tile[a][b][c].y;
                    Save<<" Strip_x "<< tile[a][b][c].s_x;
                    Save<<" Strip_y "<<tile[a][b][c].s_y;
                    Save<<" Hieght "<< H;
                    Save<<" Width "<< W;
                    Save<<" Flag "<< tile[a][b][c].flag;
                    Save<<" END \n\n";
                }
                Save<<"\n";
            }
            Save<<"\n \n \n";
        }
        cout<<"done."<<endl;
        cout << "file is good" << endl;
    }
    else
    {
        cout<<"File: "<< buffer<<" could not be created!"<<endl;
    }
    Save.flush(); // just make sure everything is written
    Save.close();

}

void Level::Load_Map(std::string buffer)
{

    string temp;
    int flag;
#ifndef Debug

    ifstream Load( buffer.c_str() );
#endif

#ifdef Debug
    cout<<"debug mode. Please Enter Filename: "<<endl;
    cin>>buffer;
    cin.ignore();
    ifstream Load( buffer.c_str() );
#endif

    if(Load.is_open())
    {
        cout<<"Found file"<<endl;
        while(Load>>temp)
        {
            if(temp == "MapX")
            {
                Load>>x;
            }
            if(temp == "MapY")
            {
                Load>>y;
            }
            if(temp == "Layer")
            {
                Load>>layer;
            }
            if(temp == "Tile")
            {
                Load>>tile_count;
            }
            if(temp == "Flag")
            {
                Load>>flag;
            }
            if(temp == "X")
            {
                Load>>x_coord;
            }
            if(temp == "Y")
            {
                Load>>y_coord;
            }
            if(temp == "Strip_x")
            {
                Load>>strip_x;
            }
            if(temp == "Strip_y")
            {
                Load>>strip_y;
            }
            if(temp == "H")
            {
                Load>>h;
            }
            if(temp == "W")
            {
                Load>>w;
            }
            if(temp == "END")
            {
                tile[layer][x_coord / w][y_coord / h].x = x_coord;
                tile[layer][x_coord / w][y_coord / h].y = y_coord;
                tile[layer][x_coord / w][y_coord / h].s_x = strip_x;
                tile[layer][x_coord / w][y_coord / h].s_y = strip_y;
                tile[layer][x_coord / w][y_coord / h].h = h;
                tile[layer][x_coord / w][y_coord / h].w = w;
                tile[layer][x_coord / w][y_coord / h].flag = flag;

            }
        }
    }
    else
    {
        cout<<"Could not open or find file: "<< buffer <<endl;
    }
    Load.close();
}

void Level::Draw(sf::Image &image, sf::RenderWindow &Window)
{
    draw.SetImage( image );

    if(layer == -1)
    {
        for(int a = 0; a < z; a++)
        {
            for(int b = 0; b < x; b++)
            {
                for(int c = 0; c < y; c++)
                {
                    if(tile[a][b][c].rendered)
                    {
                        draw.SetSubRect( sf::IntRect(tile[a][b][c].s_x,tile[a][b][c].s_y,
                                                    tile[a][b][c].s_x + tile[a][b][c].w,
                                                    tile[a][b][c].s_y + tile[a][b][c].h) );
                        draw.SetPosition(tile[a][b][c].x + ofs_x, tile[a][b][c].y + ofs_y);
                        Window.Draw(draw);
                    }
                }
            }
        }
    }
    else
    {
        for(int d = 0; d < x; d++)
        {
            for(int e = 0; e < y; e++)
            {
                draw.SetSubRect( sf::IntRect(tile[layer][d][e].s_x,tile[layer][d][e].s_y, tile[layer][d][e].s_x + tile[layer][d][e].w, tile[layer][d][e].s_y + tile[layer][d][e].h) );
                draw.SetPosition(tile[layer][d][e].x + ofs_x, tile[layer][d][e].y + ofs_y);
                Window.Draw(draw);
            }
        }
    }
}
