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

#include <core/controller/ProjectResetController.h>

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>

#include <string>

namespace Tww {
namespace Core {


log_define("Core.ProjectResetController")


void ProjectResetController::worker (
    tnt::HttpRequest& request,
    tnt::HttpReply& reply,
    tnt::QueryParams& qparam
){

    bool form_reset_button =
        qparam.arg<bool>("form_reset_button");
    log_debug( "## form_reset_button ##: " << form_reset_button);

    // save button pressed
    if ( form_reset_button ) {
        log_debug( "## " << __LINE__ << " ##" );
        std::string command = "rm -Rf " + this->userSession.getSessionPath() + "/*";
        log_debug( "do command: " << command );
        // I wish good luck and all the best...!
        system( command.c_str() );
        // read and reset project configuration...
        this->projectData = Tww::Core::ProjectData();
        this->makefileData = Tww::Core::MakefileData();
        this->feedback="All generated data is delete now.";
        this->warning = false;
        return;
    }
}

std::string ProjectResetController::getProjectFilePath(){
    std::stringstream file_projectdata;
    file_projectdata
        << this->userSession.getSessionPath()
        << "/tntwebwizard.pro"
    ;
    return file_projectdata.str();
}

std::string ProjectResetController::getMakefilePath(){
    std::stringstream file_makefile;
    file_makefile
        << this->userSession.getSessionPath()
        << "/Makefile.tnt"
    ;
    return file_makefile.str();
}


} // namespace core
} // namespace Tww

