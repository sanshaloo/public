#Let's get the image first
From ubuntu

# Update the packages and image

RUN apt -y  update
# In case we need to debug with wget or curl, install them
RUN DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC apt-get -y install tzdata
RUN apt install -y apache2 wget curl cronolog
#RUN apt install -t apach2-utils
RUN apt clean

# Got to change the port to 8080
# Lets change the ports.conf for port 8080
# RUN sed -i 's/^Listen 80/Listen 8080/g' /etc/apache/ports.conf

#Lets enable some module. Running a listen on port 80 is not desirable so lets redirect to port 443
RUN a2enmod ssl socache_shmcb rewrite

# Rather than inserting a line within a block, It's better to push the file
# In real world the config files can really get complicated
#
#  Let's add cronolog to the log files as well
RUN a2ensite default-ssl
COPY files/000-default.conf /etc/apache2/sites-available/000-default.conf
COPY files/index.html /var/www/html/index.html
# Better source the file

#RUN  . /etc/apache2/envvars ; chown $APACHE_RUN_USER:$APACHE_RUN_GROUP /var/www/html/index.html
RUN  chown www-data:www-data /var/www/html/index.html


EXPOSE  80 443

CMD ["/usr/sbin/apachectl", "-D", "FOREGROUND"]
