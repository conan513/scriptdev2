REPLACE INTO game_event VALUES ('201', '2011-01-01 08:00:00', '2020-12-30 00:00:00', '90', '60', '0', 'DK hack quest');
DELETE FROM `game_event_creature` WHERE `event`=201;
INSERT INTO `game_event_creature` (`guid`, `event`) VALUES ('116836', '201');


