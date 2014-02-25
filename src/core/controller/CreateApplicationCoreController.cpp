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

#include <core/controller/CreateApplicationCoreController.h>

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>

#include <string>

namespace Tww {
namespace Core {


log_define("Core.CreateApplicationCoreController")


void CreateApplicationCoreController::worker (
    tnt::HttpRequest& request,
    tnt::HttpReply& reply,
    tnt::QueryParams& qparam
){
    // define the query parameters


    std::string form_cli_support =
        qparam.arg<std::string>("form_cli_support");
    std::string config_format =
        qparam.arg<std::string>("config_format");
    bool form_create =
        qparam.arg<bool>("form_create");

    std::stringstream file_projectdata;
    file_projectdata << this->userSession.getSesstonPath() << "/tntwebwizard.pro";
    std::stringstream file_makefile;
    file_makefile << this->userSession.getSesstonPath() << "/Makefile.tnt";

    log_debug("form_create: " << form_create );

    // save button pressed
    if ( form_create ) {
        this->projectData.write( file_projectdata.str() );
        this->makefileData.write( file_makefile.str() );
    } else {
        // read project configuration...
        this->projectData.read( file_projectdata.str() );
        this->makefileData.read( file_makefile.str() );
    }
}



} // namespace core
} // namespace Tww

