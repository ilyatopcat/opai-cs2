#pragma once

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_freetype.h"
#include "../sdk/math/Vector.h"

#include "../sdk/interfaces/interfaces.h"

#include "../utils/utils.h"

#include <algorithm>

enum EFontFlags
{
	FontFlags_Center = 1 << 0,
	FontFlags_Outline = 1 << 1,
	FontFlags_DropShadow = 1 << 2
};

struct CFonts
{
public:
	ImFont* verdana;
	ImFont* verdanaSmall;
	ImFont* onetapPixel;
};

namespace Render {
	inline Vector screenSize;
	inline Vector screenCenter;
	inline float aspectRatio;
	inline ImDrawList* backgroundDrawList;

	inline CFonts fonts;

	void UpdateScreenSize(ImGuiIO);

	void Initialize();

	void UpdateBackgroundDrawList(ImDrawList*);

	bool WorldToScreen(Vector&, Vector&);

	void Line(Vector startPosition, Vector endPosition, ColorRGBA color);

	void Rect(Vector startPosition, Vector endPosition, ColorRGBA color, float rounding = 0.0f);
	void RectOutline(Vector startPosition, Vector endPosition, ColorRGBA color, float thickness = 1.f, float rounding = 0.0f);

	void Gradient(Vector startPosition, Vector endPosition, ColorRGBA topLeftColor, ColorRGBA topRightColor, ColorRGBA bottomLeftColor, ColorRGBA bottomRightColor);

	void Text(Vector txt_pos, ColorRGBA color, const int flags, const ImFont* font, const std::string_view& message, const int font_size);
}

class Animation {
public:
	float value;

	Animation(float initValue = 0) {
		value = initValue;
	}

	void Update(float min, float max, bool active, float time);
};