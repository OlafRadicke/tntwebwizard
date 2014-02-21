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

    // ######################## RESOURCES ############################

    // /core/resources/tntnet.png

    app.mapUrl("^/core/tntnet.png$", "resources")
        .setPathInfo("./src/core/resources/tntnet.png");

    RouteReverse::Manager::add(
        std::string("core_tntnet_png"),
        std::string("core/tntnet.png") );

    // /core/resources/normalize.css

    app.mapUrl("^/core/normalize.css$", "resources")
        .setPathInfo("./src/core/resource/normalize.css");

    RouteReverse::Manager::add( "core_normalize_css", "core/normalize.css" );

//     RouteReverse::URLData urlData_1_2;
//     urlData_1_2.componentName      = "resources";
//     urlData_1_2.urlRegEx           = "^/core/normalize.css$";
//     urlData_1_2.reverseRoute       = "/core/normalize.css";
//     urlData_1_2.componentPathInfo  = "core/normalize.css";
//     RouteReverse::Manager::addRoute( urlData_1_2, app );

    // /core/resources/tntwebwizard.css

    app.mapUrl("^/core/tntwebwizard.css$", "resources")
        .setPathInfo("core/resource/tntwebwizard.css");

//     RouteReverse::URLData urlData_1_3;
//     urlData_1_3.componentName      = "resources";
//     urlData_1_3.urlRegEx           = "^/core/tntwebwizard.css$";
//     urlData_1_3.reverseRoute       = "/core/tntwebwizard.css";
//     urlData_1_3.componentPathInfo  = "core/resources/tntwebwizard.css";
//     RouteReverse::Manager::addRoute( urlData_1_3, app );


    // ############################ SITES ##########################

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

