/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013-2014
* @copyright
* Copyright (C) 2014  Olaf Radicke <briefkasten@olaf-rdicke.de>
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

#include <core/controller/DownloadZipController.h>

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/TntWebWizardException.h>
#include <core/model/UserSession.h>
#include <core/manager/WebApplicationCoreManager.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include <cxxtools/file.h>
#include <cxxtools/directory.h>
#include <cxxtools/log.h>

#include <string>

namespace Tww {
namespace Core {


log_define("Core.DownloadZipController")


void DownloadZipController::worker (
    tnt::HttpRequest& request,
    tnt::HttpReply& reply,
    tnt::QueryParams& qparam
){
    log_debug( "[" << __LINE__ << "] DownloadZipController::worker" );
    std::stringstream sysCommand;
    std::ostringstream errorText;
    std::stringstream zipPathStream;

    if ( !system(NULL) ) {
        errorText
            << "Can not do systems command!"
        ;
        throw Core::TntWebWizardException( errorText.str() );
    }

    // read project configuration...
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
    this->projectData.read( file_projectdata.str() );
    this->makefileData.read( file_makefile.str() );

    if ( this->makefileData.getBinName() == "" ) {
        errorText
            << "The name of the executable file is not set!"
        ;
        throw Core::TntWebWizardException( errorText.str() );
    }
    sysCommand
        << "cd "
        << this->userSession.getSessionPath()
        << "; "
        << "zip -r "
        << this->makefileData.getBinName()
        << ".zip ./* ;"
    ;

    log_debug( "[" << __LINE__ << "] command: " << sysCommand.str() );
    if (
        cxxtools::Directory::exists(
            this->userSession.getSessionPath().c_str()
        )
    ) {
        log_debug( "[" << __LINE__ << "] do command..." );
        int i=system( sysCommand.str().c_str() );
        log_debug( "[" << __LINE__ << "]The value returned was: " << i);
    } else {
        errorText
            << "Failed to open project directory \""
            << sysCommand.str()
            << '". It is sure, do you have create a Project?'
        ;
        throw Core::TntWebWizardException( errorText.str() );
    }
    zipPathStream
        << this->userSession.getSessionPath()
        << "/"
        << this->makefileData.getBinName()
        << ".zip"
    ;
    this->zipPath = zipPathStream.str();

}

void DownloadZipController::cleanUp() {

    if ( cxxtools::File::exists( this->zipPath ) ){
        cxxtools::File oldZipFile( this->zipPath );
        oldZipFile.remove ();
    }
}

} // namespace core
} // namespace Tww

