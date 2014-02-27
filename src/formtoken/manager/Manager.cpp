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



#include <string>
#include <unistd.h>

#include <cxxtools/log.h>

#include <tnt/component.h>
#include <tnt/httprequest.h>

#include <SessionForm/manager/Manager.h>
#include <Core/models/OString.h>

namespace SessionForm
{


log_define("SessionForm.Manager")

// G --------------------------------------------------------------------------


std::string  Manager::getFormToken( tnt::HttpRequest& request )
{
    TNT_SESSION_SHARED_VAR( std::string, SESSIONFORM_AVAILABLE_TOKEN, () );
    std::string token = genRandomToken(16);
    token += ":" + OString::IntToStr( request.getSerial() );
    std::string formTokenInput = "<input \n\
            type=\"hidden\" \n\
            name=\"SESSIONFORM_TOKEN\" \n\
            value=\"";
    formTokenInput += token + "\" >";
    SESSIONFORM_AVAILABLE_TOKEN = token;
    return formTokenInput;
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


} // END namespace SessionForm




