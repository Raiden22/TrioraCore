UPDATE `creature_template` SET `ScriptName` = 'npc_demolisher_engineerer' WHERE `entry` IN (30400,30499);

DELETE FROM `outdoorpvp_template` WHERE TypeId=7;
INSERT INTO `outdoorpvp_template` (`TypeId`, `ScriptName`, `comment`) VALUES
('7', 'outdoorpvp_wg', 'Wintergrasp');