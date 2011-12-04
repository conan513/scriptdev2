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
SDName: pit_of_saron
SD%Complete: 60%
SDComment: support event
SDCategory: Pit of Saron
EndScriptData */

#include "precompiled.h"
#include "pit_of_saron.h"

enum
{
	KRICK_SAY_1	                        = -1658030, //1
	KRICK_SAY_2		                    = -1658033, //3
	KRICK_SAY_3							= -1658036, //5
	KRICK_SAY_4							= -1658038, //7

	SL_LORE_SAY_1						= -1658032, //2
	SL_LORE_SAY_2						= -1658035, //4
	SL_LORE_SAY_3						= -1658041, //8
	SL_LORE_SAY_4						= -1658066, //11.1
	SL_LORE_SAY_5						= -1658068, //11.2

	TYRANNUS_E_SAY_1					= -1658037, //10
	TYRANNUS_E_SAY_2					= -1658039, //6
	TYRANNUS_E_SAY_3					= -1658050, //9
	TYRANNUS_E_SAY_4					= -1658053,
	TYRANNUS_E_SAY_5					= -1658054,
		
	JA_A_SAY_1							= -1658031, //2.1
	JA_A_SAY_2							= -1658034, //4.2
	JA_A_SAY_3							= -1658040, //7.3
	JA_A_SAY_4							= -1658065, //9.1
	JA_A_SAY_5							= -1658067, //9.2
	JA_A_SAY_6							= -1658069, //9.3
	
	MARTIN_AND_GONROK_1					= -1999805, //not text in db
	MARTIN_AND_GONROK_2					= -1658063, //10.2
	MARTIN_AND_GONROK_3					= -1658064,	//10.3

	NPC_TYRANNUS_EVENT					= 36794,

	SPELL_STRANGULATING                 = 69413,
	SPELL_FROST_BOMB                    = 70521,

	SPELL_JAINA_SUMMON					= 70623,
	SPELL_SYLVANAS_SUMMON				= 70638,

};

struct MANGOS_DLL_DECL npc_jaina_or_sylvanas_POSintroAI : public ScriptedAI
{
   npc_jaina_or_sylvanas_POSintroAI(Creature *pCreature) : ScriptedAI(pCreature)
   {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
   }

   ScriptedInstance* m_pInstance;
   uint32 m_uiUpdateTimer;

   void Reset()
   {
	   if(!m_pInstance) return;
	   m_uiUpdateTimer = 0;
   }

   void UpdateAI(const uint32 uiDiff)
    {
        if(!m_pInstance) return;

        if (m_pInstance->GetData(TYPE_EVENT_NPC) == NPC_SYLVANAS_PART1 || m_pInstance->GetData(TYPE_EVENT_NPC) == NPC_JAINA_PART1)
        {
			m_uiUpdateTimer = m_pInstance->GetData(TYPE_EVENT_TIMER);
			if (m_uiUpdateTimer <= uiDiff)
			{
				debug_log("EventMGR: creature %u received signal %u ",m_creature->GetEntry(),m_pInstance->GetData(TYPE_EVENT));
				switch (m_pInstance->GetData(TYPE_EVENT))
	                {
				case 5: //case 1..4 - старт первого ивента после входа.
				    m_creature->SetActiveObjectState(true);
					if (Creature* pKrick = m_pInstance->GetSingleCreatureFromStorage(NPC_KRICK))
					{
						pKrick->RemoveAllAuras();
						DoScriptText(KRICK_SAY_1, pKrick);
					}
					m_uiUpdateTimer = 7000;
					m_pInstance->SetData(TYPE_EVENT, 10);
					break;
				case 10:
					if (m_pInstance->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
						DoScriptText(SL_LORE_SAY_1, m_creature);
					else DoScriptText(JA_A_SAY_1, m_creature);
					m_uiUpdateTimer = 5000;
					m_pInstance->SetData(TYPE_EVENT, 15);
					break;
				case 15:
					if (Creature* pKrick = m_pInstance->GetSingleCreatureFromStorage(NPC_KRICK))
						DoScriptText(KRICK_SAY_2, pKrick);
					m_uiUpdateTimer = 6000;
					m_pInstance->SetData(TYPE_EVENT, 20);
					break;
				case 20:
					if (m_pInstance->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
						DoScriptText(SL_LORE_SAY_2, m_creature);
					else DoScriptText(JA_A_SAY_2, m_creature);
					m_uiUpdateTimer = 7000;
					m_pInstance->SetData(TYPE_EVENT, 25);
					break;
				case 25:
					if (Creature* pKrick = m_pInstance->GetSingleCreatureFromStorage(NPC_KRICK))
						DoScriptText(KRICK_SAY_3, pKrick);
					m_uiUpdateTimer = 1000;
					m_pInstance->SetData(TYPE_EVENT, 30);
					break;
				case 30:
					if (Creature* pTyrannus = m_pInstance->GetSingleCreatureFromStorage(NPC_TYRANNUS_EVENT))
					{
						pTyrannus->SetSpeedRate(MOVE_RUN, 6.0f);
						pTyrannus->GetMotionMaster()->Clear();
						pTyrannus->GetMotionMaster()->MovePoint(1, 848.254395f, 294.516144f, 588.981934f);
					}
					m_uiUpdateTimer = 6000;
					m_pInstance->SetData(TYPE_EVENT, 35);
					break;
				case 35:
					if (Creature* pTyrannus = m_pInstance->GetSingleCreatureFromStorage(NPC_TYRANNUS_EVENT))
						pTyrannus->GetMotionMaster()->MovePoint(2, 831.122314f, 171.628357f, 538.350159f);
					m_uiUpdateTimer = 2000;
					m_pInstance->SetData(TYPE_EVENT, 40);
					break;
				case 40:
					if (Creature* pTyrannus = m_pInstance->GetSingleCreatureFromStorage(NPC_TYRANNUS_EVENT))
					{
						pTyrannus->SetSpeedRate(MOVE_RUN, 2.0f);
						pTyrannus->GetMotionMaster()->MovePoint(3, 839.059387f, 143.279602f, 534.954834f);
					}
					m_uiUpdateTimer = 2000;
					m_pInstance->SetData(TYPE_EVENT, 45);
					break;
				case 45:
					if (Creature* pTyrannus = m_pInstance->GetSingleCreatureFromStorage(NPC_TYRANNUS_EVENT))
						DoScriptText(TYRANNUS_E_SAY_1, pTyrannus);
					m_uiUpdateTimer = 4000;
					m_pInstance->SetData(TYPE_EVENT, 50);
					break;
				case 50:
					if (Creature* pKrick = m_pInstance->GetSingleCreatureFromStorage(NPC_KRICK))
						DoScriptText(KRICK_SAY_4, pKrick);
					m_uiUpdateTimer = 3000;
					m_pInstance->SetData(TYPE_EVENT, 55);
					break;
				case 55:
					if(Creature* pTyrannus = m_pInstance->GetSingleCreatureFromStorage(NPC_TYRANNUS_EVENT))
					{
						if (Creature* pKrick = m_pInstance->GetSingleCreatureFromStorage(NPC_KRICK))
						{
							pKrick->CastSpell(pKrick, SPELL_STRANGULATING, true);
							pKrick->SetLevitate(true);
							pKrick->GetMotionMaster()->Clear();
							pKrick->GetMotionMaster()->MovePoint(1, pKrick->GetPositionX(), pKrick->GetPositionY(), pKrick->GetPositionZ()+5);
							DoScriptText(TYRANNUS_E_SAY_2, pTyrannus);
						}
					}
					m_uiUpdateTimer = 6000;
					m_pInstance->SetData(TYPE_EVENT, 60);
					break;
				case 60:
					if(Creature* pKrick = m_pInstance->GetSingleCreatureFromStorage(NPC_KRICK))
					{	
						pKrick->SetLevitate(false);
						pKrick->SetRespawnDelay(DAY);
						pKrick->DealDamage(pKrick, pKrick->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
						m_pInstance->SetData(TYPE_KRICK, DONE);
					}
					m_uiUpdateTimer = 2000;
					m_pInstance->SetData(TYPE_EVENT, 65);
					break;
				case 65:
					if (m_pInstance->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
						DoScriptText(SL_LORE_SAY_3, m_creature);
					else DoScriptText(JA_A_SAY_3, m_creature);
					m_uiUpdateTimer = 5000;
					m_pInstance->SetData(TYPE_EVENT, 70);
					break;
				case 70:
					if (Creature* pTyrannus = m_pInstance->GetSingleCreatureFromStorage(NPC_TYRANNUS_EVENT))
						DoScriptText(TYRANNUS_E_SAY_3, pTyrannus);
					m_uiUpdateTimer = 4000;
					m_pInstance->SetData(TYPE_EVENT, 75);
					break;
				case 75:
					if (Creature* pTyrannus = m_pInstance->GetSingleCreatureFromStorage(NPC_TYRANNUS_EVENT))
					{
						pTyrannus->SetSpeedRate(MOVE_RUN, 2.0f);
						pTyrannus->GetMotionMaster()->Clear();
						pTyrannus->GetMotionMaster()->MovePoint(1, 821.386292f, -126.036270f, 627.701782f);
					}
					m_uiUpdateTimer = 5000;
					m_pInstance->SetData(TYPE_EVENT, 80);
					break;
				case 80:
					m_creature->setFaction(35);
					m_creature->SetSpeedRate(MOVE_RUN, 0.6f);
					m_creature->GetMotionMaster()->Clear();
					m_creature->GetMotionMaster()->MovePoint(0, 811.380920f, 80.483505f, 509.527222f);
					m_uiUpdateTimer = 7000;
					m_pInstance->SetData(TYPE_EVENT, 85);
					break;
				case 85:
					m_creature->SetSpeedRate(MOVE_RUN, 1.0f);
					m_creature->GetMotionMaster()->MovePoint(1, 848.286926f, -21.280975f, 509.445770f);
					m_uiUpdateTimer = 24000;
					m_pInstance->SetData(TYPE_EVENT, 90);
					break;
				case 90:
					m_creature->ForcedDespawn(10000);
					m_creature->SetActiveObjectState(false);
					m_pInstance->SetData(TYPE_EVENT, 0);
					break;
				default:
					break;
				}
			}
			else m_uiUpdateTimer -= uiDiff;
			m_pInstance->SetData(TYPE_EVENT_TIMER, m_uiUpdateTimer);
		}
   }
};

struct MANGOS_DLL_DECL npc_jaina_or_sylvanas_POSoutroAI : public ScriptedAI
{
   npc_jaina_or_sylvanas_POSoutroAI(Creature *pCreature) : ScriptedAI(pCreature)
   {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
   }

   ScriptedInstance* m_pInstance;
   uint32 m_uiUpdateTimer;

   void Reset()
   {
	   if(!m_pInstance) return;
	   m_uiUpdateTimer = 0;
   }

   void UpdateAI(const uint32 uiDiff)
   {
        if(!m_pInstance) return;

		if (m_pInstance->GetData(TYPE_EVENT_NPC) == NPC_SYLVANAS_PART2 || m_pInstance->GetData(TYPE_EVENT_NPC) == NPC_JAINA_PART2)
        {
			m_uiUpdateTimer = m_pInstance->GetData(TYPE_EVENT_TIMER);
			if (m_uiUpdateTimer <= uiDiff)
			{
				debug_log("EventMGR: creature %u received signal %u ",m_creature->GetEntry(),m_pInstance->GetData(TYPE_EVENT));
				switch (m_pInstance->GetData(TYPE_EVENT))
	                {
				case 101:
					m_creature->SetActiveObjectState(true);
					if (Creature* pRimefang = m_pInstance->GetSingleCreatureFromStorage(NPC_RIMEFANG))
						pRimefang->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					if (m_pInstance->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
						m_creature->SummonCreature(NPC_GORKUN_IRONSKULL, 1039.963623f, 146.529724f, 628.156189f, 2.195847f, TEMPSUMMON_TIMED_DESPAWN, 600000);
					else m_creature->SummonCreature(NPC_MARITN_VICTUS, 1039.963623f, 146.529724f, 628.156189f, 2.195847f, TEMPSUMMON_TIMED_DESPAWN, 600000);
					m_uiUpdateTimer = 2000;
					m_pInstance->SetData(TYPE_EVENT, 102);
					break;
				case 102:
					if (Creature* pTyrannus = m_pInstance->GetSingleCreatureFromStorage(NPC_TYRANNUS))
						DoScriptText(TYRANNUS_E_SAY_4, pTyrannus);
					m_uiUpdateTimer = 14000;
					m_pInstance->SetData(TYPE_EVENT, 103);
					break;
				case 103:
					if (Creature* pGorkun = m_pInstance->GetSingleCreatureFromStorage(NPC_GORKUN_IRONSKULL))
						DoScriptText(MARTIN_AND_GONROK_1, pGorkun);
					else
						if (Creature* pMartin = m_pInstance->GetSingleCreatureFromStorage(NPC_MARITN_VICTUS))
							DoScriptText(MARTIN_AND_GONROK_1, pMartin);
					m_uiUpdateTimer = 3000;
					m_pInstance->SetData(TYPE_EVENT, 104);
					break;
				case 104:
					if (Creature* pGorkun = m_pInstance->GetSingleCreatureFromStorage(NPC_GORKUN_IRONSKULL))
					{
						pGorkun->SetSpeedRate(MOVE_RUN, 1.2f);
						pGorkun->GetMotionMaster()->Clear();
						pGorkun->GetMotionMaster()->MovePoint(0, 1054.834839f, 103.437775f, 628.823914f);
					} else 
						if (Creature* pMartin = m_pInstance->GetSingleCreatureFromStorage(NPC_MARITN_VICTUS))
						{
							pMartin->SetSpeedRate(MOVE_RUN, 1.2f);
							pMartin->GetMotionMaster()->Clear();
							pMartin->GetMotionMaster()->MovePoint(0, 1054.834839f, 103.437775f, 628.823914f);
						}
					m_uiUpdateTimer = 3000;
					m_pInstance->SetData(TYPE_EVENT, 105);
					break;
				case 105:
					if (Creature* pTyrannus = m_pInstance->GetSingleCreatureFromStorage(NPC_TYRANNUS))
						DoScriptText(TYRANNUS_E_SAY_5, pTyrannus);
					if (Creature* pRimefang = m_pInstance->GetSingleCreatureFromStorage(NPC_RIMEFANG))
						pRimefang->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					m_creature->SetActiveObjectState(false);
					m_pInstance->SetData(TYPE_EVENT, 0);
					break;
				case 115:
					m_creature->SetActiveObjectState(true);
					if (Creature* pGorkun = m_pInstance->GetSingleCreatureFromStorage(NPC_GORKUN_IRONSKULL))
					{
						pGorkun->SetSpeedRate(MOVE_RUN, 1.5f);
						pGorkun->GetMotionMaster()->Clear();
						pGorkun->GetMotionMaster()->MovePoint(0, 1031.036743f, 148.157318f, 628.156250f);
					} else 
						if (Creature* pMartin = m_pInstance->GetSingleCreatureFromStorage(NPC_MARITN_VICTUS))
						{
							pMartin->SetSpeedRate(MOVE_RUN, 1.5f);
							pMartin->GetMotionMaster()->Clear();
							pMartin->GetMotionMaster()->MovePoint(0, 1031.036743f, 148.157318f, 628.156250f);
						}					
					m_creature->SummonCreature(NPC_SINDRAGOSA, 920.644958f, 226.479370f, 575.108948f, 5.367381f, TEMPSUMMON_DEAD_DESPAWN, 0);
					m_uiUpdateTimer = 10000;
					m_pInstance->SetData(TYPE_EVENT, 116);
					break;
				case 116:
					if (Creature* pGorkun = m_pInstance->GetSingleCreatureFromStorage(NPC_GORKUN_IRONSKULL))
						DoScriptText(MARTIN_AND_GONROK_2, pGorkun);
					else
						if (Creature* pMartin = m_pInstance->GetSingleCreatureFromStorage(NPC_MARITN_VICTUS))
							DoScriptText(MARTIN_AND_GONROK_2, pMartin);
	
					else m_creature->SummonCreature(NPC_MARITN_VICTUS, 1025.12f, 151.641f, 628.156f, 2.35846f, TEMPSUMMON_TIMED_DESPAWN, 600000);
					if (Creature* pSindragosa = m_pInstance->GetSingleCreatureFromStorage(NPC_SINDRAGOSA))
					{
						pSindragosa->GetMotionMaster()->Clear();
						pSindragosa->GetMotionMaster()->MovePoint(0, 920.644958f, 226.479370f, 655.609009f);
					}
					m_uiUpdateTimer = 18000;
 					m_pInstance->SetData(TYPE_EVENT, 117);
					break;
				case 117:
					if (Creature* pGorkun = m_pInstance->GetSingleCreatureFromStorage(NPC_GORKUN_IRONSKULL))
						DoScriptText(MARTIN_AND_GONROK_3, pGorkun);
					else
						if (Creature* pMartin = m_pInstance->GetSingleCreatureFromStorage(NPC_MARITN_VICTUS))
							DoScriptText(MARTIN_AND_GONROK_3, pMartin);

					if (Creature* pSindragosa = m_pInstance->GetSingleCreatureFromStorage(NPC_SINDRAGOSA))
						pSindragosa->GetMotionMaster()->MovePoint(1, 980.057434f, 177.009705f, 673.349792f);
					m_uiUpdateTimer = 7000;
					m_pInstance->SetData(TYPE_EVENT, 118);
					break;
				case 118:
					if (m_pInstance->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
						DoScriptText(SL_LORE_SAY_4, m_creature);
					else DoScriptText(JA_A_SAY_4, m_creature);
					
					m_uiUpdateTimer = 1000;
					m_pInstance->SetData(TYPE_EVENT, 119);
					break;
				case 119:
					if (m_pInstance->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
						m_creature->CastSpell(m_creature, SPELL_SYLVANAS_SUMMON, true);
					else m_creature->CastSpell(m_creature, SPELL_JAINA_SUMMON, true);
					m_uiUpdateTimer = 2000;
					m_pInstance->SetData(TYPE_EVENT, 120);
					break;
				case 120:
					if (Creature* pSindragosa = m_pInstance->GetSingleCreatureFromStorage(NPC_SINDRAGOSA))
					{
						if (m_pInstance->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
						{
							if (Creature* pChampion = m_pInstance->GetSingleCreatureFromStorage(NPC_GORKUN_IRONSKULL))
								pSindragosa->CastSpell(pChampion, SPELL_FROST_BOMB, true);
						} else {
							if (Creature* pChampion = m_pInstance->GetSingleCreatureFromStorage(NPC_MARITN_VICTUS))
								pSindragosa->CastSpell(pChampion, SPELL_FROST_BOMB, true);
						}
					}
					m_uiUpdateTimer = 2000;
					m_pInstance->SetData(TYPE_EVENT, 121);
					break;
				case 121:
						if (m_pInstance->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
						{
							if (Creature* pChampion = m_pInstance->GetSingleCreatureFromStorage(NPC_GORKUN_IRONSKULL))
							{
								pChampion->SetRespawnDelay(DAY);
								pChampion->DealDamage(pChampion, pChampion->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
							}
						} else {
							if (Creature* pChampion = m_pInstance->GetSingleCreatureFromStorage(NPC_MARITN_VICTUS))
							{
								pChampion->SetRespawnDelay(DAY);
								pChampion->DealDamage(pChampion, pChampion->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
							}
						}
					m_uiUpdateTimer = 7000;
					m_pInstance->SetData(TYPE_EVENT, 122);
					break;
				case 122:
					if (Creature* pSindragosa = m_pInstance->GetSingleCreatureFromStorage(NPC_SINDRAGOSA))
						pSindragosa->GetMotionMaster()->MovePoint(2, 735.664734f, 329.785889f, 629.761902f);
					m_uiUpdateTimer = 10000;
					m_pInstance->SetData(TYPE_EVENT, 123);
					break;
				case 123:
					m_creature->SetSpeedRate(MOVE_RUN, 0.4f);
					m_creature->GetMotionMaster()->Clear();
					m_creature->GetMotionMaster()->MovePoint(0, 1059.242065f, 123.729301f, 628.156189f); 
					m_uiUpdateTimer = 7000;
					m_pInstance->SetData(TYPE_EVENT, 124);
					break;
				case 124:
					if (m_pInstance->GetData(DATA_TEAM_IN_INSTANCE) == HORDE)
					{
						DoScriptText(SL_LORE_SAY_5, m_creature);
						m_creature->SetActiveObjectState(false);
						m_pInstance->SetData(TYPE_EVENT, 0);
					} else {
						DoScriptText(JA_A_SAY_5, m_creature);
						m_uiUpdateTimer = 4000;
						m_pInstance->SetData(TYPE_EVENT, 125);	
					}
					break;
				case 125:
					m_creature->GetMotionMaster()->MovePoint(1, 1053.641846f, 139.921280f, 628.156189f); 
					m_uiUpdateTimer = 6000;
					m_pInstance->SetData(TYPE_EVENT, 126);	
					break;
				case 126:
					DoScriptText(JA_A_SAY_6, m_creature);
					m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
					m_creature->SetActiveObjectState(false);
					m_pInstance->SetData(TYPE_EVENT, 0);
					break;
				default:
					break;
				}
			} else m_uiUpdateTimer -= uiDiff;
			m_pInstance->SetData(TYPE_EVENT_TIMER, m_uiUpdateTimer);
		}
   }

};

CreatureAI* GetAI_npc_jaina_or_sylvanas_POSintro(Creature* pCreature)
{
    return new npc_jaina_or_sylvanas_POSintroAI(pCreature);
}

CreatureAI* GetAI_npc_jaina_or_sylvanas_POSoutro(Creature* pCreature)
{
    return new npc_jaina_or_sylvanas_POSoutroAI(pCreature);
}

void AddSC_pit_of_saron()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="npc_jaina_or_sylvanas_POSintro";
    newscript->GetAI = &GetAI_npc_jaina_or_sylvanas_POSintro;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="npc_jaina_or_sylvanas_POSoutro";
    newscript->GetAI = &GetAI_npc_jaina_or_sylvanas_POSoutro;
    newscript->RegisterSelf();
}
