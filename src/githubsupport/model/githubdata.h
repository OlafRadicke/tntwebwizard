/*****************************************************************************
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

*****************************************************************************/

#ifndef GITHUBSUPPORT_GITHUBDATA_H
#define GITHUBSUPPORT_GITHUBDATA_H

#include <string>

namespace GithubSupport {

/**
* @class GithubData This class storage the data for download existing code
* from GitHub.
*/
class GithubData {

public:
    /**
     * @todo need a comment for constructor.
     */
    GithubData():
        downloadUrl("https://github.com/OlafRadicke/tntwebwizard.git"){};

    /**
     * Get the url from github sources.
     * @return
     */
     const std::string get_downloadUrl() const {
        return this->downloadUrl;
    }

    /**
     * Set the url from github sources.
     * @arg _newValue new url value.
     */
    void set_downloadUrl( std::string _newValue ){
        this->downloadUrl = _newValue;
    }

    /**
     * This function make a git checkout with the url from property  downloadUrl.
     */
     bool gitCheckout();

private:

   /**
    * @todo need a comment.
    */
    std::string downloadUrl;

}; // and of class GithubData
} // and of namespace GithubSupport
#endif
