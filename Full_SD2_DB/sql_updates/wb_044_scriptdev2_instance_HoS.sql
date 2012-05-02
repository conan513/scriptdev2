-- Yells de Brann (Sjonnir)

DELETE FROM `script_texts` WHERE `entry` = -1599069;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
	(-1599069, 'Don\'t worry! Ol\' Brann\'s got yer back! Keep that metal monstrosity busy, and I\'ll see if I can\'t sweet talk this machine into helping ye!', NULL, NULL, NULL, NULL, NULL, '?Tranquilos! ?El viejo Brann os cubre las espaldas! Distraed a ese monstruo de metal y yo vere si puedo convencer a esta maquina de que os ayude.', '?Tranquilos! ?El viejo Brann os cubre las espaldas! Distraed a ese monstruo de metal y yo vere si puedo convencer a esta maquina de que os ayude.', NULL, 14274, 1, 0, 0, 'brann IRON_SPAWN');

DELETE FROM `script_texts` WHERE `entry` = -1599070;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
	(-1599070, 'This is a wee bit trickier than before... Oh, bloody--incomin\'!', NULL, NULL, NULL, NULL, NULL, 'Esto es un poquito mas dificil que antes... Oh, maldita... ?vienen!', 'Esto es un poquito mas dificil que antes... Oh, maldita... ?vienen!', NULL, 14275, 1, 0, 0, 'brann TROGG_SPAWN');

DELETE FROM `script_texts` WHERE `entry` = -1599071;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
	(-1599071, 'What in the name o\' Madoran did THAT do? Oh! Wait: I just about got it...', NULL, NULL, NULL, NULL, NULL, 'En el nombre de Madoran, ?que ha hecho eso? ?Oh! Esperad, creo que lo tengo...', 'En el nombre de Madoran, ?que ha hecho eso? ?Oh! Esperad, creo que lo tengo...', NULL, 14276, 1, 0, 0, 'brann OOZE_SPAWN');
