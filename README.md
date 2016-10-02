# docker-mod_condb

## Run Docker container

```
sudo docker run --name mysqld -e MYSQL_ROOT_PASSWORD=password -d -p 13306:3306 mysql
mysql -u root -h 127.0.0.1 -P 13306 -p < setup.sql
sudo docker build -t mod_condb .
docker run -it --name mod_condb --rm  --link mysqld:mysql -p 8080:80 mod_condb
curl localhost:8080/condb
```

