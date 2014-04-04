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
        << "_" << toUpper( this->modelName ) << "_H \n"


        << "#endif"
    ;
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
        allProperties.push_back( it->second + "  " + it->first );
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

    for (std::string::size_type i=0; i<_mixedString.length(); ++i)
        upperString << std::toupper(_mixedString[i],loc);
    return upperString.str();
}


// === W ===




} // namespace core
} // namespace Tww
