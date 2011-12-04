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
SDName: Grizzly_Hills
SD%Complete:
SDComment: Quest support: 12138, 12198
SDCategory: Grizzly Hills
EndScriptData */

/* ContentData
npc_depleted_war_golem
EndContentData */

#include "precompiled.h"
#include "pet_ai.h"

/*######
## npc_depleted_war_golem
######*/

enum
{
    SAY_GOLEM_CHARGE            = -1000626,
    SAY_GOLEM_COMPLETE          = -1000627,

    NPC_LIGHTNING_SENTRY        = 26407,

    SPELL_CHARGE_GOLEM          = 47799,
    SPELL_GOLEM_CHARGE_CREDIT   = 47797,
};

struct MANGOS_DLL_DECL npc_depleted_war_golemAI : public ScriptedPetAI
{
    npc_depleted_war_golemAI(Creature* pCreature) : ScriptedPetAI(pCreature) { Reset(); }

    void Reset() { }

    void OwnerKilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetEntry() == NPC_LIGHTNING_SENTRY)
        {
            // Is distance expected?
            if (m_creature->IsWithinDistInMap(pVictim, 10.0f))
                m_creature->CastSpell(m_creature, SPELL_CHARGE_GOLEM, true);
        }
    }
};

CreatureAI* GetAI_npc_depleted_war_golem(Creature* pCreature)
{
    return new npc_depleted_war_golemAI(pCreature);
}

bool EffectAuraDummy_npc_depleted_war_golem(const Aura* pAura, bool bApply)
{
    if (pAura->GetId() != SPELL_CHARGE_GOLEM)
        return true;

    Creature* pCreature = (Creature*)pAura->GetTarget();

    if (!pCreature)
        return true;

    if (pAura->GetEffIndex() == EFFECT_INDEX_0)
    {
        if (bApply)
        {
            DoScriptText(SAY_GOLEM_CHARGE, pCreature);
            pCreature->addUnitState(UNIT_STAT_STUNNED);
        }
        else
        {
            DoScriptText(SAY_GOLEM_COMPLETE, pCreature);
            pCreature->clearUnitState(UNIT_STAT_STUNNED);

            // targets master
            pCreature->CastSpell(pCreature, SPELL_GOLEM_CHARGE_CREDIT, true);
        }
    }

    return true;
}

struct MANGOS_DLL_DECL npc_lake_frong_qAI : public ScriptedAI
{
    npc_lake_frong_qAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	bool transform;
	ObjectGuid CreatureGUID;
	ObjectGuid m_pPlayerGUID;

    void Reset() 
	{
		CreatureGUID.Clear();
		m_pPlayerGUID.Clear();
		transform = false;
	}

    void ReceiveEmote(Player* pPlayer, uint32 uiEmote)
    {
		if (uiEmote == TEXTEMOTE_KISS)
		{
			if (!pPlayer->HasAura(62581) && pPlayer->HasAura(62574))
			{
				DoCast(m_creature, 62537);
				pPlayer->RemoveAurasDueToSpell(62574);
				m_creature->GetMotionMaster()->MoveFollow(pPlayer, PET_FOLLOW_DIST, pPlayer->GetAngle(m_creature));
				if (m_creature->GetEntry() == 33224)
				{
					m_pPlayerGUID = pPlayer->GetObjectGuid();
					CreatureGUID = m_creature->GetObjectGuid();
					transform = true;
					DoScriptText(-1800007, m_creature);
					m_creature->GetMotionMaster()->Clear();
				}
			}
			else DoCast(pPlayer, 62581);
		}
	}

	void UpdateAI(const uint32 uiDiff)
	{
		if (Unit* pPlayer = m_creature->GetMap()->GetPlayer(m_pPlayerGUID))
		{
			if (transform && CreatureGUID && m_creature->GetDistance2d(pPlayer) <= 5.0f)
			{
				if (Creature* pTemp = m_creature->GetMap()->GetCreature(CreatureGUID))
				{
					DoCast(pTemp, 62550);
					pTemp->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
					pTemp->RemoveAurasDueToSpell(62537);
					Reset();
				}
			}
		}
		if (!m_creature->HasAura(62537))
			m_creature->GetMotionMaster()->Clear();
	}
};

CreatureAI* GetAI_npc_lake_frong_q(Creature* pCreature)
{
    return new npc_lake_frong_qAI(pCreature);
}

bool GossipHello_npc_lake_frong_q(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetItemCount(44981, false) < 1)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3608002, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_lake_frong_q(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
		pCreature->CastSpell(pPlayer, 62554, true);
		DoScriptText(-1800008, pCreature);
		pCreature->ForcedDespawn(15000);
    }
	pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

enum eSmokeEmOut
{
    SAY_SEO1                                     = -1603535,
    SAY_SEO2                                     = -1603536,
    SAY_SEO3                                     = -1603537,
    SAY_SEO4                                     = -1603538,
    SAY_SEO5                                     = -1603539,
    QUEST_SMOKE_EM_OUT_A                         = 12323,
    QUEST_SMOKE_EM_OUT_H                         = 12324,
    SPELL_SMOKE_BOMB                             = 49075,
    NPC_VENTURE_CO_STABLES_KC                    = 27568,
};

struct MANGOS_DLL_DECL npc_venture_co_stragglerAI : public ScriptedAI
{
    npc_venture_co_stragglerAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

	ObjectGuid uiPlayerGUID;
    uint32 uiRunAwayTimer;
	uint32 uiTimer;

	void Reset()
	{
		uiPlayerGUID.Clear();
		uiTimer = 0;
		m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_OOC_NOT_ATTACKABLE);
	}

	void UpdateAI(const uint32 uiDiff)
	{
		if (uiRunAwayTimer <= uiDiff)
		{
			if (Player* player = m_creature->GetMap()->GetPlayer(uiPlayerGUID))
			{
				switch (uiTimer)
				{
				case 0:
					if (player->GetQuestStatus(QUEST_SMOKE_EM_OUT_A) == QUEST_STATUS_INCOMPLETE ||
						player->GetQuestStatus(QUEST_SMOKE_EM_OUT_H) == QUEST_STATUS_INCOMPLETE)
						player->KilledMonsterCredit(NPC_VENTURE_CO_STABLES_KC);
					m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX()-7, m_creature->GetPositionY()+7, m_creature->GetPositionZ());
					uiRunAwayTimer = 2500;
					++uiTimer;
					break;
				case 1:
					switch (urand(0, 4))
					{
					case 0:
						DoScriptText(SAY_SEO1, m_creature);
						break;
					case 1:
						DoScriptText(SAY_SEO2, m_creature);
						break;
					case 2:
						DoScriptText(SAY_SEO3, m_creature);
						break;
					case 3:
						DoScriptText(SAY_SEO4, m_creature);
						break;
					case 4:
						DoScriptText(SAY_SEO5, m_creature);
						break;
					default:
						break;
					}
					m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX()-7, m_creature->GetPositionY()-5, m_creature->GetPositionZ());
					uiRunAwayTimer = 2500;
					++uiTimer;
					break;
				case 2:
					m_creature->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX()-5, m_creature->GetPositionY()-5, m_creature->GetPositionZ());
					uiRunAwayTimer = 2500;
					++uiTimer;
					break;
				case 3:
					m_creature->DealDamage(m_creature, m_creature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
					uiTimer = 0;
					break;
				default:
					break;
				}
			}
		}
		else
			uiRunAwayTimer -= uiDiff;

		DoMeleeAttackIfReady();
	}

	void SpellHit(Unit* pCaster, const SpellEntry *pSpell)
	{
		if (pCaster && pCaster->GetTypeId() == TYPEID_PLAYER && pSpell->Id == SPELL_SMOKE_BOMB)
		{
			m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_OOC_NOT_ATTACKABLE);
			m_creature->CombatStop(false);
			uiPlayerGUID = pCaster->GetObjectGuid();
			uiRunAwayTimer = 3500;
		}
	}
};

CreatureAI* GetAI_npc_venture_co_straggler(Creature* pCreature)
{
    return new npc_venture_co_stragglerAI(pCreature);
}

void AddSC_grizzly_hills()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_depleted_war_golem";
    pNewScript->GetAI = &GetAI_npc_depleted_war_golem;
    pNewScript->pEffectAuraDummy = &EffectAuraDummy_npc_depleted_war_golem;
    pNewScript->RegisterSelf();

	pNewScript = new Script;
    pNewScript->Name = "npc_lake_frong_q";
	pNewScript->GetAI = &GetAI_npc_lake_frong_q;
	pNewScript->pGossipHello = &GossipHello_npc_lake_frong_q;
    pNewScript->pGossipSelect = &GossipSelect_npc_lake_frong_q;
    pNewScript->RegisterSelf();

	pNewScript = new Script;
    pNewScript->Name = "npc_venture_co_straggler";
	pNewScript->GetAI = &GetAI_npc_venture_co_straggler;
    pNewScript->RegisterSelf();
}
