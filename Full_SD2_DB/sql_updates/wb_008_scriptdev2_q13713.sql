set names utf8;
DELETE FROM `script_texts` WHERE `entry` IN ('-1800000', '-1800001');
INSERT INTO `script_texts` VALUES ('-1800000', 'You believe you are ready to be a champion? Defend yourself!', null, null, null, null, null, null, null, 'Небось, уже считаешь себя чемпионом? Защищайся!', '0', '0', '0', '0', 'SAY_CHAMPION_1');
INSERT INTO `script_texts` VALUES ('-1800001', 'Most impressive. You are worthy to gain the rank of champion.', null, null, null, null, null, null, null, 'Теперь я вижу, что ты заслуживаешь звания чемпиона.', '0', '0', '0', '0', 'SAY_CHAMPION_2');

DELETE FROM `gossip_texts` WHERE `entry` = '-3700000';
INSERT INTO `gossip_texts` (`entry`, `content_default`, `content_loc8`, `comment`) VALUES ('-3700000', 'I am ready to fight!', 'Я готов драться!', 'gossip danny');

DELETE FROM `script_texts` WHERE `entry` IN ('-1800002', '-1800003', '-1800004');
INSERT INTO `script_texts` VALUES ('-1800002', 'Prepare yourself', null, null, null, null, null, null, null, 'Приготовиться!', '0', '0', '0', '0', null);
INSERT INTO `script_texts` VALUES ('-1800003', 'Let it begin!', null, null, null, null, null, null, null, 'Начинаем!!', '0', '0', '0', '0', null);
INSERT INTO `script_texts` VALUES ('-1800004', 'That was a well fought battle. I yield to you.', null, null, null, null, null, null, null, 'Красивая победа. Сдаюсь!', '0', '0', '0', '0', null);

DELETE FROM `script_waypoint` WHERE `entry` = 33519;
INSERT INTO `script_waypoint` (`entry`,`pointid`,`location_x`,
`location_y`,`location_z`,`waittime`,`point_comment`) values
(33519, 0, 8524.63, 578.345, 552.524, 0, ''),
(33519, 1, 8455.89, 694.577, 547.292, 0, ''),
(33519, 2, 8397.99, 748.036, 547.293, 0, ''),
(33519, 3, 8373.84, 797.464, 547.91, 0, ''),
(33519, 4, 8375.42, 858.007, 547.996, 0, ''),
(33519, 5, 8391.85, 867.635, 547.556, 0, ''),
(33519, 6, 8461.66, 871.668, 547.293, 0, ''),
(33519, 7, 8472.43, 881.281, 547.294, 0, ''),
(33519, 8, 8478.89, 1017.11, 547.293, 0, ''),
(33519, 9, 8525.79, 1032.95, 547.293, 0, ''),
(33519, 10, 8537.57, 1076.91, 554.394, 0, ''),
(33519, 11, 8544.016, 1093.445, 562.226, 0, ''),
(33519, 12, 8576.88, 1211.09, 562.226, 0, ''),
(33519, 13, 9094.39, 2031.69, 97.599, 0, ''),
(33519, 14, 9086.074, 2058.25, 82.827, 0, ''),
(33519, 15, 9066.61, 2114.63, 67.966, 0, ''),
(33519, 16, 9052.65, 2115.8, 57.863, 3000, '');