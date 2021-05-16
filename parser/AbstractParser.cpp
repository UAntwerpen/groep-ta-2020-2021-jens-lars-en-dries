#include "AbstractParser.h"
#include "tinyxml/tinyxml.h"
#include <sys/stat.h>
#include <iostream>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

/*
 * Simple helper function that checks whether the given directory or file exists.
 * @param dirname String containing the name of the file or the path(relative to wd) to check existence of.
 * @return bool True if the file/path exists.
 */
bool FileExists(const string dirname) {
    struct stat st;
    return stat(dirname.c_str(), &st) == 0;
}

void AbstractParser::loadFile(string filename) {
    if(!(FileExists(filename))) {
        std::cerr << "File to parse does not exist." << std::endl;
        char buff[FILENAME_MAX]; //create string buffer to hold path
        GetCurrentDir( buff, FILENAME_MAX );
        string current_working_dir(buff);
        std::cerr << current_working_dir << std::endl;
    }
    fDoc.LoadFile(filename.c_str());
    if(fDoc.Error()){
        std::string compareStr = std::string(fDoc.ErrorDesc());
        if("Failed to open file" == compareStr){
            string error = string("Failed to open file:" + filename);
            std::cerr << error << std::endl;
            assert(error.c_str());
        }
        else if("Error parsing Element." == compareStr){
            string error = string("Error parsing Element.");
            std::cerr << error << std::endl;
        }
        else if("Failed to read Element name" == compareStr){
            string error = string("Failed to read Element name");
            std::cerr << error << std::endl;        }
        else if("Error reading Element value." == compareStr){
            string error = string("Error reading Element value.");
            std::cerr << error << std::endl;        }
        else if("Error reading Attributes." == compareStr){
            string error = string("Error reading Attributes.");
            std::cerr << error << std::endl;        }
        else if("Error: empty tag." == compareStr){
            string error = string("Error: empty tag.");
            std::cerr << error << std::endl;        }
        else if("Error reading end tag." == compareStr){
            string error = string("Error reading end tag.");
            std::cerr << error << std::endl;        }
        else if("Error parsing Comment." == compareStr){
            string error = string("Error parsing Comment.");
            std::cerr << error << std::endl;        }
        else if("Error document empty." == compareStr){
            string error = string("Error document empty.");
            std::cerr << error << std::endl;
        }
        else{
            string error = string("Generic error occurred while loading file.");
            std::cerr << error << std::endl;
        }
    }
    fRoot = fDoc.FirstChildElement();
}

TiXmlElement *AbstractParser::getRoot() {
    return fRoot;
}
