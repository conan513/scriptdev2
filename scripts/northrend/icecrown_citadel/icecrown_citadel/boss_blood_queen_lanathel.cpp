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
SDName: boss_blood_queen_lanathel
SD%Complete: 90%
SDComment:
SDCategory: Icecrown Citadel
EndScriptData */
// Need to implement MC & Pact of darkfallen
#include "precompiled.h"
#include "icecrown_citadel.h"

enum BossSpells
{
    SPELL_BERSERK                           = 47008,
    SPELL_INCITE_TERROR                     = 73070,
    SPELL_SHROUD_OF_SORROW                  = 72981,
    SPELL_DELIRIOUS_SLASH                   = 72261,
    SPELL_BLOOD_MIRROR_TANK                 = 70821,
    SPELL_BLOOD_MIRROR_OFF                  = 70838,
    SPELL_VAMPIRIC_BITE                     = 71726,
    SPELL_ESSENCE_OF_BLOOD_QUEEN            = 70867,
    SPELL_ESSENCE_OF_BLOOD_QUEEN_2          = 70871,
    SPELL_FRENZIED_BLOODTHIRST              = 70877,
    SPELL_UNCONTROLLABLE_FRENZY             = 70923,
    SPELL_PACT_OF_DARKFALLEN                = 71340,
    SPELL_SWARMING_SHADOWS                  = 71264,
    SPELL_TWILIGHT_BLOODBOLT                = 72313,
    SPELL_BLOODBOLT_WHIRL                   = 71772,
    SPELL_PRESENCE_OF_DARKFALLEN            = 71952,

    NPC_SWARMING_SHADOWS                    = 38163,
    SPELL_SWARMING_SHADOWS_VISUAL           = 71267,
    THIRST_QUENCHED_AURA                    = 72154,
};

// talks
enum
{
    SAY_AGGRO                   = -1631321,
    SAY_BITE_1                  = -1631322,
    SAY_BITE_2                  = -1631323,
    SAY_PACT                    = -1631324,
    SAY_GROUND_PHASE            = -1631325,
    SAY_SHADOWS                 = -1631326,
    SAY_AIR_PHASE               = -1631327,
    SAY_MC                      = -1631329,
    SAY_RESET                   = -1631328,
    SAY_PLAYER_KILLED_1			= -1631330,
    SAY_PLAYER_KILLED_2			= -1631331,
    SAY_BERSERK                 = -1631332,
    SAY_DEATH                   = -1631333,
};

static Locations SpawnLoc[]=
{
    {4595.640137f, 2769.195557f, 400.137054f},  // 0 Phased
    {4595.904785f, 2769.315918f, 421.838623f},  // 1 Fly
};


struct MANGOS_DLL_DECL boss_blood_queen_lanathelAI : public BSWScriptedAI
{
    boss_blood_queen_lanathelAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);
        Reset();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;
    ObjectGuid HasPlayerItem;
    uint32 m_uiShadows;
    int32 m_uiStep;
    uint32 m_uiEventTimer;
    uint32 m_uiNextPoint;
    uint32 m_uiSummonTimer;
    uint32 m_uiBiteTimer;
    uint32 m_uiDeliriousSlashTimer;
    uint32 m_uiPactTimer;
    uint32 m_uiShadowsTimer;
    uint32 m_uiTwilightTimer;
    uint32 m_uiBloodboltWhirlTimer;
    uint32 m_uiFlyTimer;
    uint32 m_uiEnrageTimer;
    uint32 m_uiQuestTimer;
    uint32 m_uiCountItem;
	uint32 m_uiQuestTimer1;
    bool m_bMovementStarted;
    bool m_bIsHeroic;
    bool m_bIs25Man;
    bool m_bBite;
    bool m_bEnrage;
    bool m_bCastShadows;
	bool m_bQuestCheck;
	bool m_uiQuest;

    void Reset()
    {
        if(!m_pInstance)
            return;

        if (m_creature->isAlive())
            m_pInstance->SetData(TYPE_LANATHEL, NOT_STARTED);

                HasPlayerItem.Clear();
        m_bBite = false;
        m_bEnrage = false;
        m_bCastShadows = true;
        m_bQuestCheck = true;
		m_uiQuest = true;
        m_uiShadows = 0;
        m_uiStep = 0;
        m_uiEventTimer = 0;
        m_uiBiteTimer = 15000;
        m_uiPactTimer = 15000;
        m_uiShadowsTimer = 30000;
        m_uiSummonTimer = 0;
        m_uiCountItem = 0;
        m_uiTwilightTimer = urand(12000, 17000);
        m_uiDeliriousSlashTimer = urand(15000, 20000);
        m_uiFlyTimer = 2 * MINUTE * IN_MILLISECONDS;
        m_uiEnrageTimer = 5.5 * MINUTE * IN_MILLISECONDS; //5:30 min
        m_uiQuestTimer = 6 * MINUTE * IN_MILLISECONDS;
		m_uiQuestTimer1 = 1800000;

        m_bMovementStarted = false;
        m_creature->SetWalk(false);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);

        DoRemoveFromAll(SPELL_ESSENCE_OF_BLOOD_QUEEN);
        DoRemoveFromAll(SPELL_ESSENCE_OF_BLOOD_QUEEN_2);
        DoRemoveFromAll(SPELL_FRENZIED_BLOODTHIRST);
        DoRemoveFromAll(SPELL_PACT_OF_DARKFALLEN);
        DoRemoveFromAll(SPELL_BLOOD_MIRROR_TANK);
        DoRemoveFromAll(SPELL_BLOOD_MIRROR_OFF);
    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiStep;
        m_uiEventTimer = uiTime;
    }

    void DoRemoveFromAll(uint32 spell)
    {
        Map* pMap = m_creature->GetMap();
        Map::PlayerList const& pPlayers = pMap->GetPlayers();
        if (!pPlayers.isEmpty())
        {
            for (Map::PlayerList::const_iterator itr = pPlayers.begin(); itr != pPlayers.end(); ++itr)
            {
                Unit *pTarget = itr->getSource();
                if (pTarget->HasAura(spell))
                    m_creature->RemoveAurasDueToSpell(spell);
            }
        }
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_LANATHEL, FAIL);

		DoScriptText(SAY_RESET, m_creature);

		if (Creature* pCreature = GetClosestCreatureWithEntry(m_creature, 38558, 60.0f))
			if (pCreature->isAlive())
				pCreature->DealDamage(pCreature, pCreature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
    }

    // Hacky way
    void DoSummonShadows(Unit *pTarget)
    {
        float x,y,z;
        pTarget->GetPosition(x,y,z);
        m_creature->SummonCreature(NPC_SWARMING_SHADOWS, x, y, z, 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0);
        --m_uiShadows;
        if (m_uiShadows <= 0)
        {
            m_uiShadowsTimer = 20000;
            m_bCastShadows = true;
        }
        if (m_uiShadows > 0)
            m_uiSummonTimer = 500;
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim && pVictim->HasAura(SPELL_BLOOD_MIRROR_OFF))
           pVictim->RemoveAurasDueToSpell(SPELL_BLOOD_MIRROR_OFF);

        if (pVictim && pVictim->HasAura(SPELL_BLOOD_MIRROR_TANK))
           pVictim->RemoveAurasDueToSpell(SPELL_BLOOD_MIRROR_TANK);

                switch (urand(0,1))
        {
            case 0:
               DoScriptText(SAY_PLAYER_KILLED_1, m_creature, pVictim);
               break;
            case 1:
               DoScriptText(SAY_PLAYER_KILLED_2, m_creature, pVictim);
               break;
        }
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE || !m_bMovementStarted)
            return;

        if (id == 0 || id == 1)
        {
            m_bMovementStarted = false;
            m_creature->GetMotionMaster()->MovementExpired();
        }
    }

    void StartMovement(uint32 id)
    {
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MovePoint(id, SpawnLoc[id].x, SpawnLoc[id].y, SpawnLoc[id].z);
        m_bMovementStarted = true;
    }

    enum Equipment
    {
        EQUIP_MAIN           = 29996,
        EQUIP_OFFHAND        = EQUIP_NO_CHANGE,
        EQUIP_RANGED         = EQUIP_NO_CHANGE,
        EQUIP_DONE           = EQUIP_NO_CHANGE,
    };

    void Aggro(Unit* pWho)
    {
        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_LANATHEL, IN_PROGRESS);

        m_creature->CastSpell(m_creature, SPELL_SHROUD_OF_SORROW, true);
        SetEquipmentSlots(false, EQUIP_MAIN, EQUIP_OFFHAND, EQUIP_RANGED);

        DoScriptText(SAY_AGGRO, m_creature, pWho);

        /*if (Unit* pTarget = doSelectRandomPlayer(SPELL_SHADOWS_EDGE, true, 100.0f))
            doAura(THIRST_QUENCHED_AURA,pTarget);*/

    }

    Unit* SelectRandomRangedTarget(Unit *pSource, uint8 maxTargets)
    {
        Unit *pResult = NULL;
        std::list<Unit*> lTargets;
        ThreatList const& tList = m_creature->getThreatManager().getThreatList();

        for (ThreatList::const_iterator i = tList.begin();i != tList.end(); ++i)
        {
            if (!(*i)->getUnitGuid().IsPlayer())
                continue;

            if (Unit* pTmp = m_creature->GetMap()->GetUnit((*i)->getUnitGuid()))
                lTargets.push_back(pTmp);
        }

        if (!lTargets.empty())
        {
            std::list<Unit*>::iterator iter;

            lTargets.sort(ObjectDistanceOrderReversed(pSource));
            iter = lTargets.begin();

            if (maxTargets >= lTargets.size())
                maxTargets = lTargets.size() - 1;

            std::advance(iter, urand(0, maxTargets));
            pResult = (*iter);
        }

        return pResult;
    }

    void JustDied(Unit *killer)
    {
        if(!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_LANATHEL, DONE);
        DoScriptText(SAY_DEATH, m_creature, killer);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);

        doRemoveFromAll(getSpellWithDifficulty(SPELL_ESSENCE_OF_BLOOD_QUEEN));
        doRemoveFromAll(SPELL_ESSENCE_OF_BLOOD_QUEEN_2);
        doRemoveFromAll(SPELL_FRENZIED_BLOODTHIRST);
        doRemoveFromAll(SPELL_PACT_OF_DARKFALLEN);
        doRemoveFromAll(SPELL_BLOOD_MIRROR_TANK);
        doRemoveFromAll(SPELL_BLOOD_MIRROR_OFF);

        if (m_bQuestCheck && m_bIs25Man)
        {
            Map* pMap = m_creature->GetMap();
            Map::PlayerList const& pPlayers = pMap->GetPlayers();
            if (!pPlayers.isEmpty())
            {
                for (Map::PlayerList::const_iterator itr = pPlayers.begin(); itr != pPlayers.end(); ++itr)
                {
                    if (Unit *pTarget = itr->getSource())
                    {
                        if (((Player*)pTarget)->HasItemCount(49888, 1) && pTarget->GetTypeId() == TYPEID_PLAYER)
                        {
                            ++m_uiCountItem;
                            HasPlayerItem = pTarget->GetObjectGuid();
                        }
                    }
                }
            }
            if (m_uiCountItem == 1)
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(HasPlayerItem))
                    if (pPlayer->GetQuestStatus(24756) == QUEST_STATUS_INCOMPLETE)
                        pPlayer->CompleteQuest(24756);
        }

		if (m_uiQuest)
        {
            if (Creature* pCreature = GetClosestCreatureWithEntry(m_creature, 38558, 60.0f))
                if (!pCreature->isAlive())
                    return;

             Map* pMap = m_creature->GetMap();
             Map::PlayerList const &PlayerList = pMap->GetPlayers();
             if (PlayerList.isEmpty())
                 return;

             for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                 if (Player* pPlayer = i->getSource())
                     if (pPlayer->isAlive() && pPlayer->GetQuestStatus(24874) == QUEST_STATUS_INCOMPLETE && (currentDifficulty == RAID_DIFFICULTY_10MAN_NORMAL || currentDifficulty == RAID_DIFFICULTY_10MAN_HEROIC))
                         pPlayer->KilledMonsterCredit(38558);
                     else if (pPlayer->isAlive() && pPlayer->GetQuestStatus(24879) == QUEST_STATUS_INCOMPLETE && (currentDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || currentDifficulty == RAID_DIFFICULTY_25MAN_HEROIC))
                         pPlayer->KilledMonsterCredit(39123);
        } else {
			if (Creature* pCreature = GetClosestCreatureWithEntry(m_creature, 38558, 60.0f))
				if (pCreature->isAlive())
					pCreature->DealDamage(pCreature, pCreature->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
		}
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (Unit *pTarget1 = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
        {
            if (Unit* pTarget2 = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 1))
            {
                if(pTarget1->HasAura(SPELL_BLOOD_MIRROR_OFF))
                    pTarget1->RemoveAurasDueToSpell(SPELL_BLOOD_MIRROR_OFF);

                if(pTarget2->HasAura(SPELL_BLOOD_MIRROR_TANK))
                    pTarget2->RemoveAurasDueToSpell(SPELL_BLOOD_MIRROR_TANK);

                if (!pTarget1->HasAura(SPELL_BLOOD_MIRROR_TANK))
                {
                    pTarget2->CastSpell(pTarget1, SPELL_BLOOD_MIRROR_TANK, true);
                }
                if (!pTarget2->HasAura(SPELL_BLOOD_MIRROR_OFF))
                {
                    pTarget1->CastSpell(pTarget2, SPELL_BLOOD_MIRROR_OFF, true);
                }
            }
        }

        if (m_uiQuestTimer >= uiDiff)
            m_uiQuestTimer -= uiDiff;
        else m_bQuestCheck = false;

		if (m_uiQuestTimer1 >= uiDiff)
			m_uiQuestTimer1 -= uiDiff;
		else m_uiQuest = false;

        if (m_uiEventTimer <= uiDiff)
        {
            switch (m_uiStep)
            {
            case 0:
                {
                    if (m_uiTwilightTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature, m_bIs25Man ? 2 : 1))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_TWILIGHT_BLOODBOLT) == CAST_OK)
                                m_uiTwilightTimer = urand(12000, 17000);
                        }
                    }
                    else m_uiTwilightTimer -= uiDiff;

                    if (m_uiDeliriousSlashTimer < uiDiff)
                    {
                        if (Unit* pTarget= m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,2))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_DELIRIOUS_SLASH) == CAST_OK)
                                m_uiDeliriousSlashTimer = urand(15000, 20000);
                        }
                    }
                    else m_uiDeliriousSlashTimer -= uiDiff;

                                        if (m_uiPactTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature , m_bIs25Man ? 3 : 2))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_PACT_OF_DARKFALLEN) == CAST_OK)
                            {
                                DoScriptText(SAY_PACT, m_creature);
                                m_uiPactTimer = 30000;
                            }
                        }
                    }
                                        else m_uiPactTimer -= uiDiff;

                    if (m_uiShadowsTimer < uiDiff)
                    {
                        if (Unit *pTarget = SelectRandomRangedTarget(m_creature , m_bIs25Man ? 2 : 1))
                        {
                            if (m_bCastShadows)
                            {
                                m_creature->CastSpell(pTarget, SPELL_SWARMING_SHADOWS, false);
                                m_uiShadows = 6;
                                DoScriptText(SAY_SHADOWS, m_creature);
                                m_uiSummonTimer = 1500;
                                m_bCastShadows = false;
                            }
                            if (!m_bCastShadows)
                            {
                                if (m_uiSummonTimer < uiDiff)
                                {
                                    DoSummonShadows(pTarget);
                                }
                                else m_uiSummonTimer-= uiDiff;
                            }
                        }
                    }
                    else m_uiShadowsTimer -= uiDiff;

                    if (m_uiBiteTimer < uiDiff && !m_bBite)
                    {
                        if (Unit* pTarget= m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO,2))
                        {
                            if (DoCastSpellIfCan(pTarget, SPELL_VAMPIRIC_BITE) == CAST_OK)
                            {
                                m_bBite = true;
                                                                switch (urand(0,1))
                                                                {
                                                                case 0:
                                                                        DoScriptText(SAY_BITE_1, m_creature);
                                                                        break;
                                                                case 1:
                                                                        DoScriptText(SAY_BITE_2, m_creature);
                                                                        break;
                                                                }
                            }
                        }
                    }
                    else m_uiBiteTimer -= uiDiff;

                    if (m_uiFlyTimer < uiDiff && m_creature->GetHealthPercent() >= 10)
                    {
                        NextStep();
                    }
                    else m_uiFlyTimer -= uiDiff;

                    DoMeleeAttackIfReady();
                    break;
                }
            case 1:             // Go in fly phase
                {
                    m_uiFlyTimer = 2 * MINUTE * IN_MILLISECONDS;
                    m_creature->SetWalk(true);
                    m_creature->AttackStop();
                    SetCombatMovement(false);
                    StartMovement(0);
                    NextStep(0);
                    break;
                }
            case 2:
                {
                    if (m_bMovementStarted)
                        return;
                    StartMovement(1);
                    m_creature->SetWalk(false);
                    m_creature->SetLevitate(true);
                    m_creature->CastSpell(m_creature, SPELL_INCITE_TERROR, true);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
                    DoScriptText(SAY_AIR_PHASE, m_creature);
                    NextStep(0);
                    break;
                }
            case 3:
                {
                    if (m_bMovementStarted)
                        return;

                    m_creature->CastSpell(m_creature, SPELL_BLOODBOLT_WHIRL, false);
                    NextStep(8000);
                    break;
                }
            case 4:             // Go in grownd phase
                {
                                        DoScriptText(SAY_GROUND_PHASE, m_creature);
                    StartMovement(0);
                    NextStep(0);
                    break;
                }
            case 5:
                {
                    if (m_bMovementStarted)
                        return;
                    m_creature->SetLevitate(false);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                    SetCombatMovement(true);
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    if (m_uiStep = -(1))
                    {
                        NextStep();
                    }
                    break;
                }
            default:
                break;
            }
        }
        else
            m_uiEventTimer -= uiDiff;

        if (m_uiEnrageTimer < uiDiff && !m_bEnrage)
        {
             m_creature->CastSpell(m_creature, SPELL_BERSERK, true);
             DoScriptText(SAY_BERSERK, m_creature);
             m_bEnrage = true;
        }
        else m_uiEnrageTimer -= uiDiff;
    }
};


CreatureAI* GetAI_boss_blood_queen_lanathel(Creature* pCreature)
{
    return new boss_blood_queen_lanathelAI(pCreature);
}

struct MANGOS_DLL_DECL mob_swarming_shadowsAI : public ScriptedAI
{
    mob_swarming_shadowsAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_m_pInstance;
    uint32 m_lifetimer;

    void Reset()
    {
        //m_creature->SetDisplayId(11686);
        //m_creature->SetRespawnDelay(7*DAY);
        SetCombatMovement(false);
        m_creature->SetInCombatWithZone();
        m_lifetimer = 30000;
        m_creature->CastSpell(m_creature, SPELL_SWARMING_SHADOWS_VISUAL, true);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->HasAura(SPELL_SWARMING_SHADOWS_VISUAL))
              m_creature->CastSpell(m_creature, SPELL_SWARMING_SHADOWS_VISUAL, true);

        if (m_lifetimer <= uiDiff)
            m_creature->ForcedDespawn();
        else m_lifetimer -= uiDiff;

    }
};

CreatureAI* GetAI_mob_swarming_shadows(Creature* pCreature)
{
     return new mob_swarming_shadowsAI (pCreature);
}


void AddSC_boss_blood_queen_lanathel()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_blood_queen_lanathel";
    newscript->GetAI = &GetAI_boss_blood_queen_lanathel;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_swarming_shadows";
    newscript->GetAI = &GetAI_mob_swarming_shadows;
    newscript->RegisterSelf();
}
