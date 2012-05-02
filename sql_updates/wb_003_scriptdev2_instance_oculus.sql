SET NAMES UTF8;

-- Oculus Drakos event

DELETE FROM `script_texts` WHERE `entry` = -1578040;
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`)
VALUES
	(-1578040, 'Thank you for freeing us, mortals. Beware, the Blue Flight is alerted to your presence. Even now, Malygos sends Varos Cloudstrider and his ring guardians to defend the Oculus. You will need our help to stand a chance.', NULL, NULL, NULL, NULL, NULL, 'Gracias por liberarnos, mortales. Tened cuidado, el Vuelo Azul ha sido alertado de vuestra presencia. Incluso ahora, Malygos envia a Varos Zancanubes y a sus guardianes del anillo para defender El Oculus. Necesitareis nuestra ayuda o no tendreis nada que hacer.', 'Gracias por liberarnos, mortales. Tened cuidado, el Vuelo Azul ha sido alertado de vuestra presencia. Incluso ahora, Malygos envia a Varos Zancanubes y a sus guardianes del anillo para defender El Oculus. Necesitareis nuestra ayuda o no tendreis nada que hacer.', NULL, 0, 0, 0, 0, 'SAY_BELGAR');