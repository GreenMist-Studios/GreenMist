#include "B2DDebugDraw.h"

B2DDebugDraw::B2DDebugDraw(SDL_Renderer* r)
{
	renderer = r;
}

void B2DDebugDraw::Create()
{

}

void B2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    Sint16* xlist = (Sint16*)malloc(vertexCount * sizeof(Sint16));
    Sint16* ylist = (Sint16*)malloc(vertexCount * sizeof(Sint16));

    for (int i = 0; i < vertexCount; i++)
    {
        xlist[i] = SimToReal(vertices[i].x);
        ylist[i] = SimToReal(vertices[i].y);
    }

    polygonRGBA(renderer, xlist,ylist, vertexCount, color.r*255,color.g*255,color.b*255,color.a*255);
}

void B2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    Sint16* xlist = (Sint16*)malloc(vertexCount * sizeof(Sint16));
    Sint16* ylist = (Sint16*)malloc(vertexCount * sizeof(Sint16));

    for (int i = 0; i < vertexCount; i++)
    {
        xlist[i] = SimToReal(vertices[i].x);
        ylist[i] = SimToReal(vertices[i].y);
    }
    polygonRGBA(renderer, xlist,ylist, vertexCount, color.r*255,color.g*255,color.b*255,color.a*255);
}

void B2DDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
    circleRGBA(renderer,SimToReal(center.x), SimToReal(center.y),SimToReal(radius), color.r*255,color.g*255,color.b*255,color.a*255);
}

void B2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
    circleRGBA(renderer,SimToReal(center.x), SimToReal(center.y),SimToReal(radius), color.r*255,color.g*255,color.b*255,color.a*255);
}

void B2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    lineRGBA(renderer, SimToReal(p1.x),SimToReal(p1.y),SimToReal(p2.x),SimToReal(p2.y), color.r*255, color.g*255,color.b*255, color.a*255);
}

void B2DDebugDraw::DrawTransform(const b2Transform& xf)
{

}

void B2DDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
    pixelRGBA(renderer,SimToReal(p.x),SimToReal(p.y), color.r,color.g,color.b, color.a);
}

void B2DDebugDraw::DrawString(int x, int y, const char* string, ...)
{

}

void B2DDebugDraw::DrawString(const b2Vec2& p, const char* string, ...)
{

}

void B2DDebugDraw::DrawAABB(b2AABB* aabb, const b2Color& color)
{
    rectangleRGBA(renderer,SimToReal(aabb->lowerBound.x), SimToReal(aabb->lowerBound.y), SimToReal(aabb->upperBound.x),SimToReal(aabb->upperBound.y), color.r,color.g,color.b,color.a);
}

void B2DDebugDraw::Flush()
{

}
