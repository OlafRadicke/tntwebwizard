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

#ifndef CORE_CREATEAPPLICATIONCORECONTROLLER_H
#define CORE_CREATEAPPLICATIONCORECONTROLLER_H

#include <tnt/ecpp.h>


#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include <string>

namespace Tww {
namespace Core {

class WebApplicationCoreManager;

/**
* @class CreateApplicationCoreController This class is the controller of
* the Site core_createapplicationcore.
*/
class CreateApplicationCoreController : public tnt::EcppComponent{

public:

    CreateApplicationCoreController(
        Tww::Core::UserSession& _userSession,
        Tww::Core::ProjectData& _projectData,
        Tww::Core::MakefileData& _makefileData
    ):
        form_hostname("rename.me"),
        form_host_ipv4("0.0.0.0"),
        form_port_no(10080),
        form_session_timeout(7200),
        warning(false),
        makefileData( _makefileData ),
        projectData( _projectData ),
        userSession( _userSession ),
        EcppComponent("resources")
        {};

   /**
    * This function is call from the view when it comes a client request.
    */
    void worker (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );

    /**
     * If this variable value not empty than it is a message for the
     * user (target for display in the web user interface).
     */
    std::string feedback;

    /**
     * This variable storage the last user form input or the default value
     * for the host name configuration.
     */
    std::string form_hostname;

    /**
     * This variable storage the last user form input or the default value
     * for the port number configuration.
     */
    std::string form_host_ipv4;

    /**
     * This variable storage the last user form input or the default value
     * for the port number configuration.
     */
    int form_port_no;

    /**
     * This variable storage the last user form input or the default value
     * for the session time out configuration.
     */
    int form_session_timeout;

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

    /**
     * Some plausibility data checks before start working.
     */
    bool preChecksOk ( WebApplicationCoreManager& webappManager );

};


} // namespace core
} // namespace Tww

#endif
