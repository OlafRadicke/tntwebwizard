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

#include <core/model/NewControllerData.h>
#include <core/model/TntWebWizardException.h>

#include <cxxtools/directory.h>
#include <cxxtools/log.h>

#include <fstream>
#include <ostream>
#include <sstream>

#include <string>
#include <locale>


namespace Tww {
namespace Core {

log_define("Core.NewControllerData")
// === C ===


void NewControllerData::createFiles(){
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
        << "/controller/"
    ;
    if ( !cxxtools::Directory::exists( compDirName.str() ) ) {
        cxxtools::Directory::create( compDirName.str() );
    }
    this->createCppFile();
    this->createHFile();
}

void NewControllerData::createCppFile(){
    std::stringstream fileContent;
    std::map<std::string,std::string>& propertyMap =
        this->newModelData.getPropertyMap();
    fileContent
        << "/* \n"
        << this->projectData.getSourceCodeHeader()
        << "\n*/ \n\n"
        << "#include <" <<  this->toLower( this->componentNamespace )
        << "/controller/" << this->toLower( this->controllerName ) << ".h>\n\n"
    ;
    if( this->projectData.isFlashMessagesSupport() == true ){
        fileContent
            << "#include <flashmessages/model/messagedata.h> \n"
        ;
    }
    fileContent
        << "#include <tnt/httprequest.h>\n"
        << "#include <tnt/httpreply.h>\n"
    ;
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::string") {
            fileContent  << "#include <string>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::vector") {
            fileContent  << "#include <vector>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::map") {
            fileContent  << "#include <map>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::list") {
            fileContent  << "#include <list>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::stringstream" ) {
            fileContent  << "#include <sstream>\n";
            break;
        }
    }
    if( this->componentNamespace != "" ){
        fileContent  << "\nnamespace " << this->componentNamespace << " {\n\n";
    }
    fileContent
        << "void " << this->controllerName << "::worker ( \n"
        << "    tnt::HttpRequest& request, \n"
        << "    tnt::HttpReply& reply, \n"
        << "    tnt::QueryParams& qparam \n"
        << "){\n"
    ;

    if ( this->formSupport == true ) {
        fileContent
            << "    if ( qparam.arg<bool>(\"form_submit_button\") ) {\n"
        ;
        for (
            std::map<std::string,std::string>::iterator it2=propertyMap.begin();
            it2!=propertyMap.end();
            ++it2
        ){
            fileContent
                << "        " << this->toLower( this->newModelData.getName() )
                << ".set_" << it2->first << "( qparam.arg<" << it2->second
                << ">( \"form_" << it2->first << "\" ) );\n"
            ;
        }
        if ( this->projectData.isTntDB() == true ){
            fileContent
                << "        this->" << this->toLower( this->newModelData.getName() ) << ".saveAsNew();\n"
            ;
        } else {
            fileContent
                << "        /// @todo modified this function call\n"
                << "        /// this->" << this->toLower( this->newModelData.getName() ) << ".save();\n"
            ;
        }
        if( this->projectData.isFlashMessagesSupport() == true ){
            fileContent
                << "        this->flashmessage.feedback=\"Data is all ready submit\";\n"
                << "        this->flashmessage.warning = false;\n"
            ;
        }
        fileContent
            << "    }\n"
        ;
    }
    fileContent
        << "    return;\n"
        << "}\n\n"
        << "} // namespace  \n"
    ;

    // --------- witting file(s) ---------
    std::stringstream compControllerCppFileName;
    compControllerCppFileName
        << this->userSession.getSessionPath()
        << "/src/"
        << this->toLower( this->componentNamespace )
        << "/controller/"
        << this->toLower( this->controllerName )
        << ".cpp"
    ;

    log_debug(
        __LINE__
        << " write in: \n"
        << compControllerCppFileName.str()
    );
    std::ofstream compCppFile( compControllerCppFileName.str().c_str() );
    compCppFile << fileContent.str() ;
    compCppFile.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->userSession.getSessionPath() + "/Makefile.tnt" );
    this->makefileData.addCppFile(
        "./src/"
        + this->toLower( this->componentNamespace )
        + "/controller/"
        + this->toLower( this->controllerName )
        + ".cpp"
    );
    this->makefileData.write( this->userSession.getSessionPath() + "/Makefile.tnt" );
}

void NewControllerData::createHFile(){
    log_debug("createHFile()" );
    std::map<std::string,std::string>& propertyMap =
        this->newModelData.getPropertyMap();

    // Create file content
    std::stringstream fileContent;
    fileContent
        << "/* \n"
        << this->projectData.getSourceCodeHeader()
        << "\n*/ \n\n"
        << "#ifndef " << toUpper( this->componentNamespace )
        << "_" << toUpper( this->controllerName ) << "_H \n"
        << "#define " << toUpper( this->componentNamespace )
        << "_" << toUpper( this->controllerName ) << "_H \n\n"
        << "#include <" <<  this->toLower( this->componentNamespace ) << "/model/"
        << this->toLower( this->newModelData.getName() ) << ".h>\n"
    ;
    if( this->projectData.isFlashMessagesSupport() == true ){
        fileContent
            << "#include <flashmessages/model/messagedata.h> \n"
        ;
    }
    fileContent
        << "#include <tnt/httprequest.h>\n"
        << "#include <tnt/httpreply.h>\n"
    ;
    if ( this->projectData.isCxxtoolsLoging( ) ){
        fileContent  << "#include <cxxtools/log.h>\n";
    }
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::string") {
            fileContent  << "#include <string>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::vector") {
            fileContent  << "#include <vector>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::map") {
            fileContent  << "#include <map>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::list") {
            fileContent  << "#include <list>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=propertyMap.begin();
        it!=propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::stringstream" ) {
            fileContent  << "#include <sstream>\n";
            break;
        }
    }

    if( this->componentNamespace != "" ){
        fileContent  << "\nnamespace " << this->componentNamespace << " {\n\n";
    }
    if ( this->projectData.isCxxtoolsLoging( ) ){
        fileContent
            << "log_define(\"" << this->componentNamespace << "."
            << this->controllerName << "\")\n\n"
        ;
    }

    if( this->projectData.isDoxygenTemplates( ) == true ){
        fileContent
            << "/** \n"
            << "* @class " << this->controllerName << " This class is the controller of ... \n"
            << "* @todo fill this with information!\n"
            << "*/\n"
        ;
    }
    fileContent << "class " << this->controllerName << " {\n\n"
        << " public: \n\n"
    ;

    if( this->projectData.isDoxygenTemplates( ) == true ){
        fileContent
            << "    /** \n"
            << "    * Thisis the class constructor... \n"
            << "    * @arg _" << this->toLower( this->newModelData.getName() ) << " This is the model...\n"
            << "    * @todo fill this with information!\n"
            << "    */\n"
        ;
    }
    fileContent
        << "    " << this->controllerName << " ( \n"
        << "        " << this->newModelData.getName() << " _"
        << this->toLower( this->newModelData.getName() )
    ;
    if( this->projectData.isFlashMessagesSupport() == true ){
        fileContent
            << ",\n"
            << "        FlashMessages::MessageData  _flashmessage"
        ;
    }


    fileContent
        << "\n): \n"
        << "        " << this->toLower( this->newModelData.getName() )
        << "( _" << this->toLower( this->newModelData.getName() )
        << " )"
    ;
    if( this->projectData.isFlashMessagesSupport() == true ){
        fileContent
            << ",\n"
            << "        flashmessage( _flashmessage )"
        ;
    }
    fileContent
        << "{}\n\n"
    ;
    if( this->projectData.isDoxygenTemplates( ) == true ){
        fileContent
            << "   /** \n"
            << "    * This function is call from the view when it comes a client request. \n"
            << "    * @arg request \n"
            << "    * @arg reply \n"
            << "    * @arg qparam \n"
            << "    * @todo fill this with information!\n"
            << "    */ \n"
        ;
    }
    fileContent
        << "    void worker ( \n"
        << "        tnt::HttpRequest& request, \n"
        << "        tnt::HttpReply& reply, \n"
        << "        tnt::QueryParams& qparam \n"
        << "    ); \n\n"
        << "private: \n\n"
    ;
    if( this->projectData.isDoxygenTemplates( ) == true ){
        fileContent
            << "   /** \n"
            << "    * @todo fill this with information. \n"
            << "    */ \n"
        ;
    }
    fileContent
        << "    " << this->newModelData.getName() << " "
        << this->toLower( this->newModelData.getName() ) << ";\n"
    ;

    if( this->projectData.isFlashMessagesSupport() == true ){
        if( this->projectData.isDoxygenTemplates( ) == true ){
            fileContent
                << "   /** \n"
                << "    * Flash message class. \n"
                << "    */ \n"
            ;
        }
        fileContent
            << "    FlashMessages::MessageData  flashmessage; \n"
        ;
    }
    fileContent
        << "\n}; //end class\n"
        << "} // namespace  \n"
        << "#endif \n"
    ;

    // --------- witting file(s) ---------
    std::stringstream compControllerHFileName;
    compControllerHFileName
        << this->userSession.getSessionPath()
        << "/src/"
        << this->toLower( this->componentNamespace )
        << "/controller/"
        << this->toLower( this->controllerName )
        << ".h"
    ;

    log_debug(
        __LINE__
        << " write in: \n"
        << compControllerHFileName.str()
    );
    std::ofstream compHFile( compControllerHFileName.str().c_str() );
    compHFile << fileContent.str() ;
    compHFile.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->userSession.getSessionPath() + "/Makefile.tnt" );
    this->makefileData.addHFile(
        "./src/"
        + this->toLower( this->componentNamespace )
        + "/controller/"
        + this->toLower( this->controllerName )
        + ".h"
    );
    this->makefileData.write( this->userSession.getSessionPath() + "/Makefile.tnt" );
}




// === T ===

std::string NewControllerData::toLower( std::string _mixedString ){
    std::ostringstream upperString;
//     std::locale loc("de_DE.UTF8");
    std::locale loc;
    for (std::string::size_type i=0; i<_mixedString.length(); ++i){
        upperString << std::tolower(_mixedString[i],loc);
    }
    return upperString.str();
}

std::string NewControllerData::toUpper( std::string _mixedString ){
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
