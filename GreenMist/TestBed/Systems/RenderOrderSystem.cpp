#include "RenderOrderSystem.h"

bool Compare(Entity* e1, Entity* e2)
{			
	if (e1 == NULL || e2 == NULL)
		return true;

	RenderOrderComponent* roc1 = (RenderOrderComponent*) e1->GetComponent(&typeid(RenderOrderComponent*));
	RenderOrderComponent* roc2 = (RenderOrderComponent*) e2->GetComponent(&typeid(RenderOrderComponent*));
	
	if (roc1->RenderOrder == -1)
		return false;

	if (roc2->RenderOrder == -1 || roc1->RenderOrder < roc2->RenderOrder )
		return true;
	else
		return false;
}

void RenderOrderSystem::Sort()
{
	std::sort(GetActives()->begin(), GetActives()->end(), Compare);
}
