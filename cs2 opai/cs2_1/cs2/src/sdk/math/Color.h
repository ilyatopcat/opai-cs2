#pragma once

#include "../imgui/imgui.h"
#include <algorithm>
#include <cmath>

class ByteColorRGB {
public:
	unsigned char r, g, b;

	ByteColorRGB(float _r = 0, float _g = 0, float _b = 0) {
		r = static_cast<unsigned char>(_r);
		g = static_cast<unsigned char>(_g);
		b = static_cast<unsigned char>(_b);
	}

	ByteColorRGB operator+(ByteColorRGB color) {
		return ByteColorRGB(r + color.r, g + color.g, b + color.b);
	}

	ByteColorRGB operator+(unsigned char n) {
		return ByteColorRGB(r + n, g + n, b + n);
	}

	ByteColorRGB operator+=(ByteColorRGB color) {
		r += color.r;
		g += color.g;
		b += color.b;

		return *this;
	}

	ByteColorRGB operator+=(unsigned char n) {
		r += n;
		g += n;
		b += n;

		return *this;
	}

	ByteColorRGB operator-(ByteColorRGB color) {
		return ByteColorRGB(r - color.r, g - color.g, b - color.b);
	}

	ByteColorRGB operator-(unsigned char n) {
		return ByteColorRGB(r - n, g - n, b - n);
	}

	ByteColorRGB operator-=(ByteColorRGB color) {
		r -= color.r;
		g -= color.g;
		b -= color.b;

		return *this;
	}

	ByteColorRGB operator-=(unsigned char n) {
		r -= n;
		g -= n;
		b -= n;

		return *this;
	}

	ByteColorRGB operator/(ByteColorRGB color) {
		return ByteColorRGB(r / color.r, g / color.g, b / color.b);
	}

	ByteColorRGB operator/(unsigned char n) {
		return ByteColorRGB(r / n, g / n, b / n);
	}

	ByteColorRGB operator/=(ByteColorRGB color) {
		r /= color.r;
		g /= color.g;
		b /= color.b;

		return *this;
	}

	ByteColorRGB operator/=(unsigned char n) {
		r /= n;
		g /= n;
		b /= n;

		return *this;
	}

	ByteColorRGB operator*(ByteColorRGB color) {
		return ByteColorRGB(r * color.r, g * color.g, b * color.b);
	}

	ByteColorRGB operator*(unsigned char n) {
		return ByteColorRGB(r * n, g * n, b * n);
	}

	ByteColorRGB operator*=(ByteColorRGB color) {
		r *= color.r;
		g *= color.g;
		b *= color.b;

		return *this;
	}

	ByteColorRGB operator*=(unsigned char n) {
		r *= n;
		g *= n;
		b *= n;

		return *this;
	}

	bool operator==(ByteColorRGB color) {
		return r == color.r && g == color.g && b == color.b;
	}

	bool operator!=(ByteColorRGB color) {
		return !(*this == color);
	}
};

class ByteColorRGBA {
public:
	unsigned char r, g, b, a;

	ByteColorRGBA(float _r = 0, float _g = 0, float _b = 0, float _a = 0) {
		r = static_cast<unsigned char>(_r);
		g = static_cast<unsigned char>(_g);
		b = static_cast<unsigned char>(_b);
		a = static_cast<unsigned char>(_a);
	}

	ByteColorRGBA operator+(ByteColorRGBA color) {
		return ByteColorRGBA(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	ByteColorRGBA operator+(unsigned char n) {
		return ByteColorRGBA(r + n, g + n, b + n, a + n);
	}

	ByteColorRGBA operator+=(ByteColorRGBA color) {
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;

		return *this;
	}

	ByteColorRGBA operator+=(unsigned char n) {
		r += n;
		g += n;
		b += n;
		a += n;

		return *this;
	}

	ByteColorRGBA operator-(ByteColorRGBA color) {
		return ByteColorRGBA(r - color.r, g - color.g, b - color.b, a - color.a);
	}

	ByteColorRGBA operator-(unsigned char n) {
		return ByteColorRGBA(r - n, g - n, b - n, a - n);
	}

	ByteColorRGBA operator-=(ByteColorRGBA color) {
		r -= color.r;
		g -= color.g;
		b -= color.b;
		a -= color.a;

		return *this;
	}

	ByteColorRGBA operator-=(unsigned char n) {
		r -= n;
		g -= n;
		b -= n;
		a -= n;

		return *this;
	}

	ByteColorRGBA operator/(ByteColorRGBA color) {
		return ByteColorRGBA(r / color.r, g / color.g, b / color.b, a / color.a);
	}

	ByteColorRGBA operator/(unsigned char n) {
		return ByteColorRGBA(r / n, g / n, b / n, a / n);
	}

	ByteColorRGBA operator/=(ByteColorRGBA color) {
		r /= color.r;
		g /= color.g;
		b /= color.b;
		a /= color.a;

		return *this;
	}

	ByteColorRGBA operator/=(unsigned char n) {
		r /= n;
		g /= n;
		b /= n;
		a /= n;

		return *this;
	}

	ByteColorRGBA operator*(ByteColorRGBA color) {
		return ByteColorRGBA(r * color.r, g * color.g, b * color.b, a * color.a);
	}

	ByteColorRGBA operator*(unsigned char n) {
		return ByteColorRGBA(r * n, g * n, b * n, a * n);
	}

	ByteColorRGBA operator*=(ByteColorRGBA color) {
		r *= color.r;
		g *= color.g;
		b *= color.b;
		a *= color.a;

		return *this;
	}

	ByteColorRGBA operator*=(unsigned char n) {
		r *= n;
		g *= n;
		b *= n;
		a *= n;

		return *this;
	}

	bool operator==(ByteColorRGBA color) {
		return r == color.r && g == color.g && b == color.b && a == color.a;
	}

	bool operator!=(ByteColorRGBA color) {
		return !(*this == color);
	}
};

class ColorRGB {
public:
	float r, g, b;

	ColorRGB(float _r = 0, float _g = 0, float _b = 0) {
		r = _r;
		g = _g;
		b = _b;
	}

	ColorRGB operator+(ColorRGB color) {
		return ColorRGB(r + color.r, g + color.g, b + color.b);
	}

	ColorRGB operator+(float n) {
		return ColorRGB(r + n, g + n, b + n);
	}

	ColorRGB operator+=(ColorRGB color) {
		r += color.r;
		g += color.g;
		b += color.b;

		return *this;
	}

	ColorRGB operator+=(float n) {
		r += n;
		g += n;
		b += n;

		return *this;
	}

	ColorRGB operator-(ColorRGB color) {
		return ColorRGB(r - color.r, g - color.g, b - color.b);
	}

	ColorRGB operator-(float n) {
		return ColorRGB(r - n, g - n, b - n);
	}

	ColorRGB operator-=(ColorRGB color) {
		r -= color.r;
		g -= color.g;
		b -= color.b;

		return *this;
	}

	ColorRGB operator-=(float n) {
		r -= n;
		g -= n;
		b -= n;

		return *this;
	}

	ColorRGB operator/(ColorRGB color) {
		return ColorRGB(r / color.r, g / color.g, b / color.b);
	}

	ColorRGB operator/(float n) {
		return ColorRGB(r / n, g / n, b / n);
	}

	ColorRGB operator/=(ColorRGB color) {
		r /= color.r;
		g /= color.g;
		b /= color.b;

		return *this;
	}

	ColorRGB operator/=(float n) {
		r /= n;
		g /= n;
		b /= n;

		return *this;
	}

	ColorRGB operator*(ColorRGB color) {
		return ColorRGB(r * color.r, g * color.g, b * color.b);
	}

	ColorRGB operator*(float n) {
		return ColorRGB(r * n, g * n, b * n);
	}

	ColorRGB operator*=(ColorRGB color) {
		r *= color.r;
		g *= color.g;
		b *= color.b;

		return *this;
	}

	ColorRGB operator*=(float n) {
		r *= n;
		g *= n;
		b *= n;

		return *this;
	}

	bool operator==(ColorRGB color) {
		return r == color.r && g == color.g && b == color.b;
	}

	bool operator!=(ColorRGB color) {
		return !(*this == color);
	}

	ImColor im()
	{
		return ImColor(r, g, b);
	}

	ByteColorRGBA ToByteRGBA() {
		return ByteColorRGBA(r, g, b);
	}

	ByteColorRGB ToByteRGB() {
		return ByteColorRGB(r, g, b);
	}
};

class ColorRGBA {
public:
	float r, g, b, a;

	ColorRGBA(float _r = 0, float _g = 0, float _b = 0, float _a = 0) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	ColorRGBA operator+(ColorRGBA color) {
		return ColorRGBA(r + color.r, g + color.g, b + color.b, a + color.a);
	}

	ColorRGBA operator+(float n) {
		return ColorRGBA(r + n, g + n, b + n, a + n);
	}

	ColorRGBA operator+=(ColorRGBA color) {
		r += color.r;
		g += color.g;
		b += color.b;
		a += color.a;

		return *this;
	}

	ColorRGBA operator+=(float n) {
		r += n;
		g += n;
		b += n;
		a += n;

		return *this;
	}

	ColorRGBA operator-(ColorRGBA color) {
		return ColorRGBA(r - color.r, g - color.g, b - color.b, a - color.a);
	}

	ColorRGBA operator-(float n) {
		return ColorRGBA(r - n, g - n, b - n, a - n);
	}

	ColorRGBA operator-=(ColorRGBA color) {
		r -= color.r;
		g -= color.g;
		b -= color.b;
		a -= color.a;

		return *this;
	}

	ColorRGBA operator-=(float n) {
		r -= n;
		g -= n;
		b -= n;
		a -= n;

		return *this;
	}

	ColorRGBA operator/(ColorRGBA color) {
		return ColorRGBA(r / color.r, g / color.g, b / color.b, a / color.a);
	}

	ColorRGBA operator/(float n) {
		return ColorRGBA(r / n, g / n, b / n, a / n);
	}

	ColorRGBA operator/=(ColorRGBA color) {
		r /= color.r;
		g /= color.g;
		b /= color.b;
		a /= color.a;

		return *this;
	}

	ColorRGBA operator/=(float n) {
		r /= n;
		g /= n;
		b /= n;
		a /= n;

		return *this;
	}

	ColorRGBA operator*(ColorRGBA color) {
		return ColorRGBA(r * color.r, g * color.g, b * color.b, a * color.a);
	}

	ColorRGBA operator*(float n) {
		return ColorRGBA(r * n, g * n, b * n, a * n);
	}

	ColorRGBA operator*=(ColorRGBA color) {
		r *= color.r;
		g *= color.g;
		b *= color.b;
		a *= color.a;

		return *this;
	}

	ColorRGBA operator*=(float n) {
		r *= n;
		g *= n;
		b *= n;
		a *= n;

		return *this;
	}

	bool operator==(ColorRGBA color) {
		return r == color.r && g == color.g && b == color.b && a == color.a;
	}

	bool operator!=(ColorRGBA color) {
		return !(*this == color);
	}

	ByteColorRGBA ToByteRGBA() {
		return ByteColorRGBA(r, g, b, a);
	}

	ColorRGBA Lerp(ColorRGBA& other, float step)
	{
		ColorRGBA lerpedClr{};
		lerpedClr.r = std::lerp(r, other.r, step);
		lerpedClr.g = std::lerp(g, other.g, step);
		lerpedClr.b = std::lerp(b, other.b, step);
		lerpedClr.a = std::lerp(a, other.a, step);

		return lerpedClr;
	}

	ColorRGBA ConvertFromRGBToFloats() {
		r /= 255.f;
		g /= 255.f;
		b /= 255.f;
		a /= 255.f;
		return *this;
	}

	ImColor im()
	{
		return ImColor(r, g, b, a);
	}

	ByteColorRGB ToByteRGB() {
		return ByteColorRGB(r, g, b);
	}
};