#ifndef _IMAGE_MANAGER_H_
#define _IMAGE_MANAGER_H_

#include "SFML/Graphics.hpp"
#include <string>
#include <map>


/**************************************************************************************************
 * ImageManager is a singleton class that will be used to store and manager
 * all the images in the game, you just call the GetImage function and it
 * either gets an existing image with that name or loads a new one, stores
 * it and returns it
 *
 * example use:
 *     sprite.SetImage(manager.GetImage("image.png"));
 *
 * @TODO consider creating a class that packs 2 types of vars together and store it in a vector
 *        rather then a map
 **************************************************************************************************/

namespace cell
{
    typedef std::map<std::string, sf::Image> ImageList;
     // i think im going to start documenting more
    class ImageManager
    {
        private:
            ImageManager();
            static ImageManager* _instance;

        public:
            /******************************************************************************************
             * Destructor
             * deletes the singleton if it exists
             ******************************************************************************************/
            ~ImageManager();



            /******************************************************************************************
             * GetInst is a method that allows access as a pointer to the class as a singleton
             * @return ImageManager*
             ******************************************************************************************/
            static ImageManager* GetInst();



            /******************************************************************************************
             * GetRef is a method that allows direct access to the class as a singleton
             * @return ImageManager&
             ******************************************************************************************/
            static ImageManager& GetRef();



            /******************************************************************************************
             * GetImage is a method that allows you to retreive an existing image or add a new one if
             * one with the param name dose not exist
             * @param std::string
             * @return sf::Image&
             ******************************************************************************************/
            sf::Image& GetImage(std::string image_name);

        private:
            sf::Image&          _addImage(std::string image_name);
            ImageList           _images;
            ImageList::iterator _iterator;

    };
}


#endif
