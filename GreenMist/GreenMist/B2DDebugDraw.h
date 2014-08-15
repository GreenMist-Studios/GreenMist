#ifndef B2DDEBUGDRAW_H
#define B2DDEBUGDRAW_H

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include "SDL2_gfx/SDL2_gfxPrimitives.h"
#include "MathExtender.h"

class B2DDebugDraw : public b2Draw
{
public:
	B2DDebugDraw(SDL_Renderer* renderer);

	void Create();
	void Destroy();

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	void DrawTransform(const b2Transform& xf);

    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);

    void DrawString(int x, int y, const char* string, ...);

    void DrawString(const b2Vec2& p, const char* string, ...);

    void DrawAABB(b2AABB* aabb, const b2Color& color);

    void Flush();

private:
    SDL_Renderer* renderer;
};

#endif // B2DDEBUGDRAW_H
