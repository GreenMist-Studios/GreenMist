#ifndef ENTITYOBSERVER_H
#define ENTITYOBSERVER_H

class Entity;

class EntityObserver
{
public:
    virtual void Added(Entity* e){}
    virtual void Changed(Entity* e){}
    virtual void Deleted(Entity* e){}
    virtual void Enabled(Entity* e){}
    virtual void Disabled(Entity* e){}
};

#endif // ENTITYOBSERVER_H
