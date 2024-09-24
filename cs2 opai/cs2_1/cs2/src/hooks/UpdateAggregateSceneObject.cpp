#include "hooks.h"

void* Hooks::UpdateAggregateSceneObject::Hook(CAggregateSceneObject* pAggregateSceneObject, void* a2) {
    IS_UNINITIALIZED(pAggregateSceneObject, a2);

    void* result = Original(pAggregateSceneObject, a2);

    ByteColorRGB color = (config.world_modulation.worldColor * 255).ToByteRGB();

    int count = pAggregateSceneObject->count;

    for (int i = 0; i < count; i++) {
        CAggregateSceneObjectData* pAggregateSceneObjectData = &pAggregateSceneObject->array[i];

        pAggregateSceneObjectData->color = color;
    }

    return result;
}