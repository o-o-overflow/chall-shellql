CREATE DATABASE IF NOT EXISTS `shellql`;

CREATE USER 'shellql'@'%' IDENTIFIED BY 'shellql';

GRANT USAGE ON * . * TO 'shellql'@'%' IDENTIFIED BY 'shellql' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0 ;

GRANT SELECT ON `shellql` . * TO 'shellql'@'%';

USE `shellql`;

DROP TABLE IF EXISTS `flag`;

CREATE TABLE flag (
  flag varchar(160)
);

INSERT INTO `flag` values('OOO{shellcode and webshell is old news, get with the times my friend!}');
