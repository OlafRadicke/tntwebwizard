/*
* Copyright (C) 2013 Olaf Radicke <briefkasten@olaf-radicke.de>
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


#include <core/manager/WebApplicationCoreManager.h>
#include <core/model/TntWebWizardException.h>
#include <routereverse/manager/manager.h>

#include <tnt/component.h>
#include <tnt/httprequest.h>

#include <cxxtools/fileinfo.h>
#include <cxxtools/directory.h>
#include <cxxtools/log.h>


#include <ostream>
#include <fstream>
#include <string>
// #include <unistd.h>

namespace Tww {
namespace Core
{


log_define("Core.WebApplicationCoreManager")

// C -------------------------------------------------------------------------

void WebApplicationCoreManager::createApplicationCore(
    const tnt::HttpRequest& request
){
    log_debug("createApplicationCore()" );
    std::string mainCppPath = this->getMainCppPath();
    if ( cxxtools::FileInfo::exists( mainCppPath ) ) {
        std::ostringstream errorText;
        errorText
            << "The file "
            << mainCppPath
            << " is all ready exist!"
            << "I can not create this file. Abort..."
        ;
        throw Core::TntWebWizardException( errorText.str() );
    }

    this->createCoreDirectoryStructure();
    this->createMain_cpp();
    this->createConfig_h();
    this->createConfig_cpp();
    this->createInitcomponent_h();
    this->createMainCSS();
    if ( this->projectData.isFormToken( ) ) {
        this->createModulFormToken( request );
    }
    if ( this->projectData.isRouteReverse( ) ) {
        this->createModulRouteReverse( request );
    }
}


void WebApplicationCoreManager::createCoreDirectoryStructure(){

    if ( !cxxtools::Directory::exists( this->getSourceDir() ) ) {
        cxxtools::Directory::create( this->getSourceDir() );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/core" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/core" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/core/controller" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/core/controller" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/core/manager" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/core/manager" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/core/model" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/core/model" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/core/resources" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/core/resources" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/core/view" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/core/view" );
    }

}


void WebApplicationCoreManager::createMain_cpp(){
        log_debug("createMain_cpp()" );

    std::ostringstream fileContent;
    fileContent
        << "/* ***************************************************************************\n"
        << this->projectData.getSourceCodeHeader()
        << "\n"
        << "*************************************************************************** */ \n"
        << "#include <core/model/config.h>\n"
        << "#include <core/initcomponent.h>\n"
    ;
    if ( this->projectData.isFormToken( ) ) {
        fileContent << "#include <formtoken/initcomponent.h>\n";
    }
    if ( this->projectData.isRouteReverse( ) ) {
        fileContent << "#include <routereverse/initcomponent.h>\n";
    }
    fileContent << "\n";
    // ***** tnt lib part *****
    fileContent
        << "#include <tnt/tntnet.h>\n"
        << "#include <tnt/configurator.h>\n"
    ;
    fileContent << "\n";
    // ***** cxxtools lib part *****
    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent
            << "#include <cxxtools/log.h>\n"
        ;
    }
    if (  this->projectData.isCliSupport( ) ){
        fileContent << "#include <cxxtools/arg.h>\n";
    }
    fileContent << "\n";
    // ***** std lib part *****
    fileContent << "#include  <ostream> \n";
    fileContent << "\n\n";

    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent
            << "log_define(\"main\")\n"
        ;
    }
    fileContent
        << "\n\n"
        <<  "int main ( int argc, char* argv[] )\n"
        <<  "{ \n"
    ;
    if (  this->projectData.isCliSupport( ) ){
        fileContent
            << "\t cxxtools::Arg<bool> arg_verbose(argc, argv, 'v');\n"
            << "\t cxxtools::Arg<std::string> arg_config(argc, argv, 'c', \"\");\n"
            << "\t if ( arg_verbose )\n"
            << "\t\t std::cout << \"verbose option is set\" << std::endl;\n"
            << "\t if ( arg_verbose && arg_config.getValue() != \"\")\n"
            << "\t\t std::cout << \"us config:\" << arg_config.getValue() << std::endl;\n"
        ;
    }

    fileContent <<  "\t Core::Config& config = Core::Config::it();\n";
    if (  this->projectData.isCliSupport( ) ){
        fileContent
            <<  "\t if ( arg_config.getValue() != \"\" ) {\n"
            <<  "\t\t config.read( arg_config.getValue() );\n"
            <<  "\t } else {\n"
            <<  "\t\t config.read();\n"
            <<  "\t }\n"
        ;
    } else {
        fileContent <<  "\t config.read();\n";
    }
    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent <<  "\t log_init( config.getLogging() );\n\n";
    }
    fileContent
        <<  "\t // Init Application Server\n"
        <<  "\t tnt::Tntnet app;\n"
        <<  "\t tnt::Configurator tntConfigurator( app );\n"
        <<  "\t tntConfigurator.setSessionTimeout ( config.getSessionTimeout() );\n"
        <<  "\t app.listen( config.getAppIp(), config.getAppPort() );\n\n"
        <<  "\t // init comonent parts\n"
        <<  "\t Core::initcomponent( app );\n"
    ;
    if ( this->projectData.isFormToken( ) ) {
        fileContent << "\t FormToken::initcomponent( app );\n";
    }
    if ( this->projectData.isRouteReverse( ) ) {
        fileContent << "\t RouteReverse::initcomponent( app );\n\n";
    }
    fileContent
        << "\t std::cout \n"
        << "\t\t << \""
        << this->projectData.getProjectName()
        << " is started and run on http://\" \n"
        << "\t\t << config.getAppIp() << \":\" \n"
        << "\t\t << config.getAppPort() << \"/\" << std::endl\n"
        << "\t ;\n"
        << "\t log_info( \"starting " << this->projectData.getProjectName() << "\");\n"
        << "\t log_info( \" " << this->projectData.getProjectName()
        << " is started and run on http://\" <<  config.getAppIp() << \":\" "
        << "<<  config.getAppPort() << \"/\"); \n\n"
        << "\t app.run(); \n\n"
        << "\t return 0;\n"
        << "}\n"
    ;

    log_debug( __LINE__ << " write in: \n"  << this->getMainCppPath().c_str() );
    std::ofstream maincpp_file( this->getMainCppPath().c_str() );
    maincpp_file << fileContent.str() ;
    maincpp_file.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->getMakefilePath() );
    this->makefileData.addCppFile( "./src/main.cpp" );
    this->makefileData.write( this->getMakefilePath() );

}


void WebApplicationCoreManager::createConfig_cpp(){
    log_debug("createConfig_cpp()" );

    std::ostringstream fileContent;
    fileContent
        << "/* ***************************************************************************\n"
        << this->projectData.getSourceCodeHeader()
        << "\n"
        << "*************************************************************************** */ \n"
        << "\n"
        << "#include <core/model/config.h>\n"
        << "#include <stdexcept>\n"
    ;
    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent
            << "#include <cxxtools/log.h>\n"
        ;
    }
    if (  this->projectData.getConfigFormat( ) == "json" ){
        fileContent
            << "#include <cxxtools/jsondeserializer.h>\n"
        ;
    } else {
        fileContent
            << "#include <cxxtools/serializationinfo.h>\n"
        ;
    }
    fileContent
        << "#include <cxxtools/fileinfo.h>\n"
        << "\n"
        << "#include <fstream>\n"
        << "#include <ostream>\n"
        << "\n"
        << "namespace Core {\n"
    ;

    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent
            << "log_define(\"Core.Config\")\n"
        ;
    }

    fileContent
        << "Config& Config::it() {\n"
        << "\t static Config theConfig;\n"
        << "\t return theConfig;\n"
        << "}\n"
        << "\n"
        << "void Config::read(const std::string& filename) {\n"
        << "\t std::string fname;\n"
        << "\n"
        << "\t if (!filename.empty()) {\n"
        << "\t\t fname = filename;\n"
        << "\t }\n"
        << "\t if (\n"
        << "\t\t cxxtools::FileInfo::exists(\" "
        << this->makefileData.getBinName()  << ".conf\")\n"
        << "\t ){\n"
        << "\t\t fname = \"" << this->makefileData.getBinName()  << ".conf\";\n"
        << "\t } else {\n"
        << "\t\t fname = \"/etc/" << this->makefileData.getBinName()  << ".conf\";\n"
        << "\t }\n"
        << "\n"
        << "\t std::ifstream in(fname.c_str());\n"
        << "\t if (!in) {\n"
        << "\t\t std::ostringstream errorText;\n"
        << "\t\t errorText << \"failed to open configuration file \";\n"
        << "\t\t errorText  << fname << \"\\\"\";\n"
    ;
    if (  this->projectData.isCxxtoolsLoging( ) ){
        fileContent
            << "\t\t log_error( \"failed to open configuration file \\\"\" << fname << \"\\\"\" );\n"
        ;
    }
    fileContent
        << "\t\t throw std::runtime_error( errorText.str() );\n"
        << "\t\t return;\n"
        << "\t }\n"
    ;
    if (  this->projectData.getConfigFormat( ) == "json" ){
        fileContent
            << "\t cxxtools::JsonDeserializer deserializer(in);\n"
        ;
    } else {
        fileContent
            << "\t cxxtools::xml::XmlDeserializer deserializer(in);\n"
        ;
    }
    fileContent
        << "\t deserializer.deserialize(*this);\n"
        << "\t }\n"
        << "\n"
        << "\n"
    ;
    if (  this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "\t /**\n"
            << "\t * define how to deserialize the config file\n"
            << "\t * @arg si serialization info\n"
            << "\t * @arg config config class\n"
            << "\t */\n"
        ;
    }
    fileContent
        << "\t void operator>>= (const cxxtools::SerializationInfo& si, Config& config ){\n"
        << "\t\t // \"si.getMember\" with 2 parameters - member name and a reference - fills\n"
        << "\t\t // the reference only if found This makes logging configuration optional.\n"
        << "\n"
        << "\t\t si.getMember(\"logging\", config.logging);\n"
        << "\n"
        << "\t\t // \"si.getMember\" with one parameter - the member name - throws an\n"
        << "\t\t // exception when the member is not found. Using it makes the setting\n"
        << "\t\t // mandatory.\n"
        << "\n"
        << "\t\t si.getMember(\"appIp\")           >>= config.appIp;\n"
        << "\t\t si.getMember(\"appPort\")         >>= config.appPort;\n"
        << "\t\t si.getMember(\"sessionRuntime\")  >>= config.sessionTimeout;\n"
        << "\t\t si.getMember(\"domain\")          >>= config.domainName;\n"
        << "\n"
        << "\t }\n"
        << "\n"
        << "} // namespace core\n"
    ;

    log_debug( __LINE__ << " write in: \n"  << this->getConfigCppPath().c_str() );
    std::ofstream configcpp_file( this->getConfigCppPath().c_str() );
    configcpp_file << fileContent.str() ;
    configcpp_file.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->getMakefilePath() );
    this->makefileData.addCppFile( "./src/core/model/config.cpp" );
    this->makefileData.write( this->getMakefilePath() );
}

void WebApplicationCoreManager::createConfig_h(){
    log_debug("createConfig_h()" );

    std::ostringstream fileContent;
    fileContent
        << "/* ***************************************************************************\n"
        << this->projectData.getSourceCodeHeader()
        << "\n"
        << "*************************************************************************** */ \n"
        << "\n"
        << "#ifndef CORE_CONFIG_H \n"
        << "#define CORE_CONFIG_H \n"
        << "\n"
        << "#include <string> \n"
        << "#include <cxxtools/serializationinfo.h> \n"
        << "\n"
        << "namespace Core { \n"
        << "\n"
    ;
    if (  this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "/** \n"
            << "* @class Config This class read a configuration file. \n"
            << "* The form of date in the configuration file is json. \n"
            << "*/ \n"
        ;
    }
    fileContent
        << "class Config { \n"
        << "\n"
        << "\t friend void operator>>= (const cxxtools::SerializationInfo& si, Config& config ); \n"
        << "\n"
        << "public: \n"
        << "\n"
    ;
    if (  this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "\t /** \n"
            << "\t * Get a instance of a static configuration class. \n"
            << "\t */ \n"
        ;
    }
    fileContent
        << "\t static Config& it(); \n"
        << "\n"
    ;
    if (  this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "\t /** \n"
            << "\t * Read the configuration file. \n"
            << "\t * @arg filename the file name of the configuration file. \n"
            << "\t */ \n"
        ;
    }
    fileContent
        << "\t void read(const std::string& filename = \"\"); \n"
        << "\n"
    ;
    if (  this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "\t /** \n"
            << "\t * Get the loging configuration. \n"
            << "\t */ \n"
        ;
    }
    fileContent
        << "\t const cxxtools::SerializationInfo& getLogging() const \n"
        << "\t { return this->logging; } \n"
        << "\n"
    ;
    if (  this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "\t /** \n"
            << "\t * Get the IP addres of this application. \n"
            << "\t */ \n"
        ;
    }
    fileContent
        << "\t const std::string& getAppIp() const \n"
        << "\t { return this->appIp; } \n"
        << "\n"
    ;
    if (  this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "\t /** \n"
            << "\t * Get the port number of this application. \n"
            << "\t */ \n"
        ;
    }
    fileContent
        << "\t unsigned short getAppPort() const \n"
        << "\t { return this->appPort; } \n"
        << "\n"
    ;
    if (  this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "\t /** \n"
            << "\t * Get the domain name of this application. \n"
            << "\t */ \n"
        ;
    }
    fileContent
        << "\t const std::string& getDomainName() const \n"
        << "\t { return this->domainName; } \n"
        << "\n"
    ;
    if (  this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "\t /** \n"
            << "\t * Get the session timeout (in seconds) of this application. \n"
            << "\t */ \n"
        ;
    }
    fileContent
        << "\t unsigned getSessionTimeout() const \n"
        << "\t { return this->sessionTimeout; } \n"
        << "\n"
        << "private: \n"
        << "\t bool                        configRead; \n"
        << "\t cxxtools::SerializationInfo logging; \n"
        << "\t std::string                 appIp; \n"
        << "\t unsigned short              appPort; \n"
        << "\t std::string                 domainName; \n"
        << "\t unsigned                    sessionTimeout; \n"
        << "\n"
        << "public: \n"
        << "\n"
        << "\t Config() : \n"
        << "\t\t configRead(false), \n"
        << "\t\t appIp(""), \n"
        << "\t\t appPort(8008), \n"
        << "\t\t domainName( \"" << this->makefileData.getBinName() << ".domain\" ), \n"
        << "\t\t sessionTimeout( 1000 ) \n"
        << "\t { } \n"
        << "\n"
        << "}; \n"
        << "\n"
        << "} // namespace Core \n"
        << "#endif \n"
    ;

    log_debug( __LINE__ << " write in: \n"  << this->getConfigHPath().c_str() );
    std::ofstream configh_file( this->getConfigHPath().c_str() );
    configh_file << fileContent.str() ;
    configh_file.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->getMakefilePath() );
    this->makefileData.addHFile( "./src/core/model/config.h" );
    this->makefileData.write( this->getMakefilePath() );
}

void WebApplicationCoreManager::createHomeSite_epcc(){
    log_debug("createHomeSite_epcc()" );

    std::ostringstream fileContent;
    fileContent
        << "<# ###########################################################################\n"
        << this->projectData.getSourceCodeHeader()
        << "\n"
        << "############################################################################ #>\n"
        << "\n"
    ;
    if ( this->projectData.isRouteReverse( ) ) {
        fileContent
            << "<%pre>\n"
            << "\t #include <routereverse/manager/manager.h>\n"
            << "</%pre>\n"
            << "<%cpp>\n"
            << "\t std::string href_favicon_ico =\n"
            << "\t\t RouteReverse::Manager::getLinkTo(\n"
            << "\t\t\t \"core_favicon_ico\",\n"
            << "\t\t\t request\n"
            << "\t );\n"
            << "</%cpp>\n"
        ;
    }
    fileContent
        << "<!DOCTYPE HTML>\n"
        << "<html>\n"
        << "<head>\n"
        << "\t <title>\n"
        << this->projectData.getProjectName()
        << " - Home</title>\n"
        << "\t <meta charset = \"UTF-8\">  \n"
        << "\t <link\n"
        << "\t\t rel=\"icon\"\n"
    ;

    if ( this->projectData.isRouteReverse( ) ) {
        fileContent
            << "\t\t href=\"<$ href_favicon_ico $>\"\n"
        ;
    } else {
        fileContent
            << "\t\t href=\"/core/favicon.ico\"\n"
        ;
    }
    fileContent
        << "\t\t type=\"image/x-icon\">\n"
        << "</head>\n"
        << "<body>\n"

        << "\t <h2>\n"
        << this->projectData.getProjectName()
        << "</h2>\n"
        << "\t <p>\n"
        << "\t\t hello world!\n"
        << "\t </p>\n"

        << "</body>\n"
        << "</html>\n"
    ;

    log_debug( __LINE__ << " write in: \n"  << this->getInitcomponentHPath().c_str() );
    std::ofstream initcomph_file( this->getInitcomponentHPath().c_str() );
    initcomph_file << fileContent.str() ;
    initcomph_file.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->getMakefilePath() );
    this->makefileData.addCppFile( "./src/core/initcomponent.h" );
    this->makefileData.write( this->getMakefilePath() );
}

void WebApplicationCoreManager::createInitcomponent_h(){
    log_debug("createInitcomponent_h()" );

    std::ostringstream fileContent;
    fileContent
        << "/* ***************************************************************************\n"
        << this->projectData.getSourceCodeHeader()
        << "\n"
        << "*************************************************************************** */ \n"
        << "\n"
        << "#ifndef CORE_INITCOMPONENT_H\n"
        << "#define CORE_INITCOMPONENT_H\n"
    ;
    if ( this->projectData.isRouteReverse( ) ) {
        fileContent
            << "#include <routereverse/manager/manager.h>\n"
        ;
    };
    fileContent
        << "#include <string>\n"
    ;
    if ( this->projectData.isCxxtoolsLoging( ) ){
        fileContent
            << "#include <cxxtools/log.h>\n"
        ;
    }
    fileContent
        << "#include <tnt/tntnet.h>\n"
        << "\n"
        << "namespace Core {\n"
        << "\n"
        << "log_define(\"Core.initcomponent\")\n"
        << "\n"
    ;
    if ( this->projectData.isDoxygenTemplates( ) ){
        fileContent
            << "/**\n"
            << " * This function prepare the component \"Core\". Specifically the routing.\n"
            << " * @arg app a reference of the application server.\n"
            << " */\n"
        ;
    }
    fileContent
        << "void initcomponent ( tnt::Tntnet &app ) {\n"
        << "\n"
        << "\t // special pages\n"
        << "\t // 1:1 rout\n"
        << "\t app.mapUrl( \"^/(.*)$\", \"$1\" );\n"
        << "\n"
        << "\t // default route for / \n"
        << "\t app.mapUrl( \"^/$\", \"core_home\" );\n"
        << "\n"
        << "\t // ######################## RESOURCES ############################\n"
        << "\n"
        << "\t // configure generic static stuff\n"
        << "\t app.mapUrl(\n"
        << "\t\t \"^/Core/resources/(.*)\",\n"
        << "\t\t \"resources\"\n"
        << "\t ).setPathInfo(\"core/resources/$1\");\n"
        << "\n"
        << "\t // /core/favicon.ico\n"
        << "\t app.mapUrl(\n"
        << "\t\t \"^/core/favicon.ico$\",\n"
        << "\t\t \"resources\"\n"
        << "\t ).setPathInfo(\"core/resources/favicon.ico\");\n"
        << "\n"
    ;
    if ( this->projectData.isRouteReverse( ) ) {
        fileContent
            << "\t RouteReverse::Manager::add(\n"
            << "\t\t \"core_favicon_ico\",\n"
            << "\t\t \"core/favicon.ico\"\n"
            << "\t );\n"
        ;
    }
    fileContent
        << "\t // /core/resources/normalize.css\n"
        << "\n"
        << "\t app.mapUrl(\"^/core/normalize.css$\", \"resources\")\n"
        << "\t\t .setPathInfo(\"core/resources/normalize.css\");\n"
        << "\n"
    ;
    if ( this->projectData.isRouteReverse( ) ) {
        fileContent
            << "\t RouteReverse::Manager::add(\n"
            << "\t\t \"core_normalize_css\",\n"
            << "\t\t \"core/normalize.css\"\n"
            << "\t );\n"
            << "\n"
        ;
    }
    fileContent
        << "\t // /core/resources/" << this->makefileData.getBinName() << ".css\n"
        << "\t app.mapUrl(\n"
        << "\t\t \"^/core/" << this->makefileData.getBinName() << ".css$\",\n"
        << "\t\t \"resources\"\n"
        << "\t ).setPathInfo( \"core/resources/" << this->makefileData.getBinName() << ".css\" );\n"
        << "\n"
    ;
    if ( this->projectData.isRouteReverse( ) ) {
        fileContent
            << "\t RouteReverse::Manager::add(\n"
            << "\t\t \"core_" << this->makefileData.getBinName() << "_css\",\n"
            << "\t\t \"core/" << this->makefileData.getBinName() << ".css\"\n"
            << "\t );\n"
        ;
    }
    fileContent
        << "\n"
        << "\t // ######################### OTHER SITES ##########################\n"
        << "\n"
        << "\t // ##################### END OF ROUTING RULES #####################\n"
        << "\n"
    ;
    if ( this->projectData.isCxxtoolsLoging( ) ){
        fileContent
            << "\t log_debug( RouteReverse::Manager::getAllReversesRoutes() );\n"
        ;
    }
    fileContent
        << "\n"
        << "}\n"
        << "\n"
        << "} // END namespace Core\n"
        << "\n"
        << "#endif // CORE_INITCOMPONENT_H\n"
    ;

    log_debug( __LINE__ << " write in: \n"  << this->getInitcomponentHPath().c_str() );
    std::ofstream initcomph_file( this->getInitcomponentHPath().c_str() );
    initcomph_file << fileContent.str() ;
    initcomph_file.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->getMakefilePath() );
    this->makefileData.addHFile( "./src/core/initcomponent.h" );
    this->makefileData.write( this->getMakefilePath() );

}

void WebApplicationCoreManager::createMainCSS(){
    log_debug("createMainCSS()" );

    std::ostringstream fileContent;
    fileContent
        << "\n"
        << "html {\n"
        << "\t color: #0076ff;\n"
        << "\t background-color: #CCDDFF;\n"
        << "}\n"
        << "\n"
    ;

    log_debug( __LINE__ << " write in: \n"  << getHomeSiteEcppPath().c_str() );
    std::ofstream css_file( getHomeSiteEcppPath().c_str() );
    css_file << fileContent.str() ;
    css_file.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->getMakefilePath() );
    this->makefileData.addEcppFile( "./src/core/view/core_home.ecpp" );
    this->makefileData.write( this->getMakefilePath() );

}



void WebApplicationCoreManager::createModulFormToken(
    const tnt::HttpRequest& request
) {
    log_debug("createModulFormToken()" );
    std::ofstream writting_file;
    std::ostringstream fileContent;

    if ( !cxxtools::Directory::exists(
        this->getSourceDir() + "/formtoken"
    ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/formtoken" );
    }
    if ( !cxxtools::Directory::exists(
        this->getSourceDir() + "/formtoken/controller"
    ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/formtoken/controller" );
    }
    if ( !cxxtools::Directory::exists(
        this->getSourceDir() + "/formtoken/manager"
    ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/formtoken/manager" );
    }
    if ( !cxxtools::Directory::exists(
        this->getSourceDir() + "/formtoken/model"
    ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/formtoken/model" );
    }
    if ( !cxxtools::Directory::exists(
        this->getSourceDir() + "/formtoken/resources"
    ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/formtoken/resources" );
    }
    if ( !cxxtools::Directory::exists(
        this->getSourceDir() + "/formtoken/view"
    ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/formtoken/view" );
    }

    if ( !system(NULL) ) {
        throw Core::TntWebWizardException( "Can not do systems command!" );
    }

    // ====== creating files ======

    const unsigned int PATH = 0;
    const unsigned int ALIAS = 1;
    const unsigned int TYPE = 2;
    std::string files[6][3] = {
        "formtoken/controller/controller.cpp","formtoken_controller_cpp","cpp",
        "formtoken/initcomponent.h","formtoken_initcomponent_h","h",
        "formtoken/manager/manager.cpp", "formtoken_manager_cpp","cpp",
        "formtoken/manager/manager.h", "formtoken_manager_h","h",
        "formtoken/subpage_form_token.dox","formtoken_subpage_form_token_dox","dox",
        "formtoken/view/formtoken_no_availabe_token.ecpp","formtoken_no_availabe_token_ecpp","ecpp"
    };
    for (unsigned int i = 0 ; i < 6; i++) {
        std::cout
            << "##############################################################"
            << std::endl;
        std::cout << "path: " << files[i][0] << " alias: " << files[i][1] << std::endl;
        std::cout
            << "##############################################################"
            << std::endl;

        std::string fileName = this->getSourceDir() + "/" + files[i][PATH] ;
        std::stringstream sysCommand;
        std::stringstream errorText;

        std::string href_file =
            RouteReverse::Manager::getAbsolutURL(
                files[i][ALIAS],
                request
            );
        sysCommand
            << "curl " <<  href_file << " > " <<  fileName << ";"
        ;

        log_debug( "[" << __LINE__ << "] command: " << sysCommand.str() );
        int returncode = system( sysCommand.str().c_str() );
        log_debug( "[" << __LINE__ << "]The value returned was: " << returncode);
        if ( returncode != 0 ) {
            errorText
                << "Download file is Failed: \""
                << sysCommand.str()
            ;
            throw Core::TntWebWizardException( errorText.str() );
        }


        if ( !popen( sysCommand.str().c_str(), "r") ) {
            errorText
                << "Download file is Failed: \""
                << sysCommand.str()
            ;
            throw Core::TntWebWizardException( errorText.str() );

        }

        // Add new file in Makefile.tnt configuration.
        this->makefileData.read( this->getMakefilePath() );
        if ( files[i][TYPE] == "cpp" ) {
            this->makefileData.addCppFile( "./src/" + files[i][PATH] );
        }
        if ( files[i][TYPE] == "ecpp" ) {
            this->makefileData.addEcppFile( "./src/" + files[i][PATH] );
        }
        if ( files[i][TYPE] == "h" ) {
            this->makefileData.addHFile( "./src/" + files[i][PATH] );
        }
        this->makefileData.write( this->getMakefilePath() );
    };

}

void WebApplicationCoreManager::createModulRouteReverse(
    const tnt::HttpRequest& request
) {
    log_debug("createModulFormToken()" );
    std::ofstream writting_file;
    std::ostringstream fileContent;

    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/routereverse" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/routereverse" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/routereverse/controller" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/routereverse/controller" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/routereverse/manager" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/routereverse/manager" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/routereverse/model" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/routereverse/model" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/routereverse/resources" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/routereverse/resources" );
    }
    if ( !cxxtools::Directory::exists( this->getSourceDir() + "/routereverse/view" ) ) {
        cxxtools::Directory::create( this->getSourceDir() + "/routereverse/view" );
    }

    if ( !system(NULL) ) {
        throw Core::TntWebWizardException( "Can not do systems command!" );
    }
    // ====== creating files ======


    const unsigned int PATH = 0;
    const unsigned int ALIAS = 1;
    const unsigned int TYPE = 2;
    std::string files[5][3] = {
        "routereverse/initcomponent.h", "routereverse_initcomponent_h","h",
        "routereverse/subpage_route_reverse.dox", "routereverse_subpage_route_reverse_dox","dox",
        "routereverse/manager/manager.cpp", "routereverse_manager_cpp","cpp",
        "routereverse/manager/manager.h", "routereverse_manager.h","h",
        "routereverse/model/routereverseexception.h", "routereverse_routereverseexception.h","h"
    };

    for (unsigned int i = 0 ; i < 5; i++) {
        std::cout
            << "##############################################################"
            << std::endl;
        std::cout << "path: " << files[i][0] << " alias: " << files[i][1] << std::endl;
        std::cout
            << "##############################################################"
            << std::endl;

        std::string fileName = this->getSourceDir() + "/" + files[i][PATH] ;
        std::stringstream sysCommand;
        std::stringstream errorText;

        std::string href_file =
            RouteReverse::Manager::getAbsolutURL(
                files[i][ALIAS],
                request
            );
        sysCommand
            << "curl " <<  href_file << " > " <<  fileName << ";"
        ;

        log_debug( "[" << __LINE__ << "] command: " << sysCommand.str() );
        int returncode = system( sysCommand.str().c_str() );
        log_debug( "[" << __LINE__ << "]The value returned was: " << returncode);
        if ( returncode != 0 ) {
            errorText
                << "Download file is Failed: \""
                << sysCommand.str()
            ;
            throw Core::TntWebWizardException( errorText.str() );
        }

        // Add new file in Makefile.tnt configuration.
        this->makefileData.read( this->getMakefilePath() );
        if ( files[i][TYPE] == "cpp" ) {
            this->makefileData.addCppFile( "./src/" + files[i][PATH] );
        }
        if ( files[i][TYPE] == "h" ) {
            this->makefileData.addHFile( "./src/" + files[i][PATH] );
        }
        this->makefileData.write( this->getMakefilePath() );
    };
}

// G --------------------------------------------------------------------------

std::string WebApplicationCoreManager::getConfigCppPath(){
    return this->userSession.getSessionPath() + "/src/core/model/config.cpp";
}

std::string WebApplicationCoreManager::getConfigHPath(){
    return this->userSession.getSessionPath() + "/src/core/model/config.h";
}

std::string WebApplicationCoreManager::getCSSPath(){
    std::ostringstream completPath;
    completPath
        << this->userSession.getSessionPath()
        << "/src/core/resources/"
        << this->makefileData.getBinName()
        << ".css"
    ;
    return completPath.str();
}

std::string WebApplicationCoreManager::getHomeSiteEcppPath(){
    return this->userSession.getSessionPath() + "/src/core/view/core_home.ecpp";
}

std::string WebApplicationCoreManager::getInitcomponentHPath(){
    return this->userSession.getSessionPath() + "/src/core/initcomponent.h";
}

std::string WebApplicationCoreManager::getMainCppPath( ){
    return this->userSession.getSessionPath() + "/src/main.cpp";
}

std::string WebApplicationCoreManager::getMakefilePath(){
    log_debug( __LINE__ << " getMakefilePath()\n" );
    log_debug(
        __LINE__
        << " this->userSession.getSessionPath()\n"
        << this->userSession.getSessionPath()
    );
    std::string complied_path = this->userSession.getSessionPath() + "/Makefile.tnt";
    log_debug( __LINE__ << " complied_path: \n" << complied_path );

    return complied_path;
}

std::string WebApplicationCoreManager::getSourceDir(){
    return this->userSession.getSessionPath() + "/src";
}

// I --------------------------------------------------------------------------
bool WebApplicationCoreManager::isApplicationCoreExist(){

    if ( !cxxtools::Directory::exists( this->getSourceDir() ) ) {
        return false;
    };
    if ( !cxxtools::FileInfo::exists( this->getMainCppPath() ) ) {
        return false;
    };
    return true;
}


} // END namespace Core
} // end namespace Tww




