#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "glut.h"


class point {
public:
    int x = 0;
    int y = 0;
    int z = 0;

};
class pointn {
public:
    int xm = 0;
    int ym = 0;
    int zm = 0;
    int xp = 0;
    int yp = 0;
    int zp = 0;

};


class Functions {
public:
    using vector3d = std::vector<std::vector<std::vector<int>>>;
    float zoom = -5;
    float anglex = 0;
    float angley = 0, anglez = 0;
    
    
   
    // Передача по ссылке копирования не вызывает
    void out(const vector3d& v);
    vector3d start();
    void draw(const vector3d& mat, bool flagdraw);
    void read_kb(unsigned char key);
    void read_speckb(int k);
    void Axis();
    vector3d wave(const vector3d& mat);
    int mintrail(const vector3d& trail);
    void reversetrail(const vector3d& trail, int min);
    void back_step(const vector3d& trail, int x, int y, int z, int stage);
    void reversetrail1(const vector3d& trail);
    pointn negtbors(const vector3d& mat, int x, int y, int z);

};