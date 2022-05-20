#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include <vector>

using namespace std;
using namespace sf;

class Menu {
private:
	Font mainFont;
	Font gameFont;
	Texture bg;
	Texture leaderboardImg;
	Texture scoreImg;
	enum GameState { MENU, GAME, ABOUT, TUTORIAL, END, GAMEOVER };
	GameState state;
	vector<int> leaderboard;
public:
	Menu();
	~Menu();
	void start();
	void levels();
	void about();
	void menu();
	void tutorial();
	void Gameover(bool win);
	int readScore();
	void Leaderboard();
	void sort(vector <int>& v);
};

	

