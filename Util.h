
#ifndef SERVERPROJ2_UTILS_H
#define SERVERPROJ2_UTILS_H

#include <fstream>
#include <string>
#include <vector>


class Util {


public:

    static const std::vector<std::string> explode(std::string &s, const char &c);

    static std::string readFile(std::string fileName);

    static void addToFile(std::string fileName, std::string dataToAppend);

    struct result {

        std::string shortestPath;

        int developedVertex;

        int weight;

    };

};

//global enum
enum Directions {

    NotSet = 0,
    Start = 1,
    Left = 2,
    Up = 3,
    Right = 4,
    Down = 5,


};


#endif //SERVERPROJ2_UTILS_H
