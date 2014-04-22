/* 
Copyright (C) <year>  <name of author> 

This program is free software: you can redistribute it and/or modify 
it under the terms of the GNU Affero General Public License as published by 
the Free Software Foundation, either version 3 of the License, or later 
version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU Affero General Public License for more details. 

You should have received a copy of the GNU Affero General Public License 
along with this program.  If not, see <http://www.gnu.org/licenses/>.    

*/ 

#include <githubsupport/model/githubdata.h>

#include <tntdb/connect.h>
#include <tntdb/transaction.h>
#include <tntdb/statement.h>

#include <string>
#include <cxxtools/log.h>

namespace GithubSupport {

log_define("GithubSupport.GithubData")

int GithubData::saveAsNew() {
    log_debug("saveAsNew"  );
    std::string dbDriver;
    dbDriver = "sqlite:newproject_a.db";
    // alternativ driver configuration for PostgreSQL
    // dbDriver = "postgresql:password=XXX dbname=newproject_a host=localhost port=5432 user=newproject_a";
    tntdb::Connection conn( tntdb::connectCached( dbDriver ) );
    tntdb::Transaction trans(conn);
    tntdb::Statement insQuote = conn.prepare(
        "INSERT INTO GithubData (\
            downloadUrl\
        ) VALUES ( \
            :downloadUrl\
        )"
    );
    insQuote
        .set( "downloadUrl", this->downloadUrl)
        .execute(); 
    int itemID = conn.lastInsertId("GithubData_id_seq");
    return itemID;
}
} // and of namespace GithubSupport
