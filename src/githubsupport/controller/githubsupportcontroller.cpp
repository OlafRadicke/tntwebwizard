/*
Copyright (C) <year>  <name of author>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or later
version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <githubsupport/controller/githubsupportcontroller.h>

#include <core/model/TntWebWizardException.h>
#include <flashmessages/model/messagedata.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>
#include <string>

namespace GithubSupport {

log_define("GithubSupport.GithubSupportController")

void GithubSupportController::worker (
    tnt::HttpRequest& request,
    tnt::HttpReply& reply,
    tnt::QueryParams& qparam,
    Tww::Core::ProjectData& _projectData,
    Tww::Core::MakefileData& _makefileData
){
    log_debug("worker()" );

    if ( qparam.arg<bool>("form_submit_button") ) {

        std::string command = "rm -Rf " + this->userSession.getSessionPath() + "/";
        log_debug( "do command: " << command );
        system( command.c_str() );
        // Create new...
        command = "mkdir " + this->userSession.getSessionPath() + "/";
        log_debug( "do command: " << command );
        // I wish good luck and all the best...!
        system( command.c_str() );


        this->githubdata.set_downloadUrl(
            qparam.arg<std::string>("form_downloadUrl")
        );
        try {
            this->githubdata.gitClone();
        } catch ( Tww::Core::TntWebWizardException& tww_exception ) {
            this->flashmessage.feedback=
                "Can't clone project data! Is the project all ready cloned? ";
            this->flashmessage.feedback += tww_exception.what();
            this->flashmessage.warning = true;
            return;
        } catch ( ... ) {
            this->flashmessage.feedback=
                "Can't clone project data! Is the project all ready cloned? Or make a reset before?";
            this->flashmessage.warning = true;
            return;
        }

        // read and reset project configuration...
        _projectData = Tww::Core::ProjectData();
        _makefileData = Tww::Core::MakefileData();

        this->flashmessage.feedback="Clone project data is ready.";
        this->flashmessage.warning = false;
    }
    return;
}

} // namespace
