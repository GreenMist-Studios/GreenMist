#ifndef DELAYEDENTITYPROCESSINGSYSTEM_H
#define DELAYEDENTITYPROCESSINGSYSTEM_H

#include "../EntitySystem.h"


class DelayedEntityProcessingSystem : public EntitySystem
{
    public:
        DelayedEntityProcessingSystem(Aspect* aspect) : EntitySystem(aspect)
        {
			running = false;
			delay = 0.0f;
			acc = 0.0f;
        }

		void ProcessEntities(std::vector<Entity*>* entities)
        {
			for (int i = 0, s = entities->size(); s > i; i++) {
                Entity* entity = entities->at(i);
                ProcessDelta(entity, acc);
                float remaining = GetRemainingDelay(entity);
                if(remaining <= 0) {
                    ProcessExpired(entity);
                } else {
                    OfferDelay(remaining);
                }
            }
            Stop();
        }

        void Inserted(Entity* e)
        {
            float delay = GetRemainingDelay(e);
            if(delay > 0) {
                OfferDelay(delay);
            }
        }

        virtual float GetRemainingDelay(Entity* e){}
        bool CheckProcessing() {
            if(running) {
                acc += world->GetDelta();

                if(acc >= delay) {
                    return true;
                }
            }
            return false;
        }

        virtual void ProcessDelta(Entity* e, float accumulatedDelta){}
        virtual void ProcessExpired(Entity* e);

        void Restart(float d)
        {
            delay = d;
            acc = 0;
            running = true;
        }

        void OfferDelay(float delay)
        {
            if(!running || delay < GetRemainingTimeUntilProcessing()) {
                Restart(delay);
            }
        }

        float GetInitialTimeDelay()
        {
            return delay;
        }

        float GetRemainingTimeUntilProcessing() {
            if(running) {
                return delay-acc;
            }
            return 0;
        }

        bool IsRunning() {
            return running;
        }

        void Stop()
        {
            running = false;
            acc = 0;
        }

    private:
        float delay;
        bool running;
        float acc;
};

#endif // DELAYEDENTITYPROCESSINGSYSTEM_H
