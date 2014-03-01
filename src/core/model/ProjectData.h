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

// http://www.tntnet.org/howto/serialization-howto.html

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
        projectName("newproject"),
        doxygenTemplates(true),
        formToken(true),
        routeRevers(true)
    { }

    // === G ===

    /**
     * Get a export of user projekt data in json format.
     * @return A json document.
     */
    std::string getJson( );

    /**
     * Get a export of user projekt data in xml format.
     * @return A xml document.
     */
    std::string getXml();

    /**
     * Get project name.
     */
    const std::string& getProjectName() const
    { return this->projectName; }

    /**
     * Get the header template with the licence and author.
     */
    const std::string& getSourceCodeHeader() const
    { return this->sourceCodeHeader; }

    /**
     * Get project name.
     */
    const int getWizardVersion() const
    { return this->wizardVersion; }

    // === I ===

    /**
     * Swith on and off generating code with cxxtools loging support.
     */
    const bool isCxxtoolsLoging( ) const
    { return this->cxxtoolsLoging; };

    /**
     * If that "true" than use doxygen comments.
     */
    const bool isDoxygenTemplates( ) const
    { return this->doxygenTemplates; };

    /**
     * If that "true" than make forms with tokens.
     * That is for csrf "cross site request forgery".
     */
    const bool isFormToken( ) const
    { return this->formToken; };

    /**
     * If that "true" than it use the module "routereverse".
     * \see subpage_route_reverse
     */
    const bool isRouteRevers( ) const
    { return this->routeRevers; };

    // === R ===

    /**
     * read the project configuration file.
     */
    void read(const std::string& filename);

    // === S ===

    /**
     * Swith on and off generating code with cxxtools loging support.
     */
    void setCxxtoolsLoging( bool _yesOrNo )
    { this->cxxtoolsLoging = _yesOrNo; };

    /**
     * that set is doxygen use or not.
     * @arg _yesOrNo "true" is using doxygen.
     */
    void setDoxygenTemplates( bool _yesOrNo )
    { this->doxygenTemplates = _yesOrNo; };

    /**
     * that set is form token use or not.
     * The token is for csrf "cross site request forgery".
     */
    void setFormToken( bool _yesOrNo )
    { this->formToken = _yesOrNo; };

    /**
     * Set project name.
     */
    void setProjectName( std::string _projectName )
    { this->projectName = _projectName; };

    /**
     * Swith on and off generating code with revers route support.
     */
    void setRouteRevers( bool _yesOrNo )
    { this->routeRevers = _yesOrNo; };

    /**
     * Set the header template with the licence and author.
     */
    void setSourceCodeHeader( std::string _sourceCodeHeader )
    { this->sourceCodeHeader = _sourceCodeHeader ; };

    // === W ===

    /**
     * Write the project configuration in a file.
     */
    void write(const std::string filename);


private:

    /**
     * The version of wizard that is create the configuration file.
     * With this number it can check the compatibility of a configuration.
     */
    int wizardVersion;

    /**
     * Name of the project.
     */
    std::string projectName;

    /**
     * The header template with the licence and author.
     */
    std::string sourceCodeHeader;

    /**
     * If that "true" than use doxygen comments.
     */
    bool doxygenTemplates;

    /**
     * If that "true" than make forms with tokens.
     * That is for csrf "cross site request forgery".
     */
    bool formToken;

    /**
     * If that "true" than it is generating code with cxxtools loging support.
     */
    bool cxxtoolsLoging;

    /**
     * If that "true" than it is generating code with reverse routing support.
     */
    bool routeRevers;
};

} // namespace Core
} // namespace Tww

#endif
