#include "hooks.h"

enum ModelType_t : int
{
    MODEL_SUN,
    MODEL_EFFECTS,
    MODEL_OTHER,
};

int GetModelType(const std::string_view& name)
{
    if (name.find("sun") != std::string::npos
        || name.find("clouds") != std::string::npos)
        return MODEL_SUN;

    if (name.find("effects") != std::string::npos)
        return MODEL_EFFECTS;
   
    return MODEL_OTHER;
}

void Hooks::DrawAggregateSceneObject::Hook(void* this_ptr, void* a2, CBaseSceneData* base_scene_data, int count, int a5, void* a6, void* a7, void* a8)
{
    IS_UNINITIALIZED(this_ptr, a2, base_scene_data, count, a5, a6, a7, a8);

    int type = GetModelType(base_scene_data->material->GetName());
    ByteColorRGB color{};
    switch (type)
    {
    case MODEL_SUN:
        color = (config.world_modulation.sunCloundsColor * 255).ToByteRGB();
        break;
    case MODEL_EFFECTS:
    case MODEL_OTHER:
        color = ((config.world_modulation.custom_prop_color ? config.world_modulation.propColor : config.world_modulation.worldColor) * 255).ToByteRGB();
        break;
    }

    for (int i = 0; i < count; ++i)
    {
        auto pScenePtr = &base_scene_data[i];
        if (pScenePtr)
        {
            pScenePtr->r = color.r;
            pScenePtr->g = color.g;
            pScenePtr->b = color.b;
            pScenePtr->a = 255;
        }
    }

    Original(this_ptr, a2, base_scene_data, count, a5, a6, a7, a8);
}