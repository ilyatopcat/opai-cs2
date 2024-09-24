#pragma once

#include "../math/Color.h"

class CAggregateSceneObjectData {
private:
	char pad_0000[0x38]; // 0x0
public:
	ByteColorRGB color; // 0x38
private:
	char pad_0038[0x9];
};

class CAggregateSceneObject {
private:
	char pad_0000[0x120];
public:
	int count; // 0x120
private:
	char pad_0120[0x4];
public:
	CAggregateSceneObjectData* array; // 0x128
};