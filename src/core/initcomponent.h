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


namespace tntwebwizard {
namespace Core {

    log_define("Core.initcomponent")

/**
 * This function prepare the component "Core". specifically the routing.
 * @arg app a reference of the application server.
 */
void initcomponent ( tnt::Tntnet &app ) {
    RouteReverse::URLData urlData;


    // feed-icon.png

//     RouteReverse::URLData urlData4;
//     urlData4.componentName      = "resources";
//     urlData4.urlRegEx           = "^/Core/feed-icon.png$";
//     urlData4.componentPathInfo  = "Core/resources/feed-icon.png";
//     RouteReverse::Manager::addRoute( urlData4, app );
//
//     RouteReverse::URLData urlData4_1;
//     urlData4_1.componentName      = "Core/feed-icon.png";
//     urlData4_1.reverseRoute       = "Core/feed-icon.png";
//     RouteReverse::Manager::addRoute( urlData4_1, app );

    // SwitchToHandheldVersion

//     RouteReverse::URLData urlData5_1;
//     urlData5_1.urlRegEx           = "^SwitchToHandheldVersion$";
//     urlData5_1.componentName      = "SwitchToHandheldVersionView";
//     RouteReverse::Manager::addRoute( urlData5_1, app );
//
//     RouteReverse::URLData urlData5_2;
//     urlData5_2.urlRegEx           = "^SwitchToHandheldVersion$";
//     urlData5_2.componentName      = "SwitchToHandheldVersionController";
//     RouteReverse::Manager::addRoute( urlData5_2, app );
//
//     RouteReverse::URLData urlData5_3;
//     urlData5_3.reverseRoute       = "SwitchToHandheldVersion";
//     urlData5_3.componentName      = "SwitchToHandheldVersion";
//     RouteReverse::Manager::addRoute( urlData5_3, app );

    // NewAccount

//     app.mapUrl("^NewAccount$", "NewAccountView");
//     app.mapUrl("^NewAccount$", "NewAccountController");
//
//     RouteReverse::URLData urlData6;
//     urlData5_3.reverseRoute       = "NewAccount";
//     urlData5_3.componentName      = "NewAccount";
//     RouteReverse::Manager::addRoute( urlData5_3, app );


    // ready get info...

    log_debug( RouteReverse::Manager::getAllReversesRoutes() );

}



} // END namespace Core
} // namespace tntwebwizard

#endif // CORE_INITCOMPONENT_H

