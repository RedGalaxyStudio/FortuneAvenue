#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>

typedef struct _points {

    float x, y, z;

} points;

typedef struct _cells {

    int n[4] = {-1, -1, -1, -1};

} cells;

// https://codereview.stackexchange.com/questions/38879/parsing-text-file-in-c
class Vtk {

public:
    std::string s;
    float x[3];
    int c[4];

    Vtk() {}
    ~Vtk() {}
    friend std::istream& operator>>(std::istream &, Vtk &);

};

void readData(std::vector<points> &p, std::vector<cells> &c, std::string fileName);

#endif // FILEIO_H
