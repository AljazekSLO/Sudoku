#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "MapPicker.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>

class Sudoku {
private:
	Text sudokuNums[9][9];
	RectangleShape box[9][9];
	Font font;
	Font playtime;
	Texture bg;
	Texture sudokuTable;
	enum GAMESTATE { END };
	GAMESTATE state;
	MapPicker map;
	Clock clock;
	Time elapsed;
	Text timer;
	int selectedMap[9][9];
	int selI;
	int selJ;
	int num;
	bool selected;
	int seconds;
public:
	Sudoku();
	void getSudoku(int lvl);
	void startSudoku(RenderWindow& window, int lvl);
	void gameover(RenderWindow& window);
	void initSudokuText();
	void initBox();
	void inputNumber();
	bool checkRow(int n);
	bool checkColumn(int n);
	bool checkBox(int n);
	void checkWin();
	void Timer();
	void calcScore();
	int readScore();
	int readHighScore();
};