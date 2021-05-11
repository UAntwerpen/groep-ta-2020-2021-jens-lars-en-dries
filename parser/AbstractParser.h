#ifndef TO_GROEP_ABSTRACTPARSER_H
#define TO_GROEP_ABSTRACTPARSER_H

#include "tinyxml/tinyxml.h"
#include <string>

using std::string;

class AbstractParser {
public:
    /*
     * Default constructor
     */
    AbstractParser() = default;

    /*
     * Default destructor.
     */
    ~AbstractParser() = default;

    /*
     * Loads the given inputfile into the tinyxml parser.
     * @param filename The string containing the inputfile name/path(relative to wd).
     */
    void loadFile(string filename);

    /*
     * Simple getter for the xml root.
     * @return fRoot Pointer to the root element of the xml file.
     */
    TiXmlElement* getRoot();
private:
    TiXmlElement* fRoot = nullptr;
    TiXmlDocument fDoc;
};


#endif //TO_GROEP_ABSTRACTPARSER_H
