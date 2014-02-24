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

#include <core/model/MakefileData.h>
#include <core/model/TntWebWizardException.h>

#include <cxxtools/fileinfo.h>
#include <cxxtools/jsondeserializer.h>
#include <cxxtools/jsonserializer.h>
#include <cxxtools/log.h>

#include <fstream>
#include <ostream>

namespace Tww {
namespace Core {

log_define("Core.MakefileData")


void MakefileData::read(const std::string& filename)
{
    std::string fname;

    if (!filename.empty())
    {
        fname = filename;
    }
    if (cxxtools::FileInfo::exists("Makefile.tnt"))
    {
        fname = "Makefile.tnt";
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

std::string MakefileData::getJson( ) {
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


void operator>>= (const cxxtools::SerializationInfo& si, MakefileData& makefileData )
{
    si.getMember("tntmakeVersion") >>= makefileData.tntmakeVersion;
    si.getMember("binName") >>= makefileData.binName;
    si.getMember("cppCompiler") >>= makefileData.cppCompiler;
    si.getMember("cppFiles") >>= makefileData.cppFiles;
    si.getMember("hFiles") >>= makefileData.hFiles;
    si.getMember("cppFlags") >>= makefileData.cppFlags;
    si.getMember("cppLinkerFlags") >>= makefileData.cppLinkerFlags;
    si.getMember("ecppCompiler") >>= makefileData.ecppCompiler;
    si.getMember("ecppFlags") >>= makefileData.ecppFlags;
    si.getMember("ecppFiles") >>= makefileData.ecppFiles;
    si.getMember("resourcesFiles") >>= makefileData.resourcesFiles;
    si.getMember("buildDir") >>= makefileData.buildDir;
}

void operator<<= ( cxxtools::SerializationInfo& si, const MakefileData& makefileData )
{
    si.addMember("tntmakeVersion") <<= makefileData.getTntmakeVersion();
    si.addMember("binName") <<= makefileData.getBinName();
    si.addMember("cppCompiler") <<= makefileData.getCppCompiler();
    si.addMember("cppFiles") <<= makefileData.getCppFiles();
    si.addMember("hFiles") <<= makefileData.getHFiles();
    si.addMember("cppFlags") <<= makefileData.getCppFlags();
    si.addMember("cppLinkerFlags") <<= makefileData.getCppLinkerFlags();
    si.addMember("ecppCompiler") <<= makefileData.getEcppCompiler();
    si.addMember("ecppFlags") <<= makefileData.getEcppFlags();
    si.addMember("ecppFiles") <<= makefileData.getEcppFiles();
    si.addMember("resourcesFiles") <<= makefileData.getResourcesFiles();
    si.addMember("buildDir") <<= makefileData.getBuildDir();
}


} // namespace core
} // namespace Tww
