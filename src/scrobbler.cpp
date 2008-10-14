#include "scrobbler.h"

void scrobbler::setUsername(const string& username)
{
	m_username = username;
}


void scrobbler::setPassword(const string& password)
{
	m_password = MD5String(const_cast<char*>(password.c_str()));
}
