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

#ifndef CORE_NEWMODELDATA_H
#define CORE_NEWMODELDATA_H

#include <map>
#include <vector>
#include <string>


namespace Tww {
namespace Core {

/**
* @class NewModel This class storage the data of a new model class. It is use
* in the wizard based process when the user create a new component.
*/
class NewModelData {

public:

    NewModelData():
        modelName("rename_me"){};

    // === A ===

    /**
     * Add a file name in the list of *.cpp files.
     */
    void addProperty( std::string _property_name, std::string _property_type ){
        this->propertyMap[ _property_name ] = _property_type;
    };


    // === G ===

    /**
     * Get the name of model class.
     */
     std::string getName(){
        return this->modelName;
     }


    /**
     * Get a list of model properties in form "[type] [name]".
     */
    std::vector<std::string> getPropertyList();

    // === S ===

    /**
     * Set the name of the new model.
     */
    void setName( std::string _name ){
        this->modelName = _name;
    }


private:

    /**
     * The name of the model class.
     */
    std::string modelName;

    /**
     * A map of model properties
     */
    std::map<std::string,std::string> propertyMap;

};

} // namespace Core
} // namespace Tww

#endif
