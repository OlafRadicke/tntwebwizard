/*
* Copyright (C) 2013 Tommi Maekitalo
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

#ifndef SESSIONFORM_MANAGER_H
#define SESSIONFORM_MANAGER_H


#include <string>

#include <tnt/component.h>
#include <tnt/httprequest.h>

namespace SessionForm
{

/**
 * This class support methods too prevent reloads of html-forms requests.
 */
class Manager
{
public:


// G --------------------------------------------------------------------------

    /**
    * Get back a hidden input form tag, with a token id as value. The input tag
    * name is SESSIONFORM_TOKEN.
     * @para request
    * @return a hidden input form tag, with a token id.
    */
    static std::string  getFormToken( tnt::HttpRequest& request );

private:

    /**
     * Generated a random string as html form token.
     * @para len teh length of sting.
     * @return a random string
     */
    static std::string genRandomToken ( const int len) ;

};


} // END namespace SessionForm


#endif // SESSIONFORM_MANAGER_H

