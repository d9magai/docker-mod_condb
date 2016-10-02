FROM centos
MAINTAINER d9magai

RUN yum update -y && yum install -y \
    gcc-c++ \
    make \
    httpd-devel \
    apr-util-mysql \
    && yum clean all

COPY mod_condb.conf  /etc/httpd/conf.d/mod_condb.conf
COPY src /opt/condb_build
WORKDIR /opt/condb_build
RUN make && make install && make clean

EXPOSE 80
CMD ["/usr/sbin/httpd", "-D", "FOREGROUND"] 

