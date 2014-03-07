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

#ifndef CORE_BASICPROJECTDATACONTROLLER_H
#define CORE_BASICPROJECTDATACONTROLLER_H

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include <string>

namespace Tww {
namespace Core {

/**
* @class BasicProjectDataController This class is the controller of the
* Site basic_project_data.
*/
class BasicProjectDataController {

public:

    BasicProjectDataController(
        Tww::Core::UserSession& _userSession,
        Tww::Core::ProjectData& _projectData,
        Tww::Core::MakefileData& _makefileData
    ):
        warning(false),
        makefileData( _makefileData ),
        projectData( _projectData ),
        userSession( _userSession )
        {};

    void worker (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );

    std::string feedback;

    /**
     * If this set true than the feeback text get a warning css stile.
     */
    bool warning;

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
     * Assume a licence from a template.
     */
    void assumeLicence( const std::string& _licence_template );

    /**
     * This function read web form entires and assume in the
     * property makefileData and projectData but without saving.
     */
    void formDataAssume ( tnt::QueryParams& qparam );

};


} // namespace core
} // namespace Tww

#endif
