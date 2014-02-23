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

#ifndef CORE_PROJECTDATA_H
#define CORE_PROJECTDATA_H

#include <string>
#include <cxxtools/serializationinfo.h>


namespace Tww {
namespace Core {

/**
* @class ProjectData This class represent the projektdata.
*/
class ProjectData {


    /**
    * define how to deserialize the project data file
    * @arg si serialization info
    * @arg projektData project data class
    */
    friend void operator>>= (const cxxtools::SerializationInfo& si, ProjectData& projektData );


    /**
    * define how to serialize the ProjectData class.
    * @arg si serialization info
    * @arg ProjectData project data class
    */
    friend void operator<<= ( cxxtools::SerializationInfo& si, const ProjectData& projektData );

public:

    ProjectData():
        wizardVersion( 1 ),
        projectName("newproject")
    { }

    // === G ===

    /**
     * Get a export of user quote data in json format.
     * @arg userID Id of a user.
     * @return A json document.
     */
    std::string getJson( );

    /**
     * Get project name.
     */
    const std::string& getProjectName() const
    { return this->projectName; }


    /**
     * Get project name.
     */
    const int getWizardVersion() const
    { return this->wizardVersion; }

    // === R ===

    /**
     * read the project configuration file.
     */
    void read(const std::string& filename = "");

    // === S ===


    /**
     * Set project name.
     */
    void setProjectName( std::string _projectName )
    { this->projectName = _projectName; }


private:

    /**
     * The version of wizard that is create the configuration file.
     * With this number it can check the compatibility of a configuration.
     */
    int                         wizardVersion;

    /**
     * Name of the project.
     */
    std::string                 projectName;


};

} // namespace Core
} // namespace Tww

#endif
