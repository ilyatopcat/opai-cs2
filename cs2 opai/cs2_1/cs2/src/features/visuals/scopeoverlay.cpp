#include "visuals.h"

Animation linesTransparentAlpha;

void Visuals::ScopeOverlay(C_CSPlayerPawn* pPlayerPawn) {
	if (config.overrideZoom.overlay != ZOOM_OVERLAY_REMOVE_OVERLAY)
		return;

	if (!pPlayerPawn)
		return;

	if (!pPlayerPawn->IsAlive())
		return;

	if (!pPlayerPawn->m_bIsScoped())
		return;

	const Vector screenSize = Render::screenSize;

	const Vector screenCenter = Render::screenCenter;
	const float screenCenterX = screenCenter.x;
	const float screenCenterY = screenCenter.y;

	const float aspectRatio = Render::aspectRatio;

	const ColorRGBA overlayColor = config.overrideZoom.color;

	const float line = config.overrideZoom.line * 0.01;

	const float lineX = line * screenCenterX;
	const float lineY = line * screenCenterY * aspectRatio;

	const float gap = config.overrideZoom.gap * 2.5;

	linesTransparentAlpha.Update(0, 1, line == 1, 0.03);

	const ColorRGBA color = ColorRGBA(overlayColor.r, overlayColor.g, overlayColor.b, overlayColor.a);
	const ColorRGBA transparentColor = ColorRGBA(overlayColor.r, overlayColor.g, overlayColor.b, linesTransparentAlpha.value);

	// left
	Render::Gradient(
		Vector(screenCenterX - gap, screenCenterY + 1),
		Vector(screenCenterX - lineX, screenCenterY),
		color, transparentColor, color, transparentColor
	);

	// top
	Render::Gradient(
		Vector(screenCenterX, screenCenterY - gap),
		Vector(screenCenterX + 1, fmax(0, screenCenterY - lineY)),
		color, color, transparentColor, transparentColor
	);

	// right
	Render::Gradient(
		Vector(round(screenCenterX + gap + 1), screenCenterY + 1),
		Vector(screenCenterX + lineX, screenCenterY),
		color, transparentColor, color, transparentColor
	);

	// bottom
	Render::Gradient(
		Vector(screenCenterX, round(screenCenterY + gap + 1)),
		Vector(screenCenterX + 1, fmin(screenSize.y, screenCenterY + lineY)),
		color, color, transparentColor, transparentColor
	);
}