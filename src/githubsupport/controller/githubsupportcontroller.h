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

#ifndef GITHUBSUPPORT_GITHUBSUPPORTCONTROLLER_H
#define GITHUBSUPPORT_GITHUBSUPPORTCONTROLLER_H

#include <githubsupport/model/githubdata.h>
#include <flashmessages/model/messagedata.h>
#include <core/model/UserSession.h>
#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <string>

namespace GithubSupport {

/**
* @class GithubSupportController This class is the controller of ...
* @todo fill this with information!
*/
class GithubSupportController {

 public:

    /**
    * Thisis the class constructor...
    * @arg _githubdata This is the model...
    * @todo fill this with information!
    */
    GithubSupportController (
        Tww::Core::UserSession& _userSession,
        GithubData _githubdata,
        FlashMessages::MessageData  _flashmessage
    ):
        githubdata( _githubdata ),
        flashmessage( _flashmessage ),
        userSession( _userSession ){}

   /**
    * This function is call from the view when it comes a client request.
    * @arg request
    * @arg reply
    * @arg qparam
    * @todo fill this with information!
    */
    void worker (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam,
        Tww::Core::ProjectData& _projectData,
        Tww::Core::MakefileData& _makefileData
    );

private:

    /**
     * Data about github sources.
     */
    GithubData githubdata;

    FlashMessages::MessageData  flashmessage;

    /**
     * Session information.
     */
    Tww::Core::UserSession& userSession;


}; //end class
} // namespace
#endif
