#include "pch.h"
#include "TabGUI.h"
#include "../../SDK/DrawUtils.h"
#include "../CheatManager.h"

TabGUI::TabGUI():Cheat::Cheat("TabGUI", "Visuals")
{
	enabled = true;
}

int highlightedCht = 0;
int highlightedCat = 0;
bool catIsSel = false;
void TabGUI::onPostRender()
{
	if (enabled) {
		vector<Cheat*> cheats = CheatManager::getCheats();
		vector<string> categories = CheatManager::getCategories();

		if (catIsSel) {
			vector<Cheat*> cheatsInThisCat = vector<Cheat*>();
			for (uint i = 0; i < cheats.size(); i++) {
				if (cheats[i]->category.compare(categories[highlightedCat]) == 0) {
					cheatsInThisCat.push_back(cheats[i]);
				}
			}
			// x and y are position, z is width and w is height
			DrawUtils::fillRectangle(Vector4(8, 8, 150, 32 + (cheatsInThisCat.size() * 10)), Color(0, 0, 0, 1), .5);
			DrawUtils::drawRectangle(Vector4(8, 8, 150, 32 + (cheatsInThisCat.size() * 10)), Color(0.31, 0.34, 0.35, 1), .5, 2);
			Color* test = new Color(0.31, 0.34, 0.35, 1);
			Color* ts = new Color(0.75, 0.75, 0.75, 1);
			std::string sorStr = std::string("Sorion Silver");
			DrawUtils::drawText(Vector2(12, 11), &sorStr, ts, 2.0f);
			Color* white = new Color(0.31, 0.34, 0.35, 1);
			for (uint i = 0; i < cheatsInThisCat.size(); i++) {
				bool selected = highlightedCht == i;
				Color* color = nullptr;
				if (cheatsInThisCat[i]->enabled) {
					color = new Color(0.31, 0.34, 0.35, 1);
				}
				if (selected) {
					DrawUtils::drawText(Vector2(12, 30 + (i * 10)), &string(">" + cheatsInThisCat[i]->name), color, 1.0f);
				}
				else {
					DrawUtils::drawText(Vector2(12, 30 + (i * 10)), &cheatsInThisCat[i]->name, color, 1.0f);
				}
			}
		}
		else {
			DrawUtils::fillRectangle(Vector4(8, 8, 150, 32 + (categories.size() * 10)), Color(0, 0, 0, 1), .5);
			DrawUtils::drawRectangle(Vector4(8, 8, 150, 32 + (categories.size() * 10)), Color(0.31, 0.34, 0.35, 1), .5, 2);
			Color* test = new Color(0.31, 0.34, 0.35, 1);
			Color* white = new Color(0.31, 0.34, 0.35, 1);
			Color* ts = new Color(0.75, 0.75, 0.75, 1);
			std::string sorStr = std::string("Sorion Silver");
			DrawUtils::drawText(Vector2(12, 11), &sorStr, ts, 2.0f);
			for (uint i = 0; i < categories.size(); i++) {
				bool selected = highlightedCat == i;
				if (selected) {
					DrawUtils::drawText(Vector2(12, 30 + (i * 10)), &string(">" + categories[i]), test, 1.0f);
				}
				else {
					DrawUtils::drawText(Vector2(12, 30 + (i * 10)), &categories[i], nullptr, 1.0f);
				}
			}
		}
	}
}

void TabGUI::onKey(ulong key)
{
	if (enabled) {
		//logHex("key", key);
		vector<string> categories = CheatManager::getCategories();
		if (catIsSel) {
			vector<Cheat*> cheatsInThisCat = vector<Cheat*>();
			vector<Cheat*> cheats = CheatManager::getCheats();
			for (uint i = 0; i < cheats.size(); i++) {
				if (cheats[i]->category.compare(categories[highlightedCat]) == 0) {
					cheatsInThisCat.push_back(cheats[i]);
				}
			}
			if (key == 0x28) {
				highlightedCht++;
			}
			if (key == 0x26) {
				highlightedCht--;
			}
			if (key == 0x25) {
				catIsSel = false;
			}
			if (key == 0x27) {
				cheatsInThisCat[highlightedCht]->enabled = !cheatsInThisCat[highlightedCht]->enabled;
			}
			//Logger::log("HCht: " + to_string(highlightedCht));
			if (highlightedCht <= -1) {
				highlightedCht = cheatsInThisCat.size() - 1;
			}
			if (highlightedCht >= cheatsInThisCat.size()) {
				highlightedCht = 0;
			}
		}
		else {
			if (key == 0x28) {
				highlightedCat++;
			}
			if (key == 0x26) {
				highlightedCat--;
			}
			if (key == 0x27) {
				highlightedCht = 0;
				catIsSel = true;
			}
			if (highlightedCat >= categories.size()) {
				highlightedCat = 0;
			}
		}
	}
}
