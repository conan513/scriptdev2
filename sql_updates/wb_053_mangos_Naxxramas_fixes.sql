-- Achievemets:
-- Arachnophobia
delete from achievement_criteria_requirement where criteria_id in(7129,7128);
insert into achievement_criteria_requirement values(7128,12,0,0),(7129,12,1,0);

-- And The Would All Go Down Together
delete from achievement_criteria_requirement where criteria_id in(7600,7601);
insert into achievement_criteria_requirement values(7600,12,0,0),(7600,18,0,0),(7601,12,1,0),(7601,18,0,0);

-- The Military Quarter (Horsemen)
delete from achievement_criteria_requirement where criteria_id in(7192,7193);
insert into achievement_criteria_requirement values(7192,12,0,0),(7193,12,1,0);

-- Make Quick Werk of Him
delete from achievement_criteria_requirement where criteria_id in(7126,7127);
insert into achievement_criteria_requirement values(7126,12,0,0),(7127,12,1,0);
