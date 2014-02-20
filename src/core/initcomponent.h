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

#ifndef CORE_INITCOMPONENT_H
#define CORE_INITCOMPONENT_H

#include <routereverse/model/URLData.h>
#include <routereverse/manager/Manager.h>

#include <string>
#include <cxxtools/log.h>
#include <tnt/tntnet.h>


namespace Tww {
namespace Core {

    log_define("Core.initcomponent")

/**
 * This function prepare the component "Core". specifically the routing.
 * @arg app a reference of the application server.
 */
void initcomponent ( tnt::Tntnet &app ) {
    RouteReverse::URLData urlData;

    // feed-icon.png

    RouteReverse::URLData urlData_1;
    urlData_1.componentName      = "resources";
    urlData_1.urlRegEx           = "^/core/resources/feed-icon.png$";
    urlData_1.componentPathInfo  = "core/resources/feed-icon.png";
    RouteReverse::Manager::addRoute( urlData_1, app );

    // basic_project_data

    RouteReverse::URLData urlData_2;
    urlData_2.componentName      = "core_basicprojectdata";
    urlData_2.urlRegEx             = "^/core/basicprojectdata$";
    urlData_2.reverseRoute       = "core/basicprojectdata";
    RouteReverse::Manager::addRoute( urlData_2, app );

    // ready get info...

    log_debug( RouteReverse::Manager::getAllReversesRoutes() );

}



} // END namespace Core
} // namespace Tww

#endif // CORE_INITCOMPONENT_H

