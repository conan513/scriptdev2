set names utf8;

DROP TABLE IF EXISTS `guildhouse`;
CREATE TABLE `guildhouse` (
  `id` int(8) unsigned NOT NULL AUTO_INCREMENT,
  `guildid` bigint(20) NOT NULL DEFAULT '0',
  `x` double NOT NULL,
  `y` double NOT NULL,
  `z` double NOT NULL,
  `map` int(11) NOT NULL,
  `guildname` varchar(255) NOT NULL DEFAULT '',
  `location` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=22 DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of guildhouse
-- ----------------------------
REPLACE INTO `guildhouse` VALUES ('1', 'ИД ГИЛЬДИИ', '-8625.70', '-545.06', '144.94', '0', 'Lethal', 'id guild Lethal 1043');

DELETE FROM `gossip_texts` where `entry` IN (-3100770, -3100771,-3100772,-3100773,-3100774);
REPLACE INTO `gossip_texts` VALUES ('-3100770', 'Teleport in Guild House.', null, null, null, null, null, null, null, 'Телепортироваться в Guild House', '');
REPLACE INTO `gossip_texts` VALUES ('-3100771', 'You are currently in combat!', null, null, null, null, null, null, null, 'Вы в бою!', '');
REPLACE INTO `gossip_texts` VALUES ('-3100772', 'Create teleport item.', null, null, null, null, null, null, null, 'Создать итема для телепорта в Guild House', '');
REPLACE INTO `gossip_texts` VALUES ('-3100773', 'You are not gold!', null, null, null, null, null, null, null, 'У вас недостаточно голд!', '');