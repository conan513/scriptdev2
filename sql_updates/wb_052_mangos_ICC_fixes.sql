-- Professor Putricide
delete from creature_spell where guid in(37672, 38605, 38786, 38787, 38285, 38788, 38789, 38790);

replace into creature_spell values(37672, 70360, 0, 0, 0, 0);
replace into creature_spell values(37672, 70539, 1, 0, 0, 0);
replace into creature_spell values(37672, 70542, 2, 0, 0, 0);

replace into creature_spell values(38285, 72527, 0, 0, 0, 0);
replace into creature_spell values(38285, 70539, 1, 0, 0, 0);
replace into creature_spell values(38285, 70542, 2, 0, 0, 0);

delete from creature_template_addon where entry in (37672, 38605, 38786, 38787, 38285, 38788, 38789, 38790);
insert into creature_template_addon(entry, auras) values
(37672, '70385'),(38605, '70385'),(38786, '70385'),(38787, '70385'),
(38285, '70385'),(38788, '70385'),(38789, '70385'),(38790, '70385');

DELETE FROM `spell_script_target` WHERE `entry` IN (72527, 70360);
INSERT INTO `spell_script_target` VALUES (72527,1,37690), (70360,1,37690);

update creature_template set ScriptName="mob_mutated_amobination" where entry=38285;
update creature_template set ScriptName="mob_mutated_amobination" where entry=37672;
