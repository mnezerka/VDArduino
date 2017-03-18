-- phpMyAdmin SQL Dump
-- version 3.4.3.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Mar 18, 2017 at 10:53 PM
-- Server version: 5.7.17
-- PHP Version: 5.6.30-7+deb.sury.org~xenial+1

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `arduino`
--

-- --------------------------------------------------------

--
-- Table structure for table `graph`
--

CREATE TABLE IF NOT EXISTS `graph` (
  `id` char(1) COLLATE utf8_czech_ci NOT NULL,
  `description` varchar(30) COLLATE utf8_czech_ci NOT NULL,
  `unit` varchar(5) COLLATE utf8_czech_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `measure`
--

CREATE TABLE IF NOT EXISTS `measure` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `sensor` varchar(5) COLLATE utf8_czech_ci NOT NULL,
  `value1` float DEFAULT NULL,
  `value2` float DEFAULT NULL,
  `value3` float DEFAULT NULL,
  `value4` float DEFAULT NULL,
  `value5` float DEFAULT NULL,
  `text1` varchar(32) COLLATE utf8_czech_ci DEFAULT NULL,
  `text2` varchar(32) COLLATE utf8_czech_ci DEFAULT NULL,
  `text3` varchar(32) COLLATE utf8_czech_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `timestamp` (`timestamp`,`sensor`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `program`
--

CREATE TABLE IF NOT EXISTS `program` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `title` varchar(50) COLLATE utf8_czech_ci NOT NULL,
  `color` varchar(10) COLLATE utf8_czech_ci NOT NULL,
  `priority` int(11) NOT NULL,
  `production` tinyint(1) NOT NULL,
  `sun` tinyint(1) NOT NULL,
  `mon` tinyint(1) NOT NULL,
  `tue` tinyint(1) NOT NULL,
  `wed` tinyint(1) NOT NULL,
  `thu` tinyint(1) NOT NULL,
  `fri` tinyint(1) NOT NULL,
  `sat` tinyint(1) NOT NULL,
  `from_time` time NOT NULL,
  `to_time` time NOT NULL,
  `from_date` date DEFAULT NULL,
  `to_date` date DEFAULT NULL,
  `min` float DEFAULT NULL,
  `max` float DEFAULT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

-- --------------------------------------------------------

--
-- Table structure for table `sensor`
--

CREATE TABLE IF NOT EXISTS `sensor` (
  `sensor` varchar(5) COLLATE utf8_czech_ci NOT NULL,
  `comment` varchar(64) COLLATE utf8_czech_ci NOT NULL,
  `color1` varchar(7) COLLATE utf8_czech_ci NOT NULL,
  `color2` varchar(7) COLLATE utf8_czech_ci NOT NULL,
  `color3` varchar(7) COLLATE utf8_czech_ci NOT NULL,
  `color4` varchar(7) COLLATE utf8_czech_ci NOT NULL,
  `color5` varchar(7) COLLATE utf8_czech_ci NOT NULL,
  `graph1` char(1) COLLATE utf8_czech_ci NOT NULL,
  `graph2` char(1) COLLATE utf8_czech_ci NOT NULL,
  `graph3` char(1) COLLATE utf8_czech_ci NOT NULL,
  `graph4` char(1) COLLATE utf8_czech_ci NOT NULL,
  `graph5` char(1) COLLATE utf8_czech_ci NOT NULL,
  `sufix1` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `sufix2` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `sufix3` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `sufix4` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `sufix5` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `visible` tinyint(1) NOT NULL,
  `implicit` tinyint(1) NOT NULL,
  PRIMARY KEY (`sensor`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
