 #ifndef MAINMENU_H
 #define MAINMENU_H
 int launchCraft;
void initializeMainMenu(int argc, char** argv);
void renderMainMenu();
void processNormalKeys(unsigned char key, int x, int y);
void handleMouseClick(int button, int state,int x, int y);
void renderButtonBackground();
#endif 