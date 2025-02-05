#include "game_engine.hpp"
#include <iostream>
#include <string>

const std::string PROJECT_PATH = "D:\\Code\\project\\";
const std::string PERSONS_PATH = PROJECT_PATH + "persons\\";
const std::string SETTINGS_PATH = PROJECT_PATH + "settings\\";

PROFILE_SETTINGS settings;
PERSON person1, person2;
const int mainFilesCount = 3;

int main(int argc, char *argv[]) {
  hideCursor();
  person1.setPersonPath(PERSONS_PATH + "person1.txt");
  person2.setPersonPath(PERSONS_PATH + "person2.txt");

  std::string fileArray[mainFilesCount] = {person1.getPersonPath(),
                                           person2.getPersonPath(),
                                           SETTINGS_PATH + "settings.txt"};

  int error = 0;
  error = checkFiles(fileArray, mainFilesCount);
  if (error == 0) {
    loadProfile(SETTINGS_PATH + "settings.txt", settings);
    mainMenu();
  } else {
    std::cerr << "ERROR: Files not found" << '\n';
  }
  showCursor();
  return 0;
}
