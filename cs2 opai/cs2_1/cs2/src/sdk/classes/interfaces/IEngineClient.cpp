#include "../../../utils/vmt.h"

#include "IEngineClient.h"

int IEngineClient::GetLocalPlayerIndex() {
	int index = -1;

	CALL_VIRTUAL(this, void, 47, &index, 0);

	return index + 1;
}