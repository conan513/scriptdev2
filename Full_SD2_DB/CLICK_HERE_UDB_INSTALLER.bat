@echo off
:quick
rem Quick install section
rem This will automatically use the variables below to install the world and scriptdev2 databases without prompting then optimize them and exit
rem To use: Set your environment variables below and change 'set quick=off' to 'set quick=on' 
set quick=off
if %quick% == off goto standard
echo (( MangosR2 Quick Installer ))
rem -- Change the values below to match your server --
set svr=localhost
set user=root
set pass=
set port=3306
set wdb=mangos
set sd2db=scriptdev2
rem -- Don't change past this point --
set yesno=y
goto install

:standard
rem Standard install section
color 3
echo .
echo 8888888b.  888888b.      ( Infinity Database Project )
echo 888  "Y88b 888  "88b     ( Starting template and still updated w/YTDB )
echo 888    888 888  .88P     
echo 888    888 8888888K.     
echo 888    888 888  "Y88b    ( Credits for DB project lay out and set up to PSMDB )
echo 888    888 888    888
echo 888  .d88P 888   d88P    
echo 8888888P"  8888888P"     
echo Infinity_DB Project       DB__Version 1.0                      
echo.
echo.
set /p svr=What is your MySQL host name?           [localhost]   : 
if %svr%. == . set svr=localhost
set /p user=What is your MySQL user name?           [root]        : 
if %user%. == . set user=root
set /p pass=What is your MySQL password?            [ ]           : 
if %pass%. == . set pass=
set /p port=What is your MySQL port?                [3306]        : 
if %port%. == . set port=3306
set /p wdb=What is your World database name?       [udb]      : 
if %wdb%. == . set wdb=udb
set /p cdb=What is your Characters database name?  [scriptdev2]  : 
if %cdb%. == . set cdb=scriptdev2


:install
set dbpath=udb
set dbpath1=udb
set mysql=.

:checkpaths
if not exist %dbpath% then goto patherror
if not exist %mysql%\mysql.exe then goto patherror
goto world

:patherror
echo Cannot find required files, please ensure you have gotten the full files
pause
goto :eof

:world
if %quick% == off echo.
if %quick% == off echo This will wipe out your current World database and replace it.
if %quick% == off set /p yesno=Do you wish to continue? (y/n) 
if %quick% == off if %yesno% neq y if %yesno% neq Y goto sd2

echo.
echo Importing World database

for %%i in (%dbpath%\mr*mangos*sql) do if %%i neq %dbpath3%\mr*mangos*sql if %%i neq %dbpath1%\mr*mangos*sql if %%i neq %dbpath2%\mr*mangos*sql echo %%i & %mysql%\mysql -q -s -h %svr% --user=%user% --password=%pass% --port=%port% %wdb% < %%i


:characters
echo.
echo This will wipe out your current ScriptDev2 database and replace it.
set /p yesno=Do you wish to continue? (y/n) 
if %yesno% neq y if %yesno% neq Y goto realm

echo.
echo Importing ScriptDev2 database

for %%i in (%dbpath1%\mr*scriptdev2*sql) do if %%i neq %dbpath%\mr*scriptdev2*sql if %%i neq %dbpath1%\mr*scriptdev2*sql if %%i neq %dbpath2%\mr*scriptdev2*sql echo %%i & %mysql%\mysql -q -s -h %svr% --user=%user% --password=%pass% --port=%port% %cdb% < %%i

if %quick% neq off goto :eof

:done
echo.
echo Done :)
echo.
pause