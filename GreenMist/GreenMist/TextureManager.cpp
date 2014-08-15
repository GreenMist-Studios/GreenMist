#include "TextureManager.h"

SDL_Renderer* TextureManager::renderer = NULL;
int TextureManager::INDEX = 0;
std::map<std::string, Texture*>* TextureManager::textures = new std::map<std::string, Texture*>();
std::map<Texture*, std::string >* TextureManager::stringByTexture = new std::map<Texture*, std::string >();