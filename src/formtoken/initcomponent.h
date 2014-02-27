/*
* Copyright (C) 2014 Olaf Radicke <briefkasten@olaf-radicke.de>
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

#ifndef FORMTOKEN_INITCOMPONENT_H
#define FORMTOKEN_INITCOMPONENT_H

#include <string>
#include <cxxtools/log.h>
#include <tnt/tntnet.h>
#include <RouteReverse/models/URLData.h>
#include <RouteReverse/manager/Manager.h>


namespace Tww {
namespace FormToken
{

    log_define("FormToken.initcomponent")

/**
 * This function prepare the component "FormToken". specifically the routing.
 * @arg app a reference of the application server.
 */
void initcomponent ( tnt::Tntnet &app ) {

    // controller rout for SessionForm token check.
    app.mapUrl( "^/(.*)", "formtoken_controller" );
    // controller rout for SessionForm token check.
    app.mapUrl( "^/FormToken/NoAvailabeToken$", "formtoken_no_availabe_token" );

    // error page
    app.mapUrl(
        "^/FormToken/NoAvailabeToken$",
        "formtoken_no_availabe_token"
    );

    RouteReverse::Manager::add(
        "formtoken_no_availabe_token",
        "core/basicprojectdata"
    );
}



} // END namespace RouteReverse
} // namespace Tww


#endif // CORE_INITCOMPONENT_H

