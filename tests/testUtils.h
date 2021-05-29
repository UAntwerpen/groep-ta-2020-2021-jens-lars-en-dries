#ifndef TO_GROEP_TESTUTILS_H
#define TO_GROEP_TESTUTILS_H

#include <iostream>

/*
 * This function checks if a given directory exists. Source Prof. Demeyer and https://www.systutorials.com/how-to-test-a-file-or-directory-exists-in-c/
 * @ param dirname  The name of the directory you want to check exists
 * @ return Returns true if the directory exists, else returns false
 */
bool DirectoryExists(const std::string dirname);

/*
 * This function checks if the two files given are identical.
 * @ param leftFileName The name of the first file
 * @ param rightFileName The name of the second file
 * @ return Return true if the two files are identical, else returns false
 */
bool FileCompare(const std::string leftFileName, const std::string rightFileName);

#endif //TO_GROEP_TESTUTILS_H
