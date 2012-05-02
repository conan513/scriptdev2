DELETE FROM creature_ai_scripts WHERE creature_id = 23119;
UPDATE `creature_template` SET AIName = '', `ScriptName` = 'npc_bombing_run' WHERE `entry` = 23119;
