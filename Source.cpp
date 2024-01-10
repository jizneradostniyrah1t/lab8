#include <fstream>
#include <clocale>
#include <iostream>
#include <vector>
#include "Functions.h"
#include "glut.h"
const int size = 29;
using vector3d = std::vector<std::vector<std::vector<int>>>;
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
Functions functions;
int flag;
int flagwave = 0;
int min = 0;
bool flagdraw;
vector3d mat(size, std::vector<std::vector<int>>(size, std::vector<int>(size, 0)));

void readspecKB(int k, int, int) {
    functions.read_speckb(k);
    glutPostRedisplay();
}
void readKB(unsigned char k, int, int) {
    functions.read_kb(k);
    glutPostRedisplay();
}



void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Начало нашего кода
    if (flag == 0) {
        mat = functions.start();
        flag = 1;
    }



    functions.Axis();
    functions.draw(mat, flagdraw);
    if (flagwave == 0) {
    mat = functions.wave(mat);
    flagwave = 1;
    functions.out(mat);
    min =  functions.mintrail(mat);

    std::cout << std::endl << min; 
    } 
    functions.reversetrail(mat, min);
    // Конец нашего кода
    glutSwapBuffers();
}

void ReshapeWindow(GLsizei width, GLsizei height) {
    if (height == 0)
        height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 1000.0f);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL,"rus");
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Пример вывода 3D графики");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearColor(0, 0, 0, 1);
    glutKeyboardFunc(readKB);
    glutSpecialFunc(readspecKB);
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ReshapeWindow);

    glutMainLoop();

    return 0;
}