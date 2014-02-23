/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013-2014
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


#include <core/controller/BasicProjectDataController.h>
#include <core/model/UserSession.h>
#include <core/model/ProjectData.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>

#include <string>

namespace Tww {
namespace Core {


log_define("Core.BasicProjectDataController")

void BasicProjectDataController::worker (
    tnt::HttpRequest& request,
    tnt::HttpReply& reply,
    tnt::QueryParams& qparam
){
    // define the query parameters
    std::string  form_projectname =
        qparam.arg<std::string>("form_projectname");
    std::string  form_binaryfilename =
        qparam.arg<std::string>("form_binaryfilename");
    bool  form_save =
        qparam.arg<bool>("form_save");

    log_debug("form_save: " << form_save );
    log_debug("form_projectname: " << form_projectname );

    if ( form_save ) {
        this->projectData.setProjectName( form_projectname );
    } else {
        // read project configuration...
    }
}

} // namespace core
} // namespace Tww

