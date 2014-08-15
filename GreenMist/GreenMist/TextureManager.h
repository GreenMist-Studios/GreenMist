#pragma once
#include <map>
#include <SDL2/SDL.h>
#include "Texture.h"
#include <string>

class TextureManager
{
public:
	TextureManager()
	{
	}

	~TextureManager()
	{
		for (std::map<std::string, Texture*>::iterator it = textures->begin(); it != textures->end(); it++)
		{
			(*it).second->free();
		}

		stringByTexture = NULL;
		textures = NULL;
		INDEX = 0;
	}
	
	static Texture* Add(std::string name, Texture* t)
	{

		if (!Exists(t) && !Exists(name))
		{
			textures->insert(std::pair<std::string, Texture* >(name, t));
			stringByTexture->insert(std::pair<Texture*, std::string >(t, name));

			return t;
		}
		else if (Exists(name))
		{
			printf ("Warning: Texture Name (%s) exists.", name.c_str());
		}
		else if (Exists(t))
		{
			printf ("Warning: Texture with path (%s) exists.", t->texPath.c_str());
		}
		return NULL;
	}

	static Texture* Get(std::string name)
	{
		if (Exists(name))
			return textures->at(name);
		else
			return NULL;
	}

	static std::string GetName(Texture* t)
	{
		if (Exists(t))
			return stringByTexture->at(t);
		else
			return "";
	}

	static bool Exists(std::string name)
	{
		if ( textures->find(name) == textures->end() )
			return false;
		else
			return true;
	}

	static bool Exists(Texture* t)
	{
		if (stringByTexture->find(t) == stringByTexture->end())
			return false;
		else 
			return true;
	}

	static void SetRenderer(SDL_Renderer* r)
	{
		if (r != NULL)
			renderer = r;
	}

	static SDL_Renderer* GetRenderer()
	{
		return renderer;
	}

	static bool IsRendererSet()
	{
		if (renderer != NULL)
			return true;
		return false;
	}
private:
	static SDL_Renderer* renderer;
	static int INDEX;
	static std::map<std::string , Texture* >* textures;
	static std::map<Texture*, std::string>* stringByTexture;
};

