#ifndef BASICRENDERSYSTEM_H
#define BASICRENDERSYSTEM_H

#include "ECS/ComponentMapper.h"
#include "ECS/Systems/EntityProcessingSystem.h"
#include <ECS/Components/PositionComponent.h>
#include <ECS/Components/TextureComponent.h>


class BasicRenderSystem : public EntityProcessingSystem
{
    public:
        BasicRenderSystem() : EntityProcessingSystem(&typeid(this), Aspect::GetAspectForAll(&typeid(PositionComponent*), &typeid(TextureComponent*),NULL))
		{
		}

        void Initialize()
        {
            tcm = new ComponentMapper<TextureComponent*>(world);
            pcm = new ComponentMapper<PositionComponent*>(world);
        }

        void ProcessEntity(Entity* e)
        {
            PositionComponent* pc = pcm->GetSafe(e);
            TextureComponent* tc = tcm->GetSafe(e);

			tc->texture->setAlpha(255 * tc->Opacity);
            tc->texture->render(pc->x,pc->y);
        }

    private:
        ComponentMapper<PositionComponent*>* pcm;
        ComponentMapper<TextureComponent*>* tcm;

};

#endif // BASICRENDERSYSTEM_H
