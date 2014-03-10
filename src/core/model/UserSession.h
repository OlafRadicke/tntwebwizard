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

#ifndef CORE_USERSESSION_H
#define CORE_USERSESSION_H

#include <tnt/httprequest.h>

#include <string>

namespace Tww {
namespace Core {


/**
* This class represent a data set of a session.
**/
class UserSession {

public:

    UserSession ( std::string token );

    ~UserSession ( );

    /**
     * Get back the path to a tmp directory.
     **/
    std::string getSessionPath();



private:

    /**
     * Session token
     **/
    std::string  sessionToken;

};


} // namespace Core
} // namespace Tww

#endif
