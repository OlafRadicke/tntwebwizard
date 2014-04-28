/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2014
* @copyright GNU Affero General Public License
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

#include <core/model/Config.h>
#include <core/initcomponent.h>

#include <formtoken/initcomponent.h>
#include <githubsupport/initcomponent.h>
#include <routereverse/initcomponent.h>

#include <tnt/tntnet.h>
#include <tnt/configurator.h>
#include <cxxtools/log.h>
#include <cxxtools/directory.h>

#include <string>
#include <stdlib.h>



log_define("main")

int main ( int argc, char* argv[] )
{
    try
    {

        Tww::Core::Config& config = Tww::Core::Config::it();
        config.read();

        log_init( config.logging() );

        if ( cxxtools::Directory::exists( "/tmp/tntwebwizard/" ) ) {
            system("rm -Rf /tmp/tntwebwizard/");
        }

        // Init Application Server
        tnt::Tntnet app;
        tnt::Configurator tntConfigurator( app );
        tntConfigurator.setSessionTimeout ( config.sessionTimeout() );
        app.listen( config.appIp(), config.appPort() );

        // init comonent parts
        FormToken::initcomponent( app );
        GithubSupport::initcomponent( app );
        RouteReverse::initcomponent( app );
        Tww::Core::initcomponent( app );


        std::cout << "tntwebwizard is started and run on http://" << config.appIp()
            << ":" <<  config.appPort() << "/" << std::endl;
        log_info("starting tntwebwizard");
        log_info(
            "tntwebwizard is started and run on http://" <<  config.appIp() \
            << ":" <<  config.appPort() << "/"
        );

        app.run();
    } catch ( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

