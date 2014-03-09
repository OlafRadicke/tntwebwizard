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
#include <core/model/TntWebWizardException.h>
#include <core/model/UserSession.h>
#include <core/manager/WebApplicationCoreManager.h>

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


    bool form_cli_support =
        qparam.arg<bool>("form_cli_support");
    std::string form_config_format =
        qparam.arg<std::string>("form_config_format");
    bool form_create =
        qparam.arg<bool>("form_create_button");

    std::stringstream file_projectdata;
    file_projectdata
        << this->userSession.getSessionPath()
        << "/tntwebwizard.pro"
    ;
    std::stringstream file_makefile;
    file_makefile
        << this->userSession.getSessionPath()
        << "/Makefile.tnt"
    ;

    log_debug("file_projectdata: " << file_projectdata.str() );
    log_debug("file_makefile: " << file_makefile.str() );
    log_debug("form_cli_support: " << form_cli_support );
    log_debug("form_config_format: " << form_config_format );
    log_debug("form_create: " << form_create );

    // save button pressed
    if ( form_create ) {
        log_debug("webappManager.createApplicationCore()" );

        this->projectData.setCliSupport( form_cli_support );
        WebApplicationCoreManager webappManager(
            this->userSession,
            this->projectData,
            this->makefileData
        );
        if ( !this->preChecksOk( webappManager ) ) return;

        try {
            webappManager.createApplicationCore();
        } catch ( Core::TntWebWizardException& tww_exception ) {
            this->feedback = "Mistake! Project core is NOT created! \n";
            this->feedback += tww_exception.what();
            this->warning = true;
        }
        this->feedback = "Okay! Project core is created now!";
        this->warning = false;
        return;
    } else {
        log_debug("Read project data and makefile..." );
        // read project configuration...
        this->projectData.read( file_projectdata.str() );
        this->makefileData.read( file_makefile.str() );

        WebApplicationCoreManager webappManager(
            this->userSession,
            this->projectData,
            this->makefileData
        );
        this->preChecksOk( webappManager );
        return;
    }
}

bool CreateApplicationCoreController::preChecksOk (
    WebApplicationCoreManager& webappManager
) {
    if( webappManager.isApplicationCoreExist() ) {
        this->feedback = "This step is all ready done. You can't do this on more!";
        this->warning = true;
        log_debug( __LINE__ );
        return false;
    }
    if( this->makefileData.getBinName() == "" ) {
        this->feedback = "The binary file name is not set! Go back to step (1.).";
        this->warning = true;
        return false;
    }

    if ( this->projectData.getSourceCodeHeader() == "getSourceCodeHeader()" ) {
        this->feedback = "The licence template for the source code header is \
        not set. Go to the menu point \"Basic project data\" make the basic \
        configuration please.";
        this->warning = true;
        return false;
    }
    return true;
}

} // namespace core
} // namespace Tww

