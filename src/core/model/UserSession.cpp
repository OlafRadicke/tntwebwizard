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

#include <fstream>
#include <ostream>
#include <iostream>

namespace Tww {
namespace Core {

log_define("core.models.UserSession")

UserSession::UserSession ( cxxtools::atomic_t token ) {

    sessionToken = token;
}


UserSession::~UserSession ( ) {

    // clean up tmp dir with sessionToken;
}

std::string UserSession::getSesstonPath() {
    std::ostringstream tmpPath;

    tmpPath << "/tmp/";
    tmpPath << this->sessionToken;
    return tmpPath.str();
}




} // namespace Core
} // namespace Tww
