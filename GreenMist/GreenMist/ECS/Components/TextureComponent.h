#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include "../Component.h"
#include "../../Texture.h"
#include "../../TextureManager.h"

class TextureComponent : public Component
{
public:
    TextureComponent(Texture* tex)
    {
        texture = tex;
		Scale = 1;
		Opacity = 1;
    }

	TextureComponent(std::string name)
    {
        texture = TextureManager::Get(name);
		Scale = 1;
		Opacity = 1;
    }

     Texture* texture;
	 
     float Scale;
     float Opacity;
};

#endif
