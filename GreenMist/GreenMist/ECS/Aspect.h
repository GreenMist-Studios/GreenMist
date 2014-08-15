#ifndef ASPECT_H
#define ASPECT_H

#include <bitset>
#include <typeinfo>
#include <stdarg.h>
#include "ImmutableBag.h"
#include "Bitsize.h"
#include "ComponentType.h"

class Aspect
{
    public:
        Aspect()
        {
            allSet = new std::bitset<BITSIZE>();
            exclusionSet = new std::bitset<BITSIZE>();
            oneSet = new std::bitset<BITSIZE>();
            allSet->reset();
            exclusionSet->reset();
            oneSet->reset();
        }

        std::bitset<BITSIZE>* GetAllSet() {
            return allSet;
        }

        std::bitset<BITSIZE>* GetExclusionSet() {
            return exclusionSet;
        }

        std::bitset<BITSIZE>* GetOneSet() {
            return oneSet;
        }

        Aspect* All(const std::type_info* type, ...)
        {
            va_list arguments;

            for (va_start(arguments, type); type != NULL; type = va_arg(arguments, const std::type_info*)) {
                allSet->set(ComponentType::GetIndexFor(type), true);
            }

            va_end(arguments);

            return this;
        }

        Aspect* Exclude(const std::type_info* type,...)
        {
            va_list arguments;

            for (va_start(arguments, type); type != NULL; type = va_arg(arguments, const std::type_info*)) {
                exclusionSet->set(ComponentType::GetIndexFor(type), true);
            }

            va_end(arguments);
            return this;
        }

        Aspect* One(const std::type_info* type, ...)
        {
            va_list arguments;

            for (va_start(arguments, type); type != NULL; type = va_arg(arguments, const std::type_info*)) {
                oneSet->set(ComponentType::GetIndexFor(type), true);
            }

            va_end(arguments);
            return this;
        }

        static Aspect* GetAspectFor(const std::type_info* type,...)
        {
            return GetAspectForAll(type);
        }

        static Aspect* GetAspectForAll(const std::type_info* type, ...)
        {
            Aspect* aspect = new Aspect();

            va_list arguments;

            for (va_start(arguments, type); type != NULL; type = va_arg(arguments, const std::type_info*)) {
                aspect->allSet->set(ComponentType::GetIndexFor(type), true);
            }

            va_end(arguments);

            return aspect;
        }

        static Aspect* GetAspectForOne(const std::type_info* type)
        {
            Aspect* aspect = new Aspect();

            aspect->oneSet->set(ComponentType::GetIndexFor(type), true);

            return aspect;
        }

        static Aspect* GetEmpty()
        {
            return new Aspect();
        }
    protected:
    private:
        std::bitset<BITSIZE>* allSet;
        std::bitset<BITSIZE>* exclusionSet;
        std::bitset<BITSIZE>* oneSet;
};

#endif // ASPECT_H
