#pragma once

#include <stdint.h>
#include <string>

#include "../../utils/utils.h"
#include "../../sdk/math/CUtlBuffer.h"

#include "../math/Vector.h"
#include "../math/Color.h"

class CDebugOverlaySystem
{
public:
	void AddBoxOverlay(const Vector& end, const Vector& mins, const Vector& maxs, const Vector& a3, ColorRGBA clr)
	{
		using function_t = void(__thiscall*)(CDebugOverlaySystem*, const Vector&, const Vector&, const Vector&, const Vector&, int, int, int, int, double);
		(*reinterpret_cast<function_t**>(std::uintptr_t(this)))[48](this, end, mins, maxs, a3, clr.r, clr.g, clr.b, clr.a, static_cast<double>(4.f));
	}
};