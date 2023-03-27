FROM ubuntu:22.04
RUN apt-get -y update
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Bratislava
RUN apt-get install -y tzdata
RUN apt -y install mysql-server
RUN chmod -R 777 /run/mysqld
RUN sed -i 's/bind-address\t\t= 127.0.0.1/bind-address\t\t= 0.0.0.0/g' /etc/mysql/mysql.conf.d/mysqld.cnf
RUN sed -i 's/mysqlx-bind-address\t\t= 127.0.0.1/mysqlx-bind-address\t\t= 0.0.0.0/g' /etc/mysql/mysql.conf.d/mysqld.cnf

## CREATE IMAGE
# docker build -t dbs_image .

## RUN CONTAINER
# docker run -dit -v path.to.sql_folder:/home/ --name dbs -p 3307:3306 dbs_image
# ! docker run -dit -v C:\Users\l3moN\Documents\GithubRepos\stu-fei\docker\sql:/home/ --name dbs -p 3307:3306 dbs_image

## CONFIGURE MYSQL
# docker container exec -it dbs /bin/bash
#  service mysql start
#  mysql -u root < /home/test.sql