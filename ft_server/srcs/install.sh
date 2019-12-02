#!/bin/bash

apt-get install -y -qq wget gnupg lsb-release
apt-get update -y -qq

# mysql
wget https://repo.mysql.com/mysql-apt-config_0.8.13-1_all.deb
DEBIAN_FRONTEND=noninteractive echo "mysql-apt-config mysql-apt-config/select-server select mysql-5.7" | /usr/bin/debconf-set-selections
DEBIAN_FRONTEND=noninteractive dpkg --install mysql-apt-config_0.8.13-1_all.deb
apt-get -y -qq update
DEBIAN_FRONTEND=noninteractive apt-get install -y -qq mysql-server

chown -R mysql: /var/lib/mysql/
service mysql start
mysql -u root -e "CREATE USER 'wordpress'@'localhost' IDENTIFIED BY 'wppassword';"
mysql -u root -e "CREATE DATABASE wordpress;"
mysql -u root -e "GRANT ALL PRIVILEGES ON wordpress.* TO wordpress@localhost IDENTIFIED BY 'wppassword'; FLUSH PRIVILEGES;"

# phpmyadmin
apt-get install -y -qq php7.3-fpm php7.3-mysql php7.3-mbstring php-fpm 
wget https://files.phpmyadmin.net/phpMyAdmin/4.9.2/phpMyAdmin-4.9.2-all-languages.tar.gz
mkdir /var/www/html/phpmyadmin
tar xzf phpMyAdmin-4.9.2-all-languages.tar.gz --strip-components=1 -C /var/www/html/phpmyadmin

# wordpress
wget https://wordpress.org/latest.tar.gz
tar -xzvf latest.tar.gz
chown -R www-data:www-data wordpress/
mv wordpress/* /var/www/html/
rm -rf wordpress latest.tar.gz mysql-apt-config_0.8.13-1_all.deb phpMyAdmin-4.9.2-all-languages.tar.gz