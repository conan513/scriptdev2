/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
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
SDName: Isle_of_Queldanas
SD%Complete: 100
SDComment: Quest support: 11524, 11525, 24535, 24563
SDCategory: Isle Of Quel'Danas
EndScriptData */

/* ContentData
npc_converted_sentry
EndContentData */

#include "precompiled.h"

/*######
## npc_converted_sentry
######*/

enum
{
    SAY_CONVERTED_1             = -1000188,
    SAY_CONVERTED_2             = -1000189,

    SPELL_CONVERT_CREDIT        = 45009,
    TIME_PET_DURATION           = 7500
};

struct MANGOS_DLL_DECL npc_converted_sentryAI : public ScriptedAI
{
    npc_converted_sentryAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiCreditTimer;

    void Reset()
    {
        m_uiCreditTimer = 2500;
    }

    void MoveInLineOfSight(Unit* pWho) {}

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiCreditTimer)
        {
            if (m_uiCreditTimer <= uiDiff)
            {
                DoScriptText(urand(0, 1) ? SAY_CONVERTED_1 : SAY_CONVERTED_2, m_creature);

                DoCastSpellIfCan(m_creature, SPELL_CONVERT_CREDIT);
                ((Pet*)m_creature)->SetDuration(TIME_PET_DURATION);
                m_uiCreditTimer = 0;
            }
            else
                m_uiCreditTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_converted_sentry(Creature* pCreature)
{
    return new npc_converted_sentryAI(pCreature);
}

/*######
## npc_thalorien_dawnseeker
######*/

#define GOSSIP_ITEM_QUEST_24535_AND_24563  -3100800

bool GossipHello_npc_thalorien_dawnseeker(Player* pPlayer, Creature *pCreature)
{
	if (pPlayer->GetQuestStatus(24535) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(24563) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_QUEST_24535_AND_24563, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
	pPlayer->SEND_GOSSIP_MENU(15155, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_thalorien_dawnseeker(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF + 1)
		pPlayer->KilledMonsterCredit(37601);

	pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

void AddSC_isle_of_queldanas()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_converted_sentry";
    pNewScript->GetAI = &GetAI_npc_converted_sentry;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="npc_thalorien_dawnseeker";
    pNewScript->pGossipHello =  &GossipHello_npc_thalorien_dawnseeker;
    pNewScript->pGossipSelect = &GossipSelect_npc_thalorien_dawnseeker;
    pNewScript->RegisterSelf();
}
