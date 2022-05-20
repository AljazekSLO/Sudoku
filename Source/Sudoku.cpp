#include "Sudoku.h"

using namespace std;

Color changableColor(181, 181, 181);
Color changableOverlay(146, 146, 146);


Sudoku::Sudoku() {
	//Font 
    font.loadFromFile("./Fonts/arial.ttf");
    playtime.loadFromFile("./Fonts/roboto.ttf");

    //Image 
	bg.loadFromFile("./Images/menu_bg.png");
    sudokuTable.loadFromFile("./Images/sudoku.png");

    selI = -1;
    selJ = -1;
    selected = false;
    
}

void Sudoku::startSudoku(RenderWindow &window, int lvl) {

	Sprite background(bg);
    background.setScale(1.5, 1.5);


    Sprite table(sudokuTable);
    table.setScale(0.8, 0.8);
    table.setPosition(800 / 2 - table.getGlobalBounds().width / 2, 5);

    Text back;
    back.setString("Press ESC to quit!");
    back.setFont(playtime);
    back.setCharacterSize(20);
    back.setPosition(800 / 2 - back.getGlobalBounds().width / 2 + 10, 550);


    getSudoku(lvl);
    initSudokuText();
    initBox();


    while (window.isOpen() && state != END)
    {
		Vector2f mouse(sf::Mouse::getPosition(window));
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.key.code == sf::Keyboard::Escape) {
                Menu menu;
                menu.start();
            }
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (box[i][j].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
                    {
                        if (sudokuNums[i][j].getString() == "") {
                            selI = i;
                            selJ = j;
                            selected = true;

                        }
                        else 
                            cout << "Please select an empty field!" << endl;
                    }
                    else if(box[i][j].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Right)
                        if (sudokuNums[i][j].getString() != "" && selectedMap[j][i] == 0) {
                            sudokuNums[i][j].setString("");
                    }
                }
                
            }

            //CHANGE APPEARANCE
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++) {

                    box[i][j].setOutlineColor(Color::Transparent);
                    box[i][j].setFillColor(Color::Transparent);

                    if (box[i][j].getGlobalBounds().contains(mouse) && sudokuNums[i][j].getString() == "") {
                        box[i][j].setOutlineColor(Color::Green);
                        box[i][j].setOutlineThickness(4);
                    }
                    if (selected) {
                        box[selI][selJ].setOutlineColor(Color::Blue);
                        box[selI][selJ].setFillColor(Color::Transparent);
                    }

                    if (selectedMap[j][i] == 0 && sudokuNums[i][j].getString() != "") {
                        box[i][j].setOutlineColor(changableOverlay);
                        box[i][j].setFillColor(changableColor);
                        box[i][j].setOutlineThickness(4);
                    }

                    
                }
        }

        if (selected) {
            inputNumber();
        }

        if (seconds > 600) {
            Menu menu;
            menu.Gameover(0);
        }
        else {
            Timer();
        }
        
        
        window.clear();
        window.draw(background);
        window.draw(table);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                window.draw(box[i][j]);
            }
        }
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                window.draw(sudokuNums[i][j]);
            }
        }
        window.draw(back);
        window.draw(timer);
        window.display();
    }
}


void Sudoku::initBox() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; ++j) {
            box[i][j].setSize(Vector2f(42.f, 42.f));
            box[i][j].setFillColor(Color::Transparent);
            box[i][j].setPosition(49.3 * i + 183, 49.43 * j + 26);
        }
    }

}
void Sudoku::initSudokuText()
{   

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; ++j) {
            if (selectedMap[j][i] == 0) {
                sudokuNums[i][j].setString("");
            }
            else {
                sudokuNums[i][j].setString(to_string(selectedMap[j][i]));
            }
            sudokuNums[i][j].setFont(font);
            sudokuNums[i][j].setCharacterSize(40);
            sudokuNums[i][j].setFillColor(Color::Black);
            sudokuNums[i][j].setPosition(49.3 * i + 191, 49.3 * j + 24);
        }
    }

}

void Sudoku::inputNumber()
{
    num = -1;
    Keyboard key;
    if (key.isKeyPressed(key.Num1))
    {
        num = 1;
    }
    else if (key.isKeyPressed(key.Num2))
    {
        num = 2;
    }
    else if (key.isKeyPressed(key.Num3))
    {
        num = 3;
    }
    else if (key.isKeyPressed(key.Num4))
    {
        num = 4;
    }
    else if (key.isKeyPressed(key.Num5))
    {
        num = 5;
    }
    else if (key.isKeyPressed(key.Num6))
    {
        num = 6;
    }
    else if (key.isKeyPressed(key.Num7))
    {
        num = 7;
    }
    else if (key.isKeyPressed(key.Num8))
    {
        num = 8;
    }
    else if (key.isKeyPressed(key.Num9))
    {
        num = 9;
    }

    if (num != -1) {
        if (checkRow(num) && checkColumn(num) && checkBox(num)) {
            sudokuNums[selI][selJ].setString(to_string(num));
            checkWin();
        };
    }
}

void Sudoku::checkWin() {
    int empty = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudokuNums[i][j].getString() == "") {
                empty++;

            }
        }
    }
    if (empty == 0) {
        Menu menu;
        state = END;
        calcScore();
        menu.Gameover(1);

    }
}

void Sudoku::calcScore() {
    int score = (seconds / 10 * (-16.653) + 999);
    fstream dat;
    dat.open("score.txt", ios::out | ios::app);
    if (!dat.is_open()) {
        cout << "File couldn't load!" << endl;
    }
    else {
        dat << score << endl;
    }
    dat.close();

}

void Sudoku::Timer() {
    elapsed = clock.getElapsedTime();
    seconds = elapsed.asSeconds();
    timer.setCharacterSize(30);
    timer.setFillColor(Color::Black);
    timer.setStyle(Text::Bold);
    timer.setFont(playtime);
    timer.setPosition(800 / 2 - timer.getGlobalBounds().width / 2, 500);
    timer.setString("Playtime: " + to_string(seconds) + " seconds");

}

void Sudoku::getSudoku(int lvl) {

    switch (lvl) {
        case 0:
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    selectedMap[i][j] = map.easy1[i][j];
                }
            }
            break;
        case 1:
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    selectedMap[i][j] = map.medium1[i][j];
                }
            }
            break;
        case 2:
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    selectedMap[i][j] = map.hard1[i][j];
                }
            }
            break;
    }  
    cout << "Level: " << lvl + 1 << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << selectedMap[i][j] << " ";;
        }
        cout << endl;
    }
}

bool Sudoku::checkRow(int n) {
    for (int i = 0; i < 9; i++) {
        if (sudokuNums[i][selJ].getString() == to_string(n)) {
            return 0;
        }
    }
    return 1;
}

bool Sudoku::checkColumn(int n) {
    for (int i = 0; i < 9; i++) {
        if (sudokuNums[selI][i].getString() == to_string(n)) {
            return 0;
        }
    }
    return 1;
}

bool Sudoku::checkBox(int n) {
    bool success = false;
    if (selJ <= 2) {
        if (selI <= 2) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (sudokuNums[i][j].getString() == to_string(n))
                        return 0;
                }
            }
            return 1;
        }
        else if (selI <= 5 && selI >= 3) {
            for (int i = 3; i < 6; i++) {
                for (int j = 0; j < 3; j++) {
                    if (sudokuNums[i][j].getString() == to_string(n))
                        return 0;
                }
            }
            return 1;
        }
        else {
            for (int i = 6; i < 9; i++) {
                for (int j = 0; j < 3; j++) {
                    if (sudokuNums[i][j].getString() == to_string(n))
                        return 0;
                }
            }
            return 1;
        }
    }
    else if (selJ <= 5 && selJ >= 3) {
        if (selI <= 2) {
            for (int i = 0; i < 3; i++) {
                for (int j = 3; j < 6; j++) {
                    if (sudokuNums[i][j].getString() == to_string(n))
                        return 0;
                }
            }
            return 1;
        }
        else if (selI <= 5 && selI >= 3) {
            for (int i = 3; i < 6; i++) {
                for (int j = 3; j < 6; j++) {
                    if (sudokuNums[i][j].getString() == to_string(n))
                        return 0;
                }
            }
            return 1;
        }
        else {
            for (int i = 6; i < 9; i++) {
                for (int j = 3; j < 6; j++) {
                    if (sudokuNums[i][j].getString() == to_string(n))
                        return 0;
                }
            }
            return 1;
        }

    }
    else {
        if (selI <= 2) {
            for (int i = 0; i < 3; i++) {
                for (int j = 6; j < 9; j++) {
                    if (sudokuNums[i][j].getString() == to_string(n))
                        return 0;
                }
            }
            return 1;
        }
        else if (selI <= 5 && selI >= 3) {
            for (int i = 3; i < 6; i++) {
                for (int j = 6; j < 9; j++) {
                    if (sudokuNums[i][j].getString() == to_string(n))
                        return 0;
                }
            }
            return 1;
        }
        else {
            for (int i = 6; i < 9; i++) {
                for (int j = 6; j < 9; j++) {
                    if (sudokuNums[i][j].getString() == to_string(n))
                        return 0;
                }
            }
            return 1;
        }
    }

    return 0;
}