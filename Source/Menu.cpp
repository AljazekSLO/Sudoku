#include "Menu.h"
#include "Sudoku.h"
#include <iostream>

RenderWindow window(VideoMode(800, 600), "Aljazek's Sudoku", Style::Titlebar | Style::Close);

//Colors
sf::Color menuColor(0, 196, 255);
sf::Color hoverColor(254, 77, 77);


Menu::Menu()
{

	//Background 
	bg.loadFromFile("./Images/menu_bg.png");
	leaderboardImg.loadFromFile("./Images/leaderboard.png");


	//Font loading
	gameFont.loadFromFile("./Fonts/arial.ttf");
	mainFont.loadFromFile("./Fonts/olive.ttf");

	state = MENU;
}


Menu::~Menu() {}


void Menu::start()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::ABOUT:
			about();
			break;
		case GameState::TUTORIAL:
			tutorial();
			break;
		case GameState::GAME:
			levels();
			break;
		}		
	}
}

//MAIN MENU
void Menu::menu()
{
	Sprite background(bg);
	background.setScale(1.5, 1.5);

	//MAIN TITLE
	Text title;
	title.setString("Aljazek's Sudoku");
	title.setFont(mainFont);
	title.setCharacterSize(80);
	title.setStyle(Text::Bold);
	title.setFillColor(menuColor);
	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 60);

	const int options = 4;
	Text optionsText[options];

	string tab[] = { "PLAY","PROJECT","HOW TO PLAY", "EXIT"};
	for (int i = 0; i<options; i++)
	{
		if (i != 3) {
			// PLAY, PROJECT, TUTORIAL
			optionsText[i].setFont(gameFont);
			optionsText[i].setStyle(Text::Bold);
			optionsText[i].setCharacterSize(50);
			optionsText[i].setString(tab[i]);
			optionsText[i].setPosition(800 / 2 - optionsText[i].getGlobalBounds().width / 2, 200 + i * 70);
		}
		else {
			//EXIT
			optionsText[i].setFont(gameFont);
			optionsText[i].setCharacterSize(60);
			optionsText[i].setStyle(Text::Bold);
			optionsText[i].setString(tab[i]);
			optionsText[i].setPosition(800 / 2 - optionsText[i].getGlobalBounds().width / 2, 200 + i * 90);
		}
		
	}


	while (state == MENU && window.isOpen())
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			//START                                      
			if (optionsText[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = GAME;
			}

			//PROJECT
			else if (optionsText[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = ABOUT;
			}

			//TUTORIAL
			else if (optionsText[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = TUTORIAL;
			}
			//EXIT
			else if (event.type == Event::Closed || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape || optionsText[3].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				window.close();
		}
		//APPEARANCE
		for (int i = 0; i<options; i++)
			if (optionsText[i].getGlobalBounds().contains(mouse)) optionsText[i].setFillColor(hoverColor);
			else optionsText[i].setFillColor(Color::White);

			window.clear();
			window.draw(background);
			window.draw(title);
			for (int i = 0; i< options; i++) window.draw(optionsText[i]);
			window.display();
	}
}


//GAME OVER SCREEN
void Menu::Gameover(bool win) {
	state = GAMEOVER;

	Sprite leaderimg(leaderboardImg);
	leaderimg.setScale(0.75, 0.75);
	leaderimg.setPosition(800 / 2 - leaderimg.getGlobalBounds().width / 2, 170);

	Leaderboard();

	Sprite background(bg);
	background.setScale(1.5, 1.5);


	//TEXTS
	sf::Text winner;
	winner.setString("Congratulations! You have Won!");
	winner.setFont(mainFont);
	winner.setCharacterSize(50);
	winner.setStyle(sf::Text::Bold);
	winner.setFillColor(menuColor);
	winner.setPosition(800 / 2 - winner.getGlobalBounds().width / 2, 40);

	sf::Text loser;
	loser.setString("You ran out of time!");
	loser.setFont(mainFont);
	loser.setCharacterSize(50);
	loser.setStyle(sf::Text::Bold);
	loser.setFillColor(menuColor);
	loser.setPosition(800 / 2 - loser.getGlobalBounds().width / 2, 40);

	sf::Text score;
	score.setFont(gameFont);
	score.setCharacterSize(30);
	score.setStyle(sf::Text::Bold);
	score.setString("Score: " + to_string(readScore()));
	score.setFillColor(Color::Black);
	score.setPosition(800 / 2 - score.getGlobalBounds().width / 2, 130);

	const int options = 5;

	sf::Text highscore[options];

	int size = leaderboard.size() - 1;
	for (int i = 0; i <= size && i < 5; i++) {
		highscore[i].setFont(gameFont);
		highscore[i].setCharacterSize(25);
		highscore[i].setString(to_string(leaderboard[size - i]));
		highscore[i].setFillColor(Color::Black);
		highscore[i].setPosition(430, 288 + i * 34.5);
	}
	

	Text back;
	back.setString("Press ESC to return!");
	back.setFont(gameFont);
	back.setCharacterSize(20);
	back.setStyle(Text::Bold);
	back.setPosition(800 / 2 - back.getGlobalBounds().width / 2 + 10, 550);


	while (state == GAMEOVER && window.isOpen())
	{
		Vector2f mouse(sf::Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.key.code == sf::Keyboard::Escape)
			{
				state = MENU;
				start();
			}
		}
			
			window.clear();
			window.draw(background);
			window.draw(leaderimg);
			for (int i = 0; i < 5; i++) {
				window.draw(highscore[i]);
			}
			
			window.draw(back);
			if (win) {
				window.draw(winner);
				window.draw(score);
			}
			else {
				window.draw(loser);
			}
			window.display();
		}
}
// HOW TO PLAY SCREEN
void Menu::tutorial() {
	Sprite background(bg);
	background.setScale(1.5, 1.5);

	Text tutorial;
	tutorial.setString("HOW TO PLAY:");
	tutorial.setFont(mainFont);
	tutorial.setCharacterSize(60);
	tutorial.setFillColor(menuColor);
	tutorial.setStyle(Text::Bold);
	tutorial.setPosition(800 / 2 - tutorial.getGlobalBounds().width / 2, 100);

	const int options = 4;
	Text text[options];

	string tab[] = { "Move around the field with your MOUSE","Select a field with LEFT-CLICK","Input a selected number with KEYBOARD (1-9)", "Delete a specific field with RIGHT-CLICK" };
	

	for (int i = 0; i < options; i++)
	{
			text[i].setFont(gameFont);
			text[i].setStyle(Text::Bold);
			text[i].setCharacterSize(20);
			text[i].setString(tab[i]);
			text[i].setPosition(800 / 2 - text[i].getGlobalBounds().width / 2, 200 + i * 40);
	}


	Text back;
	back.setString("BACK");
	back.setFont(gameFont);
	back.setCharacterSize(60);
	back.setStyle(Text::Bold);
	back.setPosition(800 / 2 - back.getGlobalBounds().width / 2, 440);


	while (state == TUTORIAL && window.isOpen())
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (back.getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left || event.key.code == Keyboard::Escape)
			{
				state = MENU;
			}
		}
		//CHANGE COLOR ON HOVER 
		if (back.getGlobalBounds().contains(mouse)) back.setFillColor(hoverColor);	
		else back.setFillColor(Color::White);
			
		window.clear();
		window.draw(background);
		window.draw(tutorial);
		window.draw(back);
		for (int i = 0; i < 4; i++) window.draw(text[i]);
		window.display();
	}
}

//PROJECT
void Menu::about()
{
	Sprite background(bg);
	background.setScale(1.5, 1.5);

	Text author;
	author.setString("AUTHOR: Aljaz Radovan, R3A");
	author.setFont(gameFont);
	author.setCharacterSize(40);
	author.setStyle(Text::Bold);
	author.setPosition(800 / 2 - author.getGlobalBounds().width / 2, 200);
	author.setStyle(Text::Bold);

	Text text;
	text.setString("Replica of a popular logic-based puzzle named Sudoku!");
	text.setFont(gameFont);
	text.setCharacterSize(25);
	text.setPosition(800 / 2 - text.getGlobalBounds().width / 2, 250);

	Text back;
	back.setString("BACK");
	back.setFont(gameFont);
	back.setCharacterSize(60);
	back.setStyle(Text::Bold);
	back.setPosition(800 / 2 - back.getGlobalBounds().width / 2, 440);


	while (state == ABOUT && window.isOpen())
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//BACK
			else if (back.getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left || event.key.code == Keyboard::Escape)
			{
				state = MENU;
			}
		}
		//CHANGE COLOR ON HOVER
		if (back.getGlobalBounds().contains(mouse)) back.setFillColor(hoverColor);	
		else back.setFillColor(Color::White);		

		window.clear();
		window.draw(background);
		window.draw(author);
		window.draw(text);
		window.draw(back);
		window.display();
	}
}


 void Menu::levels()
{

	Sprite background(bg);
	background.setScale(1.5, 1.5);

	//TEXT
	sf::Text title;
	title.setString("Choose Difficulty");
	title.setFont(mainFont);
	title.setCharacterSize(80);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(menuColor);
	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2, 60);

	const int options = 4;
	Text optionsText[options];

	string tab[] = { "EASY","MEDIUM","HARD", "BACK" };
	for (int i = 0; i< options; i++)
	{
		if (i != 3) {
			optionsText[i].setFont(gameFont);
			optionsText[i].setCharacterSize(50);
			optionsText[i].setString(tab[i]);
			optionsText[i].setStyle(sf::Text::Bold);
			optionsText[i].setPosition(800 / 2 - optionsText[i].getGlobalBounds().width / 2, 200 + i * 70);
		}
		else {
			optionsText[i].setFont(gameFont);
			optionsText[i].setCharacterSize(60);
			optionsText[i].setStyle(Text::Bold);
			optionsText[i].setString(tab[i]);
			optionsText[i].setPosition(800 / 2 - optionsText[i].getGlobalBounds().width / 2, 200 + i * 90);
		}
	}


	while (state == GAME && window.isOpen())
	{
		Vector2f mouse(sf::Mouse::getPosition(window));
		Event event;
		Sudoku sudoku;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (optionsText[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				//STARTING LEVEL: EASY
				sudoku.startSudoku(window, 0);
				state = GAME;
				
			}

			else if (optionsText[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				//STARTING LEVEL: NORMAL
				sudoku.startSudoku(window, 1);
				state = GAME;
			}

			else if (optionsText[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				//STARTING LEVEL: HARD
				sudoku.startSudoku(window, 2);
				state = GAME;
			}

			else if (optionsText[3].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left || event.key.code == Keyboard::Escape)
			{
				state = MENU;

			}
		}
		//CHANGE COLOR ON HOVER
		for (int i = 0; i<options; i++)
			if (optionsText[i].getGlobalBounds().contains(mouse)) optionsText[i].setFillColor(hoverColor);	
			else optionsText[i].setFillColor(Color::White);


		window.clear();
		window.draw(background);
		window.draw(title);
		for (int i = 0; i<options; i++)
			window.draw(optionsText[i]);
		window.display();
	}
	

}

 //READING SCORE FROM FILE
 int Menu::readScore() {
	 fstream dat;
	 string vrstica;
	 int stevilo = 0;

	 dat.open("score.txt", ios::in);
	 while (getline(dat, vrstica)) {
		 stevilo = stoi(vrstica);
	 }
	 return stevilo;
	 dat.close();
 }

 void Menu::Leaderboard() {
	 fstream dat;
	 string vrstica;

	 dat.open("score.txt", ios::in);
	 while (getline(dat, vrstica)) {
		 leaderboard.push_back(stoi(vrstica));
	 }
	 sort(leaderboard);
	 dat.close();
 }

 void Menu::sort(vector <int>& v) {
	 vector<int> res;
	 if (v.size() == 1)
	 {
		 return;
	 }
	 int temp = v[v.size() - 1];
	 v.pop_back();
	 sort(v);

	 int it = 0;
	 while (it < v.size())
	 {

		 if (temp < v[it])
		 {
			 res.insert(it + res.begin(), temp);
			 temp = 1000000;
		 }
		 else
		 {
			 res.push_back(v[it]);
			 it = it + 1;
		 }
	 }

	 if (res.size() == v.size())
		 res.push_back(temp);

	 v = res;
 }
