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
