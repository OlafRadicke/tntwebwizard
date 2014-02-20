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

#ifndef ROUTEREVERSE_URLDATA_H
#define ROUTEREVERSE_URLDATA_H


#include <string>
#include <tnt/tntnet.h>


namespace Tww {
namespace RouteReverse {

/**
 * This class storage data about url routing.
 */
class URLData
{
public:


    /**
     * Storage a regular expression for a component.
     */
    std::string  urlRegEx;

    /**
     * Storage the name of a component.
     */
    std::string  componentName;

    /**
     * Storage the path info for multi binary components.
     * For example resources components.
     */
    std::string  componentPathInfo;

    /**
     * Storage the path to components for link(ing).
     */
    std::string  reverseRoute;

};


} // END namespace RouteReverse
} // namespace Tww


#endif // ROUTEREVERSE_URLDATA_H

