## Sample commands for running docker container on your local manchine

### build the image with docker

docker image build -t . -t apache_image:1.0

docker image list 

REPOSITORY     TAG       IMAGE ID       CREATED         SIZE

apache_image   1.3       d2482f6251dc   5 minutes ago   234MB

ubuntu         latest    08d22c0ceb15   4 weeks ago     77.8MB


### Run the docker container image locally

docker -d run -p 8080:80 -p 8443:443  d2482f6251dc


sas@sas-Inspiron-5537:~$ docker run -d -p 8080:80 -p 8443:443  d2482f6251dc

b8ba240d1c7553f65b25116c4e927b0dc64647633726152e75acadc4aa270c7e


### Check if it's running

sas@sas-Inspiron-5537:~$ docker ps

CONTAINER ID   IMAGE          COMMAND                  CREATED         STATUS         PORTS                                                                            NAMES

b8ba240d1c75   d2482f6251dc   "/usr/sbin/apachectl…"   8 seconds ago   Up 6 seconds   0.0.0.0:8080->80/tcp, :::8080->80/tcp, 0.0.0.0:8443->443/tcp, :::8443->443/tcp   funny_shtern



### As the config file in the container redirects the incoming port 80 connections to port localhost:8443->container:443


wget -S --no-check-certificate -O - http://localhost:8080


sas@sas-Inspiron-5537:~$ wget -S --no-check-certificate -O - http://localhost:8080

--2023-04-06 17:34:33--  http://localhost:8080/

Resolving localhost (localhost)... 127.0.0.1

Connecting to localhost (localhost)|127.0.0.1|:8080... connected.

HTTP request sent, awaiting response...

  HTTP/1.1 301 Moved Permanently
  
  Date: Fri, 07 Apr 2023 00:34:33 GMT
  
  Server: Apache/2.4.52 (Ubuntu)
  
  Location: https://localhost:8443/
  


### Shutdown your container


docker stop funny_shtern

funny_shtern

sas-Inspiron-5537:~# docker ps

CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS    PORTS     NAMES

