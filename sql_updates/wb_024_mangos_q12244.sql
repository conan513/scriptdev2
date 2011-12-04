DELETE FROM `creature` WHERE `id`=27396;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(4457233, 27396, 571, 1, 65535, 0, 0, 4000.15, -3188, 282.034, 3.21054, 25, 0, 0, 1, 0, 0, 0);

DELETE FROM `gameobject` WHERE `id`=300202;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(222026, 300202, 571, 1, 1, 3997.37, -3184.59, 281.672, 4.67128, 0, 0, 0.721492, -0.692423, 300, 255, 1);
