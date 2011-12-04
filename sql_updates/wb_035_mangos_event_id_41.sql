UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry` = '32820';
DELETE FROM `creature_ai_scripts` WHERE (`id`='328201');
INSERT INTO `creature_ai_scripts` VALUES ('328201', '32820', '6', '0', '100', '0', '0', '0', '0', '0', '11', '62014', '6', '3', '0', '0', '0', '0', '0', '0', '0', '0', 'ytdb');

delete from npc_spellclick_spells where npc_entry IN (34812, 34819, 34822, 34824, 34823);
insert into npc_spellclick_spells (npc_entry, spell_id, quest_start, quest_start_active, quest_end, cast_flags) values
(34812,65403,0,0,0,1);
insert into npc_spellclick_spells (npc_entry, spell_id, quest_start, quest_start_active, quest_end, cast_flags) values
(34819,65403,0,0,0,1);
insert into npc_spellclick_spells (npc_entry, spell_id, quest_start, quest_start_active, quest_end, cast_flags) values
(34822,65403,0,0,0,1);
insert into npc_spellclick_spells (npc_entry, spell_id, quest_start, quest_start_active, quest_end, cast_flags) values
(34824,65403,0,0,0,1);
insert into npc_spellclick_spells (npc_entry, spell_id, quest_start, quest_start_active, quest_end, cast_flags) values
(34823,65403,0,0,0,1);
     
     
    update creature_template set vehicle_id=321, speed_run=0, speed_walk=0, spell1=66261, spell2=61784, spell3=61785, spell4=61788, spell5=61786, spell6=61787 where entry=34823;
    update creature_template set vehicle_id=321, speed_run=0, speed_walk=0, spell1=66250, spell2=61784, spell3=61785, spell4=61788, spell5=61786, spell6=61787 where entry=34812;
    update creature_template set vehicle_id=321, speed_run=0, speed_walk=0, spell1=66259, spell2=61784, spell3=61785, spell4=61788, spell5=61786, spell6=61787 where entry=34819;
    update creature_template set vehicle_id=321, speed_run=0, speed_walk=0, spell1=66260, spell2=61784, spell3=61785, spell4=61788, spell5=61786, spell6=61787 where entry=34822;
    update creature_template set vehicle_id=321, speed_run=0, speed_walk=0, spell1=66262, spell2=61784, spell3=61785, spell4=61788, spell5=61786, spell6=61787 where entry=34824;
     
    DELETE FROM creature_spell WHERE guid IN (34823,34812,34819,34822,34824);
     
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34823,66261,0,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34823,61784,1,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34823,61785,2,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34823,61788,3,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34823,61786,4,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34823,61787,5,0,0,0);
     
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34812,66250,0,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34812,61784,1,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34812,61785,2,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34812,61788,3,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34812,61786,4,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34812,61787,5,0,0,0);
     
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34819,66259,0,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34819,61784,1,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34819,61785,2,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34819,61788,3,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34819,61786,4,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34819,61787,5,0,0,0);
     
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34822,66260,0,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34822,61784,1,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34822,61785,2,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34822,61788,3,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34822,61786,4,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34822,61787,5,0,0,0);
     
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34824,66262,0,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34824,61784,1,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34824,61785,2,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34824,61788,3,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34824,61786,4,0,0,0);
    insert into `creature_spell`(`guid`,`spell`,`index`,`active`,`disabled`,`flags`) values(34824,61787,5,0,0,0);
     
DELETE FROM `creature_template_addon` WHERE `entry` IN (34823,34812,34819,34822,34824); 
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES (34823, 0, 0, 0, 0, 0, 0, '61798');
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES (34812, 0, 0, 0, 0, 0, 0, '61801');
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES (34819, 0, 0, 0, 0, 0, 0, '61800');
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES (34822, 0, 0, 0, 0, 0, 0, '61799');	
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`) VALUES (34824, 0, 0, 0, 0, 0, 0, '61802');

-- UPDATE `game_event` SET `start_time` = '2011-11-20 03:00:00', `end_time` = '2020-12-30 22:00:00', `occurence` = 545760, `length` = 10019 WHERE `entry` = 41;
UPDATE `game_event` SET `start_time` = '2011-11-20 03:00:00', `end_time` = '2020-12-30 22:00:00', `occurence` = 540000, `length` = 15779 WHERE `entry` = 41;

UPDATE `creature_template` SET `modelid_1` = 29205, `modelid_2` = 29205 WHERE `entry` IN (34823, 34812, 34819, 34822, 34824);
update `creature` set `spawntimesecs`=3 where `id` IN (34823, 34812, 34819, 34822, 34824);