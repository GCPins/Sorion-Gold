#pragma once
#include "../Cheat.h"
class ClickGui : public Cheat
{
public:
	ClickGui();
	void onMouseButton(ulong button);
	void onMouseMove();
	void onEnable();
	void onDisable();
	void onKey(ulong key);
	void onPostRender();
};

void drawKeybindSetting(Cheat* cheat, Rect cheatRect, int* cheatExpOff, int* settingOff, int mx, int my);
