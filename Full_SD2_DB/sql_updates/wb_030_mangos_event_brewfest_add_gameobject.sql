DELETE FROM `gameobject` WHERE `id` IN (189989, 189990);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (600025, 189989, 0, 1, 1, -5156.03, -604.25, 398.29, 1.92609, 0, 0, 0.820935, 0.571021, 300, 0, 1);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (600026, 189990, 1, 1, 1, 1198.8, -4296.72, 21.3374, 2.40173, 0, 0, 0.932353, 0.361549, 300, 0, 1);
REPLACE INTO `game_event_gameobject` (`guid`, `event`) VALUES (600025, 26);
REPLACE INTO `game_event_gameobject` (`guid`, `event`) VALUES (600026, 26);

UPDATE `quest_template` SET `PrevQuestId` = 0 WHERE `entry` = 12020;


