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

namespace Tww {
namespace Core {

log_define("Core.NewModelData")

// === A ===



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



// === W ===




} // namespace core
} // namespace Tww
