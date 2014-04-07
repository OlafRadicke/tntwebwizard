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

#include <core/model/NewModelData.h>
#include <core/model/TntWebWizardException.h>

#include <cxxtools/fileinfo.h>
#include <cxxtools/log.h>

#include <fstream>
#include <ostream>

#include <string>         // std::string
#include <locale>         // std::locale, std::toupper
// #include <algorithm>
#include <cxxtools/utf8codec.h>
#include <cxxtools/string.h>
#include <cxxtools/char.h>


namespace Tww {
namespace Core {

log_define("Core.NewModelData")

// === A ===

// === C ===


void NewModelData::createCppFile(){

    //pass
}

void NewModelData::createFiles( Tww::Core::ProjectData& _projectData ){
    this->createHFile( _projectData );
    this->createCppFile();
}


void NewModelData::createHFile( Tww::Core::ProjectData& _projectData ){
    log_debug("createHFile()" );
    std::ofstream writting_file;
    std::ostringstream fileContent;

    fileContent
        << "/* \n"
        << _projectData.getSourceCodeHeader()
        << "\n*/ \n\n"
        << "#ifndef " << toUpper( this->componentNamespace )
        << "_" << toUpper( this->modelName ) << "_H \n"
        << "#define " << toUpper( this->componentNamespace )
        << "_" << toUpper( this->modelName ) << "_H \n\n"
    ;


    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::string") {
            fileContent  << "#include <string>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::vector") {
            fileContent  << "#include <vector>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::map") {
            fileContent  << "#include <map>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::list") {
            fileContent  << "#include <list>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::stringstream") {
            fileContent  << "#include <sstream>\n";
            break;
        }
    }
    if ( this->serializationSupport == true ){
        fileContent  << "#include <cxxtools/serializationinfo.h>\n";
    }
    if( this->componentNamespace != "" ){
        fileContent  << "namespace " << this->componentNamespace << " {\n\n";
    }
    if( _projectData.isDoxygenTemplates( ) == true ){
        fileContent
            << "/** \n"
            << "* @class " << this->modelName << " This class storage the data of ... \n"
            << "* @todo fill this with information!\n"
            << "*/\n"
        ;
    }
    fileContent
        << "class " << this->modelName << " {\n\n"
        << "public:\n"
    ;

    

    log_debug("isGetterFunctions(): " << this->isGetterFunctions() );
    if ( this->isGetterFunctions() == true){
        log_debug( "this->propertyMap.end(): " << this->propertyMap.size() );
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            std::cout << it->first << " => " << it->second << '\n';
            if ( _projectData.isDoxygenTemplates( ) == true ) {
                fileContent
                    << "    /** \n"
                    << "     * @dodo need a comment. \n"
                    << "     * @return \n"
                    << "     */\n"
                ;
            }
            fileContent
                << "    " << it->second << " get_" << it->first << "(){\n"
                << "        return this->" << it->first << ";\n"
                << "    };\n\n";

        }
    }
    log_debug("isSetterFunctions(): " << this->isSetterFunctions() );
    if ( this->isSetterFunctions() == true){
        log_debug("this->propertyMap.end(): " << this->propertyMap.size() );
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            std::cout << it->first << " => " << it->second << '\n';
            if ( _projectData.isDoxygenTemplates( ) == true ) {
                fileContent
                    << "    /** \n"
                    << "     * @dodo need a comment. \n"
                    << "     * @arg _newValue \n"
                    << "     */\n"
                ;
            }
            fileContent
                << "    " << it->second << " set_" << it->first << "( "
                << it->second << " _newValue ){\n"
                << "        this->" << it->first << " = _newValue;\n"
                << "    };\n\n"
            ;

        }
    }

    fileContent << "private:\n";
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( _projectData.isDoxygenTemplates( ) == true ) {
            fileContent  << "    /** @dodo need a comment. */\n" ;
        }
        fileContent << "    " << it->second << " " << it->first << ";\n\n";

    }

    if( this->componentNamespace != ""){
        fileContent  << "} // and of namespace " << this->componentNamespace << "\n";
    }
    fileContent << "#endif" ;

    log_debug( "\n++++++++++++++++++++++++++++\n" << fileContent.str() << "\n+++++++++++++++++++++++++++\n");

}

// === G ===

std::vector<std::string> NewModelData::getPropertyList(){
    std::vector<std::string> allProperties;
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        allProperties.push_back( it->second + " " + it->first );
    }
    return allProperties;
}

// === O ==



// === R ===

// === U ===

std::string NewModelData::toUpper( std::string _mixedString ){
    std::ostringstream upperString;
//     std::locale loc("de_DE.UTF8");
    std::locale loc;
    for (std::string::size_type i=0; i<_mixedString.length(); ++i){
        upperString << std::toupper(_mixedString[i],loc);
    }
    return upperString.str();
}

std::string NewModelData::cxxToUpper( std::string _mixedString ){
    std::ostringstream upperString;
    cxxtools::String lastLetter;
    cxxtools::String uMixedString = cxxtools::Utf8Codec::decode( _mixedString );
    for ( cxxtools::String::size_type i=0;
            i < uMixedString.length();
            ++i){
        upperString << cxxtools::toupper(uMixedString[i]);
    }
    return upperString.str();
}

// === W ===




} // namespace core
} // namespace Tww
