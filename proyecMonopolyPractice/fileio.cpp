#include "fileio.h"

std::istream& operator>>(std::istream &str, Vtk &data) {

    std::string line;
    Vtk tmp;
    if (std::getline(str, line)) {
        std::stringstream iss(line);
        if (std::getline(iss, tmp.s, '\n')) swap(data.s, tmp.s);
        else str.setstate(std::ios::failbit);
    } // if

    return str;
} // operator >>

void readData(std::vector<points> &p, std::vector<cells> &c, std::string fileName) {

    Vtk data;

    std::ifstream readFile(fileName, std::ifstream::in);

    std::string line_avoid;
    for (int i = 0; i < 6; i++) std::getline(readFile, line_avoid);

    while (readFile >> data) {
        std::stringstream ss(data.s);
        ss >> data.x[0] >> data.x[1] >> data.x[2];
        p.push_back({data.x[0], data.x[1], data.x[2]});
    } // while

    readFile.clear(); // readFile.setstate(std::ios::clear);
    std::getline(readFile, line_avoid);

    while (readFile >> data) {
        std::stringstream ss(data.s);
        int dummy;
//        ss >> dummy >> data.c[0] >> data.c[1] >> data.c[2] >> data.c[3];

        ss >> dummy >> data.c[0] >> data.c[1] >> data.c[2];
        if (dummy == 4) ss >> data.c[3];
        else if (dummy == 3) data.c[3] = -1;
        else {}

        c.push_back({data.c[0], data.c[1], data.c[2], data.c[3]});
    } // while

    readFile.close();
    data.~Vtk();

    return;
} // readData
