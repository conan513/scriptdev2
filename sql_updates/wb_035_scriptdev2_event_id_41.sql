set names utf8;
delete from script_texts where entry in (-1999001, -1999002, -1999003, -1999004);
insert into script_texts (entry, content_default, content_loc8) values (-1999001, 'Turkey Hunter!', 'Охотник на индеек!');
insert into script_texts (entry, content_default, content_loc8) values (-1999002, 'Turkey Domination!', 'Повелитель индеек!');
insert into script_texts (entry, content_default, content_loc8) values (-1999003, 'Turkey Slaughter!', 'Истребитель индеек!');
insert into script_texts (entry, content_default, content_loc8) values (-1999004, 'TURKEY TRIUMPH!', 'ТРИУМФ НАД ИНДЕЙКАМИ!');