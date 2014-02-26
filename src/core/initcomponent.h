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

    // /core/favicon.ico

    app.mapUrl(
        "^/core/favicon.ico$",
        "resources"
    ).setPathInfo("core/resources/favicon.ico");

    RouteReverse::Manager::add(
        "core_favicon_ico",
        "core/favicon.ico"
    );

    // /core/resources/tntnet.png

    app.mapUrl(
        "^/core/tntnet.png$",
        "resources"
    ).setPathInfo("core/resources/tntnet.png");

    RouteReverse::Manager::add(
        "core_tntnet_png",
        "core/tntnet.png"
    );

    // /core/resources/normalize.css

    app.mapUrl("^/core/normalize.css$", "resources")
        .setPathInfo("core/resources/normalize.css");

    RouteReverse::Manager::add(
        "core_normalize_css",
        "core/normalize.css"
    );

    // /core/resources/tntwebwizard.css

    app.mapUrl(
        "^/core/tntwebwizard.css$",
        "resources"
    ).setPathInfo( "core/resources/tntwebwizard.css" );

    RouteReverse::Manager::add(
        "core_tntwebwizard_css",
        "core/tntwebwizard.css"
    );

    // ############################ SITES ##########################

    // basic_project_data
    app.mapUrl(
        "^/core/basicprojectdata$",
        "core_basicprojectdata"
    );

    RouteReverse::Manager::add(
        "core_basicprojectdata",
        "core/basicprojectdata"
    );


    //core_createapplicationcore
    app.mapUrl(
        "^/core/createapplicationcore$",
        "core_createapplicationcore"
    );

    RouteReverse::Manager::add(
        "core_createapplicationcore",
        "core/createapplicationcore"
    );

    // ready get info...

    log_debug( RouteReverse::Manager::getAllReversesRoutes() );

}



} // END namespace Core
} // namespace Tww

#endif // CORE_INITCOMPONENT_H

