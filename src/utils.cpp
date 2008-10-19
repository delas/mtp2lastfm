/*
 * utils.cpp -- misc utilitiesc functions
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

#include "utils.h"

vector<string> explode(const string& sep, const string& s, bool ign, bool space)
{
	std::vector<std::string> v;
	unsigned int pos1 = 0, pos2, dim = sep.size();
	std::string tmp;
	while (true)
	{
		pos2 = s.find(sep, pos1);
		if (pos2 == std::string::npos)
		{
			tmp = s.substr(pos1);
			if(space)
			{
				tmp = removeSpace(tmp);
			}
			if(ign)
			{
				if(s.substr(pos1) != "")
				{
					v.push_back(tmp);
				}
			}
			else
			{
				v.push_back(s.substr(pos1));
			}
			return v;
		}
		else
		{
			tmp = s.substr(pos1, pos2-pos1);
			if(space)
			{
				tmp = removeSpace(tmp);
			}
			if(ign)
			{
				if(pos1 != pos2)
				{
					v.push_back(tmp);
				}
			}
			else
			{
				v.push_back(tmp);
			}
			pos1 = pos2 + dim;
		}
	}
}


string removeSpace(const string& s)
{
	std::string tmp = "";
	for(unsigned int i = 0; i < s.size(); i++)
	{
		if(s[i] != ' ')
		{
			tmp += s[i];
		}
	}
	return tmp;
}


string toString(int n)
{
	char cifra;
	std::string ret;
	int val, i, j;
	if(n < 0)
	{
		return "-1";
	}
	if(n == 0)
	{
		ret = "0";
	}
	while(n != 0)
	{
		val = n % 10;
		switch(val)
		{
			case 0: cifra='0'; break;
			case 1: cifra='1'; break;
			case 2: cifra='2'; break;
			case 3: cifra='3'; break;
			case 4: cifra='4'; break;
			case 5: cifra='5'; break;
			case 6: cifra='6'; break;
			case 7: cifra='7'; break;
			case 8: cifra='8'; break;
			case 9: cifra='9'; break;
			default: cifra=' ';
		}
		ret += cifra;
		n = n / 10;
	}
	for(i = 0, j = ret.size()-1; i < j; i++, j--)
	{
		cifra = ret[i];
		ret[i] = ret[j];
		ret[j] = cifra;
	}
	return ret;
}


int timestamp()
{
	int timestamp;
	time_t seconds;
	seconds = time (NULL);
	stringstream ss;
	ss << seconds;
	ss >> timestamp;
	return timestamp;
}
