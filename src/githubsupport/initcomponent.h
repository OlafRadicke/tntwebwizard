/* 
Copyright (C) <year>  <name of author> 

This program is free software: you can redistribute it and/or modify 
it under the terms of the GNU Affero General Public License as published by 
the Free Software Foundation, either version 3 of the License, or later 
version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU Affero General Public License for more details. 

You should have received a copy of the GNU Affero General Public License 
along with this program.  If not, see <http://www.gnu.org/licenses/>.    

*/ 

#ifndef GITHUBSUPPORT_INITCOMPONENT_H 
#define GITHUBSUPPORT_INITCOMPONENT_H 

#include <string>
#include <tnt/tntnet.h>
#include <routereverse/manager/manager.h>
#include <cxxtools/log.h>

namespace GithubSupport {

log_define("GithubSupport.initcomponent")
/**
 * This function prepare the component "GithubSupport". specifically the routing.
 * @arg app a reference of the application server.
 */
void initcomponent ( tnt::Tntnet &app ) {
    app.mapUrl(
        "^/githubsupport/github_download$",
        "githubsupport_github_download"
    );
    RouteReverse::Manager::add(
        "githubsupport_github_download",
        "githubsupport/github_download"
    );

    // now it is ready and get info about all know routes.
    log_debug( RouteReverse::Manager::getAllReversesRoutes() );

} // end of function 

} // END namespace
#endif // CORE_INITCOMPONENT_H
