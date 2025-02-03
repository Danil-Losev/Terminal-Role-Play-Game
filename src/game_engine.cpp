#include "game_engine.hpp"
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <windows.h>
#include <wingdi.h>

extern const std::string PROJECT_PATH = "D:\\Code\\project\\";
extern const std::string PERSONS_PATH = PROJECT_PATH + "persons\\";
extern const std::string SETTINGS_PATH = PROJECT_PATH + "settings\\";

void printStat(PERSON person);
void savePerson();
void loadPerson();

void PERSON::changeStat(std::string statistic, int value) {
  if (statistic == "strength") {
    strength = value;
  } else if (statistic == "dexterity") {
    dexterity = value;
  } else if (statistic == "constitution") {
    constitution = value;
  } else if (statistic == "intelligence") {
    intelligence = value;
  } else if (statistic == "wisdom") {
    wisdom = value;
  } else if (statistic == "charisma") {
    charisma = value;
  }
}

int PERSON::getStat(std::string statistic) {
  if (statistic == "strength") {
    return strength;
  } else if (statistic == "dexterity") {
    return dexterity;
  } else if (statistic == "constitution") {
    return constitution;
  } else if (statistic == "intelligence") {
    return intelligence;
  } else if (statistic == "wisdom") {
    return wisdom;
  } else if (statistic == "charisma") {
    return charisma;
  } else if (statistic == "armorClass") {
    return armorClass;
  } else if (statistic == "hitPoints") {
    return hitPoints;
  } else if (statistic == "modificators") {
    return modificators;
  } else if (statistic == "initiative") {
    return initiative;
  } else if (statistic == "savingThrows") {
    return savingThrows;
  }
  return -1;
}

int PERSON::getStat(int index) {
  if (index >= 0 && index < 11) {
    return this->*stats[index]; // Используем указатель на член класса
  }
  return -1;
}

std::string PERSON::getName() { return name; }

void PERSON::setPerson(int index) {
  std::system("cls");
  printByChar("[ESC] Main menu", 10);
  moveCursor(5, 0);
  std::cout << "Player №" << index << '\n';
  printByChar("Enter your name: ");
  std::cin >> name;
  int avaiblePonts = settings.countOfPoints;
  printByChar("Welcome " + name + '\n' + "Chose your person statistic " + '\n' +
              "Total points: " + std::to_string(avaiblePonts) + '\n');

  std::string statName[PERSON_STAT_COUNT] = {
      "Strength: ",     "Dexterity: ", "Constitution: ",
      "Intelligence: ", "Wisdom: ",    "Charisma: "};

  for (int i = 0; i < PERSON_STAT_COUNT; i++) {
    this->*stats[i] = 0;
  }
  for (int i = 0; i < PERSON_STAT_COUNT; i++) {
    printByChar("  " + std::to_string(i + 1) + ')' + statName[i] +
                    std::to_string(this->*stats[i]) + '\n',
                40);
  }

  char getChar = '0';
  int curStat = 0; // Вынесли переменную за цикл
  while (getChar != '\r' && getChar != '\n') {
    clearPartialArea(9, 0, 9, 30);
    moveCursor(9, 0);
    std::cout << "Total points: " << avaiblePonts << '\n';
    for (int i = 0; i < PERSON_STAT_COUNT; i++) {
      if (i == curStat) {
        std::cout << "  " << i + 1 << ')' << statName[i] << "⯇ "
                  << this->*stats[i] << " ⯈" << "    ⯅ ⯆" << '\n';
      } else {
        std::cout << "  " << i + 1 << ')' << statName[i] << this->*stats[i]
                  << '\n';
      }
    }
    getChar = getch();

    if ((getChar == 'w' || getChar == 72) && curStat > 0) {
      curStat--;
    } else if ((getChar == 's' || getChar == 80) &&
               curStat < PERSON_STAT_COUNT - 1) { // Исправили условие
      curStat++;
    } else if ((getChar == 'd' || getChar == 77) && avaiblePonts > 0) {
      (this->*stats[curStat])++;
      avaiblePonts--;
    } else if ((getChar == 'a' || getChar == 75) && this->*stats[curStat] > 0) {
      (this->*stats[curStat])--;
      avaiblePonts++;
    } else if (getChar == 27) {
      mainMenu(0);
    }
  }
}

void PERSON::setPersonPath(std::string personFilePath) {
  personPath = personFilePath;
}

std::string PERSON::getPersonPath() { return personPath; }

void PERSON::loadPerson() { std::cout << "load"; }

void PERSON::savePerson() { std::cout << "save"; }

void mainMenu(int speed) {
  std::system("cls");
  std::string menu[4] = {"Start or continue game ", "Reset game ", "Settings ",
                         "Exit "};
  moveCursor(10, 50);
  printByChar("       My game", speed);
  for (int i = 0; i < 4; i++) {
    moveCursor(11 + i, 50);
    printByChar(menu[i], speed);
  }
  char getChar = '0';
  int chose = 0;
  while (getChar != '\r' && getChar != '\n') {
    clearPartialArea(11, 50, 6, 30);
    for (int i = 0; i < 4; i++) {
      if (i == chose) {
        moveCursor(11 + i, 50);
        std::cout << " -> " << menu[i];
      } else {
        moveCursor(11 + i, 50);
        std::cout << menu[i];
      }
    }
    getChar = getch();
    if ((getChar == 'w' || getChar == 72) && chose > 0) {
      chose--;
    } else if ((getChar == 's' || getChar == 80) && chose < 3) {
      chose++;
    }
  }
  switch (chose) {
  case 0:
    startGame();
    break;
  case 1:
    resetGame();
    break;
  case 2:
    gameSettings();
    break;
  case 3:
    exitGame();
    break;
  default:
    std::cerr << "ERROR: out of range";
    break;
  }
}

void startGame() {
  makePersons(settings.newGame);
  loadLevel(settings.curLevel, settings.countOfLevels);
}
void resetGame() {
  std::system("cls");
  moveCursor(10, 50);
  printByChar("Do you want to reset game?", 50);

  int chose = 0;
  char getChar = '0';
  while (getChar != '\r' && getChar != '\n') {
    clearPartialArea(11, 50, 1, 30);
    moveCursor(11, 50);
    if (chose == 0) {
      std::cout << "    [YES]    No";
    }
    if (chose == 1) {
      std::cout << "    Yes    [NO]";
    }
    getChar = getch();
    if ((getChar == 'd' || getChar == 77)) {
      chose = 1;
    } else if ((getChar == 'a' || getChar == 75)) {
      chose = 0;
    }
  }
  switch (chose) {
  case 0:
    moveCursor(13, 50);
    printByChar("Resetting the game...", 100);
    //
    moveCursor(15, 50);
    printByChar("Game reseted", 50);
    Sleep(500);
    mainMenu(0);
    break;
  case 1:
    mainMenu(0);
    break;
  default:
    std::cerr << "ERROR: out of range";
    break;
  }
}

void gameSettings() {
  std::system("cls");
  moveCursor(10, 50);
  printByChar("   Game Settings", 50);
  PROFILE_SETTINGS tempSettings{settings};
  int *tempSetArray[SET_COUNT] = {
      &tempSettings.newGame, &tempSettings.countOfPoints,
      &tempSettings.countOfLevels, &tempSettings.curLevel};
  std::string setNames[SET_COUNT] = {
      "New game ( 1 = yes, 0 = no): ", "Count of points: ", "Count of levels: ",
      "Current level: "};
  char getChar = '0';
  int chose = 0;
  while (getChar != '\r' && getChar != '\n') {
    clearPartialArea(11, 50, 5, 50);
    moveCursor(11, 50);
    for (int i = 0; i < SET_COUNT; i++) {
      if (i == chose) {
        moveCursor(11 + i, 50);
        std::cout << "> " << setNames[i] << "⯇ " << *tempSetArray[i] << " ⯈"
                  << "    ⯅ ⯆";
      } else {
        moveCursor(11 + i, 50);
        std::cout << setNames[i] << *tempSetArray[i];
      }
    }
    getChar = getch();

    if ((getChar == 'w' || getChar == 72) && chose > 0) {
      chose--;
    } else if ((getChar == 's' || getChar == 80) && chose < SET_COUNT - 1) {
      chose++;
    } else if ((getChar == 'd' || getChar == 77) &&
               *tempSetArray[chose] < 100) {
      (*tempSetArray[chose])++;
    } else if ((getChar == 'a' || getChar == 75) && *tempSetArray[chose] > 0) {
      (*tempSetArray[chose])--;
    }
  }
  moveCursor(16, 50);
  printByChar("Do you want to save changes?", 50);
  chose = 0;
  getChar = '0';
  while (getChar != '\r' && getChar != '\n') {
    clearPartialArea(17, 50, 1, 30);
    moveCursor(17, 50);
    if (chose == 0) {
      std::cout << "    [YES]    No";
    }
    if (chose == 1) {
      std::cout << "    Yes    [NO]";
    }
    getChar = getch();
    if ((getChar == 'd' || getChar == 77)) {
      chose = 1;
    } else if ((getChar == 'a' || getChar == 75)) {
      chose = 0;
    }
  }
  switch (chose) {
  case 0:
    moveCursor(19, 50);
    printByChar("Saving changes...", 100);
    settings = tempSettings;
    moveCursor(20, 50);
    printByChar("Changes saved", 50);
    Sleep(500);
    mainMenu(0);
    break;
  case 1:
    mainMenu(0);
    break;
  default:
    std::cerr << "ERROR: out of range";
    break;
  }
}
void exitGame() {
  std::system("cls");
  moveCursor(10, 50);
  printByChar("Do you want to exit game?", 50);

  int chose = 0;
  char getChar = '0';
  while (getChar != '\r' && getChar != '\n') {
    clearPartialArea(11, 50, 1, 30);
    moveCursor(11, 50);
    if (chose == 0) {
      std::cout << "    [YES]    No";
    }
    if (chose == 1) {
      std::cout << "    Yes    [NO]";
    }
    getChar = getch();
    if ((getChar == 'd' || getChar == 77)) {
      chose = 1;
    } else if ((getChar == 'a' || getChar == 75)) {
      chose = 0;
    }
  }
  switch (chose) {
  case 0:
    moveCursor(13, 50);
    printByChar("Saving all files...", 100);
    //
    moveCursor(15, 50);
    printByChar("Exit from game", 50);
    Sleep(500);
    exit(0);
    break;
  case 1:
    mainMenu(0);
    break;
  default:
    std::cerr << "ERROR: out of range";
    break;
  }
}

int checkFiles(std::string *fileArray, int countOfFiles) {
  std::system("cls");
  int error = 0;
  for (int i = 0; i < countOfFiles; i++) {
    if (std::filesystem::exists(fileArray[i])) {
      error += 0;
    } else {
      std::cout << "FILE: " << fileArray[i] << " doesn`t exists \n";
      error++;
    }
  }

  return error;
}

void printByChar(std::string text, int speed) {
  for (int i = 0; i < text.length(); i++) {
    std::cout << text[i];
    Sleep(speed);
  }
};

void makePersons(int &gameStat) {
  if (gameStat == 1) {
    person1.setPerson(1);
    person2.setPerson(2);
    person1.savePerson();
    person2.savePerson();
    gameStat = 0;
  } else if (gameStat == 0) {
    person1.loadPerson();
    person2.loadPerson();
  }
}

void loadLevel(int curLevel, int countOfLevels) {}

void loadProfile(std::string profilePath, PROFILE_SETTINGS &profile) {
  profile.countOfPoints = 20;
  profile.newGame = 1;
}

void moveCursor(int row, int col) {
  // Перемещает курсор в
  // указанную позицию
  std::cout << "\033[" << row << ";" << col << "H";
}

void clearPartialArea(int startRow, int startCol, int height, int width) {
  for (int i = 0; i < height; ++i) {
    moveCursor(startRow + i,
               startCol); // Переход к началу
                          // строки в области
    for (int j = 0; j < width; ++j) {
      std::cout << " "; // Замена области
                        // пробелами
    }
  }
  std::cout.flush(); // Обновление
                     // экрана
}

void hideCursor() {
  HANDLE consoleHandle =
      GetStdHandle(STD_OUTPUT_HANDLE); // Получить дескриптор консоли
  CONSOLE_CURSOR_INFO cursorInfo;

  // Получаем текущие параметры курсора
  GetConsoleCursorInfo(consoleHandle, &cursorInfo);

  cursorInfo.bVisible = FALSE; // Убираем видимость
  SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Применяем изменения
}

void showCursor() {
  HANDLE consoleHandle =
      GetStdHandle(STD_OUTPUT_HANDLE); // Получить дескриптор консоли
  CONSOLE_CURSOR_INFO cursorInfo;

  // Получаем текущие параметры курсора
  GetConsoleCursorInfo(consoleHandle, &cursorInfo);

  cursorInfo.bVisible = TRUE; // Делаем курсор видимым
  SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Применяем изменения
}
