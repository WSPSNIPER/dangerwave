#include"headers.hpp"
#include"system.hpp"

System::System(string location)
{
    ifstream File;
    string temp;
    File.open( location.c_str() );
    while(File>>temp)
    {
        if(temp == "Hieght")
        {
            File>>screen_height;
        }
        if(temp == "Width")
        {
            File>>screen_width;
        }
        if(temp == "Title")
        {
            File>>window_title;
        }

        if(temp == "FPS")
        {
            File>>fps;
        }
        if(temp == "Version")
        {
            File>>version;
        }
        if(temp == "Tiles_X")
        {
            File>>amt_xtiles;
        }
        if(temp == "Tiles_Y")
        {
            File>>amt_ytiles;
        }
    }
    if(temp == "System_Font")
    {
        File>>font;
        cout<<"Font loaded:"<< font<<endl;
    }

    File.close();
}


