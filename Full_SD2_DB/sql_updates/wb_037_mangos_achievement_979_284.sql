update `gossip_menu_option` set `action_menu_id`='-1', `action_script_id` = 1291 where `option_text`='Trick or Treat!';

DELETE FROM `gossip_scripts` where `id` = 1291;
INSERT INTO `gossip_scripts` (`id`, `command`, `datalong`, `datalong2`) VALUES ('1291', '17', '34077', '1');
INSERT INTO `gossip_scripts` (`id`, `command`, `datalong`) VALUES ('1291', '15', '24755');