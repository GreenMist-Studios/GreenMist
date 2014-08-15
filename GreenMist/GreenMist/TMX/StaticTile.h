#ifndef STATICTILE_H
#define STATICTILE_H

#include "../Texture.h"
#include "../Vector2.h"


class StaticTile
{
    public:
        StaticTile(int id, Texture* t, Vector2 position);
        virtual ~StaticTile();
        void Draw(int w,int h);
    private:
        int id;
        Texture* texture;
        Vector2 position;
};

#endif // STATICTILE_H
