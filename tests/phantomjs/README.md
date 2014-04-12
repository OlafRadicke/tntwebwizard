# introduction

This tests in this directory use the phantomjs framework and the Python
binding python-selenium. It is working like a bot. It is simulating some
user case/work flows.

API-Docu: [http://selenium-python.readthedocs.org](http://selenium-python.readthedocs.org)

# Dependences / installations

## Python binding

su -c 'yum -y install python-selenium'

## phantomjs framewor

### From sources:

> [user@localhost ~]# su -c 'yum install gcc gcc-c++ make git openssl-devel freetype-devel fontconfig-devel'
> [user@localhost ~]# git clone git://github.com/ariya/phantomjs.git
> [user@localhost ~]# cd phantomjs
> [user@localhost ~]# git checkout 1.9
> [user@localhost ~]# ./build.sh
> [user@localhost ~]# cd rpm
> [user@localhost ~]# ./mkrpm.sh phantomjs


### From zip archiv

> [user@localhost ~]# su -c 'yum install gcc gcc-c++ make git openssl-devel freetype-devel fontconfig-devel'
> [user@localhost ~]# wget https://github.com/ariya/phantomjs/archive/1.9.zip
> [user@localhost ~]# unzip ./1.9.zip
> [user@localhost ~]#  cd ./phantomjs-1.9/
> [user@localhost ~]# ./build.sh
> [user@localhost ~]# cd rpm
> [user@localhost ~]# ./mkrpm.sh phantomjs
> [user@localhost ~]# su -c 'rpm -i /tmp/phantomjs-1.9.7-1.x86_64.rpm'
> [user@localhost ~]# du --max-dept=0 -h  /tmp/phantomjs-1.9.7*
> 745M    /tmp/phantomjs-1.9.7
> 13M /tmp/phantomjs-1.9.7-1.x86_64.rpm
