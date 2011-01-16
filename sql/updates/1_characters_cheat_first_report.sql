DROP TABLE IF EXISTS `cheat_first_report`;
CREATE TABLE `cheat_first_report` (
  `id` int(11) unsigned NOT NULL auto_increment,
  `guid` int(11) unsigned NOT NULL,
  `name` varchar(100) collate utf8_unicode_ci default NULL,
  `time` bigint(20) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `guid` (`guid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=1 ;
