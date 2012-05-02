/* Copyright (C) 2006 - 2012 ScriptDev2 <http://www.scriptdev2.com/>
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
SDName: Zuldrak
SD%Complete: 100
SDComment: Quest support: 12934.
SDCategory: Zuldrak
EndScriptData */

/* ContentData
npc_gurgthock
EndContentData */

#include "precompiled.h"

/*######
## npc_gurgthock
######*/

enum
{
    QUEST_FROM_BEYOND = 12934,

    NPC_AZBARIN       = 30026,
    NPC_DUKE_SINGEN   = 30019,
    NPC_ERATHIUS      = 30025,
    NPC_GARGORAL      = 30024
};

static float m_afSpawnLocation[] = {5768.71f, -2969.29f, 273.816f};
static uint32 m_auiBosses[] = {NPC_AZBARIN, NPC_DUKE_SINGEN, NPC_ERATHIUS, NPC_GARGORAL};

struct MANGOS_DLL_DECL npc_gurgthockAI : public ScriptedAI
{
    npc_gurgthockAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    ObjectGuid m_playerGuid;

    void SetPlayer(Player* pPlayer)
    {
        m_playerGuid = pPlayer->GetObjectGuid();
    }

    void Reset()
    {
        m_playerGuid.Clear();
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        uint32 uiEntry = pSummoned->GetEntry();
        for(uint8 i = 0; i < 4; ++i)
        {
            if (uiEntry == m_auiBosses[i])
            {
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
                    pPlayer->GroupEventHappens(QUEST_FROM_BEYOND, m_creature);

                m_playerGuid.Clear();
                return;
            }
        }
    }
};

bool QuestAccept_npc_gurgthock(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_FROM_BEYOND)
    {
        pCreature->SummonCreature(m_auiBosses[urand(0, 3)], m_afSpawnLocation[0], m_afSpawnLocation[1], m_afSpawnLocation[2], 0.0f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 600000);

        if (npc_gurgthockAI* pGurthockAI = dynamic_cast<npc_gurgthockAI*>(pCreature->AI()))
            pGurthockAI->SetPlayer(pPlayer);
    }
    return true;
}

CreatureAI* GetAI_npc_gurgthock(Creature* pCreature)
{
    return new npc_gurgthockAI(pCreature);
}

/*####
## npc_gymer
####*/

#define GOSSIP_ITEM_G "I'm ready, Gymer. Let's go!"

enum eGymer
{
    QUEST_STORM_KING_VENGEANCE    = 12919,
    SPELL_GYMER                   = 55568
};

bool GossipHello_npc_gymer_q(Player* pPlayer, Creature *pCreature)
{
	if (pCreature->isQuestGiver())
		pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

	if (pPlayer->GetQuestStatus(QUEST_STORM_KING_VENGEANCE) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_G, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->SEND_GOSSIP_MENU(13640,pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_gymer_q(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF + 1)
		pPlayer->CastSpell(pPlayer, SPELL_GYMER, true);

	pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

void AddSC_zuldrak()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_gurgthock";
    pNewScript->GetAI = &GetAI_npc_gurgthock;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_gurgthock;
    pNewScript->RegisterSelf();

	pNewScript = new Script;
    pNewScript->Name="npc_gymer_q";
    pNewScript->pGossipHello =  &GossipHello_npc_gymer_q;
    pNewScript->pGossipSelect = &GossipSelect_npc_gymer_q;
    pNewScript->RegisterSelf();
}
