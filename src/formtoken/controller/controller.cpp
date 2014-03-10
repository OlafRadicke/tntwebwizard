/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright
* Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>
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

#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include <cxxtools/log.h>
#include <iostream>

log_define("FormToken.Controller")


namespace FormToken {
    class Controller : public tnt::Component {
    public:
        unsigned operator() (
            tnt::HttpRequest& request,
            tnt::HttpReply& reply,
            tnt::QueryParams& qparam
        );
    };

} // namespace FormToken

static tnt::ComponentFactoryImpl<FormToken::Controller> factory("formtoken_controller");

unsigned FormToken::Controller::operator() (
    tnt::HttpRequest& request,
    tnt::HttpReply& reply,
    tnt::QueryParams& qparam
) {
    TNT_SESSION_SHARED_VAR( std::string, SESSIONFORM_AVAILABLE_TOKEN, () );
    if ( qparam.has("SESSIONFORM_TOKEN") ) {

        std::string SESSIONFORM_TOKEN =
            qparam.arg<std::string>("SESSIONFORM_TOKEN");
        log_debug( "Value of SESSIONFORM_TOKEN: " << SESSIONFORM_TOKEN );
        log_debug( "Value of SESSIONFORM_AVAILABLE_TOKEN: " << SESSIONFORM_AVAILABLE_TOKEN );

        if ( SESSIONFORM_TOKEN != SESSIONFORM_AVAILABLE_TOKEN ) {
            return reply.redirect ( "/FormToken/NoAvailabeTokenView" );
        }
    } else {
        log_debug( "No SESSIONFORM_TOKEN exist"  );
    };
    return DECLINED;
}
