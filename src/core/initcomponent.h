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

#include <routereverse/manager/manager.h>

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


    // special pages
    // 1 to 1 rout
    app.mapUrl( "^/(.*)$", "$1" );

    // default route for /
    app.mapUrl( "^/$", "core_home" );

    // ######################## RESOURCES ############################

    // configure generic static stuff
    app.mapUrl(
        "^/Core/resources/(.*)",
        "resources"
    ).setPathInfo("core/resources/$1");

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

    app.mapUrl(
        "^/core/normalize.css$",
        "resources"
    ).setPathInfo("core/resources/normalize.css");
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

    // ======= module FormToken =======

    // core/resources/modul_formtoken.zip

    app.mapUrl(
        "^/core/modul_formtoken.zip$",
        "resources"
    ).setPathInfo( "core/resources/modul_formtoken.zip" );
    RouteReverse::Manager::add(
        "core_modul_formtoken_zip",
        "core/modul_formtoken.zip"
    );

    // /formtoken/controller/controller.cpp

    app.mapUrl(
        "^/formtoken/controller.cpp$",
        "resources"
    ).setPathInfo( "formtoken/controller/controller.cpp" );
    RouteReverse::Manager::add(
        "formtoken_controller_cpp",
        "formtoken/controller.cpp"
    );

    // formtoken/initcomponent.h

    app.mapUrl(
        "^/formtoken/initcomponent.h$",
        "resources"
    ).setPathInfo( "formtoken/initcomponent.h" );
    RouteReverse::Manager::add(
        "formtoken_initcomponent_h",
        "formtoken/initcomponent.h"
    );

    // formtoken/subpage_form_token.dox

    app.mapUrl(
        "^/formtoken/subpage_form_token.dox$",
        "resources"
    ).setPathInfo( "formtoken/subpage_form_token.dox" );
    RouteReverse::Manager::add(
        "formtoken_subpage_form_token_dox",
        "formtoken/subpage_form_token.dox"
    );

    // formtoken/manager/manager.cpp

    app.mapUrl(
        "^/formtoken/manager/manager.cpp$",
        "resources"
    ).setPathInfo( "formtoken/manager/manager.cpp" );
    RouteReverse::Manager::add(
        "formtoken_manager_cpp",
        "formtoken/manager/manager.cpp"
    );

    // formtoken/manager/manager.h

    app.mapUrl(
        "^/formtoken/manager.h$",
        "resources"
    ).setPathInfo( "formtoken/manager/manager.h" );
    RouteReverse::Manager::add(
        "formtoken_manager_h",
        "formtoken/manager.h"
    );

    // formtoken/view/formtoken_no_availabe_token.ecpp

    app.mapUrl(
        "^/formtoken/view/formtoken_no_availabe_token.ecpp$",
        "resources"
    ).setPathInfo( "formtoken/view/formtoken_no_availabe_token.ecpp" );
    RouteReverse::Manager::add(
        "formtoken_no_availabe_token_ecpp",
        "formtoken/view/formtoken_no_availabe_token.ecpp"
    );


    // ======= module RouteReverse =======

    // "routereverse/initcomponent.h",

    app.mapUrl(
        "^/routereverse/initcomponent.h$",
        "resources"
    ).setPathInfo( "routereverse/initcomponent.h" );
    RouteReverse::Manager::add(
        "routereverse_initcomponent_h",
        "routereverse/initcomponent.h"
    );

    // "routereverse/subpage_route_reverse.dox",

    app.mapUrl(
        "^/routereverse/subpage_route_reverse.dox$",
        "resources"
    ).setPathInfo( "routereverse/subpage_route_reverse.dox" );
    RouteReverse::Manager::add(
        "routereverse_subpage_route_reverse_dox",
        "routereverse/subpage_route_reverse.dox"
    );

    // "routereverse/manager/manager.cpp",

    app.mapUrl(
        "^/routereverse/manager/manager.cpp$",
        "resources"
    ).setPathInfo( "routereverse/manager/manager.cpp" );
    RouteReverse::Manager::add(
        "routereverse_manager_cpp",
        "routereverse/manager/manager.cpp"
    );

    // "routereverse/manager/manager.h",

    app.mapUrl(
        "^/routereverse/manager/manager.h$",
        "resources"
    ).setPathInfo( "routereverse/manager/manager.h" );
    RouteReverse::Manager::add(
        "routereverse_manager.h",
        "routereverse/manager/manager.h"
    );

    // "routereverse/model/routereverseexception.h"

    app.mapUrl(
        "^/routereverse/model/routereverseexception.h$",
        "resources"
    ).setPathInfo( "routereverse/model/routereverseexception.h" );
    RouteReverse::Manager::add(
        "routereverse_routereverseexception.h",
        "routereverse/model/routereverseexception.h"
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

    // core_download_zip.ecpp
    app.mapUrl(
        "^/core/download.zip$",
        "core_downloadzip"
    );

    RouteReverse::Manager::add(
        "core_downloadzip",
        "core/download.zip"
    );

    // core_projectreset
    app.mapUrl(
        "^/core/projectreset$",
        "core_projectreset"
    );

    RouteReverse::Manager::add(
        "core_projectreset",
        "core/projectreset"
    );

    // ready get info...
    log_debug( RouteReverse::Manager::getAllReversesRoutes() );

}



} // END namespace Core
} // namespace Tww

#endif // CORE_INITCOMPONENT_H

