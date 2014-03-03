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
#include <core/model/TntWebWizardException.h>

#include <tnt/component.h>
#include <tnt/httprequest.h>

#include <cxxtools/fileinfo.h>
#include <cxxtools/directory.h>
#include <cxxtools/log.h>


#include <ostream>
#include <fstream>
#include <string>
// #include <unistd.h>

namespace Tww {
namespace Core
{


log_define("Core.WebApplicationCoreManager")

// C -------------------------------------------------------------------------

void WebApplicationCoreManager::createApplicationCore(){
    if ( cxxtools::FileInfo::exists( this->getMainCppPath() ) ) {
        log_debug("createApplicationCore()" );
        std::ostringstream errorText;
        errorText
            << "The file "
            << this->getMainCppPath()
            << " is all ready exist!"
            << "I can not create this file. Abort..."
        ;
        throw Core::TntWebWizardException( errorText.str() );
    }

    if ( !cxxtools::Directory::exists( this->getSourceDir() ) ) {
        cxxtools::Directory::create( this->getSourceDir() );
    }
    this->createMain_cpp();

}


void WebApplicationCoreManager::createMain_cpp(){
        log_debug("createMain_cpp()" );

    std::ostringstream fileContent;
    fileContent
        << this->projectData.getSourceCodeHeader()
        << "#include <core/model/Config.h>\n"
        << "#include <core/initcomponent.h>\n"
    ;
    if ( this->projectData.isFormToken( ) ) {
        fileContent << "#include <formtoken/initcomponent.h>\n";
    }
    if ( this->projectData.isRouteRevers( ) ) {
        fileContent << "#include <routereverse/initcomponent.h>\n";
    }
    fileContent
        << "#include <tnt/tntnet.h>\n"
        << "#include <tnt/configurator.h>\n"
    ;
    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent << "#include <cxxtools/log.h>\n\n"
        << "log_define(\"main\");\n";
    }
    fileContent
        <<  "int main ( int argc, char* argv[] )\n"
        <<  "{ \n"
        <<  "   Core::Config& config = Core::Config::it();\n"
        <<  "   config.read();\n"
    ;
    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent <<  "   log_init( config.logging() );\n\n";
    }
    fileContent
        <<  "   // Init Application Server\n"
        <<  "   tnt::Tntnet app;\n"
        <<  "   tnt::Configurator tntConfigurator( app );\n"
        <<  "   tntConfigurator.setSessionTimeout ( config.sessionTimeout() );\n"
        <<  "   app.listen( config.appIp(), config.appPort() );\n\n"
        <<  "   // init comonent parts\n"
        <<  "   Core::initcomponent( app );\n"
    ;
    if ( this->projectData.isFormToken( ) ) {
        fileContent << "   FormToken::initcomponent( app );\n";
    }
    if ( this->projectData.isRouteRevers( ) ) {
        fileContent << "   RouteReverse::initcomponent( app );\n\n";
    }
    fileContent
        << "    std::cout \n"
        << "        << \"" << this->projectData.getProjectName() << " is started and run on http://\""
        << "        << config.appIp() << \":\" \n"
        << "        << config.appPort() << \"/\" << std::endl\n"
        << "    ;\n"
        << "    log_info( \"starting " << this->projectData.getProjectName() << "\");\n"
        << "    log_info( \" " << this->projectData.getProjectName()
        << " is started and run on http://\" <<  config.appIp() << \":\" "
        << " <<  config.appPort() << \"/\"); \n\n"
        << "    app.run(); \n\n"
        << "    return 0;\n"
        << "}\n"
    ;

    log_debug("fileContent: \n"  << fileContent.str() );
    std::ofstream maincpp_file( this->getMainCppPath().c_str() );
    maincpp_file << fileContent.str() ;
    maincpp_file.close();

    this->makefileData.read( this->getMakefilePath() );
    this->makefileData.addCppFiles( this->getMainCppPath() );
    this->makefileData.write( this->getMakefilePath() );

}

// G --------------------------------------------------------------------------

const std::string& WebApplicationCoreManager::getMainCppPath( ){
    return this->userSession.getSessionPath() + "/src/main.cpp";
}

const std::string& WebApplicationCoreManager::getMakefilePath(){
    return this->userSession.getSessionPath() + "/Makefile.tnt";
}

const std::string& WebApplicationCoreManager::getSourceDir(){
    return this->userSession.getSessionPath() + "/src";
}

// I --------------------------------------------------------------------------
bool WebApplicationCoreManager::isApplicationCoreExist(){

    if ( !cxxtools::FileInfo::exists( this->getMainCppPath() ) ) {
        return false;
    };
    if ( !cxxtools::FileInfo::exists( this->getMainCppPath() ) ) {
        return false;
    };
}


} // END namespace Core
} // end namespace Tww




