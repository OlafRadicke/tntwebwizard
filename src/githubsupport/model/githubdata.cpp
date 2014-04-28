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

#include <githubsupport/model/githubdata.h>
#include <core/model/TntWebWizardException.h>

#include <tntdb/connect.h>
#include <tntdb/transaction.h>
#include <tntdb/statement.h>

#include <string>
#include <cxxtools/log.h>

namespace GithubSupport {

log_define("GithubSupport.GithubData")

void GithubData::gitClone() {
    log_debug("gitCheckout"  );
    std::ostringstream sysCommand;
    std::ostringstream errorText;

    sysCommand
        << "git clone "
        <<  this->downloadUrl << " "
        <<  this->userSession.getSessionPath()
        << "/"
    ;

    log_debug( "[" << __LINE__ << "] command: " << sysCommand.str() );
    int returncode = system( sysCommand.str().c_str() );
    log_debug( "[" << __LINE__ << "]The value returned was: " << returncode);
    if ( returncode != 0 ) {
        errorText
            << "Download file is Failed: \""
            << sysCommand.str()
        ;
        throw Tww::Core::TntWebWizardException( errorText.str() );
    }
    return;
}
} // and of namespace GithubSupport
