DELETE FROM `spell_target_position` WHERE `id` IN (70525, 70639);
INSERT INTO `spell_target_position` VALUES ('70525', '658', '1058.93', '98.38', '630.79', '1.95');
INSERT INTO `spell_target_position` VALUES ('70639', '658', '1058.93', '98.38', '630.79', '1.95');

UPDATE `creature_template` SET `faction_A` = 20, `faction_H` = 20 WHERE `entry` IN (36658, 36938);

DELETE FROM `spell_script_target` WHERE `entry` IN (70525, 70639);
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('70525', '1', '38188');
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('70525', '1', '37580');

INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('70639', '1', '38189');
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('70639', '1', '37581');