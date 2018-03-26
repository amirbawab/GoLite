#include <golite/ts_helper.h>

bool golite::TSHelper::isObject(TypeComponent *type_component) {
    return type_component->resolvesToStruct()
           || type_component->resolvesToArray()
           || type_component->resolvesToSlice();
}