#include "render.h"
#include "bytes.h"

void Render::UpdateScreenSize(ImGuiIO io) {
	const ImVec2 displaySize = io.DisplaySize;

	screenSize = Vector(displaySize.x, displaySize.y);
	
	screenCenter = screenSize * 0.5;

	aspectRatio = screenSize.x / screenSize.y;
}

void Render::Initialize()
{
	auto& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	ImGui::StyleColorsClassic();

	auto& style = ImGui::GetStyle();
	style.WindowTitleAlign = ImVec2{ 0.5f, 0.5f };
	style.WindowRounding = 10.0f;
	style.ChildRounding = 10.0f;
	style.ChildBorderSize = 0.0f;
	style.WindowBorderSize = 0.0f;

	ImFontConfig cfg;
	cfg.PixelSnapH = false;
	cfg.OversampleH = 5;
	cfg.OversampleV = 5;

	fonts.verdana = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 15.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	fonts.verdanaSmall = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 12.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

	auto prev_flags = cfg.FontBuilderFlags;
	cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_MonoHinting | ImGuiFreeTypeBuilderFlags_Monochrome;
	fonts.onetapPixel = io.Fonts->AddFontFromMemoryTTF(onetapPixelFont, sizeof(onetapPixelFont), 8.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	cfg.FontBuilderFlags = prev_flags;

	io.FontDefault = fonts.verdana;
}

void Render::UpdateBackgroundDrawList(ImDrawList* pNewBackgroundDrawList) {
	backgroundDrawList = pNewBackgroundDrawList;
}

bool Render::WorldToScreen(Vector& position, Vector& output) {
	using ScreenTransform_t = bool(__fastcall*)(Vector&, Vector&);
	static ScreenTransform_t ScreenTransform = reinterpret_cast<ScreenTransform_t>(Utils::OpcodeScan("client.dll", "48 89 74 24 ? 57 48 83 EC 20 48 8B 05 ? ? ? ? 48 8B FA"));

	if (!ScreenTransform)
		return false;

	bool onScreen = ScreenTransform(position, output);
	if (onScreen)
		return false;

	const float screenSizeX = screenSize.x;
	const float screenSizeY = screenSize.y;

	output.x = ((output.x + 1.0f) * 0.5f) * screenSizeX;
	output.y = screenSizeY - (((output.y + 1.0f) * 0.5f) * screenSizeY);

	return true;
}

void Render::Line(Vector startPosition, Vector endPosition, ColorRGBA color) {
	backgroundDrawList->AddLine(startPosition.im(), endPosition.im(), color.im());
}

void Render::Rect(Vector startPosition, Vector endPosition, ColorRGBA color, float rounding) {
	backgroundDrawList->AddRectFilled(startPosition.im(), endPosition.im(), color.im(), rounding);
}

void Render::RectOutline(Vector startPosition, Vector endPosition, ColorRGBA color, float thickness, float rounding) {
	backgroundDrawList->AddRect(startPosition.im(), endPosition.im(), color.im(), rounding, 0, thickness);
}

void Render::Gradient(Vector startPosition, Vector endPosition, ColorRGBA topLeftColor, ColorRGBA topRightColor, ColorRGBA bottomLeftColor, ColorRGBA bottomRightColor) {
	backgroundDrawList->AddRectFilledMultiColor(startPosition.im(), endPosition.im(), topLeftColor.im(), topRightColor.im(), bottomRightColor.im(), bottomLeftColor.im());
}

void Render::Text(Vector txt_pos, ColorRGBA color, const int flags, const ImFont* font, const std::string_view& message, const int font_size) {
	backgroundDrawList->PushTextureID(font->ContainerAtlas->TexID);

	const auto size = font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, message.data());
	auto pos = ImVec2(txt_pos.x, txt_pos.y);
	auto outline_clr = ColorRGBA(0, 0, 0, color.a * 0.3f);

	if (flags & FontFlags_Center)
		pos = ImVec2(txt_pos.x - size.x / 2.0f, txt_pos.y);

	if (flags & FontFlags_DropShadow)
		backgroundDrawList->AddText(ImVec2(pos.x + 1, pos.y + 1), outline_clr.im(), message.data());

	if (flags & FontFlags_Outline)
	{
		backgroundDrawList->AddText(font, font_size, ImVec2(pos.x + 1, pos.y - 1), outline_clr.im(), message.data());
		backgroundDrawList->AddText(font, font_size, ImVec2(pos.x - 1, pos.y + 1), outline_clr.im(), message.data());
		backgroundDrawList->AddText(font, font_size, ImVec2(pos.x - 1, pos.y - 1), outline_clr.im(), message.data());
		backgroundDrawList->AddText(font, font_size, ImVec2(pos.x + 1, pos.y + 1), outline_clr.im(), message.data());
		backgroundDrawList->AddText(font, font_size, ImVec2(pos.x, pos.y + 1), outline_clr.im(), message.data());
		backgroundDrawList->AddText(font, font_size, ImVec2(pos.x, pos.y - 1), outline_clr.im(), message.data());
		backgroundDrawList->AddText(font, font_size, ImVec2(pos.x + 1, pos.y), outline_clr.im(), message.data());
		backgroundDrawList->AddText(font, font_size, ImVec2(pos.x - 1, pos.y), outline_clr.im(), message.data());
	}

	backgroundDrawList->AddText(font, font_size, pos, color.im(), message.data());
}

float linear(float t, float b, float c, float d) {
	return c * t / d + b;
}

void Animation::Update(float min, float max, bool active, float time) {
	float frametime = Interfaces::globalVars->frameTime;

	value = linear(1, value, frametime * (active ? time : -time) * 175, 1);
	value = std::clamp(value, min, max);
}