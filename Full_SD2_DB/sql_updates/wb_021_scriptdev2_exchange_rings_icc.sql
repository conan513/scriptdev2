set names utf8;
DELETE FROM `gossip_texts` WHERE `entry` BETWEEN '-3001770' AND '-3001785';
REPLACE INTO `gossip_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `comment`) VALUES
('-3001770', 'You have not changed the ring?', null, null, null, null, null, null, null, 'У тебя не меняется кольцо?', 'GOSSIP RING ICC'),
('-3001771', 'Ashen Band of Greater Courage', null, null, null, null, null, null, null, 'Пепельное кольцо великой отваги', 'GOSSIP RING ICC'),
('-3001772', 'Ashen Band of Greater Wisdom', null, null, null, null, null, null, null, 'Пепельное кольцо великой мудрости', 'GOSSIP RING ICC'),
('-3001773', 'Ashen Band of Greater Might', null, null, null, null, null, null, null, 'Пепельное кольцо великой мощи', 'GOSSIP RING ICC'),
('-3001774', 'Ashen Band of Greater Destruction', null, null, null, null, null, null, null, 'Пепельное кольцо великого разрушения', 'GOSSIP RING ICC'),
('-3001775', 'Ashen Band of Greater Vengeance', null, null, null, null, null, null, null, 'Пепельное кольцо великого отмщения', 'GOSSIP RING ICC'),
('-3001776', 'Ashen Band of Unmatched Courage', null, null, null, null, null, null, null, 'Пепельное кольцо непревзойденной отваги', 'GOSSIP RING ICC'),
('-3001777', 'Ashen Band of Unmatched Wisdom', null, null, null, null, null, null, null, 'Пепельное кольцо непревзойденной мудрости', 'GOSSIP RING ICC'),
('-3001778', 'Ashen Band of Unmatched Might', null, null, null, null, null, null, null, 'Пепельное кольцо непревзойденной мощи', 'GOSSIP RING ICC'),
('-3001779', 'Ashen Band of Unmatched Destruction', null, null, null, null, null, null, null, 'Пепельное кольцо непревзойденного разрушения', 'GOSSIP RING ICC'),
('-3001780', 'Ashen Band of Unmatched Vengeance', null, null, null, null, null, null, null, 'Пепельное кольцо непревзойденного отмщения', 'GOSSIP RING ICC'),
('-3001781', 'Ashen Band of Endless Destruction', null, null, null, null, null, null, null, 'Пепельное кольцо бесконечного разрушения', 'GOSSIP RING ICC'),
('-3001782', 'Ashen Band of Endless Vengeance', null, null, null, null, null, null, null, 'Пепельное кольцо бесконечного отмщения', 'GOSSIP RING ICC'),
('-3001783', 'Ashen Band of Endless Courage', null, null, null, null, null, null, null, 'Пепельное кольцо безграничной отваги', 'GOSSIP RING ICC'),
('-3001784', 'Ashen Band of Endless Wisdom', null, null, null, null, null, null, null, 'Пепельное кольцо безграничной мудрости', 'GOSSIP RING ICC'),
('-3001785', 'Ashen Band of Endless Might', null, null, null, null, null, null, null, 'Пепельное кольцо безграничной мощи', 'GOSSIP RING ICC'),
('-3001786', 'Want to change the ring? 500 Gold!', null, null, null, null, null, null, null, 'Хотите поменять кольцо? 500 Голд!', 'GOSSIP RING ICC');

