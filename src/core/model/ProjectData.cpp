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

#include <core/model/ProjectData.h>
#include <core/model/TntWebWizardException.h>

#include <cxxtools/fileinfo.h>
#include <cxxtools/jsondeserializer.h>
#include <cxxtools/jsonserializer.h>
#include <cxxtools/log.h>

#include <fstream>
#include <ostream>

namespace Tww {
namespace Core {

log_define("Core.ProjectData")


void ProjectData::read(const std::string& filename)
{
    std::string fname;

    if (!filename.empty())
    {
        fname = filename;
    }
    if (cxxtools::FileInfo::exists("tntwebwizard.pro"))
    {
        fname = "tntwebwizard.pro";
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

std::string ProjectData::getJson( ) {
    std::string json_text;
    log_debug( "getJsonExport ");

    try
    {
        std::stringstream sstream;
        cxxtools::JsonSerializer serializer( sstream );
        // this makes it just nice to read
        serializer.beautify(true);
        serializer.serialize( *this ).finish();
        json_text = sstream.str();

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return json_text;
}


void operator>>= (const cxxtools::SerializationInfo& si, ProjectData& projektData )
{
    si.getMember("project_name") >>= projektData.projectName;
    si.getMember("wizard_version") >>= projektData.wizardVersion;
}

void operator<<= ( cxxtools::SerializationInfo& si, const ProjectData& projektData )
{
    si.addMember("project_name") <<= projektData.getProjectName();
    si.addMember("wizard_version") <<= projektData.getWizardVersion();
}


} // namespace core
} // namespace Tww
