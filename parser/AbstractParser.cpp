#include "AbstractParser.h"
#include "tinyxml/tinyxml.h"
#include <sys/stat.h>
#include <assert.h>

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
//    if(!(FileExists(filename))) _assert ("File to parse does not exist.", __FILE__, __LINE__);
    fDoc.LoadFile(filename.c_str());
    if(fDoc.Error()){
        std::string compareStr = std::string(fDoc.ErrorDesc());
        if("Failed to open file" == compareStr){
            string error = string("Failed to open file:" + filename);
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
        else if("Error parsing Element." == compareStr){
            string error = string("Error parsing Element.");
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
        else if("Failed to read Element name" == compareStr){
            string error = string("Failed to read Element name");
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
        else if("Error reading Element value." == compareStr){
            string error = string("Error reading Element value.");
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
        else if("Error reading Attributes." == compareStr){
            string error = string("Error reading Attributes.");
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
        else if("Error: empty tag." == compareStr){
            string error = string("Error: empty tag.");
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
        else if("Error reading end tag." == compareStr){
            string error = string("Error reading end tag.");
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
        else if("Error parsing Comment." == compareStr){
            string error = string("Error parsing Comment.");
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
        else if("Error document empty." == compareStr){
            string error = string("Error document empty.");
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
        else{
            string error = string("Generic error occurred while loading file.");
//            _assert(error.c_str(), __FILE__, __LINE__);
        }
    }
    fRoot = fDoc.FirstChildElement();
}

TiXmlElement *AbstractParser::getRoot() {
    return fRoot;
}
