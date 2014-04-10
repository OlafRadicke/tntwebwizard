/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2014
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

#include <core/model/NewViewData.h>
#include <core/model/TntWebWizardException.h>

#include <cxxtools/directory.h>
#include <cxxtools/log.h>

#include <fstream>
#include <ostream>
#include <sstream>

#include <string>         // std::string
#include <locale>         // std::locale, std::toupper


namespace Tww {
namespace Core {

log_define("Core.NewViewData")
// === C ===


void NewViewData::createFiles( std::map<std::string,std::string>& _propertyMap ){
    log_debug("createFile()" );

    std::stringstream fileContent;

    // Create directories
    std::stringstream compDirName;
    compDirName
        << this->userSession.getSessionPath()
        << "/src/"
        << this->toLower( this->componentNamespace )
    ;
    if ( !cxxtools::Directory::exists( compDirName.str() ) ) {
        cxxtools::Directory::create( compDirName.str() );
    }
    compDirName
        << "/model/"
    ;
    if ( !cxxtools::Directory::exists( compDirName.str() ) ) {
        cxxtools::Directory::create( compDirName.str() );
    }

    // Create file content

    fileContent
        << "<# \n"
        << this->projectData.getSourceCodeHeader()
        << "#> \n\n"
        << "<%session\n"
        << "    scope=\"shared\"\n"
        << "    include=\""
        << this->toLower( this->componentNamespace )
        << "/model/" << this->toLower( this->modelName ) << ".h\">\n"
        << "    " << this->componentNamespace << "::" << this->modelName
        << " _" << this->toLower( this->modelName ) << "();\n"
        << "</%session>\n\n"
        << "<%request\n"
        << "    include=\"" << this->toLower( this->componentNamespace )
        << "/controller/" << this->toLower( this->controllerName ) << ".h\" >\n"
        << "        " << this->componentNamespace << "::" << this->controllerName << "\n"
        << "            controller( _" << this->toLower( this->controllerName ) << ");\n"
        << "</%request>\n"
        << "<%cpp>\n"
        << "    controller.worker(\n"
        << "        request,\n"
        << "        reply,\n"
        << "        qparam\n"
        << "    );\n"
        << "</%cpp>\n"
        << "<!DOCTYPE HTML>\n"
        << "<html>\n"
        << "<head>\n"
        << "    <title>" << this->toUpper( this->componentNamespace ) << "</title>\n"
        << "</head>\n"
        << "<body>\n"
    ;
    if ( this->formSupport == true ) {
        fileContent << "    <form method=\"post\">  \n";
        std::vector<std::string> allProperties;
        for (
            std::map<std::string,std::string>::iterator it=_propertyMap.begin();
            it!=_propertyMap.end();
            ++it
        ){
            if ( it->second == "cxxtools::String"
                or it->second == "std::string"
            ) {
                fileContent
                    << "        <label from=\"" << it->first << "\">" << it->first << ":</label>\n"
                    << "        <input\n"
                    << "            id=\"" << it->first << "\"\n"
                    << "            name=\"form_" << it->first << "\"\n"
                    << "            type=\"text\"\n"
                    << "            size=\"40\"\n"
                    << "            maxlength=\"40\"\n"
                    << "            value=\"<$ _" << this->toLower( this->modelName ) << ".get_" << it->first << " $>\">\n"
                ;
            }
            if ( it->second == "int"
                or it->second == "float"
                or it->second == "long int"
                or it->second == "unsigned int"
            ) {
                fileContent
                    << "        <label from=\"" << it->first << "\">" << it->first << ":</label>\n"
                    << "        <input\n"
                    << "            id=\"" << it->first << "\"\n"
                    << "            name=\"form_" << it->first << "\"\n"
                    << "            type=\"number\"\n"
                    << "            size=\"40\"\n"
                    << "            maxlength=\"40\"\n"
                    << "            value=\"<$ _" << this->toLower( this->modelName ) << ".get_" << it->first << " $>\">\n"
                ;
            }
            if ( it->second == "bool" ) {
                fileContent
                    << "        <label from=\"" << it->first << "\">" << it->first << ":</label>\n"
                    << "        <input\n"
                    << "            id=\"" << it->first << "\"\n"
                    << "            name=\"form_" << it->first << "\"\n"
                    << "            type=\"checkbox\"\n"
                    << "            value=\"true\">\n"
                ;
            }
        }
        fileContent
            << "        <button\n"
            << "            name=\"form_submit_button\"\n"
            << "            type=\"submit\"\n"
            << "            value=\"form_create_button\" >Submit form</button>\n"
            << "    </form>\n"
        ;
    }
    fileContent
        << "</body>\n"
    ;


    // Write content in file...
    log_debug( "\n++++++++++++++++++++++++++++\n" << fileContent.str() << "\n+++++++++++++++++++++++++++\n");

    std::stringstream compEcppFileName;
    compEcppFileName
        << this->userSession.getSessionPath()
        << "/src/"
        << this->toLower( this->componentNamespace )
        << "/model/"
        << this->viewName
        << ".ecpp"
    ;

    log_debug(
        __LINE__
        << " write in: \n"
        << compEcppFileName.str()
    );
    std::ofstream compEcppFile( compEcppFileName.str().c_str() );
    compEcppFile << fileContent.str() ;
    compEcppFile.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->userSession.getSessionPath() + "/Makefile.tnt" );
    this->makefileData.addHFile(
        "./src/"
        + this->toLower( this->componentNamespace )
        + "/model/"
        + this->modelName
        + ".h"
    );
    this->makefileData.write( this->userSession.getSessionPath() + "/Makefile.tnt" );
}

// === T ===

std::string NewViewData::toLower( std::string _mixedString ){
    std::ostringstream upperString;
//     std::locale loc("de_DE.UTF8");
    std::locale loc;
    for (std::string::size_type i=0; i<_mixedString.length(); ++i){
        upperString << std::tolower(_mixedString[i],loc);
    }
    return upperString.str();
}

std::string NewViewData::toUpper( std::string _mixedString ){
    std::ostringstream upperString;
//     std::locale loc("de_DE.UTF8");
    std::locale loc;
    for (std::string::size_type i=0; i<_mixedString.length(); ++i){
        upperString << std::toupper(_mixedString[i],loc);
    }
    return upperString.str();
}



} // namespace core
} // namespace Tww
