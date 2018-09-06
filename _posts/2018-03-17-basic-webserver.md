---
layout: post
title: Basic Web Server with SSL
tags: [httpd, apache, service configuration, CentOS, ssl]
---

Host: CentOS 7<br>

<H3>Set up the server<H3>
`# yum install httpd`<br>

- httpd configuration file:<br>
`# vi /etc/httpd/conf/httpd.conf`<br>

```
[...]
# port/ip the server listens to:
# Listen *:80
# Listen 192.168.1.100:80
Listen 80
[...]
# log files located at /var/log/httpd/
ErrorLog "logs/error_log"
[...]
CustomLog "logs/access_log" combined
[...]
# root dir for the website:
DocumentRoot "/var/www/html"
[...]
# hostname as servername
ServerName localhost
[...]
```

<H3>Set up SSL</H3>
`# yum install ssl_mod openssl`<br>

- Generate self-signed certificate
```
# location to store
tmpath=/etc/pki/tls

# Generate private key 
openssl genrsa -out $tmpath/private/test.key 2048 

# Generate CSR 
openssl req -new -key $tmpath/private/test.key -out $tmpath/private/test.csr

# Generate Self Signed Cert
openssl x509 -req -days 365 -in $tmpath/private/test.csr -signkey $tmpath/private/test.key -out $tmpath/certs/test.crt
```
- update Apache SSL config file<br>
`# vi /etc/httpd/conf.d/ssl.conf`<br>

```
[...]
SSLCertificateFile /etc/pki/tls/certs/test.crt
[...]
SSLCertificateKeyFile /etc/pki/tls/private/test.key
[...]
```

- configure firewall<br>
```
firewall-cmd --permanent --zone=public --add-service=http
firewall-cmd --permanent --zone=public --add-service=https
firewall-cmd --reload
```

`# systemctl start/restart/enable httpd`

- links:<br>
https://httpd.apache.org/docs/2.4/<br>
https://wiki.centos.org/HowTos/Https<br>
https://www.tecmint.com/setup-apache-with-name-based-virtual-hosting-with-ssl-certificate/<br>

