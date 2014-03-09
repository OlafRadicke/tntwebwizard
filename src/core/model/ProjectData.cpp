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
#include <cxxtools/xml/xmlserializer.h>
#include <cxxtools/xml/xml.h>
#include <cxxtools/log.h>

#include <fstream>
#include <ostream>

namespace Tww {
namespace Core {

log_define("Core.ProjectData")

// === G ===

std::string ProjectData::getJson( ) {
    std::string json_text;
    log_debug( "getJson ");

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

std::string ProjectData::getXml( ) {

    std::string xmlCode;
    log_debug( "getXml ");

    try
    {
        std::stringstream sstream;
        cxxtools::xml::XmlSerializer serializer(sstream);
        sstream << serializer.toString( *this, "projectdata", true );
        xmlCode = sstream.str();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return xmlCode;
}

// === O ===

void operator>>= (const cxxtools::SerializationInfo& si, ProjectData& projektData )
{
    si.getMember("wizard_version")     >>= projektData.wizardVersion;
    si.getMember("project_name")       >>= projektData.projectName;
    si.getMember("source_code_header") >>= projektData.sourceCodeHeader;
    si.getMember("doxygen_templates")  >>= projektData.doxygenTemplates;
    si.getMember("form_token")         >>= projektData.formToken;
    si.getMember("route_reverse")       >>= projektData.routeReverse;
    si.getMember("cxxtools_loging")    >>= projektData.cxxtoolsLoging;

}

void operator<<= ( cxxtools::SerializationInfo& si, const ProjectData& projektData )
{
    si.addMember("wizard_version")     <<= projektData.getWizardVersion( );
    si.addMember("project_name")       <<= projektData.getProjectName( );
    si.addMember("source_code_header") <<= projektData.getSourceCodeHeader( );
    si.addMember("doxygen_templates")  <<= projektData.isDoxygenTemplates( );
    si.addMember("form_token")         <<= projektData.isFormToken( );
    si.addMember("route_reverse")       <<= projektData.isRouteReverse( );
    si.addMember("cxxtools_loging")    <<= projektData.isCxxtoolsLoging( );
}

// === R ===

void ProjectData::read(const std::string& filename)
{
    if ( cxxtools::FileInfo::exists( filename ) )
    {
        std::ifstream in(filename.c_str());
        if (!in) {
            std::ostringstream errorText;
            errorText << "failed to open configuration file \"";
            errorText  << filename << '"';
            throw Core::TntWebWizardException( errorText.str() );
        }
        cxxtools::xml::XmlDeserializer deserializer(in);
        deserializer.deserialize(*this);
    } else {
        log_debug( filename.c_str() << " does not exist");
    }
}

// === W ===

void ProjectData::write(const std::string filename)
{
    // writ config in file...
    std::ofstream out( filename.c_str() );
    cxxtools::xml::XmlSerializer serializer(out);
    serializer.serialize( *this, "projectdata");
    log_debug( "Project configuration data is writed in " << filename );
}


} // namespace core
} // namespace Tww
