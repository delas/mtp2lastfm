#
# configure.am
#
# Author: Andrea Burattin (http://www.delas.it)
# Copyright (C) 2008  Andrea Burattin
#
# $Id$

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston,
#                   MA  02111-1307, USA.
#

PACKAGE = mtp2lastfm
VERSION = 0.1
MAIL = andrea@REMOVESPAMdelas.it

AC_INIT([mtp2lastfm], [0.1], [andrea@REMOVESPAMdelas.it])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CXX
AC_PREFIX_DEFAULT([/usr])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
   Makefile
   src/Makefile
])

AC_CHECK_LIB(mtp, [LIBMTP_Get_Tracklisting_With_Callback])
LDFLAGS="$LDFLAGS -lmtp"

AC_CHECK_LIB(curl, [curl_easy_perform])
LDFLAGS="$LDFLAGS -lcurl"

AC_CHECK_LIB(xerces-c, [toupper])
LDFLAGS="$LDFLAGS -lxerces-c"

AC_OUTPUT
