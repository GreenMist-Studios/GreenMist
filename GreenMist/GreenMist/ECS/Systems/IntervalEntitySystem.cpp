#include "IntervalEntitySystem.h"

bool IntervalEntitySystem::CheckProcessing()
{
    acc += world->GetDelta();
    if(acc >= interval) {
        acc -= interval;
        return true;
    }
    return false;
}
