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

#include <core/model/NewModelData.h>
#include <core/model/TntWebWizardException.h>

#include <cxxtools/fileinfo.h>
#include <cxxtools/directory.h>
#include <cxxtools/log.h>

#include <fstream>
#include <ostream>
#include <sstream>

#include <string>         // std::string
#include <locale>         // std::locale, std::toupper
// #include <algorithm>
#include <cxxtools/utf8codec.h>
#include <cxxtools/string.h>
#include <cxxtools/char.h>


namespace Tww {
namespace Core {

log_define("Core.NewModelData")

// === A ===

// === C ===


void NewModelData::createCppFile(){
    log_debug("createCppFile()" );
    bool firstItem = true;
    std::ostringstream fileContent;

    fileContent
        << "/* \n"
        << this->projectData.getSourceCodeHeader()
        << "\n*/ \n\n"
    ;
    fileContent
        << "#include <" << this->toLower( this->componentNamespace) << "/model/"
        << this->toLower( this->modelName ) << ".h>\n\n"
    ;

    if ( this->projectData.isTntDB() == true ) {
        fileContent
            << "#include <tntdb/connect.h>\n"
            << "#include <tntdb/transaction.h>\n"
            << "#include <tntdb/statement.h>\n\n"
            << "#include <string>\n"
        ;
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if (
            it->second == "std::string"
            and this->projectData.isTntDB() == false
        ) {
            fileContent  << "#include <string>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::vector") {
            fileContent  << "#include <vector>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::map") {
            fileContent  << "#include <map>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::list") {
            fileContent  << "#include <list>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::stringstream") {
            fileContent  << "#include <sstream>\n";
            break;
        }
    }
    if ( this->jsonSerializationSupport == true ){
        fileContent
            << "#include <cxxtools/jsondeserializer.h>\n"
            << "#include <cxxtools/jsonserializer.h>\n"
        ;
    }
    if ( this->xmlSerializationSupport == true ){
        fileContent
            << "#include <cxxtools/xml/xmlserializer.h>\n"
            << "#include <cxxtools/xml/xml.h>\n"
        ;
    }
    if ( this->projectData.isCxxtoolsLoging( ) ){
        fileContent  << "#include <cxxtools/log.h>\n";
    }
    if( this->componentNamespace != "" ){
        fileContent  << "\nnamespace " << this->componentNamespace << " {\n\n";
    }

    if ( this->projectData.isCxxtoolsLoging( ) ){
        fileContent
            << "log_define(\"" << this->componentNamespace << "."
            << this->modelName << "\")\n\n"
        ;
    }

    if ( this->jsonSerializationSupport == true
        or this->xmlSerializationSupport == true
    ){

        fileContent
            << "void operator>>= (const cxxtools::SerializationInfo& si, "
            << this->modelName << "& _" << toLower( this->modelName ) << " )\n"
            << "{\n"
        ;
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            fileContent
                << "    si.getMember(\"" << it->first
                << "\") >>= _" << toLower( this->modelName ) << "."
                << it->first << ";\n"
            ;
        }
        fileContent
            << "}\n\n"
            << "void operator<<= ( cxxtools::SerializationInfo& si, const "
            << this->modelName << "& _" << toLower( this->modelName ) << " )\n"
            << "{\n"
        ;
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            fileContent
                << "    si.addMember(\"" << it->first
                << "\") <<= _" << toLower( this->modelName ) << ".get_"
                << it->first << "();\n"
            ;
        }
    }
    if ( this->jsonSerializationSupport == true ){
        fileContent
            << "} \n\n"
            << "std::string " << this->modelName << "::getJson( ) {\n"
            << "    std::string json_text;\n"
            << "    std::stringstream sstream;\n"
            << "    cxxtools::JsonSerializer serializer( sstream );\n"
            << "    // this makes it just nice to read\n"
            << "    serializer.beautify(true);\n"
            << "    serializer.serialize( *this ).finish();\n"
            << "    json_text = sstream.str();\n"
            << "    return json_text;\n"
            << "}\n\n"
            << "void " << this->modelName << "::loadJson( std::stringstream& _input ){\n"
            << "        cxxtools::JsonDeserializer deserializer( _input );\n"
            << "        deserializer.deserialize(*this);\n"
            << "        return;\n"
            << "}\n\n"
        ;
    }

    if ( this->xmlSerializationSupport == true ){
        fileContent
            << "std::string " << this->modelName << "::getXML( ) {\n"
            << "    std::stringstream sstream;\n"
            << "    cxxtools::xml::XmlSerializer serializer( sstream );\n"
            << "    // this makes it just nice to read\n"
            << "    serializer.serialize( *this, \"" << this->modelName << "\" );\n"
            << "    return sstream.str();\n"
            << "}\n\n"
            << "void " << this->modelName << "::loadXML( std::stringstream& _input ){\n"
            << "        cxxtools::xml::XmlDeserializer deserializer( _input );\n"
            << "        deserializer.deserialize(*this);\n"
            << "        return;\n"
            << "}\n"
        ;
    }

    // isTntDB( )
    if ( this->projectData.isTntDB() == true ){
        fileContent
            << "int " << this->modelName << "::saveAsNew() {\n"
        ;
        if ( this->projectData.isCxxtoolsLoging( ) ){
            fileContent
                << "    log_debug(\"saveAsNew\"  );\n"
            ;
        }
        fileContent
            << "    std::string dbDriver;\n"
            << "    dbDriver = \"sqlite:" << this->makefileData.getBinName() << ".db\";\n"
            << "    // alternativ driver configuration for PostgreSQL\n"
            << "    // dbDriver = \"postgresql:password=XXX dbname="
            << this->makefileData.getBinName() << " host=localhost port=5432 user="
            << this->makefileData.getBinName() << "\";\n"
            << "    tntdb::Connection conn( tntdb::connectCached( dbDriver ) );\n"
            << "    tntdb::Transaction trans(conn);\n"
            << "    tntdb::Statement insQuote = conn.prepare(\n"
            << "        \"INSERT INTO " << this->modelName << " (\\\n"
        ;
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            if ( firstItem == true ) {
                firstItem = false;
            } else {
                fileContent << ",\\\n" ;
            }
            fileContent  << "            " << it->first ;
        }
        fileContent
            << "\\\n        ) VALUES ( \\\n"
        ;
        firstItem = true;
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            if ( firstItem == true ) {
                firstItem = false;
            } else {
                fileContent << ",\\\n" ;
            }
            fileContent  << "            :" << it->first ;
        }
        fileContent
            << "\\\n        )\"\n"
            << "    );\n"
            << "    insQuote\n"
        ;
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            fileContent
                << "        .set( \"" << it->first << "\", this->"
                << it->first << ")\n"
            ;
        }
        fileContent
            << "        .execute(); \n"
            << "    int itemID = conn.lastInsertId(\"" << this->modelName << "_id_seq\");\n"
            << "    return itemID;\n"
            << "}\n"
        ;
    }


    if( this->componentNamespace != ""){
        fileContent  << "} // and of namespace " << this->componentNamespace << "\n";
    }

    std::stringstream modelCppFileName;
    modelCppFileName
        << this->userSession.getSessionPath()
        << "/src/"
        << this->toLower( this->componentNamespace )
        << "/model/"
        <<this->toLower( this->modelName )
        << ".cpp"
    ;

    log_debug(
        __LINE__
        << " write in: \n"
        << modelCppFileName.str()
    );
    std::ofstream modeCppFile( modelCppFileName.str().c_str() );
    modeCppFile << fileContent.str() ;
    modeCppFile.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->userSession.getSessionPath() + "/Makefile.tnt" );
    this->makefileData.addCppFile(
        "./src/"
        + this->toLower( this->componentNamespace )
        + "/model/"
        + this->toLower( this->modelName )
        + ".cpp"
    );
    this->makefileData.write( this->userSession.getSessionPath() + "/Makefile.tnt" );
}

void NewModelData::createFiles(){
    std::stringstream compDirName;
    compDirName
        << this->userSession.getSessionPath()
        << "/src/"
        << this->toLower( this->componentNamespace )
    ;
    if ( !cxxtools::Directory::exists( compDirName.str() ) ) {
        cxxtools::Directory::create( compDirName.str() );
    }
    compDirName
        << "/model/"
    ;
    if ( !cxxtools::Directory::exists( compDirName.str() ) ) {
        cxxtools::Directory::create( compDirName.str() );
    }
    this->createHFile();
    this->createCppFile();
}


void NewModelData::createHFile(){
    log_debug("createHFile()" );
    std::ostringstream fileContent;
    bool firstItem = true;

    fileContent
        << "/*****************************************************************************\n"
        << this->projectData.getSourceCodeHeader()
        << "\n*****************************************************************************/\n\n"
        << "#ifndef " << toUpper( this->componentNamespace )
        << "_" << toUpper( this->modelName ) << "_H \n"
        << "#define " << toUpper( this->componentNamespace )
        << "_" << toUpper( this->modelName ) << "_H \n\n"
    ;
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::string") {
            fileContent  << "#include <string>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::vector") {
            fileContent  << "#include <vector>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::map") {
            fileContent  << "#include <map>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::list") {
            fileContent  << "#include <list>\n";
            break;
        }
    }
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( it->second == "std::stringstream"
            or  this->jsonSerializationSupport == true
        ) {
            fileContent  << "#include <sstream>\n";
            break;
        }
    }
    if ( this->jsonSerializationSupport == true ){
        fileContent
            << "#include <cxxtools/serializationinfo.h>\n"
        ;
    }
    if( this->componentNamespace != "" ){
        fileContent  << "\nnamespace " << this->componentNamespace << " {\n\n";
    }
    if( this->projectData.isDoxygenTemplates( ) == true ){
        fileContent
            << "/**\n"
            << "* @class " << this->modelName << " This class storage the data of ... \n"
        ;
    // isTntDB( )
    if ( this->projectData.isTntDB() == true ){
        fileContent
            << "* This class has a database support. The function \"saveAsNew()\" save\n"
            << "* the class properties as new data set in a datab dase. For createing \n"
            << "* a new table for data storage you can use this command:\n"
            << "* @code \n"
            << "* CREATE TABLE " <<  this->modelName << " (\n"
            << "*     id INT PRIMARY KEY NOT NULL,\n"
        ;
        firstItem = true;
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            if ( firstItem == true ) {
                firstItem = false;
            } else {
                fileContent << ",\n" ;
            }
            if(
                it->second  == "std::string"
                or it->second  == "cxxtools::String"
            ){
                fileContent << "*     " << this->modelName << " TEXT";
            }
            if(
                it->second  == "int"
                or it->second  == "long int"
                or it->second  == "unsigned int"
                or it->second  == "bool"
            ){
                fileContent << "*     " << this->modelName << " INT";
            }
            if( it->second  == "float" ){
                fileContent << "*     " << this->modelName << " REAL";
            }

        }
        fileContent
            << "\n"
            << "* );\n"
            << "* @endcode \n"
        ;
    }
        fileContent
            << "* @todo fill this with more information!\n"
            << "*/\n"
        ;
    }
    fileContent << "class " << this->modelName << " {\n\n" ;

    if( this->isJsonSerializationSupported() == true
        or this->isXmlSerializationSupported() == true
    ) {
        fileContent
            << "   /**\n"
            << "    * Definition how to deserialize the class data of "
            << this->modelName << "\n"
            << "    * @arg si serialization info\n"
            << "    * @arg " << this->modelName << " the data class\n"
            << "    */\n"
            << "    friend void operator>>= (const cxxtools::SerializationInfo& si, "
            << this->modelName << "& _" << toLower( this->modelName ) << " );\n\n"

            << "    /**\n"
            << "    * Definition how to serialize the class of data.\n"
            << "    * @arg si serialization info\n"
            << "    * @arg " << this->modelName << " the data class\n"
            << "    */\n"
            << "    friend void operator<<= ( cxxtools::SerializationInfo& si, "
            << "const " << this->modelName << "& _" << toLower( this->modelName ) << " );\n\n"
        ;
    }

    fileContent << "public:\n" ;

    if ( this->isConstructor() == true){
        if ( this->projectData.isDoxygenTemplates( ) == true ) {
            fileContent
                << "    /**\n"
                << "     * @todo need a comment for constructor. \n"
                << "     */\n"
            ;
        }
        if( this->propertyMap.size() > 0 ){
            int contvarinits = 0;
            for (
                std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
                it!=this->propertyMap.end();
                ++it
            ){
                if(
                    it->second  == "std::string"
                    or it->second  == "cxxtools::String"
                ){
                    if(contvarinits == 0) {
                        fileContent << "    " << this->modelName << "():\n";
                    }
                    if(contvarinits > 0) {
                        fileContent << ",\n";
                    }
                    fileContent << "        " << it->first << "(\"\")";
                    ++contvarinits;
                }
                if(
                    it->second  == "int"
                    or it->second  == "long int"
                    or it->second  == "unsigned int"
                ){
                    if(contvarinits == 0) {
                        fileContent << "    " << this->modelName << "():\n";
                    }
                    if(contvarinits > 0) {
                        fileContent << ",\n";
                    }
                    fileContent << "        " << it->first << "(0)";
                    ++contvarinits;
                }
                if( it->second  == "float" ){
                    if(contvarinits == 0) {
                        fileContent << "    " << this->modelName << "():\n";
                    }
                    if(contvarinits > 0) {
                        fileContent << ",\n";
                    }
                    fileContent << "        " << it->first << "(0.0)";
                    ++contvarinits;
                }
                if( it->second  == "bool" ){
                    if(contvarinits == 0) {
                        fileContent << "    " << this->modelName << "():\n";
                    }
                    if(contvarinits > 0) {
                        fileContent << ",\n";
                    }
                    fileContent << "        " << it->first << "(true)";
                    ++contvarinits;
                }

            }
            fileContent << "{};\n\n";
        } else {
            fileContent << "    " << this->modelName << "(){};\n\n";
        }
    }
    if ( this->isDestructor() == true){
        if ( this->projectData.isDoxygenTemplates( ) == true ) {
            fileContent
                << "    /**\n"
                << "     * @todo need a comment for destructor. \n"
                << "     */\n"
            ;
        }
        fileContent << "    ~" << this->modelName << "(){};\n\n";
    }

    if ( this->jsonSerializationSupport == true ){
        fileContent
            << "   /**\n"
            << "    * Get a export of " << this->modelName << " data in json format.\n"
            << "    * @return A json document.\n"
            << "    */\n"
            << "    std::string getJson( );\n\n"
            << "   /**\n"
            << "    * read json as string stream input.\n"
            << "    */\n"
            << "    void loadJson( std::stringstream& _input );\n\n"
        ;
    }
    if ( this->xmlSerializationSupport == true ){
        fileContent
            << "   /**\n"
            << "    * Get a export of " << this->modelName << " data in xml format.\n"
            << "    * @return A xml document.\n"
            << "    */\n"
            << "    std::string getXML( );\n\n"
            << "   /**\n"
            << "    * read xml as string stream input.\n"
            << "    */\n"
            << "    void loadXML( std::stringstream& _input );\n\n"
        ;
    }

    log_debug("isGetterFunctions(): " << this->isGetterFunctions() );
    if ( this->isGetterFunctions() == true){
        log_debug( "this->propertyMap.end(): " << this->propertyMap.size() );
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            if ( this->projectData.isDoxygenTemplates( ) == true ) {
                fileContent
                    << "    /**\n"
                    << "     * @todo need a comment. \n"
                    << "     * @return \n"
                    << "     */\n"
                ;
            }
            fileContent
                << "     const " << it->second << " get_" << it->first << "() const {\n"
                << "        return this->" << it->first << ";\n"
                << "    }\n\n";

        }
    }
    if ( this->isSetterFunctions() == true){
        log_debug("this->propertyMap.end(): " << this->propertyMap.size() );
        for (
            std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
            it!=this->propertyMap.end();
            ++it
        ){
            std::cout << it->first << " => " << it->second << '\n';
            if ( this->projectData.isDoxygenTemplates( ) == true ) {
                fileContent
                    << "    /**\n"
                    << "     * @todo need a comment. \n"
                    << "     * @arg _newValue \n"
                    << "     */\n"
                ;
            }
            fileContent
                << "    void set_" << it->first << "( "
                << it->second << " _newValue ){\n"
                << "        this->" << it->first << " = _newValue;\n"
                << "    }\n\n"
            ;

        }
    }

    // isTntDB( )
    if ( this->projectData.isTntDB() == true ){
        if ( this->projectData.isDoxygenTemplates( ) == true ) {
            fileContent
                << "    /**\n"
                << "     * This function save the value(s) of the class in a \n"
                << "     * data base. \n"
                << "     * @return the id of the new data set. \n"
                << "     */\n"
            ;
        }
        fileContent
            << "     int saveAsNew();\n"
        ;
    }
    fileContent << "\nprivate:\n\n";
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        // std::cout << it->first << " => " << it->second << '\n';
        if ( this->projectData.isDoxygenTemplates( ) == true ) {
            fileContent
                << "    /**\n"
                << "     * @todo need a comment.\n"
                << "*/\n"
            ;
        }
        fileContent << "    " << it->second << " " << it->first << ";\n\n";

    }
    fileContent  << "}; // and of class " << this->modelName << "\n";

    if( this->componentNamespace != ""){
        fileContent  << "} // and of namespace " << this->componentNamespace << "\n";
    }
    fileContent << "#endif" ;

    std::stringstream compHFileName;
    compHFileName
        << this->userSession.getSessionPath()
        << "/src/"
        << this->toLower( this->componentNamespace )
        << "/model/"
        << this->toLower( this->modelName )
        << ".h"
    ;

    log_debug(
        __LINE__
        << " write in: \n"
        << compHFileName.str()
    );
    std::ofstream compHfile( compHFileName.str().c_str() );
    compHfile << fileContent.str() ;
    compHfile.close();

    // Add new file in Makefile.tnt configuration.
    this->makefileData.read( this->userSession.getSessionPath() + "/Makefile.tnt" );
    this->makefileData.addHFile(
        "./src/"
        + this->toLower( this->componentNamespace )
        + "/model/"
        + this->toLower( this->modelName )
        + ".h"
    );
    this->makefileData.write( this->userSession.getSessionPath() + "/Makefile.tnt" );
}

// === G ===

std::vector<std::string> NewModelData::getPropertyList(){
    std::vector<std::string> allProperties;
    for (
        std::map<std::string,std::string>::iterator it=this->propertyMap.begin();
        it!=this->propertyMap.end();
        ++it
    ){
        allProperties.push_back( it->second + " " + it->first );
    }
    return allProperties;
}

// === T ===

std::string NewModelData::toLower( std::string _mixedString ){
    std::ostringstream upperString;
//     std::locale loc("de_DE.UTF8");
    std::locale loc;
    for (std::string::size_type i=0; i<_mixedString.length(); ++i){
        upperString << std::tolower(_mixedString[i],loc);
    }
    return upperString.str();
}

std::string NewModelData::toUpper( std::string _mixedString ){
    std::ostringstream upperString;
//     std::locale loc("de_DE.UTF8");
    std::locale loc;
    for (std::string::size_type i=0; i<_mixedString.length(); ++i){
        upperString << std::toupper(_mixedString[i],loc);
    }
    return upperString.str();
}

// === U ===



std::string NewModelData::cxxToUpper( std::string _mixedString ){
    std::ostringstream upperString;
    cxxtools::String lastLetter;
    cxxtools::String uMixedString = cxxtools::Utf8Codec::decode( _mixedString );
    for ( cxxtools::String::size_type i=0;
            i < uMixedString.length();
            ++i){
        upperString << cxxtools::toupper(uMixedString[i]);
    }
    return upperString.str();
}

// === W ===




} // namespace core
} // namespace Tww
