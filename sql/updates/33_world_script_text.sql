DELETE FROM `script_texts` WHERE entry BETWEEN -1800074 AND -1800075;
INSERT INTO `script_texts` (`npc_entry`,`entry`,`content_default`,`content_loc1`,`content_loc2`,`content_loc3`,`content_loc4`,`content_loc5`,`content_loc6`,`content_loc7`,`content_loc8`,`sound`,`type`,`language`,`emote`,`comment`) VALUES
(0,-1800074,'Here''s the tome our representative brought from Wyrmrest. Get this to Caladis Brightspear immediately.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,11,1,'npc_36670 - SAY_2'),
(0,-1800075,'Watch your back, courier. I needn''t remind you of the value of the book, nor the fact that the Sunreavers will stop at nothing to take it from us.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,0,11,1,'npc_36670 - SAY_3');
