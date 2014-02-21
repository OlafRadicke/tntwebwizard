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

#include <cxxtools/jsondeserializer.h>
#include <cxxtools/fileinfo.h>

#include <fstream>
#include <ostream>

namespace Tww {
namespace Core {

ProjectData& ProjectData::it()
{
    static ProjectData theProjectData;
    return theProjectData;
}

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

std::string ProjectData::getJsonExport( const unsigned long userID ) {
    std::string json_text;
    log_debug( "getJsonExport for userID: " << userID );

    QuoteExportContainer quoteContainer;
    quoteContainer.allUserQuotes = ProjectData::getAllQuoteOfUser( userID );
    try
    {
        std::stringstream sstream;
        cxxtools::JsonSerializer serializer( sstream );
        // this makes it just nice to read
        serializer.beautify(true);
        serializer.serialize( quoteContainer ).finish();
        json_text = sstream.str();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return json_text;
}


/**
* define how to deserialize the project data file
* @arg si serialization info
* @arg projektData project data class
*/
void operator>>= (const cxxtools::SerializationInfo& si, ProjectData& projektData )
{
    si.getMember("projectName")     >>= projektData.projectName;
}

/**
* define how to serialize the ProjectData
* @arg si serialization info
* @arg ProjectData project data class
*/
void operator<<= ( cxxtools::SerializationInfo& si, const ProjectData& projektData )
{
    si.addMember("projectName") <<= projektData.projectName();
}


} // namespace core
} // namespace Tww
