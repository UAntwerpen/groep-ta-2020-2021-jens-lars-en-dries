#include "AbstractParser.h"
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include <sys/stat.h>
#include <assert.h>

bool FileExists(const string dirname) {
    struct stat st;
    return stat(dirname.c_str(), &st) == 0;
}

void AbstractParser::loadFile(string filename) {
    if(!(FileExists(filename))) __assert ("File to parse does not exist.", __FILE__, __LINE__);
    fDoc.LoadFile(filename.c_str());
    if(fDoc.Error()){
        // TODO: Better error descriptions.
        string error = string("There has been an error parsing file:" + filename);
        __assert(error.c_str(), __FILE__, __LINE__);
    }
    fRoot = fDoc.FirstChildElement();
}

TiXmlElement *AbstractParser::getRoot() {
    return fRoot;
}
