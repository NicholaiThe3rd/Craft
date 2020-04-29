#include "mainMenu.h"
#include <stdbool.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

int launchCraft;
//used as an additional check for the load save menu so it will
//fire the correct events on click and not the ones for main menu
static int loadSaveMenuLaunched;
static int disableMainMenuClicks;

void initializeMainMenu(int argc, char** argv){
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
glutInitWindowPosition (0, 0);
glutCreateWindow ("Craft menu");
//ensures we just exit the glut loop not close the program so we can still launch craft
glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
glutDisplayFunc(renderMainMenu);
glutKeyboardFunc(processNormalKeys);
glutMouseFunc(handleMouseClick);
glutMainLoop();
}

void renderMainMenu(void){
     //initializes the matrix and ortho so we can draw
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

//creates the title
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(0.46, 0.90);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "CRAFT");
    glPopMatrix();

//first button
    glPushMatrix();
    glTranslatef(0.0, 0.1, 0.0);
    renderButtonBackground();
    glPopMatrix();

//first button text
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(0.45, 0.76);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Play Game");
    glPopMatrix();

//second button
    glPushMatrix();
    glTranslatef(0.0, -0.2, 0.0);
    renderButtonBackground();
    glPopMatrix();

//second button text
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(0.45, 0.46);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Load Save");
    glPopMatrix();

//third button
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    renderButtonBackground();
    glPopMatrix();

//third buton text
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2f(0.45, 0.16);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Exit Game");
    glPopMatrix();

    glutSwapBuffers();
}

void renderButtonBackground(void)
{
glColor3f (0.5, 0.5, 0.5);
glBegin(GL_POLYGON);
glVertex3f (0.30, 0.60, 0.0);
glVertex3f (0.65, 0.60, 0.0);
glVertex3f (0.65, 0.75, 0.0);
glVertex3f (0.30, 0.75, 0.0);
glEnd();
}

//determines the keys a user presses and does certain actaions based on them
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

/** handles a users mouse click by getting the position of their click then executing an appropriate response
*/
void handleMouseClick(int button, int state,int x, int y){
    //we float the values by screen height and width so we can fit them within our
    //ortho matrix
    float x1=x/(float)glutGet(GLUT_SCREEN_WIDTH);
    float y1=y/(float)glutGet(GLUT_SCREEN_HEIGHT);
    printf("x: %f \n",x1);
     printf("y: %f \n",y1);
    if(!loadSaveMenuLaunched){
    if(((x1>=0.3 && x1<=0.65)&&(y1>=0.15 && y1<=0.3))){
        launchCraft=1;
        printf("Launch Craft Called \n");
        glutLeaveMainLoop();
    }
    if(((x1>=0.3 && x1<=0.65)&&(y1>=0.45 && y1<=0.6))){
        //TODO: clear the glut window and render a new screen that will allow the user to choose a saved world or start a new one
        printf("Load Save Called \n");
        x1=0;
        y1=0;
        renderLoadSaveMenu();
        loadSaveMenuLaunched=1;
    }
    if(((x1>=0.3 && x1<=0.65)&&(y1>=0.75 && y1<=0.9))){
         printf("Exit Called \n");
        exit(0);
    }
    //loadSaveMenuLaunched ensures we won't call any main menu clicks while on load save
    }else if(loadSaveMenuLaunched){
        //we need this boolean as clicking in GLUT happens in two parts onclick and on release
        //becasue of this this method gets called twice on the menu and this boolean ensures we aren't immediately
        //loading a world when clicking load save
        if(disableMainMenuClicks){
        if(((x1>=0.05 && x1<=0.15)&&(y1>=0.01 && y1<=0.4))){
            //back
            printf("back called \n");
            renderMainMenu();
            loadSaveMenuLaunched=0;
            disableMainMenuClicks=0;
        }
        if(((x1>=0.3 && x1<=0.65)&&(y1>=0.15 && y1<=0.3))){
            //World1
             launchCraft=1;
             printf("Load World 1 \n");
             glutLeaveMainLoop();
            
        }
        if(((x1>=0.3 && x1<=0.65)&&(y1>=0.45 && y1<=0.6))){
            //world2
            printf("Load World 2 \n");
        }
        if(((x1>=0.3 && x1<=0.65)&&(y1>=0.75 && y1<=0.9))){
            //world3
            printf("Load World 3 \n");
        }
        }else{
            disableMainMenuClicks=1;
        }
    }
}

