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

    friend void operator>>= (const cxxtools::SerializationInfo& si, ProjectData& config );

public:

    ProjectData()
        projectName("newproject")
    { }
    /**
     * get back a instance of ProjectData class
     */
    static ProjectData& it();

    /**
     * read the project configuration file.
     */
    void read(const std::string& filename = "");


    const std::string& projectName() const
    { return this->projectName; }


    /**
     * Get a export of user quote data in json format.
     * @arg userID Id of a user.
     * @return A json document.
     */
    static std::string getJsonExport( const unsigned long userID );

private:
    std::string                 projectName;




};

} // namespace Core
} // namespace Tww

#endif
