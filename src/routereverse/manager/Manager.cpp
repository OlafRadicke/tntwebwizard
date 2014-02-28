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

#include <routereverse/manager/Manager.h>
#include <routereverse/model/RouteReverseException.h>

#include <cxxtools/log.h>
#include <string>
#include <map>
#include <iostream>
#include <ostream>
#include <exception>


namespace Tww {
namespace RouteReverse {


log_define("RouteReverse.Manager")

std::map< std::string, std::string > Manager::reverseMAP;


// A --------------------------------------------------------------------------


void Manager::add( std::string targetID, std::string reverseRoute ) {

        if ( Manager::reverseMAP.count( targetID ) > 0 ) {
            std::ostringstream errorText;
            errorText << "[" << __FILE__ << " "
                <<  __LINE__  << "] "
                << " the target id " << targetID
                << " is all ready set with reverse route!";
            log_debug( errorText );
            throw RouteReverseException( errorText.str() );
        }
        Manager::reverseMAP[ targetID ] = reverseRoute;
        log_debug( "List of know reverse routes: \n" <<
            RouteReverse::Manager::getAllReversesRoutes() );

}

// G --------------------------------------------------------------------------

std::string Manager::getAllReversesRoutes(){

    std::string returnString;

    std::map< std::string, std::string >::const_iterator it;
    for (
        it = Manager::reverseMAP.begin();
        it != Manager::reverseMAP.end();
        ++it
    ){
        returnString += it->first + " => " + it->second + "\n";
    }
    return returnString;
}


std::string  Manager::getLinkTo(
        const std::string componentName,
        const tnt::HttpRequest& request ){

    std::string targetURL;
    std::string returnURL;
    std::string currentURL = request.getUrl ();

    std::map<std::string, std::string>::const_iterator it =
        Manager::reverseMAP.find( componentName );
    if (it != Manager::reverseMAP.end())
        targetURL = it->second;

    returnURL = targetURL;

    size_t pathDepth = std::count( currentURL.begin(), currentURL.end(), '/' );
    for ( unsigned int i = 1; i < pathDepth; i++){
        returnURL = "../" + returnURL;
    }

    return returnURL;
}

std::string  Manager::getAbsolutURL(
        const std::string componentName,
        const tnt::HttpRequest& request ){

    std::string targetURL;
    std::string returnURL;

    std::map<std::string, std::string>::const_iterator it =
        Manager::reverseMAP.find( componentName );
    if (it != Manager::reverseMAP.end())
        targetURL = it->second;

    if ( request.isSsl() ) {
        returnURL = "https://" +request.getVirtualHost()
            + "/" + targetURL;
    } else{
        returnURL = "http://" +request.getVirtualHost()
            + "/" + targetURL;
    }
    return returnURL;
}

} // END namespace SessionForm
} // namespace Tww



