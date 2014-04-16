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

#ifndef FLASHMESSAGES_MESSAGESDATA_H
#define FLASHMESSAGES_MESSAGESDATA_H

#include <tnt/httprequest.h>

#include <string>


namespace FlashMessages {


/**
* This class represent a data set of a flash messages.
**/
class MessageData {

public:

    MessageData ( ):
        feedback(""),
        warning(false);

    /**
     * If this variable value not empty than it is a message for the
     * user (target for display in the web user interface).
     */
    std::string feedback;

    /**
     * If this set true than the feeback text get a warning css stile.
     */
    bool warning;

};


} // namespace

#endif
