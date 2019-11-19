#ifndef SERVERPROJ2_FILECACHEMANAGER_H
#define SERVERPROJ2_FILECACHEMANAGER_H


#include <map>
#include "CacheManager.h"
#include "Util.h"
#include <fstream>
#include <mutex>

#define CACHEFILE "cache.txt"
#define SPLIT_CHAR '$'

    class FileCacheManager : public CacheManager {

    private:
        std::mutex mute1;

    public:

        bool doesExist(std::string key) override {

            try {
                load(key);
                return true;
            } catch (...) { // no file exist or key doesnt exists in cache
                return false;
            }
        }

        std::string load(std::string key) override{

            mute1.lock();

            std::string fileContent = Util::readFile(CACHEFILE);

            std::vector<std::string> afterSplit = Util::explode(fileContent, SPLIT_CHAR);

            std::map<std::string, std::string> cacheMap;

            auto it = afterSplit.begin();

            for (; it != afterSplit.end(); it += 2) {
                std::string currKey = *it;
                std::string currValue = *(it + 1);
                cacheMap.insert(std::pair<std::string, std::string>(currKey, currValue));

            }

            auto valueIterator = cacheMap.find(key);

            mute1.unlock();

            //iterator will be the end if key doesnt exists
            if (valueIterator != cacheMap.end()) {
                return valueIterator->second;
            } else {
                throw "key does not exist";
            }

        }


        void save(std::string key, std::string solution) override {

            mute1.lock();

            std::string dataToSave = key + SPLIT_CHAR + solution + SPLIT_CHAR;

            Util::addToFile(CACHEFILE, dataToSave);

            mute1.unlock();

        }

    };


// TODO: add mutex

#endif //SERVERPROJ2FILECACHEMANAGER_H


/*
 *     // handle cache in files
    class FileCacheManager : public CacheManager {

    private:
        std::map<std::string, std::string> problemToSolution;

    public:

        //load from cache file to map
        FileCacheManager() {
            std::string line;

            std::vector<std::string> probAndSol;

            std::ifstream cacheReader(CACHEFILE);
            if (cacheReader.is_open()) {
                while (cacheReader.good()) {
                    getline(cacheReader, line);
                    probAndSol = Util::explode(line, SPLIT_CHAR);
                    problemToSolution[probAndSol[0]] = probAndSol[1];
                }
            }
        }

        //return at key
        bool doesExist(std::string key) override {
            return problemToSolution.count(key) >= 1;
        }

        //look in map
        std::string load(std::string key) override {
            return problemToSolution.at(key);
        }

        //update map and file
        void save(std::string key, std::string solution) override {
            std::ofstream cacheWriter(CACHEFILE, std::ios::out | std::ios::app | std::ios::ate);
            if (cacheWriter.is_open()) {
                cacheWriter << key << '$' << solution << std::endl;
            }
            cacheWriter.close();
        }

    };
 */