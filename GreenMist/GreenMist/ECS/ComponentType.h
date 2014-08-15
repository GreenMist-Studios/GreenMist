#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include <map>
#include <typeinfo>
#include <cstddef>

struct compare {
    bool operator ()(const std::type_info* a, const std::type_info* b) const {
        return a->before(*b);
    }
};

class ComponentType
{
public:
        ComponentType(const std::type_info* type);
        virtual ~ComponentType();

        int GetIndex();

        static ComponentType* GetTypeFor(const std::type_info* type)
        {
            ComponentType* testType = ComponentType::componentTypes[type];
            if (testType == NULL)
                ComponentType::componentTypes[type] = new ComponentType(type);

            return ComponentType::componentTypes[type];
        }

        static int GetIndexFor(const std::type_info* type)
        {
            return GetTypeFor(type)->GetIndex();
        }

    protected:
private:
        static int INDEX;
        static std::map<const std::type_info*, ComponentType*, compare> componentTypes;
        const std::type_info* type;
        int index;
};

#endif // COMPONENTTYPE_H
