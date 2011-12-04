
-- UPDATE `quest_template` SET `SpecialFlags` = 2, `Method` = 2 WHERE `entry` IN (11131, 11219);

-- Hack
UPDATE `quest_template` SET `SpecialFlags` = 1, `Method` = 0 WHERE `entry` IN (11131, 11219);