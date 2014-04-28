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

#ifndef CORE_NEWCONTROLLERDATA_H
#define CORE_NEWCONTROLLERDATA_H

#include <core/model/MakefileData.h>
#include <core/model/NewModelData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

#include <map>
#include <string>

namespace Tww {
namespace Core {

/**
* @class NewControllerData This class storage the data of a new controller file.
* It is use in the wizard based process when the user create a new component.
*/
class NewControllerData {

public:

    NewControllerData(
        Tww::Core::UserSession& _userSession,
        Tww::Core::ProjectData& _projectData,
        Tww::Core::MakefileData& _makefileData,
        Tww::Core::NewModelData& _newModelData
    ):
        makefileData( _makefileData ),
        projectData( _projectData ),
        userSession( _userSession ),
        newModelData( _newModelData ),
        controllerName("NewController"),
        formSupport(false){};

    // === C ===

    /**
     * This function create the *.cpp and *.h view file of the controller class.
     */
    void createFiles();


    // === G ===

    /**
     * Get the name of model class.
     */
     std::string getName(){
        return controllerName;
     }

    // === I ===

    /**
     * If a generated web form needed than it get value true.
     */
    bool isFormSupport() const {
        return this->formSupport;
    }

    /**
     * This function set the value of property formSupport.
     * @arg _newValue If that value set true than it will generating a web form.
     */
    void isFormSupport( bool _newValue){
        this->formSupport = _newValue;
    }

    // === S ===

    /**
     * Set the name of the controller class.
     */
    void setName( std::string _name ){
        this->controllerName = _name;
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
     * Class with information about the model in the new component.
     */
    Tww::Core::NewModelData& newModelData;

    /**
     * The namespace of the new component.
     */
    std::string componentNamespace;

    /**
     * The name of the controller class.
     */
    std::string controllerName;

    /**
     * If this value true than it will create a web form.
     */
    bool formSupport;

    // === FUNCTIONS ===

    /**
     * This function create the implementation code file (".cpp") of a model.
     */
    void createCppFile();

    /**
     * This function create the header code file (".h") of a model.
     */
    void createHFile();


    /**
     * Convert stings to lower-case.
     */
    std::string toLower( std::string _mixedString );

    /**
     * This function change all character in upper-case and get it back.
     */
    std::string toUpper( std::string _mixedString );


}; // end class

} // namespace Core
} // namespace Tww

#endif
