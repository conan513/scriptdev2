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
SDName: Boss_Sjonnir
SD%Complete:
SDComment:
SDCategory: Halls of Stone
EndScriptData */

#include "precompiled.h"
#include "halls_of_stone.h"

enum
{
    SAY_AGGRO                   = -1599000,
    SAY_SLAY_1                  = -1599001,
    SAY_SLAY_2                  = -1599002,
    SAY_SLAY_3                  = -1599003,
    SAY_DEATH                   = -1599004,
    EMOTE_GENERIC_FRENZY        = -1000002,

    SAY_BRANN_IRON_SPAWN        = -1599069,
    SAY_BRANN_TROGG_SPAWN       = -1599070,
    SAY_BRANN_OOZE_SPAWN        = -1599071,

    SAY_BRANN_END_1             = -1599062,
    SAY_BRANN_END_2             = -1599063,

    SPELL_CHAIN_LIGHTING        = 50830,
    SPELL_CHAIN_LIGHTING_H      = 59844,
    SPELL_FRENZY                = 28747,
    SPELL_LIGHTING_SHIELD       = 50831,
    SPELL_LIGHTING_SHIELD_H     = 59845,
    SPELL_STATIC_CHARGE         = 50834, //Periodic Trigger 2s interval, spell =50835
    SPELL_STATIC_CHARGE_H       = 59846, //Periodic Trigger 2s interval, spell =50847

    SPELL_LIGHTING_RING         = 51849,
    SPELL_LIGHTING_RING_H       = 59861,
    SPELL_LIGHTING_RING1        = 50840,
    SPELL_LIGHTING_RING1_H      = 59848,

    NPC_FORGED_IRON_TROGG       = 27979,
    NPC_FORGED_IRON_DWARF       = 27982,

    ACHIEV_COMPLETE             = 485,
    ACHIEV_COMPLETE_H           = 496,

    NPC_DAILY_DUNGEON           = 22852,
};

struct Locations
{
    float x, y, z;
    uint32 id;
};

static Locations PipeLoc[]=
{
    {1295.44f, 734.07f, 200.3f}, // left
    {1297.7f,  595.6f,  199.9f}, // right
};

/*######
## brann_event
######*/

struct MANGOS_DLL_DECL brann_outroAI : public ScriptedAI
{
    brann_outroAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiStep;
    uint32 m_uiPhase_timer;

    bool m_bIsOutro;

    void Reset()
    {
        m_bIsOutro        = true;
        m_uiPhase_timer   = 2000;
        m_uiStep          = 1;

        m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
    }

    void JumpToNextStep(uint32 uiTimer)
    {
        m_uiPhase_timer = uiTimer;
        m_uiStep++;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bIsOutro)
        {
            if (m_uiPhase_timer <= uiDiff)
            {
                switch (m_uiStep)
                {
                    case 1:
                        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                        JumpToNextStep(11000);
                        break;
                    case 2:
                        m_creature->GetMotionMaster()->MovePoint(0, 1304.535f, 666.84f, 189.607f);
                        DoScriptText(SAY_BRANN_END_1, m_creature);
                        JumpToNextStep(13000);
                        break;
                    case 3:
                        DoScriptText(SAY_BRANN_END_2, m_creature);
                        JumpToNextStep(10000);
                        break;
                    case 4:
                        m_creature->SummonCreature(NPC_BRANN, 1304.535f, 666.84f, 189.607f, 3.16f, TEMPSUMMON_MANUAL_DESPAWN, 30000);
                        m_creature->ForcedDespawn();

                        if (Creature* pBrann = m_pInstance->GetSingleCreatureFromStorage(NPC_BRANN))
                        {
                            pBrann->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            pBrann->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        }
                        break;
                    case 5:
                        break;
                }
            }
            else m_uiPhase_timer -= uiDiff;
        }
    }
};

/*######
## boss_sjonnir
######*/

struct MANGOS_DLL_DECL boss_sjonnirAI : public ScriptedAI
{
    boss_sjonnirAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsFrenzy;

    uint32 m_uiStep;
    uint32 m_uiPhase_timer;

    bool m_bBrannBattle;

    std::list<uint64> m_lDwarfGUIDList;
    uint32 m_uiChainLightning_Timer;
    uint32 m_uiLightningShield_Timer;
    uint32 m_uiStaticCharge_Timer;
    uint32 m_uiLightningRing_Timer;
    uint32 m_uiSummon_Timer;
    uint32 m_uiFrenzy_Timer;

    void Reset()
    {
        m_bIsFrenzy = false;
        m_bBrannBattle = true;

        m_uiChainLightning_Timer = 3000 + rand()%5000;
        m_uiLightningShield_Timer = 20000 + rand()%5000;
        m_uiStaticCharge_Timer = 20000 + rand()%5000;
        m_uiLightningRing_Timer = 30000 + rand()%5000;
        m_uiSummon_Timer = 12000;
        m_uiFrenzy_Timer = 300000;

        m_uiPhase_timer   = 2000;
        m_uiStep          = 1;

        DespawnDwarf();

        if (Creature* pBrann = m_pInstance->GetSingleCreatureFromStorage(NPC_BRANN_EVENT))
            pBrann->HandleEmote(EMOTE_STATE_READYUNARMED);
    }

    void JumpToNextStep(uint32 uiTimer)
    {
        m_uiPhase_timer = uiTimer;
        m_uiStep++;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (Creature* pBrann = m_pInstance->GetSingleCreatureFromStorage(NPC_BRANN_EVENT))
        {
            pBrann->SetWalk(false);
            pBrann->GetMotionMaster()->MovePoint(0, 1307.582f, 666.809f, 189.607f);
            pBrann->SetStandState(UNIT_STAND_STATE_KNEEL);
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(rand()%3)
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        m_creature->SummonCreature(NPC_DAILY_DUNGEON, 1310.10f, 649.66f, 189.60f, 2.49f, TEMPSUMMON_MANUAL_DESPAWN, 5000);

        DoScriptText(SAY_DEATH, m_creature);

        m_pInstance->DoCompleteAchievement(m_bIsRegularMode ? ACHIEV_COMPLETE : ACHIEV_COMPLETE_H);

        m_creature->SummonCreature(NPC_BRANN_OUTRO, 1307.582f, 666.809f, 189.607f, 6.28f, TEMPSUMMON_MANUAL_DESPAWN, 30000);

        if (Creature* pBrann = m_pInstance->GetSingleCreatureFromStorage(NPC_BRANN_EVENT))
            pBrann->ForcedDespawn();
    }

    void DespawnDwarf()
    {
        if (m_lDwarfGUIDList.empty())
            return;

        for(std::list<uint64>::iterator itr = m_lDwarfGUIDList.begin(); itr != m_lDwarfGUIDList.end(); ++itr)
        {
            if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
            {
                if (pTemp->isAlive())
                    pTemp->ForcedDespawn();
            }
        }

        m_lDwarfGUIDList.clear();
    }

    void JustSummoned(Creature* pSummoned)
    {
        m_lDwarfGUIDList.push_back(pSummoned->GetGUID());

        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
        {
            pSummoned->AddThreat(pTarget, 0.0f);
            pSummoned->AI()->AttackStart(pTarget);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiChainLightning_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(pTarget, m_bIsRegularMode ? SPELL_CHAIN_LIGHTING_H : SPELL_CHAIN_LIGHTING);
            m_uiChainLightning_Timer = 10000 + rand()%5000;
        }
        else
            m_uiChainLightning_Timer -= uiDiff;

        if (m_uiLightningShield_Timer < uiDiff)
        {
            DoCast(m_creature, m_bIsRegularMode ? SPELL_LIGHTING_SHIELD_H : SPELL_LIGHTING_SHIELD);
            m_uiLightningShield_Timer = 20000 + rand()%5000;
        }
        else
            m_uiLightningShield_Timer -= uiDiff;

        if (m_uiStaticCharge_Timer < uiDiff)
        {
            DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_STATIC_CHARGE_H : SPELL_STATIC_CHARGE);
            m_uiStaticCharge_Timer = 20000 + rand()%5000;
        }
        else
            m_uiStaticCharge_Timer -= uiDiff;

        if (m_uiLightningRing_Timer < uiDiff)
        {
            if (m_creature->IsNonMeleeSpellCasted(false))
                m_creature->InterruptNonMeleeSpells(false);
            DoCast(m_creature, m_bIsRegularMode ? SPELL_LIGHTING_RING_H : SPELL_LIGHTING_RING);
            m_uiLightningRing_Timer = 30000 + rand()%5000;
        }
        else
            m_uiLightningRing_Timer -= uiDiff;

        if (m_uiSummon_Timer < uiDiff)
        {
            uint32 SummonPipe = rand()%2;
            uint32 SummonEntry = 0;
            switch(rand()%3)
            {
                case 0: SummonEntry = NPC_FORGED_IRON_TROGG; 
                    break;
                case 1: SummonEntry = NPC_MALFORMED_OOZE;    
                    break;
                case 2: SummonEntry = NPC_FORGED_IRON_DWARF; 
                    break;
            }
            m_creature->SummonCreature(SummonEntry, PipeLoc[SummonPipe].x, PipeLoc[SummonPipe].y, PipeLoc[SummonPipe].z, 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
            m_uiSummon_Timer = 20000;
        }
        else
            m_uiSummon_Timer -= uiDiff;

        if (!m_bIsFrenzy && m_uiFrenzy_Timer < uiDiff)
        {
            DoCast(m_creature, SPELL_FRENZY);
            m_bIsFrenzy = true;
            m_uiFrenzy_Timer = 0;
        }
        else
            m_uiFrenzy_Timer -= uiDiff;

        if (m_bBrannBattle)
        {
            if (m_uiPhase_timer <= uiDiff)
            {
                switch (m_uiStep)
                {
                    case 1:
                        JumpToNextStep(8000);
                        break;
                    case 2:
                        if (m_pInstance)
                            m_pInstance->DoUseDoorOrButton(GO_SJONNIR_CONSOLE);

                        if (Creature* pBrann = m_pInstance->GetSingleCreatureFromStorage(NPC_BRANN_EVENT))
                        {
                            DoScriptText(SAY_BRANN_IRON_SPAWN, pBrann);
                        }
                        JumpToNextStep(10000);
                        break;
                    case 3:
                        if (Creature* pBrann = m_pInstance->GetSingleCreatureFromStorage(NPC_BRANN_EVENT))
                        {
                            DoScriptText(SAY_BRANN_TROGG_SPAWN, pBrann);
                        }
                        JumpToNextStep(9000);
                        break;
                    case 4:
                        if (Creature* pBrann = m_pInstance->GetSingleCreatureFromStorage(NPC_BRANN_EVENT))
                        {
                            DoScriptText(SAY_BRANN_OOZE_SPAWN, pBrann);
                        }
                        JumpToNextStep(1000);
                        break;
                    case 5:
                        break;
                }
            }
            else m_uiPhase_timer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_brann_outro(Creature* pCreature)
{
    return new brann_outroAI(pCreature);
}

CreatureAI* GetAI_boss_sjonnir(Creature* pCreature)
{
    return new boss_sjonnirAI(pCreature);
}

void AddSC_boss_sjonnir()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "brann_outro";
    newscript->GetAI = &GetAI_brann_outro;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_sjonnir";
    newscript->GetAI = &GetAI_boss_sjonnir;
    newscript->RegisterSelf();
}
