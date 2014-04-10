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

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

#include <map>
#include <vector>
#include <string>


namespace Tww {
namespace Core {

/**
* @class NewModelData This class storage the data of a new model class. It is use
* in the wizard based process when the user create a new component.
*/
class NewModelData {

public:

    NewModelData(
        Tww::Core::UserSession& _userSession,
        Tww::Core::ProjectData& _projectData,
        Tww::Core::MakefileData& _makefileData
    ):
        makefileData( _makefileData ),
        projectData( _projectData ),
        userSession( _userSession ),
        getterFunctions(true),
        isClassConstructor(true),
        isClassDestructor(false),
        setterFunctions(true),
        jsonSerializationSupport(false),
        xmlSerializationSupport(false){};

    // === A ===

    /**
     * Add a file name in the list of *.cpp files.
     */
    void addProperty( std::string _property_name, std::string _property_type ){
        this->propertyMap[ _property_name ] = _property_type;
    };

    // === C ===


    /**
     * This function create the code files of a model.
     */
    void createFiles( );

    // === G ===

    /**
     * Get the name of model class.
     */
     std::string getName(){
        return this->modelName;
     }


    /**
     * Get back a map of model properties. The property name is the map key
     * and the map value is the property type.
     */
    std::map<std::string,std::string>& getPropertyMap(){
        return this->propertyMap;
    }

    /**
     * Get a list of model properties in form "[type] [name]".
     */
    std::vector<std::string> getPropertyList();

    // === I ===

    /**
     * If a class constructor needed than it get value true.
     */
    bool isConstructor() const {
        return this->isClassConstructor;
    }

    /**
     * This function set the value of property isClassConstructor.
     * @arg _newValue If that set true than it will create a class constructor.
     */
    void isConstructor( bool _newValue){
        this->isClassConstructor = _newValue;
    }

    /**
     * If a class destructor needed than it get value true.
     */
    bool isDestructor() const {
        return this->isClassDestructor;
    }

    /**
     * This function set the value of property isClassDestructor.
     * @arg _newValue If that set true than it will create a class Destructor.
     */
    void isDestructor( bool _newValue){
        this->isClassDestructor = _newValue;
    }

    /**
     * If will create getter functions than it get back true.
     */
    bool isGetterFunctions() const {
        return this->getterFunctions;
    }


    /**
     * This function set the value of property getterFunctions.
     * @arg _newValue If that set true than it will create getter functions.
     */
    void isGetterFunctions( bool _newValue) {
        this->getterFunctions = _newValue;
    }

    /**
     * If json serialization support needed than it get value true.
     */
    bool isJsonSerializationSupported() const {
        return this->jsonSerializationSupport;
    }

    /**
     * This function set the value of property jsonSerializationSupport.
     * @arg _newValue If this value true than it will create a class with
     * json serialization support.
     */
    void isJsonSerializationSupported( bool _newValue ) {
        this->jsonSerializationSupport = _newValue;
    }

    /**
     * This function set the value of property setterFunctions.
     * @arg _newValue If that set true than it will create getter functions.
     */
    void isSetterFunctions( bool _newValue) {
        this->setterFunctions = _newValue;
    }

    /**
     * If will create setter functions than it get back true.
     */
    bool isSetterFunctions() const {
        return this->setterFunctions;
    }

    /**
     * If xml serialization support needed than it get value true.
     */
    bool isXmlSerializationSupported() const {
        return this->xmlSerializationSupport;
    }

    /**
     * This function set the value of property xmlSerializationSupport.
     * @arg _newValue If this value true than it will create a class with
     * xml serialization support.
     */
    void isXmlSerializationSupported( bool _newValue ) {
        this->xmlSerializationSupport = _newValue;
    }
    // === S ===

    /**
     * Set the name of the new model.
     */
    void setName( std::string _name ){
        this->modelName = _name;
    }

    /**
     * Set the name of namespace.
     */
    void setNamespace( std::string _name ){
        this->componentNamespace = _name;
    }


private:

    /**
     * Represent the makefile data.
     */
    Tww::Core::MakefileData& makefileData;

    /**
     * Class with project data.
     */
    Tww::Core::ProjectData& projectData;

    /**
     * Session information.
     */
    Tww::Core::UserSession& userSession;

    /**
     * If this value true than it will create getter functions.
     */
    bool getterFunctions;

    /**
     * If this value true than it will create a class constructor.
     */
    bool isClassConstructor;

    /**
     * If this value true than it will create a class destructor.
     */
    bool isClassDestructor;

    /**
     * The name of the model class.
     */
    std::string modelName;

    /**
     * A map of model properties
     */
    std::map<std::string,std::string> propertyMap;


    /**
     * The namespace of the new component.
     */
    std::string componentNamespace;


    /**
     * If this value true than it will create setter functions.
     */
    bool setterFunctions;

    /**
     * If this value true than it will create a class with json  serialization
     * support.
     */
    bool jsonSerializationSupport;

    /**
     * If this value true than it will create a class with xml  serialization
     * support.
     */
    bool xmlSerializationSupport;

    // === FUNCTIONS ===

    /**
     * This function create the implementation code file (".cpp") of a model.
     */
    void createCppFile();

    /**
     * This function create the header code file (".h") of a model.
     */
    void createHFile( );


    /**
     * Convert stings to lower-case.
     */
    std::string toLower( std::string _mixedString );

    /**
     * This function change all character in upper-case and get it back.
     */
    std::string toUpper( std::string _mixedString );

    /**
     * Do the same like toUpper function but use cxxtools lib.
     */
    std::string cxxToUpper( std::string _mixedString );

};

} // namespace Core
} // namespace Tww

#endif
