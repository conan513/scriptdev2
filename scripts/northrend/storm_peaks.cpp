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
SDName: Storm_Peaks
SD%Complete: 0
SDComment: Placeholder
SDCategory: Storm Peaks
EndScriptData */

/* ContentData
EndContentData */

#include "precompiled.h"
#include "Vehicle.h"
#include "TemporarySummon.h"
#include "escort_ai.h"

/*######
## npc_freed_protodrake
######*/

enum
{
//    NPC_A  = 29366,
    NPC_PROTODRAKE = 29709,
    NPC_LIBERATED_VRYKUL = 29734,
    SPELL_PROTODRAKE_KILL_CREDIT = 55143,
    SPELL_LIBERATED_VRYKUL_KILL_CREDIT = 55144
};

struct MANGOS_DLL_DECL npc_freed_protodrakeAI : public ScriptedAI
{
    npc_freed_protodrakeAI(Creature* pCreature) : ScriptedAI(pCreature) { }

    void Reset() {}

    void MoveInLineOfSight(Unit* pWho)
    {
            if (pWho->GetEntry() == NPC_PROTODRAKE && (m_creature->GetDistance(7005.622f, -1752.7811f, 836.239f) < 25.0f))
            {
                if (VehicleKit *vehicle = pWho->GetVehicleKit())
                if (Unit* owner= vehicle->GetPassenger(0))
                if (owner->GetTypeId() == TYPEID_PLAYER)
                {
                           if (Unit* passenger = vehicle->GetPassenger(1))
                           {
                              vehicle->RemovePassenger(passenger);
                              passenger->CastSpell(passenger, 43014, false);
                              ((Player*)owner)->KilledMonsterCredit(NPC_LIBERATED_VRYKUL);
                           }
                           if (Unit* passenger = vehicle->GetPassenger(2))
                           {
                              vehicle->RemovePassenger(passenger);
                              passenger->CastSpell(passenger, 43014, false);
                              ((Player*)owner)->KilledMonsterCredit(NPC_LIBERATED_VRYKUL);
                           }
                           if (Unit* passenger = vehicle->GetPassenger(3))
                           {
                              vehicle->RemovePassenger(passenger);
                              passenger->CastSpell(passenger, 43014, false);
                              ((Player*)owner)->KilledMonsterCredit(NPC_LIBERATED_VRYKUL);
                           }
                           vehicle->RemoveAllPassengers();
                           ((Player*)owner)->KilledMonsterCredit(NPC_PROTODRAKE);
                }

				pWho->setFaction(35);
				pWho->CastSpell(pWho, 43014, false);
/*
				((Creature*)pWho)->ForcedDespawn(4000);
                float x, y, z;
                pWho->GetClosePoint(x, y, z, m_creature->GetObjectBoundingRadius(), 30.0f, pWho->GetOrientation());
                pWho->MonsterMoveWithSpeed(x, y, z+60.0f, 28);
*/
			}
	}

};

CreatureAI* GetAI_npc_freed_protodrake(Creature* pCreature)
{
    return new npc_freed_protodrakeAI(pCreature);
}

/*######
## npc_astrid
######*/

enum
{
//  NPC_A  = 29839,
    NPC_INJURED_ICEMAW_MATRIARCH = 29563,
    NPC_HARNESSED_ICEMAW_MATRIARCH = 30468,
    QUEST_THE_LAST_OF_HER_KIND = 12983
};

struct MANGOS_DLL_DECL npc_astridAI : public ScriptedAI
{
    npc_astridAI(Creature* pCreature) : ScriptedAI(pCreature) { }

    void Reset() {}

    void MoveInLineOfSight(Unit* pWho)
    {
		if (pWho->GetEntry() == NPC_HARNESSED_ICEMAW_MATRIARCH && m_creature->IsWithinDistInMap(pWho, 10.0f))
		{
			if (VehicleKit *vehicle = pWho->GetVehicleKit())
				if (Unit* owner= vehicle->GetPassenger(0))
					if (owner->GetTypeId() == TYPEID_PLAYER && (((Player*)owner)->GetQuestStatus(QUEST_THE_LAST_OF_HER_KIND) == QUEST_STATUS_INCOMPLETE))
					{
						((Player*)owner)->KilledMonsterCredit(NPC_INJURED_ICEMAW_MATRIARCH);
						vehicle->RemoveAllPassengers();
						pWho->CastSpell(pWho, 43014, false);
					}
		}
	}
};

CreatureAI* GetAI_npc_astrid(Creature* pCreature)
{
    return new npc_astridAI(pCreature);
}

/*######
+## npc_goblin_miner Quest 12832
+######*/

enum
{
	GOSSIP_ITEM_1			   = -3608100,	
	QUEST_BITTER_DEPARTURE     = 12832,
	SAY_END_WP_REACHED		   = -1800005,	
	SAY_START_WP_REACHED	   = -1800006,
};

struct MANGOS_DLL_DECL npc_injured_goblinAI : public npc_escortAI
{
    npc_injured_goblinAI(Creature* pCreature) : npc_escortAI(pCreature) {Reset();}

	void Reset() {}

    void WaypointReached(uint32 uiPointId)
	{
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

		switch (uiPointId)
		{
		case 14:
			DoScriptText(SAY_END_WP_REACHED, m_creature);
			if (pPlayer)
				pPlayer->GroupEventHappens(QUEST_BITTER_DEPARTURE, m_creature);
			break;
		}
	}

    void JustDied(Unit* pKiller)
    {
		Player* pPlayer = GetPlayerForEscort();
		if (HasEscortState(STATE_ESCORT_ESCORTING) && pPlayer)
			pPlayer->FailQuest(QUEST_BITTER_DEPARTURE);
    }

	void UpdateEscortAI(uint32 const uiDiff) 
	{        
		if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
			return;

		DoMeleeAttackIfReady();

		return;
	}
};

CreatureAI* GetAI_npc_injured_goblin(Creature* pCreature)
{
    return new npc_injured_goblinAI(pCreature);
}

bool GossipHello_npc_injured_goblin(Player* pPlayer, Creature* pCreature)
{
	if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_BITTER_DEPARTURE) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(8239, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_injured_goblin(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
	{
		pCreature->RemoveAurasDueToSpell(29266);
		if (npc_injured_goblinAI* pEscortAI = dynamic_cast<npc_injured_goblinAI*>(pCreature->AI()))
		{
			pEscortAI->Start(true, pPlayer);
			pCreature->setFaction(113);
		}
	}

	pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

bool QuestAccept_npc_injured_goblin(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_BITTER_DEPARTURE)
		DoScriptText(SAY_START_WP_REACHED, pCreature);
    return true;
}

/*######
## Quest 13047: The Reckoning
######*/

enum
{
    EVENT_01_THORIM                  = -1090500,
    EVENT_02_THORIM                  = -1090501,
    EVENT_03_THORIM                  = -1090502,
    EVENT_04_LOKEN                   = -1090503,
    EVENT_05_THORIM                  = -1090504,
    EVENT_06_THORIM                  = -1090505,
    EVENT_07_THORIM                  = -1090506,
    EVENT_08_LOKEN                   = -1090507,
    EVENT_09_LOKEN                   = -1090508,
    EVENT_10_LOKEN                   = -1090509,
    EVENT_11_LOKEN                   = -1090510,
    EVENT_12_LOKEN                   = -1090511,
    EVENT_13_LOKEN                   = -1090512,
    EVENT_14_LOKEN                   = -1090513,

    QUEST_THE_RECKONING              = 13047,
    EQUIP_WEAPON                     = 45900,

    NPC_THORIM                       = 30399,
    NPC_LOKEN                        = 30396,
    NPC_VERANUS                      = 30420,
    NPC_RUNEFORGED_SERVANT_1         = 30429,
    NPC_RUNEFORGED_SERVANT_2         = 30410,
};

struct MANGOS_DLL_DECL npc_thorim_eventAI : public ScriptedAI
{
    npc_thorim_eventAI(Creature* pCreature) : ScriptedAI(pCreature) 
    { 
        SetEquipmentSlots(false, EQUIP_WEAPON, -1, -1);
        Reset(); 
    }

    ObjectGuid m_VeranusGuid;
    ObjectGuid m_LokenGuid;
    ObjectGuid m_RuneforgedOneGuid;
    ObjectGuid m_RuneforgedTwoGuid;

    uint32 m_uiEventStep;
    uint32 m_uiNextEventTimer;

    void Reset()
    {
        m_creature->SetWalk(false);
        m_creature->SetSpeedRate(MOVE_RUN, 1.0f);

        m_VeranusGuid.Clear();
        m_LokenGuid.Clear();
        m_RuneforgedOneGuid.Clear();
        m_RuneforgedTwoGuid.Clear();

        m_uiEventStep                = 0;
        m_uiNextEventTimer           = 0;
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_VERANUS)
            m_VeranusGuid = pSummoned->GetObjectGuid();

        if (pSummoned->GetEntry() == NPC_LOKEN)
            m_LokenGuid = pSummoned->GetObjectGuid();

        if (pSummoned->GetEntry() == NPC_RUNEFORGED_SERVANT_1)
            m_RuneforgedOneGuid = pSummoned->GetObjectGuid();

        if (pSummoned->GetEntry() == NPC_RUNEFORGED_SERVANT_2)
            m_RuneforgedTwoGuid = pSummoned->GetObjectGuid();
    }

    void UpdateAI(const uint32 uiDiff)
    {
            if (m_uiNextEventTimer <= uiDiff)
            {   
                switch (m_uiEventStep)
                {   
                    case 1:
                        m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                        if (Creature* pVeranus = m_creature->SummonCreature(NPC_VERANUS, 8717.76f, -698.88f, 972.31f, 2.51f, TEMPSUMMON_MANUAL_DESPAWN, 20000))
                        {
                            pVeranus->SetLevitate(true);
                            pVeranus->SetWalk(false);
                            pVeranus->SetSpeedRate(MOVE_RUN, 2.0f);
                            pVeranus->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
                            pVeranus->GetMotionMaster()->MovePoint(0, 8690.88f, -582.22f, 963.31f);
                        }
                        NextStep(2000);
                        break;
                    case 2:
                        DoScriptText(EVENT_01_THORIM, m_creature);
                        NextStep(5000);
                        break;
                    case 3:
                    {
                        if (Creature* pLoken = m_creature->SummonCreature(NPC_LOKEN, 8562.55f, -579.08f, 925.55f, 5.48f, TEMPSUMMON_MANUAL_DESPAWN, 20000))
                            pLoken->SetByteValue(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_SIT);

                        m_creature->GetMotionMaster()->MovePoint(0, 8647.54f, -661.60f, 923.88f);

                        Creature* pVeranus = m_creature->GetMap()->GetCreature(m_VeranusGuid);
                        pVeranus->GetMotionMaster()->MovePoint(0, 8599.60f, -582.64f, 962.31f);
                        NextStep(11000);
                        break;
                    }
                    case 4:
                    {
                        Creature* pVeranus = m_creature->GetMap()->GetCreature(m_VeranusGuid);
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        pVeranus->SetFacingToObject(pLoken);
                        m_creature->GetMotionMaster()->MovePoint(0, 8606.12f, -621.83f, 925.65f);
                        NextStep(9000);
                        break;
                    }
                    case 5:
                        DoScriptText(EVENT_02_THORIM, m_creature);
                        m_creature->HandleEmote(EMOTE_ONESHOT_ROAR);
                        NextStep(3000);
                        break;
                    case 6:
                        m_creature->SetSpeedRate(MOVE_RUN, 2.0f);
                        m_creature->GetMotionMaster()->MovePoint(0, 8575.66f, -592.58f, 925.55f);
                        NextStep(4000);
                        break;
                    case 7:
                        DoScriptText(EVENT_03_THORIM, m_creature);
                        m_creature->HandleEmote(EMOTE_ONESHOT_ROAR);
                        NextStep(3000);
                        break;
                    case 8:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        pLoken->SetWalk(false);
                        pLoken->SetByteValue(UNIT_FIELD_BYTES_1, 0, UNIT_STAND_STATE_STAND);
                        NextStep(3000);
                        break;
                    }
                    case 9:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        pLoken->GetMotionMaster()->MovePoint(0, 8568.84f, -584.06f, 925.55f);
                        NextStep(2000);
                        break;
                    }
                    case 10:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        pLoken->CastSpell(pLoken, 64319, false);
                        NextStep(500);
                        break;
                    }
                    case 11:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        m_creature->GetMotionMaster()->MoveJump(8598.38f, -616.27f, 925.55f, 20.0f, 8.0f);
                        NextStep(3000);
                        break;
                    }
                    case 12:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        pLoken->HandleEmote(EMOTE_ONESHOT_POINT);
                        DoScriptText(EVENT_04_LOKEN, pLoken);
                        m_creature->SetFacingToObject(pLoken);
                        NextStep(3000);
                        break;
                    }
                    case 13:
                    {
                        DoScriptText(EVENT_05_THORIM, m_creature);
                        NextStep(1000);
                        break;
                    }
                    case 14:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        m_creature->CastSpell(pLoken, 56694, false);
                        DoScriptText(EVENT_06_THORIM, m_creature);
                        NextStep(1000);
                        break;
                    }
                    case 15:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        m_creature->CastSpell(pLoken, 56695, false);
                        DoScriptText(EVENT_07_THORIM, m_creature);
                        NextStep(1000);
                        break;
                    }
                    case 16:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        pLoken->GetMotionMaster()->MoveJump(8562.55f, -579.08f, 925.55f, 20.0f, 8.0f);
                        pLoken->CastSpell(pLoken, 55825, false);
                        SetEquipmentSlots(false, 0, -1, -1);
                        NextStep(2000);
                        break;
                    }
                    case 17:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        DoScriptText(EVENT_08_LOKEN, pLoken);
                        pLoken->SetFacingToObject(m_creature);
                        NextStep(3000);
                        break;
                    }
                    case 18:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        pLoken->GetMotionMaster()->MovePoint(0, 8568.84f, -584.06f, 925.55f);
                        DoScriptText(EVENT_09_LOKEN, pLoken);
                        NextStep(5000);
                        break;
                    }
                    case 19:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        DoScriptText(EVENT_10_LOKEN, pLoken);
                        pLoken->CastSpell(m_creature, 56696, false);
                        NextStep(6000);
                        break;
                    }
                    case 20:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        DoScriptText(EVENT_11_LOKEN, pLoken);
                        NextStep(10000);
                        break;
                    }
                    case 21:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        m_creature->SummonCreature(NPC_RUNEFORGED_SERVANT_1, 8561.50f, -613.84f, 925.55f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 20000);
                        m_creature->SummonCreature(NPC_RUNEFORGED_SERVANT_2, 8602.89f, -576.12f, 925.55f, 5.1f, TEMPSUMMON_MANUAL_DESPAWN, 20000);
                        DoScriptText(EVENT_12_LOKEN, pLoken);
                        NextStep(10000);
                        break;
                    }
                    case 22:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        DoScriptText(EVENT_13_LOKEN, pLoken);
                        NextStep(10000);
                        break;
                    }
                    case 23:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        DoScriptText(EVENT_14_LOKEN, pLoken);
                        NextStep(10000);
                        break;
                    }
                    case 24:
                    {
                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        pLoken->CastSpell(pLoken, 64446, false);

                        Creature* pRuneforgedOne = m_creature->GetMap()->GetCreature(m_RuneforgedOneGuid);
                        pRuneforgedOne->CastSpell(pRuneforgedOne, 64446, false);

                        Creature* pRuneforgedTwo = m_creature->GetMap()->GetCreature(m_RuneforgedTwoGuid);
                        pRuneforgedTwo->CastSpell(pRuneforgedTwo, 64446, false);

                        m_creature->CastSpell(m_creature, 56941, false);

                        NextStep(1000);
                        break;
                    }
                    case 25:
                    {

                        Creature* pLoken = m_creature->GetMap()->GetCreature(m_LokenGuid);
                        Creature* pVeranus = m_creature->GetMap()->GetCreature(m_VeranusGuid);
                        Creature* pRuneforgedOne = m_creature->GetMap()->GetCreature(m_RuneforgedOneGuid);
                        Creature* pRuneforgedTwo = m_creature->GetMap()->GetCreature(m_RuneforgedTwoGuid);

                        m_creature->ForcedDespawn();
                        pLoken->ForcedDespawn();
                        pVeranus->ForcedDespawn();
                        pRuneforgedOne->ForcedDespawn();
                        pRuneforgedTwo->ForcedDespawn();

                        NextStep(60000);
                        break;
                    }
                    case 26:
                    {
                        m_creature->SummonCreature(NPC_THORIM, 8703.28f, -715.64f, 934.34f, 2.4f, TEMPSUMMON_MANUAL_DESPAWN, 20000);
                        NextStep();
                        break;
                    }
                    default:
                        break;
                } 
            }
            else
                m_uiNextEventTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_thorim_event(Creature* pCreature)
{
    return new npc_thorim_eventAI(pCreature);
}

bool GossipHello_npc_thorim_event(Player* pPlayer, Creature* pCreature)
{
  char const* GOSSIP_EVENT = "I'm with you, Thorim.";
  
  if (pPlayer->GetQuestStatus(QUEST_THE_RECKONING) == QUEST_STATUS_INCOMPLETE)
  {
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_EVENT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->SEND_GOSSIP_MENU(13800, pCreature->GetObjectGuid());
    return true;
  }
  return false;
}

bool GossipSelect_npc_thorim_event(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        ((npc_thorim_eventAI*)pCreature->AI())->m_uiEventStep = 1;
    }
    return true;
}

void AddSC_storm_peaks()
{
  Script* pNewScript;
  
  pNewScript = new Script;
  pNewScript->Name = "npc_freed_protodrake";
  pNewScript->GetAI = &GetAI_npc_freed_protodrake;
  pNewScript->RegisterSelf();

  pNewScript = new Script;
  pNewScript->Name = "npc_astrid";
  pNewScript->GetAI = &GetAI_npc_astrid;
  pNewScript->RegisterSelf();
  
  pNewScript = new Script;
  pNewScript->Name = "npc_injured_goblin";
  pNewScript->GetAI = &GetAI_npc_injured_goblin;
  pNewScript->pQuestAcceptNPC = &QuestAccept_npc_injured_goblin;
  pNewScript->pGossipHello =  &GossipHello_npc_injured_goblin;
  pNewScript->pGossipSelect = &GossipSelect_npc_injured_goblin;
  pNewScript->RegisterSelf();
  
  pNewScript = new Script;
  pNewScript->Name = "npc_thorim_event";
  pNewScript->GetAI = &GetAI_npc_thorim_event;
  pNewScript->pGossipHello = &GossipHello_npc_thorim_event;
  pNewScript->pGossipSelect = &GossipSelect_npc_thorim_event;
  pNewScript->RegisterSelf();
}
