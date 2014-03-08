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
    log_debug("createApplicationCore()" );
    std::string mainCppPath = this->getMainCppPath();
    if ( cxxtools::FileInfo::exists( mainCppPath ) ) {
        std::ostringstream errorText;
        errorText
            << "The file "
            << mainCppPath
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
        << "/* ***************************************************************************\n"
        << this->projectData.getSourceCodeHeader()
        << "\n"
        << "*************************************************************************** */ \n"
        << "#include <core/model/Config.h>\n"
        << "#include <core/initcomponent.h>\n"
    ;
    if ( this->projectData.isFormToken( ) ) {
        fileContent << "#include <formtoken/initcomponent.h>\n";
    }
    if ( this->projectData.isRouteRevers( ) ) {
        fileContent << "#include <routereverse/initcomponent.h>\n";
    }
    fileContent << "\n";
    // ***** tnt lib part *****
    fileContent
        << "#include <tnt/tntnet.h>\n"
        << "#include <tnt/configurator.h>\n"
    ;
    fileContent << "\n";
    // ***** cxxtools lib part *****
    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent << "#include <cxxtools/log.h>\n"
        << "\t log_define(\"main\");\n";
    }
    if (  this->projectData.isCliSupport( ) ){
        fileContent << "#include <cxxtools/arg.h>.\n";
    }
    fileContent << "\n";
    // ***** std lib part *****
    fileContent << "#include  <iostream.h> \n";
    fileContent << "\n";

    fileContent
        <<  "int main ( int argc, char* argv[] )\n"
        <<  "{ \n"
    ;
    if (  this->projectData.isCliSupport( ) ){
        fileContent
            << "\t cxxtools::Arg<bool> arg_verbose(argc, argv, 'v');\n"
            << "\t cxxtools::Arg<std::string> arg_config(argc, argv, 'c', \"\");\n"
            << "\t if (verbose)\n"
            << "\t\t std::cout << \"verbose option is set\" << std::endl;\n"
            << "\t if ( verbose && arg_config != \"\")\n"
            << "\t\t std::cout << \"us config:\" << arg_config.getValue() << std::endl;\n"
        ;
    }

    fileContent <<  "\t Core::Config& config = Core::Config::it();\n";
    if (  this->projectData.isCliSupport( ) ){
        fileContent
            <<  "\t if ( arg_config.getValue() != \"\" ) {\n"
            <<  "\t\t config.read( arg_config.getValue() );\n"
            <<  "\t } else {\n"
            <<  "\t\t config.read();\n"
            <<  "\t }\n"
        ;
    } else {
        fileContent <<  "\t config.read();\n";
    }
    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent <<  "\t log_init( config.logging() );\n\n";
    }
    fileContent
        <<  "\t // Init Application Server\n"
        <<  "\t tnt::Tntnet app;\n"
        <<  "\t tnt::Configurator tntConfigurator( app );\n"
        <<  "\t tntConfigurator.setSessionTimeout ( config.sessionTimeout() );\n"
        <<  "\t app.listen( config.appIp(), config.appPort() );\n\n"
        <<  "\t // init comonent parts\n"
        <<  "\t Core::initcomponent( app );\n"
    ;
    if ( this->projectData.isFormToken( ) ) {
        fileContent << "\t FormToken::initcomponent( app );\n";
    }
    if ( this->projectData.isRouteRevers( ) ) {
        fileContent << "\t RouteReverse::initcomponent( app );\n\n";
    }
    fileContent
        << "\t std::cout \n"
        << "\t\t << \""
        << this->projectData.getProjectName()
        << " is started and run on http://\" \n"
        << "\t\t << config.appIp() << \":\" \n"
        << "\t\t << config.appPort() << \"/\" << std::endl\n"
        << "\t ;\n"
        << "\t log_info( \"starting " << this->projectData.getProjectName() << "\");\n"
        << "\t log_info( \" " << this->projectData.getProjectName()
        << " is started and run on http://\" <<  config.appIp() << \":\" "
        << "<<  config.appPort() << \"/\"); \n\n"
        << "\t app.run(); \n\n"
        << "\t return 0;\n"
        << "}\n"
    ;

    log_debug("fileContent: \n"  << fileContent.str() );
    log_debug( __LINE__ << " write in: \n"  << this->getMainCppPath().c_str() );
    std::ofstream maincpp_file( this->getMainCppPath().c_str() );
    maincpp_file << fileContent.str() ;
    maincpp_file.close();
    log_debug(
        __LINE__
        << " ready with writing file : \n"
        << this->getMainCppPath().c_str()
    );

    std::string makefilePath = this->getMakefilePath();
    log_debug( __LINE__ << " read file : \n"  << makefilePath );
    this->makefileData.read( makefilePath );
    std::string mainCppPath = this->getMainCppPath();
    log_debug( __LINE__ << " add path of: " << mainCppPath );
    this->makefileData.addCppFiles( mainCppPath );
    log_debug( __LINE__ << " write file : \n"  << this->getMakefilePath() );
    this->makefileData.write( this->getMakefilePath() );
    log_debug( __LINE__ << " ready with writing file : \n"  << this->getMakefilePath() );

}

// G --------------------------------------------------------------------------

std::string WebApplicationCoreManager::getMainCppPath( ){
    return this->userSession.getSessionPath() + "/src/main.cpp";
}

std::string WebApplicationCoreManager::getMakefilePath(){
    log_debug( __LINE__ << " getMakefilePath()\n" );
    log_debug(
        __LINE__
        << " this->userSession.getSessionPath()\n"
        << this->userSession.getSessionPath()
    );
    std::string complied_path = this->userSession.getSessionPath() + "/Makefile.tnt";
    log_debug( __LINE__ << " complied_path: \n" << complied_path );

    return complied_path;
}

std::string WebApplicationCoreManager::getSourceDir(){
    return this->userSession.getSessionPath() + "/src";
}

// I --------------------------------------------------------------------------
bool WebApplicationCoreManager::isApplicationCoreExist(){

    if ( !cxxtools::Directory::exists( this->getSourceDir() ) ) {
        return false;
    };
    if ( !cxxtools::FileInfo::exists( this->getMainCppPath() ) ) {
        return false;
    };
}


} // END namespace Core
} // end namespace Tww




