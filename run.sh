#!/bin/bash
set -eu
cd `dirname $0`

sudo docker run --name mysqld -e MYSQL_ROOT_PASSWORD=password -d -p 13306:3306 mysql
sleep 10
mysql -u root -h 127.0.0.1 -P 13306 -ppassword < setup.sql
sudo docker build -t mod_condb .
sudo docker run -id --name mod_condb --link mysqld:mysql -p 8080:80 mod_condb
sleep 10
curl localhost:8080/condb

