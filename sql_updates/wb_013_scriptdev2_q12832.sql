set names utf8;
DELETE FROM `script_texts` WHERE `entry` IN ('-1800005', '-1800006');
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc8`) VALUES ('-1800005', 'I\'m going to bring the venom sac to Ricket... and then... you know... collapse. Thank you for helping me!', 'Я отдам ядовитую железу Рикет… а затем… просто… свалюсь. Спасибо за помощь!');
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc8`) VALUES ('-1800006', 'Let me know when you\\\'re ready. I\\\'d prefer sooner than later... what with the slowly dying from poison and all.', 'Дай мне знать о своей готовности. Я бы предпочла раньше, а не позже… если принять во внимание медленную смерть от яда и прочее.');

DELETE FROM `gossip_texts` WHERE `entry`='-3608100';
INSERT INTO `gossip_texts` (`entry`, `content_default`, `content_loc8`) VALUES ('-3608100', 'I am ready, lets get you out of here', 'Я готов, пошли отсюда');

-- Quest 12832 - Bitter Departure
DELETE FROM `script_waypoint` WHERE `entry` =29434;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(29434, 1, 6667.26, -1166.33, 398.60, 0, ''),
(29434, 2, 6680.58, -1113.87, 397.135, 0, ''),
(29434, 3, 6688.28, -1097.92, 395.516, 0, ''),
(29434, 4, 6679.27, -1075.48, 404.06, 0, ''),
(29434, 5, 6680.35, -1060.54, 406.232, 0, ''),
(29434, 6, 6696.42, -1047.22, 409.943, 0, ''),
(29434, 7, 6690.70, -1006.58, 414.834, 0, ''),
(29434, 8, 6634.18, -1011.75, 423.433, 0, ''),
(29434, 9, 6607.67, -997.21, 428.595, 0, ''),
(29434, 10, 6574.26, -1019.31, 433.011, 0, ''),
(29434, 11, 6531.69, -1026.47, 433.011, 0, ''),
(29434, 12, 6519.22, -1045.55, 432.762, 0, ''),
(29434, 13, 6492.08, -1042.36, 432.348, 0, ''),
(29434, 14, 6448.42, -1024.75, 431.042, 0, '');
