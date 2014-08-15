#ifndef RENDERORDERCOMPONENT_H
#define RENDERORDERCOMPONENT_H

#include <ECS/Components/TextureComponent.h>
#include <Texture.h>
#include <TextureManager.h>

class RenderOrderComponent : public TextureComponent
{
public:
	RenderOrderComponent(Texture* tex, int ro, void (*dd)(TextureComponent*,float)) : TextureComponent(tex)
    {
		RenderOrder = ro;
		oldRenderOrder = RenderOrder;
    }

	RenderOrderComponent(Texture* tex, int ro) : TextureComponent(tex)
    {
		RenderOrder = ro;
		oldRenderOrder = RenderOrder;
    }

    RenderOrderComponent(Texture* tex) : TextureComponent(tex)
    {
		RenderOrder = -1;
		oldRenderOrder = RenderOrder;
    }

	RenderOrderComponent(std::string name) : TextureComponent(name)
    {
		RenderOrder = -1;
		oldRenderOrder = RenderOrder;
    }

	RenderOrderComponent(std::string name, int ro) : TextureComponent(name)
    {
		RenderOrder = ro;
		oldRenderOrder = RenderOrder;
    }

	bool CheckRenderOrderChanged()
	{
		if (RenderOrder == oldRenderOrder)
		{
			return false;
		}
		else
		{
			oldRenderOrder = RenderOrder;
			return true;
		}
	}

	int RenderOrder;
private:
	int oldRenderOrder;
};

#endif
