FROM    debian:buster

EXPOSE  80 443
RUN     apt-get update -qq
RUN     apt-get install -y -qq apt-utils
RUN     apt-get install -y -qq nginx
RUN     echo "daemon off;" >> /etc/nginx/nginx.conf
COPY    srcs/default /etc/nginx/sites-available/
COPY    srcs/nginx-selfsigned.crt /etc/ssl/certs/
COPY    srcs/nginx-selfsigned.key /etc/ssl/private/
COPY    srcs/dhparam.pem /etc/nginx/
COPY    srcs/start.sh /
COPY    srcs/install.sh /
RUN     sh /install.sh
COPY    srcs/wp-config.php /var/www/html/
CMD     sh /start.sh