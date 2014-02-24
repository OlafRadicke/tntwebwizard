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

#ifndef CORE_MAKEFILEDATA_H
#define CORE_MAKEFILEDATA_H

#include <cxxtools/serializationinfo.h>
#include <vector>
#include <string>


namespace Tww {
namespace Core {

/**
* @class MakefileData This class represent the data of the makefile.
*/
class MakefileData {


    /**
    * define how to deserialize the project data file
    * @arg si serialization info
    * @arg projektData makefile data class
    */
    friend void operator>>= (const cxxtools::SerializationInfo& si, MakefileData& projektData );


    /**
    * define how to serialize the MakefileData class.
    * @arg si serialization info
    * @arg MakefileData makefile data class
    */
    friend void operator<<= ( cxxtools::SerializationInfo& si, const MakefileData& projektData );

public:

    MakefileData(){ }

    // === G ===

    /**
     * Get a export of user quote data in json format.
     * @arg userID Id of a user.
     * @return A json document.
     */
    std::string getJson( );

    /**
     * Get version of tntmake program.
     */
    const int getTntmakeVersion() const
    { return this->tntmakeVersion; }

    /**
     * Get name of binary file.
     */
    const std::string& getBinName() const
    { return this->binName; }

    /**
     * Get name of c++ compiler.
     */
    const std::string& getCppCompiler() const
    { return this->cppCompiler; }

    /**
     * Get list of *.cpp files.
     */
    const std::vector<std::string>& getCppFiles() const
    { return this->cppFiles; }

    /**
     * Get list of *.h files.
     */
    const std::string& getHFiles() const
    { return this->hFiles; }

    /**
     * Get c++ compiler flags.
     */
    const std::string& getCppFlags() const
    { return this->cppFlags; }

    /**
     * Get c++ linker flags.
     */
    const std::string& getCppLinkerFlags() const
    { return this->cppLinkerFlags; }

    /**
     * Get ecpp compiler (name).
     */
    const std::string& getEcppCompiler() const
    { return this->ecppCompiler; }

    /**
     * Get ecpp compiler flags.
     */
    const std::string& getEcppFlags() const
    { return this->ecppFlags; }

    /**
     * Get list of *.ecpp files.
     */
    const std::string& getEcppFiles() const
    { return this->ecppFiles; }

    /**
     * Get list of static contend files.
     */
    const std::string& getResourcesFiles() const
    { return this->resourcesFiles; }

    /**
     * Get the build directory.
     */
    const std::string& getBuildDir() const
    { return this->buildDir; }

    // === R ===

    /**
     * read the project configuration file.
     */
    void read(const std::string& filename = "");

    // === S ===


    /**
     * Set project name.
     */
    void setBinName( std::string _binName )
    { this->binName = _binName; }


private:

    /**
     * The version of tntmake that is create the configuration file.
     * With this number it can check the compatibility of a configuration.
     */
    int tntmakeVersion;

    /**
    * Name of binary file.
    */
    std::string binName;

    /**
    * Name of c++ compiler.
    */
    std::string cppCompiler;

    /**
    * List of *.cpp files.
    */
    std::vector<std::string> cppFiles;

    /**
    * List of *.h fils.
    */
    std::string hFiles;

    /**
    * c++ compiler flags.
    */
    std::string cppFlags;

    /**
    * c++ linker flags.
    */
    std::string cppLinkerFlags;

    /**
    * ecpp compiler (name).
    */
    std::string ecppCompiler;

    /**
    * ecpp compiler flags
    */
    std::string ecppFlags;

    /**
    * List of *.ecpp files.
    */
    std::string ecppFiles;

    /**
    * List of static contend files.
    */
    std::string resourcesFiles;

    /**
    * The build directory.
    */
    std::string buildDir;


};

} // namespace Core
} // namespace Tww

#endif
