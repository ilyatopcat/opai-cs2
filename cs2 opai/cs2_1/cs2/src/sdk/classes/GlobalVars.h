#pragma once

class GlobalVars
{
public:
	float realtime; //0x0000
	int32_t frameCount; //0x0004
	float frameTime; //0x0008
	float absFrameTime; //0x000C
	int32_t maxClients; //0x0010
	bool unkBool; //0x0014
	char pad_0015[3]; //0x0015
	float unkFlt; //0x0018
	float frameTime3; //0x001C
	float unkFlt2; //0x0020
	float unkCounter; //0x0024
	char pad_0028[8]; //0x0028
	float N0000008D; //0x0030
	float curTime; //0x0034
	float curTime2; //0x0038

};