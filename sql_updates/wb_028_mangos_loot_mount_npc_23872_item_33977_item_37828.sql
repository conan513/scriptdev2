DELETE FROM `creature_loot_template` WHERE (`entry`=23872);
INSERT INTO `creature_loot_template` VALUES 
(23872, 49118, 13.4309, 0, 1, 1, 0, 0, 0),
(23872, 49116, 14.0277, 0, 1, 1, 0, 0, 0),
(23872, 49074, 14.8405, 0, 1, 1, 0, 0, 0),
(23872, 49076, 15.4289, 0, 1, 1, 0, 0, 0),
(23872, 49080, 15.9284, 0, 1, 1, 0, 0, 0),
(23872, 49078, 16.466, 0, 1, 1, 0, 0, 0),
(23872, 38280, 100, 0, 1, 1, 0, 0, 0),
(23872, 38281, 100, 0, 1, 1, 0, 0, 0);

INSERT INTO creature_loot_template (entry,item,ChanceOrQuestChance) VALUES (23872,37828,1.7); 
UPDATE creature_loot_template SET ChanceOrQuestChance=10.5 WHERE entry=23862 AND item=33977;
 
INSERT INTO creature_loot_template (entry,item,ChanceOrQuestChance) VALUES (23872,33977,1.6);
UPDATE creature_loot_template SET ChanceOrQuestChance=9.5 WHERE entry=23862 AND item=37828;