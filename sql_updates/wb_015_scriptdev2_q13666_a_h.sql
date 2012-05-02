set names utf8;
DELETE FROM `script_texts` WHERE `entry` IN ('-1800007', '-1800008');
DELETE FROM `gossip_texts` WHERE (`entry`='-3608002');
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc8`) VALUES ('-1800007', 'Can it really be? Free after all these years?', 'Не может быть! Неужели я наконец-то свободна?');
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc8`) VALUES ('-1800008', 'And now, I must return to the waters of the lake.', 'А теперь я должна вернуться в глубины озера.');

INSERT INTO `gossip_texts` (`entry`, `content_default`) VALUES ('-3608002', 'Glad to help, my lady. I\'m told you were once the guardian of a fabled sword. Do you know where I might find it?');