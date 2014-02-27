/*
* Copyright (C) 2013 Olaf Radicke <briefkasten@olaf-radicke.de>
*
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or later
* version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <formtoken/manager/Manager.h>

#include <tnt/component.h>
#include <tnt/httprequest.h>

#include <cxxtools/log.h>

#include <string>
#include <unistd.h>

namespace Tww {
namespace FormToken
{


log_define("FormToken.Manager")

// G --------------------------------------------------------------------------


std::string  Manager::getFormToken( tnt::HttpRequest& request )
{
    TNT_SESSION_SHARED_VAR( std::string, SESSIONFORM_AVAILABLE_TOKEN, () );
    std::ostringstream tokenStream;
    std::ostringstream inputTagStream;

    tokenStream << genRandomToken(16) << "-" << request.getSerial();
    inputTagStream << "<input \n"
        << "      type=\"hidden\" \n"
        << "      name=\"SESSIONFORM_TOKEN\" \n"
        << "      value=\""
        << tokenStream.str()
        << "\n \" >";

    SESSIONFORM_AVAILABLE_TOKEN = tokenStream.str();
    return inputTagStream.str();
}

std::string Manager::genRandomToken ( const int len) {
    std::string randomString = "";
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for ( int i = 0; i < len; ++i ) {
        int randNo = rand() % (sizeof(alphanum) - 1) ;
        randomString.push_back ( alphanum[randNo] );
    }
    log_debug( __FILE__ << __LINE__ << "randomString (Token): " << randomString );

    return randomString;
}


} // END namespace FormToken
} // end namespace Tww




