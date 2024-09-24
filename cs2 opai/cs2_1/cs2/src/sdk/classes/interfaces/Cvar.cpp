#include <stdint.h>

#include "CVar.h"

#include "../../../hash/hash.h"
#include "../../../utils/vmt.h"

CVarIterator_t Cvar::GetFirstCvarIterator() {
	CVarIterator_t iterator = -1;

	CALL_VIRTUAL(this, void, 12, &iterator);

	return iterator;
}

CVarIterator_t Cvar::GetNextCvarIterator(CVarIterator_t previous) {
    CVarIterator_t iterator = previous;

    CALL_VIRTUAL(this, void, 13, &iterator, previous);

    return iterator;
}

ConVar* Cvar::GetByIndex(CVarIterator_t index) {
	return CALL_VIRTUAL(this, ConVar*, 37, index);
}

ConVar* Cvar::GetByName(const char* name) {
    uint64_t hash = HASH(name);

    CVarIterator_t iterator = GetFirstCvarIterator();

    while (true) {
        ConVar* cvar = GetByIndex(iterator);

        if (!cvar)
            break;

        if (HASH(cvar->name) == hash)
            return cvar;

        iterator = GetNextCvarIterator(iterator);
    }

    return nullptr;
}

void Cvar::UnlockHidden() {
    CVarIterator_t iterator = GetFirstCvarIterator();

    while (true) {
        ConVar* cvar = GetByIndex(iterator);

        if (!cvar)
            break;

        cvar->flags &= ~(FCVAR_HIDDEN | FCVAR_DEVELOPMENTONLY);

        iterator = GetNextCvarIterator(iterator);
    }
}