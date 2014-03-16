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

#ifndef CORE_PROJECTRESETCONTROLLER_H
#define CORE_PROJECTRESETCONTROLLER_H

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include <string>

namespace Tww {
namespace Core {

/**
* @class ProjectResetController This class is the controller of the
* Site core_projectreset. In this site the user can reset the project data.
*/
class ProjectResetController {

public:

    ProjectResetController(
        Tww::Core::UserSession& _userSession,
        Tww::Core::ProjectData& _projectData,
        Tww::Core::MakefileData& _makefileData
    ):
        warning(false),
        makefileData( _makefileData ),
        projectData( _projectData ),
        userSession( _userSession )
        {};

    /**
     * This function is called when the site ist (re-)loaded.
     */
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
     * Get the path to file "./tntwebwizard.pro".
     */
    std::string getProjectFilePath();

    /**
     * Get the path to file "./Makefile.tnt".
     */
    std::string getMakefilePath();

};


} // namespace core
} // namespace Tww

#endif
