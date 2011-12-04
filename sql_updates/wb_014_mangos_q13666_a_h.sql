-- AIName = EventAI
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_lake_frong_q' WHERE `entry` IN (33211, 33224);

DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=33211);

/*INSERT INTO `creature_ai_scripts` VALUES 
(3321153, 33211, 1, 1, 100, 0, 60000, 60000, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'timer'),
(3321152, 33211, 22, 2, 100, 1, 58, 1, 62574, 0, 11, 62537, 0, 0, 28, 6, 62574, 0, 22, 1, 0, 0, 'On Kiss Love'),
(3321151, 33211, 22, 2, 100, 1, 58, 11, 62574, 0, 11, 62581, 6, 6, 28, 6, 62574, 0, 0, 0, 0, 0, 'On Kiss Borodavki');
*/

DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=33224);
/*INSERT INTO `creature_ai_scripts` VALUES 
(3322455, 33224, 1, 2, 100, 1, 0, 0, 120000, 120000, 28, 0, 62550, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'ytdb'),
(3322452, 33224, 22, 2, 70, 1, 58, 1, 62574, 0, 11, 62537, 0, 0, 28, 6, 62574, 0, 22, 1, 0, 0, 'On Kiss Love'),
(3322454, 33224, 1, 1, 100, 0, 60000, 60000, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'timer'),
(3322453, 33224, 22, 2, 100, 1, 58, 11, 62574, 0, 11, 62581, 6, 6, 28, 6, 62574, 0, 0, 0, 0, 0, 'On Kiss Borodavki'),
(3322451, 33224, 22, 2, 30, 1, 58, 1, 62574, 0, 11, 62550, 0, 0, 1, -332241, 0, 0, 11, 62554, 6, 6, 'On Kiss Transform and give sword');
*/