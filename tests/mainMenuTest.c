#include "../src/mainMenu.h"
#include "../src/loadSaveMenu.h"
#include <stdbool.h>

int main (int argc, char **argv){
initializeMainMenu(argc, argv);
handleMouseClick(0,0,3000,950);
renderButtonBackground();
renderMainMenu();
processNormalKeys(27, 0 ,0);
renderLoadButtonBackground();
renderLoadSaveMenu();
}