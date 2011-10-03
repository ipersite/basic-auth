CREATE USER `squid`@localhost IDENTIFIED BY 'squid';
CREATE DATABASE `squid`;
GRANT ALL ON `squid`.* TO `squid`@localhost;
USE `squid`;
CREATE TABLE `users` (`id` INTEGER PRIMARY KEY AUTO_INCREMENT NOT NULL, `username` VARCHAR(255), `password` VARCHAR(255), `status` INTEGER, `realname` VARCHAR(255));

