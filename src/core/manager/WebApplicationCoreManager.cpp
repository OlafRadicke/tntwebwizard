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


#include <core/manager/WebApplicationCoreManager.h>

#include <tnt/component.h>
#include <tnt/httprequest.h>

#include <cxxtools/fileinfo.h>
#include <cxxtools/directory.h>
#include <cxxtools/log.h>


#include <ostream>
#include <string>
// #include <unistd.h>

namespace Tww {
namespace Core
{


log_define("Core.WebApplicationCoreManager")

// C -------------------------------------------------------------------------

void WebApplicationCoreManager::creatMain_cpp(){
    std::ostringstream fileContent;
    fileContent
        << this->projectData.getSourceCodeHeader()
        << "#include <core/model/Config.h> \n"
        << "#include <core/initcomponent.h> \n"
    ;

    if ( this->projectData.isFormToken( ) ) {
        fileContent << "#include <formtoken/initcomponent.h> \n";
    }

    if ( this->projectData.isRouteRevers( ) ) {
        fileContent << "#include <routereverse/initcomponent.h> \n";
    }

    fileContent
        << "#include <tnt/tntnet.h> \n"
        << "#include <tnt/configurator.h> \n"
    ;

    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent << "#include <cxxtools/log.h> \n";
    }



}

// G --------------------------------------------------------------------------

bool WebApplicationCoreManager::isApplicationCoreExist(){

    std::string sourceDir = this->userSession.getSessionPath() + "/src";

    if ( !cxxtools::Directory::exists( sourceDir ) ) {
        log_debug( "[isApplicationCoreExist] /src no exist.");
        return false;
    };

    if ( !cxxtools::FileInfo::exists( sourceDir + "/src/main.cpp" ) ) {
        log_debug( "[isApplicationCoreExist] /src/main.cpp no exist.");
        return false;
    };
}


} // END namespace Core
} // end namespace Tww




