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

#include <core/controller/NewComponentController.h>

#include <core/manager/WebApplicationCoreManager.h>
#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/TntWebWizardException.h>
#include <core/model/UserSession.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>

#include <string>

namespace Tww {
namespace Core {


log_define("Core.NewComponentController")




void NewComponentController::worker (
    tnt::HttpRequest& request,
    tnt::HttpReply& reply,
    tnt::QueryParams& qparam
){
    log_debug("NewComponentController::worker..." );
    log_debug(
        "\n form_create_button\n "
        << qparam.arg<bool>("form_create_button")
        << "\n form_add_property\n "
        <<  qparam.arg<bool>("form_add_property")
    );

    //
    if ( this->isProjectFounded() == false ) return;

    if ( qparam.arg<bool>("form_create_button") == true
        or qparam.arg<bool>("form_add_property") == true
    ) {
        this->nameSpace =
            qparam.arg<std::string>("form_namespace");
        this->ecppFileName =
            qparam.arg<std::string>("form_ecppfilename");
        this->controllerName =
            qparam.arg<std::string>("form_controllername");
        this->newModelData.setName( qparam.arg<std::string>("form_modelname") );
        this->newModelData.isGetterFunctions(
            qparam.arg<bool>("form_getter_functions") );
        this->newModelData.isSetterFunctions(
            qparam.arg<bool>("form_setter_functions") );
    }

    // save button pressed
    if ( qparam.arg<bool>("form_create_button") == true ) {
        log_debug("create_button is pushed..." );
        this->newModelData.setNamespace( this->nameSpace );
        this->newModelData.createFiles( this->projectData );

        this->feedback = "Okay! Project core is created now!";
        this->warning = false;
        return;
    } else {
        // click button "add a property"
        if ( qparam.arg<bool>("form_add_property") == true  ) {
        log_debug("add_property is pushed..." );
            if ( qparam.arg<std::string>("form_property_name") == "" ) {
                this->feedback = "A property must be have a name!";
                this->warning = true;
                return;
            } else {
                this->newModelData.addProperty(
                    qparam.arg<std::string>("form_property_name"),
                    qparam.arg<std::string>("form_property_type")
                );
            }
        } else {

        }
    }
}


bool NewComponentController::isProjectFounded() {

    // read project configuration...
    this->projectData.read( this->getProjectFilePath() );
    this->makefileData.read( this->getMakefilePath() );
    // check is this step allowed.
    WebApplicationCoreManager webappManager(
        this->userSession,
        this->projectData,
        this->makefileData
    );

    if( webappManager.isApplicationCoreExist() == false ) {
        this->feedback = "There is no core project exist! Go back to menu \"Basic project data\".";
        this->warning = true;
        return false;
    }
    if( this->makefileData.getBinName() == "" ) {
        this->feedback = "The binary file name is not set! Go back to menu \"Basic project data\".";
        this->warning = true;
        return false;
    }

    if ( this->projectData.getSourceCodeHeader() == "" ) {
        this->feedback = "The licence template for the source code header is \
        not set. Go to the menu point \"Basic project data\" make the basic \
        configuration please.";
        this->warning = true;
        return false;
    }
    return true;
}


std::string NewComponentController::getProjectFilePath(){

    std::stringstream file_projectdata;
    file_projectdata
        << this->userSession.getSessionPath()
        << "/tntwebwizard.pro"
    ;
    return file_projectdata.str();
}

std::string NewComponentController::getMakefilePath(){
    std::stringstream file_makefile;
    file_makefile
        << this->userSession.getSessionPath()
        << "/Makefile.tnt"
    ;
    return file_makefile.str();
}


} // namespace core
} // namespace Tww

