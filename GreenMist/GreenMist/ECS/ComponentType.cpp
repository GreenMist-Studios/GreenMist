#include "ComponentType.h"

int ComponentType::INDEX = 0;
std::map<const std::type_info*, ComponentType*, compare> ComponentType::componentTypes = std::map<const std::type_info*, ComponentType*, compare>();

ComponentType::ComponentType(const std::type_info* type)
{
    index = ComponentType::INDEX++;
    this->type = type;
}

ComponentType::~ComponentType()
{
    //dtor
}

int ComponentType::GetIndex()
{
    return index;
}


