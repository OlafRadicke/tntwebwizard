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

#include <core/controller/BasicProjectDataController.h>

#include <core/model/MakefileData.h>
#include <core/model/ProjectData.h>
#include <core/model/UserSession.h>

#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>

#include <string>

namespace Tww {
namespace Core {


log_define("Core.BasicProjectDataController")

void BasicProjectDataController::formDataAssume ( tnt::QueryParams& qparam ){
    // query parameters

    // project data
    this->projectData.setProjectName(
        qparam.arg<std::string>("form_projectname")
    );
    this->projectData.setSourceCodeHeader(
        qparam.arg<std::string>("form_sourcecodeheader")
    );
    this->projectData.setDoxygenTemplates(
        qparam.arg<bool>("form_doxygen_templates")
    );
    this->projectData.setFormToken(
        qparam.arg<bool>("form_csrf_token")
    );
    this->projectData.setCxxtoolsLoging(
        qparam.arg<bool>("form_cxxtools_loging")
    );
    this->projectData.setRouteRevers(
        qparam.arg<bool>("form_route_revers")
    );

    // makefile data
    this->makefileData.setBinName(
        qparam.arg<std::string>("form_binaryfilename")
    );
}


void BasicProjectDataController::worker (
    tnt::HttpRequest& request,
    tnt::HttpReply& reply,
    tnt::QueryParams& qparam
){
    // query parameters

    std::string form_licence_template =
        qparam.arg<std::string>("form_licence_template");
    bool form_assume_licence =
        qparam.arg<bool>("form_assume_licence");
    bool form_save_button =
        qparam.arg<bool>("form_save_button");

    std::stringstream file_projectdata;
    file_projectdata << this->userSession.getSessionPath() << "/tntwebwizard.pro";
    std::stringstream file_makefile;
    file_makefile << this->userSession.getSessionPath() << "/Makefile.tnt";

    log_debug("file_projectdata: " << file_projectdata.str() );
    log_debug("file_makefile: " << file_makefile.str() );
    log_debug("form_save_button: " << form_save_button );
    log_debug("form_assume_licence: " << form_assume_licence );
    log_debug("form_licence_template: " << form_licence_template );

    // save button pressed
    if ( form_save_button ) {
        log_debug( "## " << __LINE__ << " ##" );
        this->formDataAssume ( qparam );
        this->projectData.write( file_projectdata.str() );
        this->makefileData.write( file_makefile.str() );
        this->feedback="The basic project date is saved.";
    } else {
        log_debug( "## " << __LINE__ << " ##" );
        // assume licence button pressed
        if ( form_assume_licence ) {
            log_debug( "## " << __LINE__ << " ##" );
            this->formDataAssume ( qparam );
            log_debug("add licence: " << form_licence_template );
            this->assumeLicence( form_licence_template );
        // page (first) load
        } else {
            log_debug( "## " << __LINE__ << " ##" );
            // read project configuration...
            log_debug("file_projectdata: " << file_projectdata.str() );
            this->projectData.read( file_projectdata.str() );
            this->makefileData.read( file_makefile.str() );
        }
    }
}


void BasicProjectDataController::assumeLicence( const std::string& _licence_template ){
    std::stringstream licencetext;

    if ( _licence_template == "AGPL3" ) {
        licencetext << "Copyright (C) <year>  <name of author> \n"
        << "\n"
        << "This program is free software: you can redistribute it and/or modify \n"
        << "it under the terms of the GNU Affero General Public License as published by \n"
        << "the Free Software Foundation, either version 3 of the License, or later \n"
        << "version. \n"
        << "\n"
        << "This program is distributed in the hope that it will be useful, \n"
        << "but WITHOUT ANY WARRANTY; without even the implied warranty of \n"
        << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the \n"
        << "GNU Affero General Public License for more details. \n"
        << "\n"
        << "You should have received a copy of the GNU Affero General Public License \n"
        << "along with this program.  If not, see <http://www.gnu.org/licenses/>.    \n";
    }

    if ( _licence_template == "Apache" ) {
        licencetext << " \n"
        << "Licensed to the Apache Software Foundation (ASF) under one \n"
        << "or more contributor license agreements.  See the NOTICE file \n"
        << "distributed with this work for additional information \n"
        << "regarding copyright ownership.  The ASF licenses this file \n"
        << "to you under the Apache License, Version 2.0 (the \n"
        << "\"License\"); you may not use this file except in compliance \n"
        << "with the License.  You may obtain a copy of the License at \n"
        << " \n"
        << "  http://www.apache.org/licenses/LICENSE-2.0 \n"
        << " \n"
        << "Unless required by applicable law or agreed to in writing, \n"
        << "software distributed under the License is distributed on an \n"
        << "\"AS IS\" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY \n"
        << "KIND, either express or implied.  See the License for the \n"
        << "specific language governing permissions and limitations \n";
    }

    if ( _licence_template == "MIT" ) {
        licencetext << " \n"
        << "Copyright (c) <year> <copyright holders> \n"
        << " \n"
        << "Permission is hereby granted, free of charge, to any person obtaining a copy \n"
        << "of this software and associated documentation files (the \"Software\"), to deal \n"
        << "in the Software without restriction, including without limitation the rights \n"
        << "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell \n"
        << "copies of the Software, and to permit persons to whom the Software is \n"
        << "furnished to do so, subject to the following conditions: \n"
        << " \n"
        << "The above copyright notice and this permission notice shall be included in \n"
        << "all copies or substantial portions of the Software. \n"
        << " \n"
        << "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR \n"
        << "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \n"
        << "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE \n"
        << "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER \n"
        << "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, \n"
        << "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN \n"
        << "THE SOFTWARE.     \n";
    }


    if ( _licence_template == "GPL3" ) {
        licencetext << " \n"
        << "<one line to give the program's name and a brief idea of what it does.> \n"
        << "Copyright (C) <year>  <name of author> \n"
        << " \n"
        << "This program is free software: you can redistribute it and/or modify \n"
        << "it under the terms of the GNU General Public License as published by \n"
        << "the Free Software Foundation, either version 3 of the License, or \n"
        << "(at your option) any later version. \n"
        << " \n"
        << "This program is distributed in the hope that it will be useful, \n"
        << "but WITHOUT ANY WARRANTY; without even the implied warranty of \n"
        << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the \n"
        << "GNU General Public License for more details. \n"
        << " \n"
        << "You should have received a copy of the GNU General Public License \n"
        << "along with this program.  If not, see <http://www.gnu.org/licenses/>.  \n" ;
    }

    if ( _licence_template == "BSD2" ) {
        licencetext << " \n"
        << "Copyright (c) <YEAR>, <OWNER>\n"
        << "All rights reserved.\n"
        << " \n"
        << "Redistribution and use in source and binary forms, with or without \n"
        << "modification, are permitted provided that the following conditions \n"
        << " are met:\n"
        << " \n"
        << "1. Redistributions of source code must retain the above copyright \n"
        << "   notice, this list of conditions and the following disclaimer.\n"
        << " \n"
        << "2. Redistributions in binary form must reproduce the above \n"
        << "   copyright notice, this list of conditions and the following  \n"
        << "   disclaimer in the documentation and/or other materials provided  \n"
        << "   with the distribution. \n"
        << " \n"
        << "THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS  \n"
        << "\"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT  \n"
        << "LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS  \n"
        << "FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE  \n"
        << "COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  \n"
        << "INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  \n"
        << "BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;  \n"
        << "LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER  \n"
        << "CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT  \n"
        << "LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN  \n"
        << "ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  \n"
        << "POSSIBILITY OF SUCH DAMAGE.     \n" ;
    }

    this->projectData.setSourceCodeHeader( licencetext.str() );
}


} // namespace core
} // namespace Tww

