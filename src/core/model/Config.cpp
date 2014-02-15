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

#include <core/model/Config.h>
#include <core/model/TntWebWizardException.h>

#include <cxxtools/jsondeserializer.h>
#include <cxxtools/fileinfo.h>

#include <fstream>
#include <ostream>

namespace Tww {
namespace Core {

Config& Config::it()
{
    static Config theConfig;
    return theConfig;
}

void Config::read(const std::string& filename)
{
    std::string fname;

    if (!filename.empty())
    {
        fname = filename;
    }
    if (cxxtools::FileInfo::exists("tntwebwizard.conf"))
    {
        fname = "tntwebwizard.conf";
    }
    else
    {
        fname = "/etc/tntwebwizard.conf";
    }

    std::ifstream in(fname.c_str());
    if (!in) {
        std::ostringstream errorText;
        errorText << "failed to open configuration file \"";
        errorText  << fname << '"';
//         log_debug( "failed to open configuration file \"" << fname << '"' );
        throw Core::TntWebWizardException( errorText.str() );
    }
    cxxtools::JsonDeserializer deserializer(in);
    deserializer.deserialize(*this);
}

/**
* define how to deserialize the config file
* @arg si serialization info
* @arg config config class
*/
void operator>>= (const cxxtools::SerializationInfo& si, Config& config )
{
    // "si.getMember" with 2 parameters - member name and a reference - fills
    // the reference only if found This makes logging configuration optional.

    si.getMember("logging", config.m_logging);

    // "si.getMember" with one parameter - the member name - throws an
    // exception when the member is not found. Using it makes the setting
    // mandatory.

    si.getMember("appIp")           >>= config.m_appIp;
    si.getMember("appPort")         >>= config.m_appPort;
    si.getMember("sessionRuntime")  >>= config.m_sessionTimeout;
    si.getMember("domain")          >>= config.m_domainName;

}


} // namespace core
} // namespace Tww
