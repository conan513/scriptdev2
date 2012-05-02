-- Gunship armory (override)
DELETE FROM `gameobject` WHERE `id` IN (201872,201873,201874,201875,202177,202178,202179,202180);
UPDATE `gameobject_template` SET `flags` = 0 WHERE `gameobject_template`.`entry` IN (201872,201873,201874,201875,202177,202178,202179,202180);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(972541, 201872, 631, 1, 1, -428.141, 2421.34, 191.233, 3.10389, 0, 0, 0.999822, 0.0188489, -604800, 100, 1),
(972543, 201873, 631, 2, 1, -428.141, 2421.34, 191.233, 3.10389, 0, 0, 0.999822, 0.0188489, -604800, 100, 1),
(972545, 201874, 631, 4, 1, -428.141, 2421.34, 191.233, 3.10389, 0, 0, 0.999822, 0.0188489, -604800, 100, 1),
(972547, 201875, 631, 8, 1, -428.141, 2421.34, 191.233, 3.10389, 0, 0, 0.999822, 0.0188489, -604800, 100, 1),
(972551, 202177, 631, 1, 1, -447.493, 2003.5, 191.235, 0.153939, 0, 0, 0.0768933, 0.997039, -604800, 100, 1),
(972553, 202178, 631, 2, 1, -447.493, 2003.5, 191.235, 0.153939, 0, 0, 0.0768933, 0.997039, -604800, 100, 1),
(972555, 202179, 631, 4, 1, -447.493, 2003.5, 191.235, 0.153939, 0, 0, 0.0768933, 0.997039, -604800, 100, 1),
(972557, 202180, 631, 8, 1, -447.493, 2003.5, 191.235, 0.153939, 0, 0, 0.0768933, 0.997039, -604800, 100, 1);

-- ---------------------
-- Valithria dreamwalker
-- ---------------------
UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35, `AIName` = '', `ScriptName` = 'boss_valithria_dreamwalker' WHERE `entry` = 36789;
UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35 WHERE `entry` = 38174; -- 25man difficulty
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `ScriptName`='mob_valithria_combat_trigger', `AIName`='', `flags_extra` = `flags_extra` &~2 WHERE `entry`= 38752;
UPDATE `creature` SET `phaseMask` = `phaseMask` | 16 WHERE `id` = 38752; -- phaseMask for Combat Trigger
UPDATE `creature_template` SET `unit_flags` = `unit_flags` &~ 33554432, `AIName` = '', `ScriptName` = 'mob_valithria_dream_phase' WHERE `entry` = 37950; -- Valithria in dream phase
REPLACE INTO `creature_template_addon` (`entry`, `emote`) VALUES (`entry` = 37950, `emote` = 453); -- flying state of dream Valithria
UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35, `ScriptName` = 'mob_dream_portal_pre', `AIName` = '' WHERE `entry`= 38186;
UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35, `IconName` = '', `npcflag` = `npcflag` | 1, `ScriptName` = 'mob_dream_portal', `AIName` = '' WHERE `entry`= 37945;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `ScriptName` = 'mob_dream_cloud', `AIName` = '', `flags_extra` = `flags_extra` &~128 WHERE `entry`= 37985;
UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35, `ScriptName` = 'mob_nightmare_portal_pre', `AIName` = '' WHERE `entry` = 38429;
UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35, `IconName` = '', `npcflag` = `npcflag` | 1, `ScriptName` = 'mob_nightmare_portal', `AIName` = '' WHERE `entry` = 38430;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `ScriptName` = 'mob_nightmare_cloud', `AIName` = '', `flags_extra` = `flags_extra` &~128 WHERE `entry` = 38421;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `ScriptName` = 'mob_gluttonous_abomination', `AIName` = '' WHERE `entry`= 37886;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `ScriptName` = 'mob_blistering_zombie', `AIName` = '' WHERE `entry`= 37934;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `ScriptName` = 'mob_risen_archmage', `AIName` = '' WHERE `entry`= 37868;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `ScriptName` = 'mob_blazing_skeleton', `AIName` = '', `mechanic_immune_mask` = `mechanic_immune_mask` | 2048 WHERE `entry`= 36791;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `ScriptName` = 'mob_suppresser', `AIName` = '' WHERE `entry`= 37863;
UPDATE `creature_template` SET `ScriptName`='mob_mana_void', `AIName`='', `flags_extra` = `flags_extra` &~128 WHERE `entry`= 38068;
UPDATE `creature_template` SET `ScriptName`='mob_column_of_frost', `AIName`='', `flags_extra` = `flags_extra` &~128 WHERE `entry`= 37918;
UPDATE `creature_template` SET `faction_A` = 35, `faction_H` = 35 WHERE `entry` = 16980;

DELETE FROM `spell_script_target` WHERE `entry` IN (71946, 72031, 72032, 72033);
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES
(71946, 1, 37950),
(72031, 1, 37950),
(72032, 1, 37950),
(72033, 1, 37950);

DELETE FROM `creature` WHERE `guid` = 47738 AND `id` = 38589;
DELETE FROM `pool_creature` WHERE `guid`=47738;

UPDATE `gameobject_template` SET `faction` = '0',`data0` = '0' WHERE `gameobject_template`.`entry` IN (201375,201373);
UPDATE `gameobject_template` SET `faction` = '114',`data0` = '0' WHERE `gameobject_template`.`entry` IN (201374);
UPDATE `gameobject` SET `state` = '1' WHERE `id` IN (201374);
UPDATE `gameobject_template` SET `faction` = '114',`data0` = '0' WHERE `gameobject_template`.`entry` IN (201380,201381,201382,201383);
UPDATE `gameobject_template` SET `faction` = '0' WHERE `entry` IN (201380,201381,201382,201383);
UPDATE `gameobject` SET `state` = '1' WHERE `id` IN (201380,201381,201382,201383);

-- ---------
-- Festergut
-- ---------

UPDATE `creature_template` SET `ScriptName`='boss_festergut', `AIName`=''  WHERE `entry`= 36626;
UPDATE `gameobject_template` SET `faction` = '114' WHERE `gameobject_template`.`entry` IN (201371);
UPDATE `gameobject` SET `state` = '0' WHERE `id` IN (201371);
UPDATE `creature_template` SET `ScriptName`='mob_vile_gas_malleable_goo', unit_flags = 0, `AIName`='', `flags_extra` = `flags_extra` | 2 | 128  WHERE `entry` IN (38548, 38556);
-- orange gas stalker
UPDATE `creature_template` SET `faction_A` = 2212, `faction_H` = 2212,  `ScriptName`='', `AIName`='' WHERE `entry`= 36659;
DELETE FROM `spell_script_target` WHERE `entry` IN (69157, 69162, 69164);
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES
(69157, 1, 36659),
(69162, 1, 36659),
(69164, 1, 36659);

-- original auras from YTDB
DELETE FROM `creature_template_addon` WHERE `entry` = 36659;
-- INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `emote`, `moveflags`, `auras`) VALUES
-- (36659, 0, 0, 1, 0, 0, '69126 69152 69154');

-- gas from valves
UPDATE `creature` SET `spawnMask` = 15, `modelid` = 11686, `spawntimesecs` = 300 WHERE `id`=37013;
DELETE FROM `spell_script_target` WHERE `entry` = 69125;
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES (69125, 1, 37013);

-- proper way for Gastric Bloat, but cooldowns for creatures not implemented yet
-- -- Gastric Bloat
DELETE FROM `spell_proc_event` WHERE `entry` = 72214;
-- INSERT INTO `spell_proc_event` VALUES
-- (72214, 0x00,  0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0.000000, 0.000000, 8);

-- fixed modelID info
DELETE FROM `creature_model_info` WHERE (`modelid`=31006);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (31006, 5, 4, 2, 0, 0);

-- fix peroicus modelID info
DELETE FROM `creature_model_info` WHERE (`modelid`=30483);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (30483, 5, 1, 2, 0, 0);

-- make triggers not visible
UPDATE `creature_template` SET `unit_flags` = `unit_flags` | 33554432 | 2 WHERE entry IN (37013, 37986, 38107, 38548, 37006, 38107, 38548, 38556, 36659);


-- --------------
-- Lanathel intro
-- --------------

UPDATE `creature_template` SET `ScriptName`='boss_blood_queen_lanathel_intro', `AIName`='' WHERE `entry`= 38004;

UPDATE `creature_template` SET `minhealth` = 5647725, `maxhealth` = 5647725, `ScriptName`='npc_blood_orb_control', `AIName`='' WHERE `entry`= 38008;
UPDATE `creature_template` SET `minhealth` = 22590900, `maxhealth` = 22590900 WHERE `entry` = 38641;
UPDATE `creature_template` SET `minhealth` = 7600025, `maxhealth` = 7600025 WHERE `entry` = 38773;
UPDATE `creature_template` SET `minhealth` = 30469825, `maxhealth` = 30469825 WHERE `entry` = 38774;

-- --------
-- Taldaram
-- --------

UPDATE `creature_template` SET `ScriptName`='boss_taldaram_icc', `AIName`='' WHERE `entry`= 37973;
UPDATE `creature_template` SET `ScriptName`='mob_ball_of_flames', `AIName`='',`minlevel` = 82, `maxlevel` = 82, `faction_A` = 14, `faction_H` = 14 WHERE `entry` IN (38332, 38451);

-- -------
-- Valanar
-- -------

UPDATE `creature_template` SET `ScriptName`='boss_valanar_icc', `AIName`='' WHERE `entry`= 37970;
UPDATE `creature_template` SET `ScriptName`='mob_kinetic_bomb', `AIName`='',`minlevel` = 82, `maxlevel` = 82, `faction_A` = 14, `faction_H` = 14 WHERE `entry`= 38454;
UPDATE `creature_template` SET `ScriptName`='mob_shock_vortex', `AIName`='',`minlevel` = 82, `maxlevel` = 82, `faction_A` = 14, `faction_H` = 14 WHERE `entry`= 38422;
UPDATE `creature_template` SET `ScriptName`='mob_kinetic_bomb_target', `AIName`='' WHERE `entry`= 38458;

DELETE FROM `spell_proc_event` WHERE `entry` = 72059;
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `procFlags`, `procEx`) VALUES
(72059, 127, 0x00000008|0x00000020|0x00000080|0x00000200|0x00002000|0x00020000|0x00400000, 0x0010000);

-- --------
-- Keleseth
-- --------

UPDATE `creature_template` SET `ScriptName`='boss_keleseth_icc', `AIName`='' WHERE `entry`= 37972;
UPDATE `creature_template` SET `ScriptName`='mob_dark_nucleus', `AIName`='',`minlevel` = 82, `maxlevel` = 82, `faction_A` = 14, `faction_H` = 14 WHERE `entry`= 38369;

DELETE FROM  `creature_template_addon` WHERE `entry` IN (37972,37973,37970,38401,38784,38785,38399,38769,38770,38400,38771,38772);


-- -----------------
-- Loot and deathstate for blood council (correct YTDB bugs, flags - from already killed princes)
-- -----------------

UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (37972,37973,37970,38401,38784,38785,38399,38769,38770,38400,38771,38772);

UPDATE `gameobject_template` SET `faction` = '114',`data0` = '0' WHERE `gameobject_template`.`entry` IN (201920,201377,201378);
UPDATE `gameobject` SET `state` = '1' WHERE `id` IN (201920,201377,201378);
UPDATE `gameobject_template` SET `faction` = '114',`data0` = '0' WHERE `gameobject_template`.`entry` IN (201376);
UPDATE `gameobject` SET `state` = '0' WHERE `id` IN (201376);

-- ---------------
-- Queen Lana'thel
-- ---------------

UPDATE `creature_template` SET `ScriptName`='boss_blood_queen_lanathel', `AIName`='' WHERE `entry`= 37955;
UPDATE `creature_template` SET  `minlevel` = 80, `maxlevel` = 80, `AIName` ='', `faction_A`= 14, `faction_H` = 14,`ScriptName`='mob_swarming_shadows' WHERE `entry`= 38163;
UPDATE `gameobject_template` SET `faction` = '0', `ScriptName` = 'go_frostwing_sigil' WHERE `gameobject_template`.`entry` IN (202181);
UPDATE `gameobject_template` SET `faction` = '0', `ScriptName` = 'go_frostwing_sigil' WHERE `gameobject_template`.`entry` IN (202181);

-- Essence of the Blood Queen
DELETE FROM `spell_proc_event` WHERE entry IN (70871);
INSERT INTO `spell_proc_event` VALUES
(70871, 0x7F,  0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0.000000, 0.000000, 0);

-- Mirror Soul proc on melee hits
DELETE FROM `spell_proc_event` WHERE entry IN (70445);
INSERT INTO `spell_proc_event` VALUES
(70445, 0x7F,  0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000008, 0x00000000, 0, 100, 0);

-- Presence of the Darkfallen
DELETE FROM spell_script_target WHERE entry IN (70995, 71952);
INSERT INTO spell_script_target VALUES
(71952, 1, 37955),
(70995, 1, 37955);

DELETE FROM `creature_model_info` WHERE (`modelid`=31165);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (31165, 3, 5, 2, 0, 0);

DELETE FROM `creature_model_info` WHERE (`modelid`=31093);
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`, `modelid_alternative`) VALUES (31093, 1.24, 2, 1, 0, 0);
