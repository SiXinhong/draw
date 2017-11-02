#ifndef COLORM_H
#define COLORM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include<QString>
#include"window/spotColorAll.h"
#include<QColor>
#include"window/spotColorAll.h"
#include<string>
#include <stdlib.h>
#include<QDebug>
using namespace std;

using std::ofstream;

class colorM
{
public:
    colorM();
    void saveColorInfo(spotColorAll,int ,QColor*);
    void getColorInfo(int&,QColor*,spotColorAll&);
};

#endif // COLORM_H
