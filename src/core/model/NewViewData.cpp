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
        << "/view/"
    ;
    if ( !cxxtools::Directory::exists( compDirName.str() ) ) {
        cxxtools::Directory::create( compDirName.str() );
    }

    // Create file content

    fileContent
        << "<# \n"
        << this->projectData.getSourceCodeHeader()
        << "\n#> \n\n"
    ;
    if( this->projectData.isFormToken() == true ){
        fileContent
            << "<%pre> \n"
            << "    #include <formtoken/manager/manager.h> \n"
            << "</%pre> \n"
        ;
    }
    fileContent
        << "<%session\n"
        << "    scope=\"shared\"\n"
        << "    include=\""
        << this->toLower( this->componentNamespace )
        << "/model/" << this->toLower( this->modelName ) << ".h\">\n"
        << "        " << this->componentNamespace << "::" << this->modelName
        << " inst_" << this->toLower( this->modelName ) << "();\n"
        << "</%session>\n\n"
        << "<%request\n"
    ;
    if( this->projectData.isFlashMessagesSupport() == true ){
        fileContent
            << "    include=\"flashmessages/model/messagedata.h\" \n"
        ;
    }
    fileContent
        << "    include=\"" << this->toLower( this->componentNamespace )
        << "/controller/" << this->toLower( this->controllerName ) << ".h\" >\n"
    ;
    if( this->projectData.isFlashMessagesSupport() == true ){
        fileContent
            << "        FlashMessages::MessageData  flashmessage;\n"
        ;
    }
    fileContent
        << "        " << this->componentNamespace << "::" << this->controllerName << "\n"
        << "            controller( \n"
        << "                inst_" << this->toLower( this->modelName )
    ;
    if( this->projectData.isFlashMessagesSupport() == true ){
        fileContent
            << ",\n                flashmessage\n"
        ;
    }
    fileContent
        << "            );\n"
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

    if( this->projectData.isFlashMessagesSupport() == true ){
        fileContent
            << "    <%include>flashmessages/view/flashmessages_feedbackbox.eccp</%include> \n"
        ;
    }

    if ( this->formSupport == true ) {
        fileContent << "    <form method=\"post\">  \n";

        if( this->projectData.isFormToken() == true ){
            fileContent
                << "        <$$  FormToken::Manager::getFormToken( request )  $>\n"
            ;
        }

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
                    << "            value=\"<$ inst_" << this->toLower( this->modelName ) << ".get_" << it->first << "() $>\">\n\n"
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
                    << "            value=\"<$ inst_" << this->toLower( this->modelName ) << ".get_" << it->first << "() $>\">\n\n"
                ;
            }
            if ( it->second == "bool" ) {
                fileContent
                    << "        <label from=\"" << it->first << "\">" << it->first << ":</label>\n"
                    << "        <input\n"
                    << "            id=\"" << it->first << "\"\n"
                    << "            name=\"form_" << it->first << "\"\n"
                    << "            type=\"checkbox\"\n"
                    << "            value=\"true\"\n"
                    << "%     if ( inst_" << this->toLower( this->modelName )
                    << ".get_" << it->first << "() ) {\n"
                    << "            checked >\n"
                    << "%     } else {\n"
                     << "                   >\n"
                    << "%     }\n\n"
                ;
            }
        }
        fileContent
            << "        <button\n"
            << "            name=\"form_submit_button\"\n"
            << "            type=\"submit\"\n"
            << "            value=\"form_submit_button\" >Submit form</button>\n"
            << "    </form>\n"
        ;
    }
    fileContent
        << "</body>\n"
    ;
    // --------- witting file(s) ---------
    std::stringstream compEcppFileName;
    compEcppFileName
        << this->userSession.getSessionPath()
        << "/src/"
        << this->toLower( this->componentNamespace )
        << "/view/"
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
    this->makefileData.addEcppFile(
        "./src/"
        + this->toLower( this->componentNamespace )
        + "/view/"
        + this->viewName
        + ".ecpp"
    );
    this->makefileData.write( this->userSession.getSessionPath() + "/Makefile.tnt" );

    this->createInitcomponent_hFile();
}

void NewViewData::createInitcomponent_hFile(){
    log_debug("createInitcomponent_hFile()" );

    std::stringstream fileContent;
    fileContent
        << "/* \n"
        << this->projectData.getSourceCodeHeader()
        << "\n*/ \n\n"
        << "#ifndef " << toUpper( this->componentNamespace )
        << "_INITCOMPONENT_H \n"
        << "#define " << toUpper( this->componentNamespace )
        << "_INITCOMPONENT_H \n\n"
        << "#include <string>\n"
        << "#include <tnt/tntnet.h>\n"
    ;
    if ( this->projectData.isRouteReverse() == true ){
        fileContent << "#include <routereverse/manager/manager.h>\n" ;
    }
    if ( this->projectData.isCxxtoolsLoging() ){
        fileContent  << "#include <cxxtools/log.h>\n";
    }
    if( this->componentNamespace != "" ){
        fileContent  << "\nnamespace " << this->componentNamespace << " {\n\n";
    }
    if ( this->projectData.isCxxtoolsLoging( ) ){
        fileContent  << "log_define(\"" << this->componentNamespace << ".initcomponent\")\n";
    }
    if ( this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "/**\n"
            << " * This function prepare the component \""
            << this->componentNamespace << "\". specifically the routing.\n"
            << " * @arg app a reference of the application server.\n"
            << " */\n"
        ;
    }
    fileContent
        << "void initcomponent ( tnt::Tntnet &app ) {\n"
        << "    app.mapUrl(\n"
        << "        \"^/" << urlRoute << "$\",\n"
        << "        \"" << this->viewName << "\"\n"
        << "    );\n"
    ;
    if ( this->projectData.isRouteReverse() == true ){
        fileContent
            << "    RouteReverse::Manager::add(\n"
            << "        \"" << this->viewName << "\",\n"
            << "        \"" << urlRoute << "\"\n"
            << "    );\n\n"
        ;
    }
    if ( this->projectData.isCxxtoolsLoging() ){
        fileContent
            << "    // now it is ready and get info about all know routes.\n"
            << "    log_debug( RouteReverse::Manager::getAllReversesRoutes() );\n\n"
        ;
    }
    fileContent
        << "} // end of function \n\n"
        << "} // END namespace\n"
        << "#endif // CORE_INITCOMPONENT_H\n"
    ;

    // --------- witting file(s) ---------
    std::stringstream compInitFileName;
    compInitFileName
        << this->userSession.getSessionPath()
        << "/src/"
        << this->toLower( this->componentNamespace )
        << "/initcomponent.h"
    ;

    log_debug(
        __LINE__
        << " write in: \n"
        << compInitFileName.str()
    );
    std::ofstream compInitFile( compInitFileName.str().c_str() );
    compInitFile << fileContent.str() ;
    compInitFile.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->userSession.getSessionPath() + "/Makefile.tnt" );
    this->makefileData.addHFile(
        "./src/"
        + this->toLower( this->componentNamespace )
        + "/initcomponent.h"
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
