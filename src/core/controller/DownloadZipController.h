/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2014
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

#ifndef CORE_DOWNLOADZIPCONTROLLER_H
#define CORE_DOWNLOADZIPCONTROLLER_H

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include <string>

namespace Tww {
namespace Core {

/**
* @class DownloadZipController This class is the controller of
* the Site core_download_zip.
*/
class DownloadZipController {

public:

    DownloadZipController(
        Tww::Core::UserSession& _userSession,
        Tww::Core::ProjectData& _projectData,
        Tww::Core::MakefileData& _makefileData
    ):
        makefileData( _makefileData ),
        projectData( _projectData ),
        userSession( _userSession )
        {};


    /**
     * remove the the temporary zip file.
     */
    void cleanUp();

    /**
     * This function remove the (old) generated zip file.
     */
    void downloadZipController();

    /**
     * Get the path to the generated zip file.
     */
    std::string getZipPath(){ return this->zipPath; };

    /**
     * This function started generating zip file. In the zip file is
     * the complied generated project (files). If no project files
     * created than the zip is empties.
     */
    void worker (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );

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
     * The path and name of a generated zip file.
     */
    std::string zipPath;

};


} // namespace Core
} // namespace Tww

#endif
