/*
* Copyright (C) 2013-2014 Olaf Radicke
*
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

#ifndef CORE_WEBAPPLICATIONCOREMANAGER_H
#define CORE_WEBAPPLICATIONCOREMANAGER_H

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

namespace Tww {
namespace Core
{

/**
 * This class manage the creating of a webaplication.
 */
class WebApplicationCoreManager {

public:


// G --------------------------------------------------------------------------

// W --------------------------------------------------------------------------

    WebApplicationCoreManager (
        Tww::Core::UserSession& _userSession,
        Tww::Core::ProjectData& _projectData,
        Tww::Core::MakefileData& _makefileData
    ):
        makefileData( _makefileData ),
        projectData( _projectData ),
        userSession( _userSession )
        {};


    /**
     * This function check is an application all reddy exist.
     * The function inspect the existence of the file "src/main.cpp"
     * \return If an application all reddy exist than returns "true".
     */
    bool isApplicationCoreExist();

    /**
     * This function try to create the core of a tntnet based web application.
     */
    void createApplicationCore();

private:


    /**
     * Represent the makefile data.
     */
    Tww::Core::MakefileData& makefileData;

    /**
     * Class with project data.
     */
    Tww::Core::ProjectData& projectData;

    /**
     * Session information.
     */
    Tww::Core::UserSession& userSession;

    // ========= private member functions =========
    /**
     * Create the "src/main.cpp" file.
     */
    void createMain_cpp();

    /**
     * Create the "src/core/model/config.cpp" file.
     */
    void createConfig_cpp();

    /**
     * Create the "src/core/model/config.h" file.
     */
    void createConfig_h();

    /**
     * Create the Directory Structure of core part:
     * src/core/model/
     * src/core/manager
     * src/core/controler
     * src/core/resources
     * src/core/view
     */
    void createCoreDirectoryStructure();

    /**
     * Create the "src/core/resources/[project name].css" file.
     */
     void createMainCSS();

    /**
     * Create the "src/core/initcomponent.h" file.
     */
    void createInitcomponent_h();

    /**
     * Get the temporary path of "src/core/model/config.cpp" file.
     */
    std::string getConfigCppPath();

    /**
     * Get the temporary path of "src/core/model/config.h" file.
     */
    std::string getConfigHPath();

    /**
     * Get the temporary path of "src/core/resources/[project name].css" file.
     */
    std::string getCSSPath();

    /**
     * Get the temporary path of "src/core/initcomponent.h" file.
     */
    std::string getInitcomponentHPath();

    /**
     * Get the temporary path of "src/main.cpp file.
     */
    std::string getMainCppPath();

    /**
     * Get the temporary path of Makefile.tnt file.
     */
    std::string getMakefilePath();

    /**
     * Get the temporary path of source code directory.
     */
    std::string getSourceDir();
};



} // END namespace Core
} // end namespace Tww
#endif // SESSIONFORM_MANAGER_H

