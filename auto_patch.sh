#!/bin/bash
#
#

echo "SCRIPTDEV2" > patch_SD2.log
echo "Git reset Hard" >> patch_SD2.log
#cd ~/server_wotlk/fork/mangos/src/bindings/scriptdev2
git reset --hard
echo "Patching" >> patch_SD2.log
#patches=`find -maxdepth 1 -name "*.patch"`
patches=`find -maxdepth 1 -name "*.patch"`
for j in $patches; do
    echo "Apply patch : "$j
    echo "Apply patch : "$j >> patch_SD2.log
    echo $(patch -p1 <$j) >> patch_SD2.log;
    #patch -p1 < $j > $j.log
    echo $? >> patch_SD2.log
    echo $?
done
