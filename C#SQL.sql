-- Adminer 4.2.2 MySQL dump

SET NAMES utf8;
SET time_zone = '+00:00';
SET foreign_key_checks = 0;
SET sql_mode = 'NO_AUTO_VALUE_ON_ZERO';

DROP TABLE IF EXISTS `uzivatel`;
CREATE TABLE `uzivatel` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `jmeno` varchar(255) COLLATE utf8_czech_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

INSERT INTO `uzivatel` (`id`, `jmeno`) VALUES
(6,	'dasdasd'),
(7,	'dasd'),
(10,	''),
(11,	'dsad'),
(12,	'dasd'),
(13,	'das'),
(14,	'das'),
(15,	'dasdas'),
(16,	'dasd'),
(17,	'dasd'),
(18,	'dasd'),
(19,	'dasd'),
(20,	'dasd'),
(21,	'dasd'),
(22,	'dasd'),
(23,	'dasd'),
(24,	'dasd'),
(25,	'dasd'),
(26,	'dasd'),
(27,	'dasd'),
(28,	'dasdasd'),
(29,	'dasdasd');

-- 2016-05-07 14:19:22
