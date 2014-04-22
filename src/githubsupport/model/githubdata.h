/*****************************************************************************
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

*****************************************************************************/

#ifndef GITHUBSUPPORT_GITHUBDATA_H 
#define GITHUBSUPPORT_GITHUBDATA_H 

#include <string>

namespace GithubSupport {

/**
* @class GithubData This class storage the data of ... 
* This class has a database support. The function "saveAsNew()" save
* the class properties as new data set in a datab dase. For createing 
* a new table for data storage you can use this command:
* @code 
* CREATE TABLE GithubData (
*     id INT PRIMARY KEY NOT NULL,
*     GithubData TEXT
* );
* @endcode 
* @todo fill this with more information!
*/
class GithubData {

public:
    /**
     * @todo need a comment for constructor. 
     */
    GithubData():
        downloadUrl(""){};

    /**
     * @todo need a comment. 
     * @return 
     */
     const std::string get_downloadUrl() const {
        return this->downloadUrl;
    }

    /**
     * @todo need a comment. 
     * @arg _newValue 
     */
    void set_downloadUrl( std::string _newValue ){
        this->downloadUrl = _newValue;
    }

    /**
     * This function save the value(s) of the class in a 
     * data base. 
     * @return the id of the new data set. 
     */
     int saveAsNew();

private:

    /**
     * @todo need a comment.
*/
    std::string downloadUrl;

}; // and of class GithubData
} // and of namespace GithubSupport
#endif