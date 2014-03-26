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

std::vector<std::string> NewComponentController::getPropertyList(){
    std::vector<std::string> allProperties;
    std::map<std::string,std::string> propertyMap;
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        allProperties.push_back( it->second + "  " + it->first );
    }
    return allProperties;
}


void NewComponentController::worker (
    tnt::HttpRequest& request,
    tnt::HttpReply& reply,
    tnt::QueryParams& qparam
){
    log_debug("NewComponentController::worker..." );
    log_debug(
        "\n form_save_button\n "
        << qparam.arg<bool>("form_save_button")
        << "\n form_add_property\n "
        <<  qparam.arg<bool>("form_add_property")
    );

    this->nameSpace =
        qparam.arg<std::string>("form_namespace");

    this->ecppFileName =
        qparam.arg<std::string>("form_ecppfilename");

    this->controllerName =
        qparam.arg<std::string>("form_controllername");

    this->modelName =
        qparam.arg<std::string>("form_modelname");

    // save button pressed
    if ( qparam.arg<bool>("form_create_button") == true ) {
        log_debug("create_button is pushed..." );

        this->feedback = "Okay! Project core is created now!";
        this->warning = false;
        return;
    } else {
        // click button "add a property"
        if ( qparam.arg<bool>("form_add_property") == true  ) {
        log_debug("add_property is pushed..." );
            propertyMap[qparam.arg<std::string>("form_property_name")]
                = qparam.arg<std::string>("form_property_type");

        } else {

        }
    }
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

