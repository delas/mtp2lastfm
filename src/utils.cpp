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


void trim(string& str)
{
	string::size_type pos = str.find_last_not_of(' ');
	if(pos != string::npos)
	{
		str.erase(pos + 1);
		pos = str.find_first_not_of(' ');
		if(pos != string::npos)
		{
			str.erase(0, pos);
		}
	}
	else
	{
		str.erase(str.begin(), str.end());
	}
}


string urlencode(const string &c)
{
	string escaped = "";
	int max = c.length();
	for(int i=0; i<max; i++)
	{
		if ((48 <= c[i] && c[i] <=  57) ||           // 0-9
			(65 <= c[i] && c[i] <=  90) ||           // abc...xyz
			(97 <= c[i] && c[i] <= 122) ||           // ABC...XYZ
			(c[i]=='~' || c[i]=='!' || c[i]=='*' ||
			 c[i]=='(' || c[i]==')' || c[i]=='\'' )  // ~!*()'
		)
		{
			escaped.append(&c[i], 1);
		}
		else
		{
			escaped.append("%");
			escaped.append(char2hex(c[i])); //converts char 255 to string "ff"
		}
	}
	return escaped;
}


string char2hex(char dec)
{
	char dig1 = (dec&0xF0)>>4;
	char dig2 = (dec&0x0F);
	if ( 0 <= dig1 && dig1 <=  9) dig1 += 48;    // 0,48inascii
	if (10 <= dig1 && dig1 <= 15) dig1 += 97-10; // a,97inascii
	if ( 0 <= dig2 && dig2 <=  9) dig2 += 48;
	if (10 <= dig2 && dig2 <= 15) dig2 += 97-10;

	string r;
	r.append(&dig1, 1);
	r.append(&dig2, 1);
	return r;
}
