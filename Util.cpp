#include "Util.h"


const std::vector<std::string> Util::explode(std::string &s, const char &c){

    std::string buff{""};
    std::vector<std::string> v;
    //remove EOL
    //s = s.substr(0,s.length()-2);

    for (auto n : s)
    {
        if (n != c)
            buff += n;
        else if (n == c && buff != "")
        {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(buff);

    return v;
}


std::string Util::readFile(std::string fileName) {

    std::ifstream t(fileName);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());

    return str;

}


void Util::addToFile(std::string fileName, std::string dataToAppend) {

    std::fstream stream;
    stream.open(fileName, std::ios::out| std::ios::app | std::ios::ate);

    stream << dataToAppend;

    stream.flush();
    stream.close();

}