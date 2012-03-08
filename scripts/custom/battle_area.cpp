/* Copyright (C) 2006 - 2012 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: battle_area
SD%Complete: 100%
SDComment: by orion
SDCategory: custom
EndScriptData */

#include "precompiled.h"
#include "sc_creature.h"
#include "sc_gossip.h"
#include "ObjectMgr.h"

#define GOSSIP_TELEPORT_IN_BATTLE "Teleport battle area"

// Teleport
static const float pTeleportPositions[5][4] =
{
    {36.99f, 909.46f, 339.39f, 4.96f},
    {323.75f, -100.34f, 271.17f, 0.05f},
    {1026.82f, 292.22f, 332.75f, 3.39f},
    {138.07f, 313.91f, 282.47f, 4.79f},
    {314.67f, 614.55f, 276.70f, 2.57f}
};

const uint16 mapId = 37;

bool GossipHello_npc_teleport(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->IsInCombat())
        return false;

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TELEPORT_IN_BATTLE, GOSSIP_SENDER_MAIN, 1);
    pPlayer->SEND_GOSSIP_MENU(3961,pCreature->GetObjectGuid());
    return true;
}

void SendDefaultMenu_npc_teleport(Player* pPlayer, Creature* pCreature, uint32 action)
{
    if (pPlayer->IsInCombat())
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL);
        return;
    }

    if (pPlayer->GetGroup()->isRaidGroup() || !pPlayer->GetGroup() || pPlayer->GetGroup()->GetLeaderGuid() != pPlayer->GetObjectGuid())
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay("You in not Group or is Raid or did'nt leader group", LANG_UNIVERSAL);
        return;
    }

    switch(action)
    {
        case 1:
        {
            QueryResult *result = CharacterDatabase.PQuery("SELECT group_id FROM character_battle_registration WHERE group_id = '%u'", pPlayer->GetGroup()->GetId());
            if (!result)
            {
                CharacterDatabase.PExecute("INSERT INTO character_battle_registration (guid, group_id) VALUES (%u, %u)", pPlayer->GetGUIDLow(), pPlayer->GetGroup()->GetId());
                QueryResult *Check = CharacterDatabase.Query("SELECT count(*) FROM character_battle_registration");
                if (Check)
                {
                    Field *fields = Check->Fetch();
                    uint32 count_team = fields[0].GetUInt32();
                    if (count_team > 1)
                    {
                        QueryResult *ListTeleport = CharacterDatabase.Query("SELECT group_id FROM character_battle_registration WHERE flag == 0");
                        if (ListTeleport)
                        {
                            do
                            {
                                Field *fields = ListTeleport->Fetch();
                                uint32 groupId = fields[0].GetUInt32();
                                if (Group* pGroup = sObjectMgr.GetGroupById(groupId))
                                {
                                    uint8 randomPostion = urand(0, 4);
                                    Group::MemberSlotList const& groupSlot = pGroup->GetMemberSlots();
                                    for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
                                        pGroup->TeleportInBattleArea(itr->guid, mapId, pTeleportPositions[randomPostion][0], pTeleportPositions[randomPostion][1], pTeleportPositions[randomPostion][2], pTeleportPositions[randomPostion][3]);
                                    CharacterDatabase.PExecute("UPDATE character_battle_registration SET flag = 1 WHERE group_id = %u", pGroup->GetId());
                                }
                            }
                            while (ListTeleport->NextRow());
                            delete ListTeleport;
                        }
                    } else {
                        pPlayer->CLOSE_GOSSIP_MENU();
                        pCreature->MonsterSay("You REGISTRATION Zdite", LANG_UNIVERSAL);
                    }
                    delete Check;
                }
            } else {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterSay("You REGISTRATION Zdite", LANG_UNIVERSAL);
                delete result;
            }
            break;
        }
    }
}

bool GossipSelect_npc_teleport(Player *pPlayer, Creature *_Creature, uint32 sender, uint32 action)
{
    // Main menu
    if (sender == GOSSIP_SENDER_MAIN)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        SendDefaultMenu_npc_teleport(pPlayer, _Creature, action);
    }
    return true;
}

void AddSC_battle_area()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_teleport_in_battle_area";
    pNewScript->pGossipHello = &GossipHello_npc_teleport;
    pNewScript->pGossipSelect = &GossipSelect_npc_teleport;
    pNewScript->RegisterSelf();

}
