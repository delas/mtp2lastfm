#
# configure.ac
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

AC_INIT([mtp2lastfm], [0.1.1], [andrea@REMOVESPAMdelas.it])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CXX
AC_PREFIX_DEFAULT([/usr])
AC_CONFIG_HEADERS([src/autoconfig.h])
AC_CONFIG_FILES([
	Makefile
	src/Makefile
])

#
# Checking required XSD binder
#
AC_CHECK_PROG(HAVE_XSD, xsd, true, false)
if test $HAVE_XSD; then
	echo "Generating XML binder..."
	xsd cxx-tree --generate-serialization --root-element mtp2lastfm \
		--output-dir src/xsd --namespace-map =xml \
		--hxx-suffix .h --cxx-suffix .cpp \
		src/xsd/mtp2lastfm.xsd
else
	echo "Error! You need to install CodeSynthesis binder!"
	echo "Check http://www.codesynthesis.com/products/xsd/download.xhtml"
	exit -1
fi


#
# Checking header files
#
AC_CHECK_HEADER(xsd/cxx/version.hxx, [], [
	echo "Error! You need to install CodeSynthesis dev files!"
	echo "Check http://www.codesynthesis.com/products/xsd/download.xhtml"
	exit -1
	])

AC_CHECK_HEADER(libmtp.h, [], [
	echo "Error! You need to install libmtp dev files!"
	exit -1
	])


#
# Checking libs...
#
AC_CHECK_LIB(mtp, [LIBMTP_Get_Tracklisting_With_Callback], [], [
	echo "Error! You need to have libmtp installed."
	exit -1
	])

AC_CHECK_LIB(curl, [curl_easy_perform], [], [
	echo "Error! You need to have libcurl installed."
	exit -1
	])

AC_CHECK_LIB(xerces-c, [toupper], [], [
	echo "Error! You need to have xerces-c installed."
	exit -1
	])

AC_OUTPUT
