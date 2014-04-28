/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013-2014
* @copyright
* Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>
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

#include <core/model/UserSession.h>

#include <cxxtools/log.h>
#include <cxxtools/directory.h>

#include <fstream>
#include <ostream>
#include <iostream>

namespace Tww {
namespace Core {

log_define("core.models.UserSession")

UserSession::UserSession ( std::string token ) {
    this->sessionToken = token;
    if ( !cxxtools::Directory::exists( "/tmp/tntwebwizard/" ) ) {
        cxxtools::Directory::create( "/tmp/tntwebwizard/" );
    }
    if ( !cxxtools::Directory::exists( this->getSessionPath() ) ) {
        cxxtools::Directory::create( this->getSessionPath() );
    }
}


UserSession::~UserSession ( ) {
    if ( cxxtools::Directory::exists( this->getSessionPath() ) ) {
        std::ostringstream syscommand;
        syscommand << "rm -Rf " << this->getSessionPath();
        system( syscommand.str().c_str() );
    }
}

std::string UserSession::getSessionPath() {
    std::ostringstream tmpPath;

    tmpPath << "/tmp/tntwebwizard/";
    tmpPath << this->sessionToken;
    return tmpPath.str();
}




} // namespace Core
} // namespace Tww
