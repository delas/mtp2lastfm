#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <time.h>

using std::string;
using std::stringstream;
using std::vector;

/**
 * Function to explode a string
 *
 * @param sep   string separator
 * @param s     base string
 * @param ign   insert empty string
 * @param space insert trailing spaces in splitted string
 * @return all the separated string
 */
vector<string> explode(const string& sep, const string& s, bool ign=true, bool space=false);

/**
 * Removes all spaces from a string
 *
 * @param s the original string
 * @return the s string, without spaces
 */
string removeSpace(const string& s);

/**
 * Converts an integer to a string
 *
 * @param n the integer to be converted
 * @return the string with the n value
 */
string toString(int n);

/**
 * This function return the current Unix timestamp
 *
 * @return the number of seconds from the Unix-epoch
 */
int timestamp();

#endif // UTILS_H
