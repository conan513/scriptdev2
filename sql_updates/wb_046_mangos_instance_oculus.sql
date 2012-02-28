UPDATE `creature_template` SET `modelid_1` = '11686', `modelid_2` = '0', `modelid_3` = '0', `unit_flags` = '33554818', `ScriptName` = 'drakos_event' WHERE `entry` = 11364;

UPDATE `gossip_menu_option` SET `action_menu_id` = '15589' WHERE `menu_id` = 27658 AND `id` = 0;
UPDATE `gossip_menu_option` SET `action_menu_id` = '15590' WHERE `menu_id` = 27657 AND `id` = 0;
UPDATE `gossip_menu_option` SET `action_menu_id` = '15591' WHERE `menu_id` = 27659 AND `id` = 0;

UPDATE `gossip_menu` SET `text_id` = '13267' WHERE `entry` = 27658;
UPDATE `gossip_menu` SET `text_id` = '13268' WHERE `entry` = 27657;
UPDATE `gossip_menu` SET `text_id` = '12917' WHERE `entry` = 27659;

DELETE FROM `gossip_menu` WHERE `entry` BETWEEN 15589 AND 15591;
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (15589, 13254);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (15590, 13258);
INSERT INTO `gossip_menu` (`entry`, `text_id`) VALUES (15591, 13256);

UPDATE `locales_npc_text` SET `Text0_0_loc6` = 'Belgaristrasz dice la verdad; ?el tiempo se agota!$B$BPuedo otorgarte el poder de invocar un draco del Vuelo Bronce. Habla con Belgaristrasz o Verdisa si prefieres aprovechar el poder del Rojo o el Verde.' WHERE `entry` = 12917;
UPDATE `locales_npc_text` SET `Text0_0_loc6` = 'Belgaristrasz dice la verdad; es cierto que la situacion es grave.$B$BPuedo otorgarte el poder de invocar un draco del Vuelo Verde. Habla con Belgaristrasz o Eternos si prefieres aprovechar el poder del Rojo o el Bronce.' WHERE `entry` = 13268;

UPDATE `locales_npc_text` SET `Text0_0_loc6` = 'Los dracos rubi destacan en aguantar dano y proteger a sus aliados.$B$BAl utilizar Colera abrasadora pueden lanzar fuego liquido que salta de objetivo en objetivo, haciendo cada vez mas dano.$B$BCada vez que un draco rubi es alcanzado por un ataque enemigo, gana una Carga evasiva. Estas cargas sirven para realizar una serie de maniobras evasivas, que permiten al draco esquivar los ataques y hechizos durante un tiempo.' WHERE `entry` = 13254;
UPDATE `locales_npc_text` SET `Text0_1_loc6` = 'Los dracos esmeralda destacan en curarse a si mismos mientras envenenan a sus enemigos.$B$BAl usar el Veneno parasitante, pueden robarle salud a sus enemigos. Varias aplicaciones de este veneno pueden aumentar el efecto.$B$BCon Tocar la pesadilla, los dracos esmeralda pueden alcanzar el sueno, tocando una parte de su energia vital en un ataque muy danino que deja debilitado al objetivo, reduciendo su dano durante poco tiempo.' WHERE `entry` = 13258;
UPDATE `locales_npc_text` SET `Text0_0_loc6` = 'Los dracos ambar destacan en causar dano gracias a que pueden manipular el tiempo a su favor.$B$BAl utilizar la Lanza de choque pueden interrumpir el flujo de tiempo alrededor de un enemigo, haciendole dano instantaneamente. El poder de este efecto aumenta enormemente dependiendo de las Cargas de choque en el objetivo.$B$BCuando se ve amenazado, un draco de ambar puede detener brevemente el flujo del tiempo de sus enemigos. Esta interrupcion del tiempo almacena una gran cantidad de Energia de choque en los objetivos afectados en la forma de Cargas de choque.' WHERE `entry` = 13256;

UPDATE `locales_npc_text` SET `Text0_0_loc7` = `Text0_0_loc6`, `Text0_1_loc7` = `Text0_1_loc6`;

-- Achievements
-- Oculus
delete from achievement_criteria_requirement where criteria_id in(203,204,205,206);
insert into achievement_criteria_requirement values(203,12,0,0),(204,12,0,0),(205,12,0,0),(206,12,0,0);

-- Oculus (heroic)
delete from achievement_criteria_requirement where criteria_id in(6859,6860,6861,6862);
insert into achievement_criteria_requirement values(6859,12,1,0),(6860,12,1,0),(6861,12,1,0),(6862,12,1,0);

-- Make It Count + Expirienced Drake Rider
delete from achievement_criteria_requirement where criteria_id in(7145,7178,7179,7177);
insert into achievement_criteria_requirement values(7145,12,1,0),(7178,12,1,0),(7179,12,1,0),(7177,12,1,0);
