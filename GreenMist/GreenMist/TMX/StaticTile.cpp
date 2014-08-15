#include "StaticTile.h"

StaticTile::StaticTile(int _id, Texture* _texture, Vector2 _position)
{
    id = _id;
    texture = _texture;
    position = _position;
}

StaticTile::~StaticTile()
{
    texture->free();
}

void StaticTile::Draw(int w, int h)
{
    SDL_Rect clip;
    if (id == 1)
    {
        clip.h = h;
        clip.w = w;
        clip.x = clip.y = 0;
        texture->render(position.X, position.Y, &clip, 0.0,NULL);
    }
}
