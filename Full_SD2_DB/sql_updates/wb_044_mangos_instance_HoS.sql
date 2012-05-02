set names utf8;
UPDATE `creature_template` SET `rank` = '1', `modelid_1` = '26353', `name` = 'Brann Bronzebeard', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '32052', `maxhealth` = '32052', `faction_A` = '35', `faction_H` = '35', `ScriptName` = '' WHERE `entry` = 24575;
UPDATE `locales_creature` SET `name_loc6` = 'Brann Barbabronce', `name_loc8`='Бранн Бронзобород' WHERE `entry` = 24575;

UPDATE `creature_template` SET `rank` = '1', `modelid_1` = '26353', `name` = 'Brann Bronzebeard', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '32052', `maxhealth` = '32052', `faction_A` = '35', `faction_H` = '35', `ScriptName` = 'brann_outro' WHERE `entry` = 24577;
UPDATE `locales_creature` SET `name_loc6` = 'Brann Barbabronce', `name_loc8`='Бранн Бронзобород' WHERE `entry` = 24577;

UPDATE `gameobject_template` SET `flags` = '6553636'  WHERE `entry` = 193906;

DELETE FROM `creature` WHERE `id` = 24575;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(null, 24575, 599, 2, 1, 0, 0, 1262.72, 667.006, 189.608, 0.00653052, 86400, 5, 0, 32052, 0, 0, 0);

UPDATE `creature` SET `spawnMask` = '3' WHERE `id` = 30897;
UPDATE `creature` SET `spawnMask` = '3' WHERE `id` = 30898;
UPDATE `creature` SET `spawnMask` = '3' WHERE `id` = 30899;
