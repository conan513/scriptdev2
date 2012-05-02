-- Anub'arak
UPDATE `creature_template` SET `scriptname`='boss_anubarak_trial', `unit_flags` = 0, `AIName` ='' WHERE `entry`=34564;

DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (34606, 34605, 34607, 34564, 34660);
UPDATE `creature_template` SET `modelid_1` = 25144, `modelid_2` = 0, `modelid_3` = 25144, `modelid_4` = 0, `faction_A` = 14, `faction_H` = 14, `AIName` = '', `ScriptName` = 'mob_frost_sphere' WHERE `entry` = 34606;
UPDATE `creature_template` SET `scriptname`='mob_swarm_scarab', `AIName` ='' WHERE `entry`=34605;
UPDATE `creature_template` SET `scriptname`='mob_nerubian_borrower', `AIName` ='' WHERE `entry`=34607;
UPDATE `creature_template` SET `scriptname`='mob_anubarak_spike', `faction_A` = 14, `minlevel` = 80, `maxlevel` = 80,`faction_H` = 14, `AIName` ='' WHERE `entry`=34660;


UPDATE `creature_template` SET `mechanic_immune_mask` = 650854363 WHERE `entry` = 34564;
UPDATE `creature_template` SET `spell1` = 0, `spell2` = 0, `spell3` = 0 WHERE `entry` = 34564;
-- FIXME: additional creature for Permafrost handling
DELETE FROM creature_template WHERE entry = 198722;
INSERT INTO creature_template(entry, KillCredit1, KillCredit2, modelid_1, modelid_2, modelid_3, modelid_4, name, subname, 
IconName, minlevel, maxlevel, minhealth, maxhealth, minmana, maxmana, armor, faction_A, faction_H, npcflag, scale, rank, 
mindmg, maxdmg, dmgschool, attackpower, dmg_multiplier, baseattacktime, rangeattacktime, unit_class, unit_flags, dynamicflags,
family, trainer_type, trainer_spell, trainer_class, trainer_race, minrangedmg, maxrangedmg, rangedattackpower, type, 
type_flags, lootid, pickpocketloot, skinloot, resistance1, resistance2, resistance3, resistance4, resistance5, resistance6, 
spell1, spell2, spell3, spell4, PetSpellDataId, mingold, maxgold, AIName, MovementType, InhabitType, unk16, unk17, 
RacialLeader, questItem1, questItem2, questItem3, questItem4, movementId, RegenHealth, equipment_id, mechanic_immune_mask, 
flags_extra, ScriptName) VALUES ('198722', '0', '0', '0', '0', '17612', '1126', '0', 'Anub\'arak Permafrost', '0','1', '1', 
'1', '1', '1', '1', '114', '114', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '','0', '3', 
'1.0', '1.0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', 'mob_anubarak_permafrost'); 
UPDATE `creature_template` SET `modelid_1` = 17612, `modelid_2` = 1126, `name` = 'Anub\'arak Permafrost', `subname` = 0, 
`unit_flags` = 516 WHERE `entry` = 198722;