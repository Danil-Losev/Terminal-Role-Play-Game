
#include <iostream>
#include <string>

struct PROFILE_SETTINGS {
  int newGame;
  int countOfPoints;
  int countOfLevels;
  int curLevel;

  PROFILE_SETTINGS()
      : newGame(0), countOfPoints(0), countOfLevels(0), curLevel(0) {};
};

const int SET_COUNT = 4;

enum STATS {
  STRENGHT = 0,
  DEXTERITY,
  CONSTITUTION,
  INTELLIGENCE,
  WISDOM,
  CHARISMA,
  ARMORCLASS,
  HITPOINTS,
  MODIFICATORS,
  INITIATIVE,
  SAVINGTHROWS,
};

class PERSON {
private:
  std::string name;
  std::string personPath;
  int strength;
  int dexterity;
  int constitution;
  int intelligence;
  int wisdom;
  int charisma;
  int PERSON::*stats[11] = {
      &PERSON::strength,     &PERSON::dexterity,   &PERSON::constitution,
      &PERSON::intelligence, &PERSON::wisdom,      &PERSON::charisma,
      &PERSON::armorClass,   &PERSON::hitPoints,   &PERSON::modificators,
      &PERSON::initiative,   &PERSON::savingThrows};

  int armorClass;
  int hitPoints;
  int modificators;
  int initiative;
  int savingThrows;

public:
  PERSON()
      : strength(0), dexterity(0), constitution(0), intelligence(0), wisdom(0),
        charisma(0), armorClass(1), hitPoints(100), modificators(0),
        initiative(0), savingThrows(4) {};

  void setPersonPath(std::string personFilePath);
  std::string getPersonPath();
  void changeStat(std::string statistic, int value);
  int getStat(std::string statistic);
  int getStat(int index);
  std::string getName();
  void setPerson(int index);
  void printStat(PERSON person);
  void savePerson();
  void loadPerson();
};

const int PERSON_STAT_COUNT = 6;

extern PROFILE_SETTINGS settings;
extern PERSON person1, person2;

void mainMenu(int speed = 100);

void startGame();
void resetGame();
void gameSettings();
void exitGame();

void loadLevel(int curLevel, int countOfLevels);

void makePersons(int &gameStat);

int checkFiles(std::string *fileArray, int countOfFiles);

void printByChar(std::string text, int speed = 100);

void loadProfile(std::string profilePath, PROFILE_SETTINGS &profile);

void moveCursor(int row, int col);
void clearPartialArea(int startRow, int startCol, int height, int width);

void hideCursor();

void showCursor();
