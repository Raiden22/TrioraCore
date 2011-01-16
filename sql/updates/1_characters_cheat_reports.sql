DROP TABLE IF EXISTS `cheat_reports`;
CREATE TABLE `cheat_reports` (
  `id` int(11) unsigned NOT NULL auto_increment,
  `guid` int(11) unsigned NOT NULL,
  `name` varchar(100) default NULL,
  `mapid` smallint(5) unsigned NOT NULL default '0',
  `position_x` float NOT NULL default '0',
  `position_y` float NOT NULL default '0',
  `position_z` float NOT NULL default '0',
  `report` varchar(100) default NULL,
  `time` bigint(20) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `guid` (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;
