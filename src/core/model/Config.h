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

#ifndef CORE_CONFIG_H
#define CORE_CONFIG_H

#include <string>
#include <cxxtools/serializationinfo.h>


namespace Tww {
namespace Core {

/**
* @class Config This class read a configuration file.
* The form of date in the configuration file is json.
*/
class Config {

    friend void operator>>= (const cxxtools::SerializationInfo& si, Config& config );



public:
    static Config& it();

    void read(const std::string& filename = "");

    const cxxtools::SerializationInfo& logging() const
    { return m_logging; }

    const std::string& appIp() const
    { return m_appIp; }

    unsigned short appPort() const
    { return m_appPort; }

    const std::string& domainName() const
    { return m_domainName; }

    unsigned sessionTimeout() const
    { return m_sessionTimeout; }


private:
    bool                        configRead;
    cxxtools::SerializationInfo m_logging;
    std::string                 m_appIp;
    unsigned short              m_appPort;
    std::string                 m_domainName;
    unsigned                    m_sessionTimeout;


public:

    Config()
      : configRead(false),
        m_appIp(""),
        m_appPort(8008),
        m_domainName( "tntwebwizard.domain" ),
        m_sessionTimeout( 1000 )
    { }

};

} // namespace Core
} // namespace Tww

#endif
