/*
 * utils.h -- misc utilities functions header
 *
 * Author: Andrea Burattin (http://www.delas.it)
 * Copyright (C) 2008  Andrea Burattin
 *
 * $Id$
 */

/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 *                   MA  02111-1307, USA.
 */

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

/**
 * This function trims leading and trailing spaces of a string
 *
 * @param str the string to be trimmed
 */
void trim(string& str);

/**
 * Converts a char to a hex string
 *
 * @param dec the char to be converted
 * @return the converted string
 */
string char2hex(char dec);

/**
 * This function encode a string as GET param
 *
 * @param decoded the string decoded
 * @return the encoded string
 */
string urlencode(const string &decoded);

#endif // UTILS_H
