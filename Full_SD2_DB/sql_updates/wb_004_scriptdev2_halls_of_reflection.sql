set names utf8;

REPLACE INTO `script_texts` VALUES ('-1999806', 'Halt! Do not carry that blade any further!', null, null, null, null, null, null, null, null, '0', '1', '0', '0', 'Uther the Lightbringer yells 1');

REPLACE INTO `script_texts` VALUES ('-1999812', "Quel'Delar leeps to life in the presence of Frostmourne!", null, null, null, null, null, null, null, null, '0', '3', '0', '0', 'QuelDelar Emote 1');

REPLACE INTO `script_texts` VALUES ('-1999807', "Do you realize what you've done?", null, null, null, null, null, null, null, null, '0', '1', '0', '0', 'Uther the Lightbringer yells 2');

REPLACE INTO `script_texts` VALUES ('-1999813', "Quel'Delar prepares to attack!", null, null, null, null, null, null, null, null, '0', '3', '0', '0', 'QuelDelar Emote 2');

REPLACE INTO `script_texts` VALUES ('-1999808', 'You have forged this blade from saronite, the very blood of an old god. The power of the Lich King calls to this weapon.', null, null, null, null, null, null, null, null, '0', '0', '0', '0', 'Uther the Lightbringer say 1');

REPLACE INTO `script_texts` VALUES ('-1999809', "Each moment you tarry here, Quel'Delar drinks in the evil of this place.", null, null, null, null, null, null, null, null, '0', '0', '0', '0', 'Uther the Lightbringer say 2');

REPLACE INTO `script_texts` VALUES ('-1999810', 'There is only one way to cleanse the sword. Make haste for the Sunwell and immerse the blade in its waters.', null, null, null, null, null, null, null, null, '0', '0', '0', '0', 'Uther the Lightbringer say 3');

REPLACE INTO `script_texts` VALUES ('-1999811', "I can resist Frostmourne's call no more...", null, null, null, null, null, null, null, null, '0', '0', '0', '0', 'Uther the Lightbringer say 4');

REPLACE INTO `script_texts` VALUES ('-1999814', "Frostmourne: the blade that destroyed our kingdom...", null, null, null, null, null, null, null, null, '0', '1', '0', '0', 'SAY_JAINA_INTRO_01');

UPDATE `script_texts` SET `content_loc8`='Ледяная Скорбь: клинок, разрушивший наше королевство…' WHERE (`entry`='-1999814');


REPLACE INTO `gossip_texts` VALUES ('-3668536', 'Lady Jaina, we are ready for next mission!', null, null, null, null, null, null, null, 'Джайна, мы готовы!', '');
REPLACE INTO `gossip_texts` VALUES ('-3594537', 'Lady Jaina, Let\'s go!', null, null, null, null, null, null, null, 'Давай быстрее!', '');
REPLACE INTO `gossip_texts` VALUES ('-3594538', 'Lady Sylvanas, we are ready for next mission!', null, null, null, null, null, null, null, 'Сильвана, мы готовы!', '');
REPLACE INTO `gossip_texts` VALUES ('-3594539', 'Lady Sylvanas, Let\'s go!', null, null, null, null, null, null, null, 'Поехали!', '');
REPLACE INTO `gossip_texts` VALUES ('-3594540', 'Let\'s go!', null, null, null, null, null, null, null, 'Побежали!', '');

/*UPDATE `script_texts` SET `content_loc8`='Ты понимаешь, что наделал?' WHERE (`entry`='-1999807'); */