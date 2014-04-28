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
    tnt::QueryParams& qparam
){
    log_debug("worker()" );

    if ( qparam.arg<bool>("form_submit_button") ) {
        this->githubdata.set_downloadUrl( qparam.arg<std::string>("form_downloadUrl") );
        this->githubdata.gitClone();
        this->flashmessage.feedback="Clone project data is ready.";
        this->flashmessage.warning = false;
    }
    return;
}

} // namespace
