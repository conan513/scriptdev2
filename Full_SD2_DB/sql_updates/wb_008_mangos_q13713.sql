UPDATE `creature_template` SET `ScriptName` = 'npc_argent_champion' WHERE `entry` IN (33707, 33448);
/*gossip_menu_id = 10343*/
UPDATE `creature_template` SET `gossip_menu_id` = 0, `ScriptName` = 'npc_squire_danny' WHERE `entry` = 33518;

DELETE FROM `creature_template_addon` WHERE `entry` = 33707;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `b2_0_sheath`) VALUES ('33707', '14337', '1');

DELETE FROM `creature` WHERE `id`=33707;

/*INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(129089, 33707, 571, 1, 1, 0, 33707, 8533.11, 1069.66, 551.884, 1.55575, 300, 0, 0, 50000, 0, 0, 0); */

/*gossip_menu_id = 10467*/
UPDATE `creature_template` SET `gossip_menu_id` = 0, `ScriptName` = 'quest_the_grand_melee' WHERE `entry` IN (33561, 33564, 33558, 33559, 33562, 33384, 33306, 33285, 33382, 33383);

UPDATE `creature_template` SET `gossip_menu_id` = 10459 WHERE `entry` = 33746;
UPDATE `creature_template` SET `gossip_menu_id` = 10461 WHERE `entry` = 33748;
UPDATE `creature_template` SET `gossip_menu_id` = 10457 WHERE `entry` = 33744;
UPDATE `creature_template` SET `gossip_menu_id` = 10458 WHERE `entry` = 33745;
UPDATE `creature_template` SET `gossip_menu_id` = 10462 WHERE `entry` = 33749;
UPDATE `creature_template` SET `gossip_menu_id` = 10454 WHERE `entry` = 33739;
UPDATE `creature_template` SET `gossip_menu_id` = 10453 WHERE `entry` = 33738;
UPDATE `creature_template` SET `gossip_menu_id` = 10460 WHERE `entry` = 33747;
UPDATE `creature_template` SET `gossip_menu_id` = 10456 WHERE `entry` = 33743;
UPDATE `creature_template` SET `gossip_menu_id` = 10455 WHERE `entry` = 33740;

UPDATE `creature_template` SET `ScriptName` = 'quest_mastery_of_melee' WHERE `entry` = 33272;

REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `mingold`, `maxgold`, `ScriptName`) VALUES (300245, 8, 299, 'TEMP Stoila(Sar)', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 1599, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');

DELETE FROM `gameobject` WHERE `id`=300245;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(null, 300245, 571, 1, 1, 8578.42, 677.537, 547.408, 2.14045, 0, 0, 0.87731, 0.479925, 25, 255, 1),
(null, 300245, 571, 1, 1, 6428.88, 2384.9, 466.464, 4.05596, 0, 0, 0.8973, -0.441421, 25, 255, 1);

DELETE FROM `gameobject` WHERE `id`=401002;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(null, 401002, 571, 1, 1, 8523.63, 569.062, 552.608, 0.962105, 0, 0, 0.462713, 0.886508, 25, 255, 1);

UPDATE `quest_template` SET `ReqCreatureOrGOId1` = 0, `ReqCreatureOrGOCount1` = 0 WHERE `entry` = 13663;

DELETE FROM `creature_template_addon` WHERE (`entry`=33519);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES (33519, 0, 50331648, 1, 0, 0, 1024, 53112);

DELETE FROM `npc_spellclick_spells` WHERE (`npc_entry`='33842') AND (`spell_id`='63791') AND (`quest_start`='13680');
DELETE FROM `npc_spellclick_spells` WHERE (`npc_entry`='33843') AND (`spell_id`='63792') AND (`quest_start`='13679');
INSERT INTO npc_spellclick_spells VALUES ('33843', '63792', '13679', '1', '0', '3');
INSERT INTO npc_spellclick_spells VALUES ('33842', '63791', '13680', '1', '0', '3');
