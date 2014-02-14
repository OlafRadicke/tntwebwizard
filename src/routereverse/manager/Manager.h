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

#ifndef ROUTEREVERS_MANAGER_H
#define ROUTEREVERS_MANAGER_H


#include <string>
#include <map>
#include <tnt/tntnet.h>
#include <routereverse/model/URLData.h>

namespace tntwebwizard {
namespace RouteReverse {

/**
 * This class or component support reverse routing.
 */
class Manager
{
public:


// A --------------------------------------------------------------------------

    /**
     * Add a url component rout.
     * @param urlData Contains routing data.
     * @param app reference of the application server.
     */
    static void addRoute( const URLData &urlData, tnt::Tntnet &app );

// G --------------------------------------------------------------------------

    /**
    * Get back a URL to a component.
    * @para componentName the name of component.
    * @return a relative URL to a component like: "../../foo/bar".
    */
    static std::string  getLinkTo(
        const std::string componentName,
        const tnt::HttpRequest& request
    );

    /**
    * Get back a URL to a component.
    * @para componentName the name of component.
    * @return a absolute URL to a component like: "http://domain.net:80/foo/bar".
    */
    static std::string getAbsolutURL(
        const std::string componentName,
        const tnt::HttpRequest& request
    );

    /**
     * Get back a string with all know everses routes.
     */
    static std::string getAllReversesRoutes();


private:

    static std::map< std::string, std::string > reverseMAP;

};


} // END namespace RouteReverse
} // namespace tntwebwizard


#endif // ROUTEREVERS_MANAGER_H

