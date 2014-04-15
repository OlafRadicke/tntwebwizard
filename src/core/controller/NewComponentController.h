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

#ifndef CORE_NEWCOMPONENT_H
#define CORE_NEWCOMPONENT_H

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>
#include <core/model/NewControllerData.h>
#include <core/model/NewModelData.h>
#include <core/model/NewViewData.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include <string>
#include <map>
#include <vector>

namespace Tww {
namespace Core {

/**
* @class NewComponentController This class is the controller of the
* Site basic_newcomponent.
*/
class NewComponentController {

public:

    NewComponentController(
        Tww::Core::UserSession& _userSession,
        Tww::Core::ProjectData& _projectData,
        Tww::Core::MakefileData& _makefileData,
        Tww::Core::NewModelData& _newModelData,
        Tww::Core::NewViewData& _newViewData,
        Tww::Core::NewControllerData& _newControllerData
    ):
        warning(false),
        controllerName("NewConroller"),
        makefileData( _makefileData ),
        newControllerData( _newControllerData ),
        newModelData( _newModelData ),
        newViewData( _newViewData ),
        projectData( _projectData ),
        userSession( _userSession )
        {};

    // === A ===


    // === S ===



    // === W ===

   /**
    * This function is call from the view when it comes a client request.
    */
    void worker (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );

    /**
     * Feedback dialogue text
     */
    std::string feedback;

    /**
     * If this set true than the feeback text get a warning css stile.
     */
    bool warning;

    /**
     * Get name of controller class.
     */
    std::string getControllerName(){
        return this->controllerName;
    }

     /**
     * Get the namespace name.
     */
     std::string getNameSpace(){
         return this->nameSpace;
     }



private:

    /**
     * The name of the controller class.
     */
    std::string controllerName;

    /**
     * The namespace of the new componet.
     */
    std::string nameSpace;


    /**
     * Represent the makefile data.
     */
    Tww::Core::MakefileData& makefileData;

    /**
     * This class storage the information about the controller class in
     * the new component.
     */
    Tww::Core::NewControllerData& newControllerData;

    /**
     * This class storage the information about the model class in
     * the new component.
     */
    Tww::Core::NewModelData& newModelData;

    /**
     * This class storage the information about the ecpp view file from
     * a new component.
     */
    Tww::Core::NewViewData& newViewData;


    /**
     * Class with project data.
     */
    Tww::Core::ProjectData& projectData;

    /**
     * Session information.
     */
    Tww::Core::UserSession& userSession;

    // === FUNCTIONS ===

    // === G ===

    /**
     * Get the path to file "./Makefile.tnt".
     */
    std::string getMakefilePath();

    /**
     * Get the path to file "./tntwebwizard.pro".
     */
    std::string getProjectFilePath();

    // === I ===

    /**
     * Check is the name of the new component all ready in use.
     * If it found than it get a "true" value.
     */
    bool isComponentFounded( std::string _newCompName );

    /**
     * Some plausibility data checks before start working.
     */
    bool isProjectFounded( );

    /**
     * Convert stings to lower-case.
     */
    std::string toLower( std::string _mixedString );

};


} // namespace core
} // namespace Tww

#endif
