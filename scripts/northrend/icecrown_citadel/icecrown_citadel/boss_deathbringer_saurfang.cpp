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
SDName: boss_deathbringer_saurfang
SD%Complete: 99%
SDComment: by przemratajczak, alliance intro/outro and corrects by carlos93 & walkum
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

// talks
enum
{
    SAY_AGGRO                   = -1731028,
    SAY_FALLENCHAMPION          = -1731029,
    SAY_BLOODBEASTS             = -1731030,
    SAY_SLAY_1                  = -1731031,
    SAY_SLAY_2                  = -1731032,
    SAY_BERSERK                 = -1731033,
    SAY_DEATH                   = -1731034,
    SAY_INTRO_ALLY_0            = -1731035,
    SAY_INTRO_ALLY_1            = -1731036,
    SAY_INTRO_ALLY_2            = -1731037,
    SAY_INTRO_ALLY_3            = -1731038,
    SAY_INTRO_ALLY_4            = -1731039,
    SAY_INTRO_ALLY_5            = -1731040,
    SAY_INTRO_HORDE_1           = -1731041,
    SAY_INTRO_HORDE_2           = -1731042,
    SAY_INTRO_HORDE_3           = -1731043,
    SAY_INTRO_HORDE_4           = -1731044,
    SAY_INTRO_HORDE_5           = -1731045,
    SAY_INTRO_HORDE_6           = -1731046,
    SAY_INTRO_HORDE_7           = -1731047,
    SAY_INTRO_HORDE_8           = -1731048,
    SAY_INTRO_HORDE_9           = -1731049,
    SAY_OUTRO_ALLY_1            = -1731050,
    SAY_OUTRO_ALLY_2            = -1731051,
    SAY_OUTRO_ALLY_3            = -1731052,
    SAY_OUTRO_ALLY_4            = -1731053,
    SAY_OUTRO_ALLY_5            = -1731054,
    SAY_OUTRO_ALLY_6            = -1731055,
    SAY_OUTRO_ALLY_7            = -1731056,
    SAY_OUTRO_ALLY_8            = -1731057,
    SAY_OUTRO_ALLY_9            = -1731058,
    SAY_OUTRO_ALLY_10           = -1731059,
    SAY_OUTRO_ALLY_11           = -1731060,
    SAY_OUTRO_ALLY_12           = -1731061,
    SAY_OUTRO_ALLY_13           = -1731062,
    SAY_OUTRO_ALLY_14           = -1731063,
    SAY_OUTRO_ALLY_15           = -1731064,
    SAY_OUTRO_ALLY_16           = -1731065,
    SAY_OUTRO_HORDE_1           = -1731066,
    SAY_OUTRO_HORDE_2           = -1731067,
    SAY_OUTRO_HORDE_3           = -1731068,
    SAY_OUTRO_HORDE_4           = -1731069,
};

enum
{
        // Blood Power
        SPELL_BLOOD_POWER                       = 72371,
        SPELL_BLOOD_LINK_BEAST                  = 72176, // proc aura for Blood Beasts
        SPELL_BLOOD_LINK                        = 72202, // cast on Saurfang to give 1 Blood Power

        // Mark of the Fallen Champion
        SPELL_MARK_OF_FALLEN_CHAMPION           = 72256, // proc on melee hit, dmg to marked targets
        SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF    = 72293, // proc on death - heal Saurfang
        SPELL_REMOVE_MARKS                      = 72257,

        // Rune of Blood
        SPELL_RUNE_OF_BLOOD                     = 72408, // cast on self on aggro
        SPELL_RUNE_OF_BLOOD_DEBUFF              = 72410,

        // Blood Nova
        SPELL_BLOOD_NOVA_10                     = 72378,
        SPELL_BLOOD_NOVA_25                     = 73058,

        // Boiling Blood
        SPELL_BOILING_BLOOD_10                  = 72385,
        SPELL_BOILING_BLOOD_25                  = 72441,

        // Grip of Agony
        SPELL_GRIP_OF_AGONY                     = 70572,

        // Blood Beasts
        SPELL_CALL_BLOOD_BEAST_1                = 72172,
        SPELL_CALL_BLOOD_BEAST_2                = 72173,
        SPELL_CALL_BLOOD_BEAST_3                = 72356,
        SPELL_CALL_BLOOD_BEAST_4                = 72357,
        SPELL_CALL_BLOOD_BEAST_5                = 72358,

        SPELL_SCENT_OF_BLOOD                    = 72769,
        SPELL_SCENT_OF_BLOOD_TRIGGERED          = 72771, // doesn't trigger, so cast in script...
        SPELL_RESISTANT_SKIN                    = 72723,

        // enrage
        SPELL_BERSERK                           = 26662,
        SPELL_FRENZY                            = 72737,

        //summons
        NPC_BLOOD_BEAST                         = 38508,
};

enum Equipment
{
    EQUIP_MAIN           = 50798,
    EQUIP_OFFHAND        = EQUIP_NO_CHANGE,
    EQUIP_RANGED         = EQUIP_NO_CHANGE,
    EQUIP_DONE           = EQUIP_NO_CHANGE,
};

enum SaurfangEvent
{
    NPC_OVERLORD_SAURFANG       = 37187,
    NPC_KORKRON_REAVER          = 37920,

    NPC_MURADIN_BRONZEBEARD     = 37200,
    NPC_ALLIANCE_MASON          = 37190,

    NPC_JAINA                   = 37188,
    NPC_VARIAN                  = 37879,

    SPELL_VEHICLE_HARDCODED     = 46598, // Deathbringer enters Overlord
};

// positions
float fPositions[18][4] =
{
    {-468.05f, 2211.69f, 541.11f, 3.16f}, // Deathbringer teleport point
    {-491.30f, 2211.35f, 541.11f, 3.16f}, // Deathbringer dest point
    {-559.82f, 2211.29f, 539.30f, 6.28f}, // main npc summon/despawn point
    {-561.87f, 2215.94f, 539.30f, 6.28f}, // guard npc1 summon/despawn point
    {-560.17f, 2214.17f, 539.30f, 6.28f}, // guard npc2 summon/despawn point
    {-560.17f, 2207.71f, 539.30f, 6.28f}, // guard npc3 summon/despawn point
    {-561.87f, 2205.68f, 539.30f, 6.28f}, // guard npc4 summon/despawn point
    {-534.82f, 2211.29f, 539.30f, 6.28f}, // main npc first move
    {-536.87f, 2215.94f, 539.30f, 6.28f}, // guard npc1 first move
    {-535.17f, 2214.17f, 539.30f, 6.28f}, // guard npc2 first move
    {-535.17f, 2207.71f, 539.30f, 6.28f}, // guard npc3 first move
    {-536.87f, 2205.68f, 539.30f, 6.28f}, // guard npc4 first move
    {-539.53f, 2221.15f, 539.30f, 5.92f}, // Varian spawn
    {-540.92f, 2217.24f, 539.30f, 6.09f}, // Jaina spawn
    {-525.09f, 2211.31f, 539.28f, 3.13f}, // Muradin looks Overlord
    {-528.83f, 2211.31f, 539.28f, 3.13f}, // Muradin aproxime to Overlord
    {-536.65f, 2211.27f, 539.29f, 0.02f}, // Overlord aproxime to Muradin
    {-505.54f ,2211.20f, 539.28f, 6.25f}  // Other Muradin moves
};

// Event handler
struct MANGOS_DLL_DECL boss_deathbringer_saurfang_eventAI : public BSWScriptedAI
{
    boss_deathbringer_saurfang_eventAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_powerBloodPower = m_creature->getPowerType(); // don't call this function multiple times in script
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);

        m_uiEventStep = 0;
        m_uiNextEventTimer = 0;
        n = 8;
		m_uiMarkCastCount = 0;		

        m_bIsAlliance = true;

        m_bTeleported = false;
        m_bIsIntroStarted = false;
        m_bIsIntroFinished = false; // if true - boss is now ready to fight untill death - outro event
        m_bIsOutroStarted = false;

        m_guidNpc.Clear();
        m_guidVarian.Clear();
        m_guidJaina.Clear();
        m_guidOverlord.Clear();
        m_lGuards.clear();
    }

    ScriptedInstance *m_pInstance;

    uint32 m_uiNextEventTimer;
    uint32 m_uiEventStep;
    int8 n;
	uint32 m_uiMarkCastCount; // For achievement I've Gone and Made a Mess (4613 and 4537)

    bool m_bIsAlliance;
    bool m_bIs25Man;
    bool m_bTeleported;
    bool m_bIsIntroStarted;
    bool m_bIsIntroFinished;
    bool m_bIsOutroStarted;

    Difficulty m_uiMapDifficulty;

    ObjectGuid m_guidNpc;
    ObjectGuid m_guidVarian;
    ObjectGuid m_guidJaina;
    ObjectGuid m_guidOverlord;
    ObjectGuid m_guidKiller;
    GUIDList m_lGuards;

    Powers m_powerBloodPower;

    void Reset()
    {
        if (m_bIsAlliance)
        {
            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidVarian))
                pTmp->ForcedDespawn();

            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidJaina))
                pTmp->ForcedDespawn();
        }
        // Despawn MainNPC
        if (Creature *pTmp = GetMainNpc())
        {
            pTmp->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
            pTmp->ForcedDespawn();
            pTmp->GetMotionMaster()->Clear();
        }

        // Despawn guards
        for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
        {
            if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
            {
                pTmp->ForcedDespawn();
                pTmp->GetMotionMaster()->Clear();
            }
        }
        m_creature->GetMotionMaster()->Clear();
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        DoCastSpellIfCan(m_creature, SPELL_REMOVE_MARKS, CAST_TRIGGERED);
        DoRemoveFromAll(SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF);
        DoRemoveFromAll(SPELL_MARK_OF_FALLEN_CHAMPION);
        m_creature->SetPower(m_powerBloodPower, 0);

        m_uiEventStep = 0;
        m_uiNextEventTimer = 0;
		m_uiMarkCastCount = 0;
        n = 8;
        m_guidNpc.Clear();
        m_guidVarian.Clear();
        m_guidJaina.Clear();
        m_guidOverlord.Clear();
        m_lGuards.clear();

        m_bTeleported = false;
        m_bIsIntroStarted = false;
        m_bIsIntroFinished = false;
        m_bIsOutroStarted = false;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bTeleported && pWho->GetTypeId() == TYPEID_PLAYER && !((Player*)pWho)->isGameMaster())
        {
            // teleport behind door
            m_creature->NearTeleportTo(fPositions[0][0], fPositions[0][1], fPositions[0][2], fPositions[0][3]);
            m_bTeleported = true;
        }

        if (m_bTeleported && !m_bIsIntroStarted && pWho->GetTypeId() == TYPEID_PLAYER && !((Player*)pWho)->isGameMaster() && m_creature->GetDistance2d(pWho) < 50.0f)
        {
            if (((Player*)pWho)->GetTeam() == ALLIANCE)
                m_bIsAlliance = true;
            else
                m_bIsAlliance = false;
            //m_bIsAlliance = false;  //DEBUG ONLY
            DoSummonEventNpcs();
            m_bIsIntroStarted = true;
            NextStep(0);
        }
    }

    void DamageTaken(Unit *pDealer, uint32 &uiDamage)
    {
        if (m_bIsOutroStarted)
        {
            uiDamage = 0;
            return;
        }

        if (uiDamage >= m_creature->GetHealth())
        {
            m_bIsOutroStarted = true;
            uiDamage = 0;
            m_creature->RemoveAllAuras();
            m_guidKiller = pDealer->GetObjectGuid();
            DoFakeDeath();
            m_uiEventStep = 0;
        }
    }

    void DoSummonEventNpcs()
    {
        // main npc
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_MURADIN_BRONZEBEARD : NPC_OVERLORD_SAURFANG, fPositions[2][0], fPositions[2][1], fPositions[2][2], fPositions[2][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_guidNpc = pTmp->GetObjectGuid();
        // 4 adds
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_ALLIANCE_MASON : NPC_KORKRON_REAVER, fPositions[3][0], fPositions[3][1], fPositions[3][2], fPositions[3][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_lGuards.push_back(pTmp->GetObjectGuid());
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_ALLIANCE_MASON : NPC_KORKRON_REAVER, fPositions[4][0], fPositions[4][1], fPositions[4][2], fPositions[4][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_lGuards.push_back(pTmp->GetObjectGuid());
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_ALLIANCE_MASON : NPC_KORKRON_REAVER, fPositions[5][0], fPositions[5][1], fPositions[5][2], fPositions[5][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_lGuards.push_back(pTmp->GetObjectGuid());
        if (Creature *pTmp = m_creature->SummonCreature(m_bIsAlliance ? NPC_ALLIANCE_MASON : NPC_KORKRON_REAVER, fPositions[6][0], fPositions[6][1], fPositions[6][2], fPositions[6][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_lGuards.push_back(pTmp->GetObjectGuid());
    }

    void DoSummonVarianAndJaina()
    {
        if (Creature *pTmp = m_creature->SummonCreature(NPC_VARIAN, fPositions[12][0], fPositions[12][1], fPositions[12][2], fPositions[12][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_guidVarian = pTmp->GetObjectGuid();

        if (Creature *pTmp = m_creature->SummonCreature(NPC_JAINA, fPositions[13][0], fPositions[13][1], fPositions[13][2], fPositions[13][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_guidJaina = pTmp->GetObjectGuid();
    }

    void DoSummonHighOverlordSaurfang()
    {
        if (Creature *pTmp = m_creature->SummonCreature(NPC_OVERLORD_SAURFANG, fPositions[2][0], fPositions[2][1], fPositions[2][2], fPositions[2][3], TEMPSUMMON_MANUAL_DESPAWN, 0))
            m_guidOverlord = pTmp->GetObjectGuid();
    }

    Creature* GetMainNpc()
    {
        return m_creature->GetMap()->GetCreature(m_guidNpc);
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

    void DoFakeDeath()
    {
        m_creature->InterruptNonMeleeSpells(false);
        m_creature->SetHealth(1);
        m_creature->StopMoving();
        m_creature->ClearComboPointHolders();
        m_creature->RemoveAllAurasOnDeath();
        m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_20_PERCENT, false);
        m_creature->ModifyAuraState(AURA_STATE_HEALTHLESS_35_PERCENT, false);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->ClearAllReactives();
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MoveIdle();
        m_creature->SetStandState(UNIT_STAND_STATE_DEAD);

        // like in JustDied()
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAURFANG, DONE);

        DoScriptText(SAY_DEATH, m_creature);

        DoCastSpellIfCan(m_creature, SPELL_REMOVE_MARKS, CAST_TRIGGERED);
        DoRemoveFromAll(SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF);
        DoRemoveFromAll(SPELL_MARK_OF_FALLEN_CHAMPION);


    }

    void NextStep(uint32 uiTime = 1000)
    {
        ++m_uiEventStep;
        m_uiNextEventTimer = uiTime;
    }

    virtual void UpdateFightAI(const uint32 uiDiff) {}

    void UpdateAI(const uint32 uiDiff)
    {
        // INTRO
        if (m_bIsIntroStarted && !m_bIsIntroFinished)
        {
            if (m_bIsAlliance)
            {
                // **************
                // ALLIANCE INTRO
                // **************
                if (m_uiNextEventTimer <= uiDiff)
                {
                    switch (m_uiEventStep)
                    {
                        case 0:
                        {
                            break;
                        }
                        case 1:
                        {
                            m_creature->SetPower(m_powerBloodPower, 0);
                            m_pInstance->DoUseDoorOrButton(GO_SAURFANG_DOOR, 0, false);
                            m_creature->GetMotionMaster()->MovePoint(0, fPositions[1][0], fPositions[1][1], fPositions[1][2]);
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                                pTmp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pTmp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                            }
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                                    pTmp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    pTmp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                                }
                            }
                            NextStep(1000);
                            break;
                        }
                        case 2:
                        {
                            m_pInstance->DoUseDoorOrButton(GO_SAURFANG_DOOR, 0, true);
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_INTRO_ALLY_0, pTmp);
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[7][0], fPositions[7][1], fPositions[7][2]);
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                    pTmp->GetMotionMaster()->MovePoint(0, fPositions[n][0], fPositions[n][1], fPositions[n][2]);
                                ++n;
                            }
                            NextStep(3000);
                            break;
                        }
                        case 3:
                        {
                            m_creature->HandleEmote(EMOTE_STATE_TALK);
                            DoScriptText(SAY_INTRO_ALLY_1, m_creature);
                            NextStep(18000);
                            break;
                        }
                        case 4:
                        {
                            m_creature->HandleEmote(EMOTE_STATE_TALK);
                            DoScriptText(SAY_INTRO_ALLY_2, m_creature);
                            NextStep(11000);
                            break;
                        }
                        case 5:
                        {
                            m_creature->HandleEmote(EMOTE_STATE_NONE);
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_TALK);
                                DoScriptText(SAY_INTRO_ALLY_3, pTmp);
                            }
                            NextStep(6500);
                            break;
                        }
                        case 6:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_READY1H);
                                DoScriptText(SAY_INTRO_ALLY_4, pTmp);
                            }
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->HandleEmote(EMOTE_STATE_READY1H);
                                }
                            }
                            NextStep(2000);
                            break;
                        }
                        case 7:
                        {
                            float x, y, z;
                            m_creature->GetPosition(x, y, z);

                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->SetWalk(false);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->SetWalk(false);
                                    pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                                }
                            }
                            NextStep(3000);
                            break;
                        }
                        case 8:
                        {
                            float x, y, z;
                            // npcs float in air
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->SetWalk(true);
                                pTmp->SetSpeedRate(MOVE_WALK, 3.0f);
                                pTmp->GetPosition(x, y, z);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z + frand(5.0f, 7.0f));
                                pTmp->_AddAura(70572);
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->SetWalk(true);
                                    pTmp->SetSpeedRate(MOVE_WALK, 3.0f);
                                    pTmp->GetPosition(x, y, z);
                                    pTmp->GetMotionMaster()->MovePoint(0, x, y, z + frand(5.0f, 7.0f));
                                    pTmp->_AddAura(70572);
                                }
                            }
                            m_creature->HandleEmote(EMOTE_STATE_TALK);
                            DoScriptText(SAY_INTRO_ALLY_5, m_creature);
                            NextStep(7000);
                            break;
                        }
                        case 9:
                        {
                            m_bIsIntroFinished = true;

                            m_creature->HandleEmote(EMOTE_STATE_NONE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                            m_creature->SetInCombatWithZone();

                            NextStep();
                            break;
                        }
                        case 12:
                        {
                            // fight is in progress
                            break;
                        }
                        default:
                            break;
                    }
                }
                else
                    m_uiNextEventTimer -= uiDiff;
            }
            else
            {
                // ***********
                // HORDE INTRO
                // ***********
                if (m_uiNextEventTimer <= uiDiff)
                {
                    switch (m_uiEventStep)
                    {
                        case 0:
                        {
                            break;
                        }
                        case 1:
                        {
                            m_creature->SetPower(m_powerBloodPower, 0);
                            m_pInstance->DoUseDoorOrButton(GO_SAURFANG_DOOR, 0, false);
                            m_creature->GetMotionMaster()->MovePoint(0, fPositions[1][0], fPositions[1][1], fPositions[1][2]);
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                                pTmp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pTmp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                            }
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                                    pTmp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    pTmp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                                }
                            }
                            NextStep(1000);
                            break;
                        }
                        case 2:
                        {
                            m_pInstance->DoUseDoorOrButton(GO_SAURFANG_DOOR, 0, true);
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_TALK);
                                DoScriptText(SAY_INTRO_HORDE_1, pTmp);
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[7][0], fPositions[7][1], fPositions[7][2]);
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                    pTmp->GetMotionMaster()->MovePoint(0, fPositions[n][0], fPositions[n][1], fPositions[n][2]);
                                ++n;
                            }
                            NextStep(6000);
                            break;
                        }
                        case 3:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_NONE);
                            }
                            m_creature->HandleEmote(EMOTE_STATE_TALK);
                            DoScriptText(SAY_INTRO_HORDE_2, m_creature);
                            NextStep(14000);
                            break;
                        }
                        case 4:
                        {
                            m_creature->HandleEmote(EMOTE_STATE_NONE);
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_TALK);
                                DoScriptText(SAY_INTRO_HORDE_3, pTmp);
                            }
                            NextStep(7000);
                            break;
                        }
                        case 5:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_NONE);
                            }
                            m_creature->HandleEmote(EMOTE_STATE_TALK);
                            DoScriptText(SAY_INTRO_HORDE_4, m_creature);
                            NextStep(11000);
                            break;
                        }
                        case 6:
                        {
                            m_creature->HandleEmote(EMOTE_STATE_NONE);
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_TALK);
                                DoScriptText(SAY_INTRO_HORDE_5, pTmp);
                            }
                            NextStep(16000);
                            break;
                        }
                        case 7:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_NONE);
                            }
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_TALK);
                                DoScriptText(SAY_INTRO_HORDE_6, pTmp);
                            }
                            NextStep(15000);
                            break;
                        }
                        case 8:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_READY1H);
                                DoScriptText(SAY_INTRO_HORDE_7, pTmp);
                            }
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->HandleEmote(EMOTE_STATE_READY1H);
                                }
                            }
                            NextStep(3000);
                            break;
                        }
                        case 9:
                        {
                            float x, y, z;
                            m_creature->GetPosition(x, y, z);

                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_INTRO_HORDE_8, pTmp);
                                pTmp->SetWalk(false);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->SetWalk(false);
                                    pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                                }
                            }
                            NextStep(3000);
                            break;
                        }
                        case 10:
                        {
                            float x, y, z;
                            // npcs float in air
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->SetWalk(true);
                                pTmp->SetSpeedRate(MOVE_WALK, 3.0f);
                                pTmp->GetPosition(x, y, z);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z + frand(5.0f, 7.0f));
                                pTmp->_AddAura(SPELL_GRIP_OF_AGONY);
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->SetWalk(true);
                                    pTmp->SetSpeedRate(MOVE_WALK, 3.0f);
                                    pTmp->GetPosition(x, y, z);
                                    pTmp->GetMotionMaster()->MovePoint(0, x, y, z + frand(5.0f, 7.0f));
                                    pTmp->_AddAura(SPELL_GRIP_OF_AGONY);
                                }
                            }
                            m_creature->HandleEmote(EMOTE_STATE_TALK);
                            DoScriptText(SAY_INTRO_HORDE_9, m_creature);
                            NextStep(10000);
                            break;
                        }
                        case 11:
                        {
                            m_bIsIntroFinished = true;

                            m_creature->HandleEmote(EMOTE_STATE_NONE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                            m_creature->SetInCombatWithZone();

                            NextStep();
                            break;
                        }
                        case 12:
                        {
                            // fight is in progress
                            break;
                        }
                        default:
                            break;
                    }
                }
                else
                    m_uiNextEventTimer -= uiDiff;
            }

            return;
        }
        // END OF INTRO

        // OUTRO
        if (m_bIsOutroStarted)
        {
            if (m_bIsAlliance)
            {
                // **************
                // ALLIANCE OUTRO
                // **************
                if (m_uiNextEventTimer <= uiDiff)
                {
                    switch (m_uiEventStep)
                    {
                        case 0:
                        {
                            float x, y, z;

                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_ONESHOT_NONE);
                                pTmp->GetPosition(x, y, z);
                                m_creature->UpdateAllowedPositionZ(x, y, z);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z - frand(5.0f, 7.0f));
                                pTmp->RemoveAllAuras();
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->GetPosition(x, y, z);
                                    m_creature->UpdateAllowedPositionZ(x, y, z);
                                    pTmp->GetMotionMaster()->MovePoint(0, x, y, z - frand(5.0f, 7.0f));
                                    pTmp->HandleEmote(EMOTE_ONESHOT_NONE);
                                    pTmp->RemoveAllAuras();
                                }
                            }
                            NextStep(1000);
                        }
                        break;
                        case 1:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->SetLevitate(false);
                                pTmp->SetSpeedRate(MOVE_WALK, 1.0f);

                                for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                                {
                                    if (Creature *pGuard = m_creature->GetMap()->GetCreature(*i))
                                    {
                                        pGuard->SetLevitate(false);
                                        pGuard->SetSpeedRate(MOVE_WALK, 1.0f);
                                        pGuard->GetMotionMaster()->MoveFollow(pTmp, frand(2.0f, 5.0f), frand(M_PI_F / 2, 1.5f * M_PI_F));
                                    }
                                }
                            }
                            NextStep(1000);
                            break;
                        }
                        case 2:
                        {
                            float x ,y ,z;
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_ALLY_1, pTmp);
                                m_creature->GetContactPoint(pTmp, x, y, z, 1.0f);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                            }
                            NextStep(1000);
                            break;
                        }
                        case 3:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                if (!pTmp->IsWithinDist(m_creature, 2.0f))
                                    return;

                                pTmp->StopMoving();
                                pTmp->SetFacingToObject(m_creature);
                            }
                            NextStep(1000);
                            break;
                        }
                        case 4:
                        {
                            NextStep(1000);
                            break;
                        }
                        case 5:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_ALLY_2, pTmp);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 6:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoSummonHighOverlordSaurfang();
                                pTmp->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                                DoScriptText(SAY_OUTRO_ALLY_3, pTmp);
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[14][0], fPositions[14][1], fPositions[14][2]);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 7:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_ALLY_4, pTmp);
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[15][0], fPositions[15][1], fPositions[15][2]);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 8:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_READY1H);
                                for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                                {
                                    if (Creature *pGuard = m_creature->GetMap()->GetCreature(*i))
                                    {
                                         pGuard->HandleEmote(EMOTE_STATE_READY1H);
                                    }
                                }
                                DoScriptText(SAY_OUTRO_ALLY_5, pTmp);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 9:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidOverlord))
                            {
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[16][0], fPositions[16][1], fPositions[16][2]);
                                DoScriptText(SAY_OUTRO_ALLY_6, pTmp);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 10:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_ALLY_7, pTmp);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 11:
                        {
                            DoSummonVarianAndJaina();
                            NextStep(100);
                            break;
                        }
                        case 12:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidVarian))
                            {
                                pTmp->CastSpell(pTmp, 52096, true);
                            }
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidJaina))
                            {
                                pTmp->CastSpell(pTmp, 52096, true);
                            }
                            NextStep(1000);
                            break;
                        }
                        case 13:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidVarian))
                            {
                                DoScriptText(SAY_OUTRO_ALLY_8, pTmp);
                                pTmp->HandleEmote(EMOTE_STATE_TALK);
                                NextStep(10000);
                            }
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_STATE_NONE);
                            }
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pGuard = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pGuard->HandleEmote(EMOTE_STATE_NONE);
                                }
                            }
                            break;
                        }
                        case 14:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidVarian))
                            {
                                pTmp->HandleEmote(EMOTE_STATE_NONE);
                            }
                            float x ,y ,z;
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidOverlord))
                            {
                                m_creature->GetContactPoint(pTmp, x, y, z, 1.0f);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                            }
                            NextStep(1000);
                            break;
                        }
                        case 15:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidOverlord))
                            {
                                // wait until Overlord comes to Deathbringer
                                if (!pTmp->IsWithinDist(m_creature, 2.0f))
                                    return;

                                pTmp->StopMoving();
                                pTmp->SetFacingToObject(m_creature);
                            }
                            NextStep(1000);
                            break;
                        }
                        case 16:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidOverlord))
                            {
                                DoScriptText(SAY_OUTRO_ALLY_9, pTmp);
                                pTmp->HandleEmote(EMOTE_ONESHOT_KNEEL);
                                // Overlord should take Deathbringer on hands (vehicle ride?)
                            }
                            NextStep(3000);
                            break;
                        }
                        case 17:
                        {
                            float x ,y ,z;
                            if (Creature *pTmp1 = m_creature->GetMap()->GetCreature(m_guidOverlord))
                            {
                                if (Creature *pTmp2 = m_creature->GetMap()->GetCreature(m_guidVarian))
                                {
                                    pTmp2->GetContactPoint(pTmp1, x, y, z, 1.0f);
                                    pTmp1->GetMotionMaster()->MovePoint(0, x, y, z);
                                }
                            }
                            NextStep(1000);
                            break;
                        }
                        case 18:
                        {
                            if (Creature *pTmp1 = m_creature->GetMap()->GetCreature(m_guidOverlord))
                            {
                                if (Creature *pTmp2 = m_creature->GetMap()->GetCreature(m_guidVarian))
                                {
                                    // wait until Overlord comes to Varian
                                    if (!pTmp1->IsWithinDist(pTmp2, 2.0f))
                                        return;

                                    pTmp1->StopMoving();
                                    pTmp1->SetFacingToObject(pTmp2);
                                }
                            }
                            NextStep(1000);
                            break;
                        }
                        case 19:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidOverlord))
                            {
                                DoScriptText(SAY_OUTRO_ALLY_10, pTmp);
                                pTmp->HandleEmote(EMOTE_STATE_TALK);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 20:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidVarian))
                            {
                                DoScriptText(SAY_OUTRO_ALLY_11, pTmp);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 21:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidJaina))
                            {
                                DoScriptText(SAY_OUTRO_ALLY_12, pTmp);
                                pTmp->HandleEmote(EMOTE_ONESHOT_CRY);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 22:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidVarian))
                            {
                                DoScriptText(SAY_OUTRO_ALLY_13, pTmp);
                                NextStep(6000);
                            }
                            break;
                        }
                        case 23:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidJaina))
                            {
                                DoScriptText(SAY_OUTRO_ALLY_14, pTmp);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 24:
                        {
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidVarian))
                            {
                                DoScriptText(SAY_OUTRO_ALLY_15, pTmp);
                                NextStep(10000);
                            }
                            break;
                        }
                        case 25:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_ALLY_16, pTmp);
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[2][0], fPositions[2][1], fPositions[2][2]);
                            }
                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidOverlord))
                            {
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[2][0], fPositions[2][1], fPositions[2][2]);
                            }
                            NextStep();
                            break;
                        }
                        case 26:
                        {
                            // wait until coming to gunship boarding place
                            if (Creature *pTmp = GetMainNpc())
                            {
                                if (!pTmp->IsWithinDist2d(fPositions[2][0], fPositions[2][1], 3.0f))
                                    return;

                                pTmp->ForcedDespawn();
                                for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                                {
                                    if (Creature *pGuard = m_creature->GetMap()->GetCreature(*i))
                                        pGuard->ForcedDespawn();
                                }
                            }

                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidVarian))
                                pTmp->ForcedDespawn();

                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidJaina))
                                pTmp->ForcedDespawn();

                            if (Creature *pTmp = m_creature->GetMap()->GetCreature(m_guidOverlord))
                            {
                                if (!pTmp->IsWithinDist2d(fPositions[2][0], fPositions[2][1], 3.0f))
                                    return;

                                pTmp->ForcedDespawn();
                            }

                            Unit *pKiller = m_creature;

                            if (m_pInstance)
                            {
                                if (Unit *pTmp = m_creature->GetMap()->GetUnit(m_guidKiller))
                                    pKiller = pTmp;
                            }

                            if (pKiller)
                                pKiller->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);

                            return;
                            break;
                        }
                        default:
                            break;
                    }
                }
                else
                    m_uiNextEventTimer -= uiDiff;
            }
            else
            {
                // ***********
                // HORDE OUTRO
                // ***********
                if (m_uiNextEventTimer <= uiDiff)
                {
                    switch (m_uiEventStep)
                    {
                        case 0:
                        {
                            float x, y, z;

                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->HandleEmote(EMOTE_ONESHOT_NONE);
                                pTmp->GetPosition(x, y, z);
                                m_creature->UpdateAllowedPositionZ(x, y, z);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z - frand(5.0f, 7.0f));
                                pTmp->RemoveAllAuras();
                            }
                            // move guards
                            for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                            {
                                if (Creature *pTmp = m_creature->GetMap()->GetCreature(*i))
                                {
                                    pTmp->GetPosition(x, y, z);
                                    m_creature->UpdateAllowedPositionZ(x, y, z);
                                    pTmp->GetMotionMaster()->MovePoint(0, x, y, z - frand(5.0f, 7.0f));
                                    pTmp->HandleEmote(EMOTE_ONESHOT_NONE);
                                    pTmp->RemoveAllAuras();
                                }
                            }
                            NextStep(1000);
                            break;
                        }
                        case 1:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                pTmp->SetLevitate(false);
                                pTmp->SetSpeedRate(MOVE_WALK, 1.0f);

                                for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                                {
                                    if (Creature *pGuard = m_creature->GetMap()->GetCreature(*i))
                                    {
                                        pGuard->SetLevitate(false);
                                        pGuard->SetSpeedRate(MOVE_WALK, 1.0f);
                                        pGuard->GetMotionMaster()->MoveFollow(pTmp, frand(2.0f, 5.0f), frand(M_PI_F / 2, 1.5f * M_PI_F));
                                    }
                                }
                            }
                            NextStep(1000);
                            break;
                        }
                        case 2:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_HORDE_1, pTmp);
                                pTmp->HandleEmote(EMOTE_ONESHOT_KNEEL);
                            }
                            NextStep(3000);
                            break;
                        }
                        case 3:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                float x, y, z;
                                m_creature->GetContactPoint(pTmp, x, y, z, 1.0f);
                                pTmp->GetMotionMaster()->MovePoint(0, x, y, z);
                            }
                            NextStep(0);
                            break;
                        }
                        case 4:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                // wait until Overlord comes to Deathbringer
                                if (!pTmp->IsWithinDist(m_creature, 2.0f))
                                    return;

                                pTmp->StopMoving();
                                pTmp->SetFacingToObject(m_creature);
                            }
                            NextStep(1000);
                            break;
                        }
                        case 5:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_HORDE_2, pTmp);
                                pTmp->HandleEmote(EMOTE_ONESHOT_KNEEL);
                                // Overlord should take Deathbringer on hands (vehicle ride?)
                            }
                            NextStep(3000);
                            break;
                        }
                        case 6:
                        {
                            // take deathbringer
                            if (Creature *pTmp = GetMainNpc())
                                DoScriptText(SAY_OUTRO_HORDE_3, pTmp);

                            NextStep(11000);
                            break;
                        }
                        case 7:
                        {
                            if (Creature *pTmp = GetMainNpc())
                            {
                                DoScriptText(SAY_OUTRO_HORDE_4, pTmp);
                                pTmp->GetMotionMaster()->MovePoint(0, fPositions[2][0], fPositions[2][1], fPositions[2][2]);
                            }
                            NextStep();
                            break;
                        }
                        case 8:
                        {
                            // wait until coming to gunship boarding place
                            if (Creature *pTmp = GetMainNpc())
                            {
                                if (!pTmp->IsWithinDist2d(fPositions[2][0], fPositions[2][1], 3.0f))
                                    return;

                                pTmp->ForcedDespawn();
                                for (GUIDList::iterator i = m_lGuards.begin(); i != m_lGuards.end(); ++i)
                                {
                                    if (Creature *pGuard = m_creature->GetMap()->GetCreature(*i))
                                        pGuard->ForcedDespawn();
                                }
                            }

                            Unit *pKiller = m_creature;

                            if (m_pInstance)
                            {
                                if (Unit *pTmp = m_creature->GetMap()->GetUnit(m_guidKiller))
                                    pKiller = pTmp;
                            }

                            if (pKiller)
                                pKiller->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);

                            return;
                        }
                    }
                }
                else
                    m_uiNextEventTimer -= uiDiff;
            }
            return;
        }

        // fight
        UpdateFightAI(uiDiff);
    }
};

struct MANGOS_DLL_DECL boss_deathbringer_saurfangAI : public boss_deathbringer_saurfang_eventAI
{
    boss_deathbringer_saurfangAI(Creature* pCreature) : boss_deathbringer_saurfang_eventAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_powerBloodPower = m_creature->getPowerType(); // don't call this function multiple times in script
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);

        ResetFight();
    }

    ScriptedInstance *m_pInstance;

    uint32 m_uiRuneOfBloodTimer;
    uint32 m_uiBoilingBloodTimer;
    uint32 m_uiBloodNovaTimer;
    uint32 m_uiBloodBeastsTimer;
    uint32 m_uiScentOfBloodTimer;
    uint32 m_uiBerserkTimer;

    bool m_bIsFrenzied;
    bool m_bIsHeroic;
    bool m_bIs25Man;
	uint8 beasts;

    Powers m_powerBloodPower;
    Difficulty m_uiMapDifficulty;

    void ResetFight()
    {
        m_uiRuneOfBloodTimer    = 20000;
        m_uiBoilingBloodTimer   = urand(10000, 35000);
        m_uiBloodNovaTimer      = urand(16000, 35000);
        m_uiBloodBeastsTimer    = 40000;
        m_uiScentOfBloodTimer   = 47000; // 5 seconds after beasts engage in combat
        m_uiBerserkTimer        = (m_bIsHeroic ? 6 : 8) * MINUTE * IN_MILLISECONDS;

        m_bIsFrenzied = false;
		beasts = 0;

        m_creature->SetPower(m_powerBloodPower, 0);
        //m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAURFANG, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, m_creature);

        SetEquipmentSlots(false, EQUIP_MAIN, EQUIP_OFFHAND, EQUIP_RANGED);

        DoCastSpellIfCan(m_creature, SPELL_BLOOD_POWER, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_RUNE_OF_BLOOD, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_MARK_OF_FALLEN_CHAMPION, CAST_TRIGGERED);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SAURFANG, FAIL);

        m_creature->SetPower(m_powerBloodPower, 0);
    }

    // used for unlocking bugged encounter
    void JustDied(Unit *pKiller)
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_SAURFANG) != DONE)
            m_pInstance->SetData(TYPE_SAURFANG, DONE);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
        {
            DoScriptText(SAY_SLAY_1 - urand(0,1), m_creature, pVictim);
        }
    }
/* using DamageDeal also increase Blood Power from basic attack
    void DamageDeal(Unit* pDoneTo, uint32& uiDamage)
    {
        if (pDoneTo == m_creature->getVictim())
        {
            if (pDoneTo->HasAura(SPELL_RUNE_OF_BLOOD_DEBUFF))
                m_creature->SetPower(m_powerBloodPower, m_creature->GetPower(m_powerBloodPower) - 1);

		}
    }
*/

    void SpellHitTarget(Unit* pTarget, const SpellEntry* pSpell)
    {
        //if (pSpell->Id == SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF)
        //        m_creature->SetPower(m_powerBloodPower, m_creature->GetPower(m_powerBloodPower) + 1);
        if (pSpell->Id == SPELL_MARK_OF_FALLEN_CHAMPION)
                m_creature->SetPower(m_powerBloodPower, m_creature->GetPower(m_powerBloodPower) + 1);
		if (pSpell->Id == SPELL_BLOOD_NOVA_10 || pSpell->Id == SPELL_BLOOD_NOVA_25)
                m_creature->SetPower(m_powerBloodPower, m_creature->GetPower(m_powerBloodPower) + 1);
		if (pSpell->Id == SPELL_BOILING_BLOOD_10 || pSpell->Id == SPELL_BOILING_BLOOD_25)
                m_creature->SetPower(m_powerBloodPower, m_creature->GetPower(m_powerBloodPower) + 1);
		// Rune of Blood do not need check.
		//if (pTarget->HasAura(SPELL_RUNE_OF_BLOOD_DEBUFF))
        //        m_creature->SetPower(m_powerBloodPower, m_creature->GetPower(m_powerBloodPower) + 1);
    }

    void JustSummoned(Creature *pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_BLOOD_BEAST)
        {
            pSummoned->CastSpell(pSummoned, SPELL_BLOOD_LINK_BEAST, true);
            pSummoned->CastSpell(pSummoned, SPELL_RESISTANT_SKIN, true);
            pSummoned->setFaction(m_creature->getFaction());
        }
    }

    Player* SelectRandomPlayerForMark()
    {
        Player *pResult = NULL;
        GUIDList lPlayers;
        ThreatList const &threatlist = m_creature->getThreatManager().getThreatList();

        if (!threatlist.empty())
        {
            for (ThreatList::const_iterator itr = threatlist.begin();itr != threatlist.end(); ++itr)
            {
                ObjectGuid const &guid = (*itr)->getUnitGuid();
                if (guid.IsPlayer() && guid != m_creature->getVictim()->GetObjectGuid()) // exclude current target
                {
                    // check if player already has the mark
                    if (Player *pPlayer = m_creature->GetMap()->GetPlayer(guid))
                    {
                        if (!pPlayer->HasAura(SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF))
                            lPlayers.push_back(guid);
                    }
                }
            }
        }

        if (!lPlayers.empty())
        {
            GUIDList::iterator i = lPlayers.begin();
            uint32 max = uint32(lPlayers.size() - 1);

            if (max > 0)
                std::advance(i, urand(0, max));

            pResult = m_creature->GetMap()->GetPlayer(*i);
        }

        // last option - current target
        if (!pResult)
        {
            Unit *pVictim = m_creature->getVictim();
            if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER && !pVictim->HasAura(SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF))
                pResult = (Player*)pVictim;
        }

        return pResult;
    }

    void UpdateFightAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Mark of the Fallen Champion
        if (m_creature->GetPower(m_powerBloodPower) >= 100)
        {
            if (Player *pTarget = SelectRandomPlayerForMark())
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MARK_OF_FALLEN_CHAMPION_DEBUFF) == CAST_OK)
                {
                    m_creature->SetPower(m_powerBloodPower, 0); // reset Blood Power
                    // decrease the buff
                    m_creature->RemoveAurasDueToSpell(72371);
                    int32 power = m_creature->GetPower(m_powerBloodPower);
                    m_creature->CastCustomSpell(m_creature, 72371, &power, &power, NULL, true);
                    DoScriptText(SAY_FALLENCHAMPION, m_creature);
					m_uiMarkCastCount++;
                }
            }
        }

        // Frenzy (soft enrage)
        if (!m_bIsFrenzied)
        {
            if (m_creature->GetHealthPercent() <= 30.0f)
            {
                DoCastSpellIfCan(m_creature, SPELL_FRENZY, CAST_TRIGGERED);
                DoScriptText(SAY_BERSERK, m_creature);
                m_bIsFrenzied = true;
            }
        }

        // Berserk (hard enrage)
        if (m_uiBerserkTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
            {
                DoScriptText(SAY_BERSERK, m_creature);
                m_uiBerserkTimer = (m_bIsHeroic ? 6 : 8) * MINUTE * IN_MILLISECONDS;
            }
        }
        else
            m_uiBerserkTimer -= uiDiff;

        // Rune of Blood
        if (m_uiRuneOfBloodTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_RUNE_OF_BLOOD_DEBUFF) == CAST_OK)
                m_uiRuneOfBloodTimer = 20000;
        }
        else
            m_uiRuneOfBloodTimer -= uiDiff;

        // Boiling Blood
        if (m_uiBoilingBloodTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, m_bIs25Man ? SPELL_BOILING_BLOOD_25 : SPELL_BOILING_BLOOD_10) == CAST_OK)
                m_uiBoilingBloodTimer = urand(10000, 35000);
        }
        else
            m_uiBoilingBloodTimer -= uiDiff;

        // Blood Nova
        if (m_uiBloodNovaTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, m_bIs25Man ? SPELL_BLOOD_NOVA_25 : SPELL_BLOOD_NOVA_10) == CAST_OK)
                m_uiBloodNovaTimer = urand(16000, 35000);
        }
        else
            m_uiBloodNovaTimer -= uiDiff;

		// Call Blood Beasts
        if (m_uiBloodBeastsTimer <= uiDiff)
        {
			for (uint8 i = 0; i < 2; ++i)
				if (Creature* pTemp = m_creature->SummonCreature(38508, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 90000))
					if (Unit* pTarget = pTemp->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))					
						pTemp->AI()->AttackStart(pTarget);

            if (m_bIs25Man)
            {
				for (uint8 i = 0; i < 3; ++i)
					if (Creature* pTemp = m_creature->SummonCreature(38508, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 90000))
						if (Unit* pTarget = pTemp->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))					
							pTemp->AI()->AttackStart(pTarget);
            }

            m_uiBloodBeastsTimer  = 40000;

            if (m_bIsHeroic)
                m_uiScentOfBloodTimer = 7000; // 5 seconds after beasts engage in combat

            DoScriptText(SAY_BLOODBEASTS, m_creature);
        }
        else
            m_uiBloodBeastsTimer -= uiDiff;

        // Scent of Blood
        if (m_bIsHeroic)
        {
            if (m_uiScentOfBloodTimer <= uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_SCENT_OF_BLOOD, CAST_TRIGGERED);
                DoCastSpellIfCan(m_creature, SPELL_SCENT_OF_BLOOD_TRIGGERED, CAST_TRIGGERED);
                m_uiScentOfBloodTimer = 40000;
                // via DB
                m_creature->MonsterTextEmote("Deathbringer Saurfang's Blood Beasts gain the scent of blood!", m_creature->getVictim(), true);
            }
            else
                m_uiScentOfBloodTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_deathbringer_saurfang(Creature* pCreature)
{
    return new boss_deathbringer_saurfangAI(pCreature);
}

struct MANGOS_DLL_DECL  mob_blood_beastAI : public ScriptedAI
{
    mob_blood_beastAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiScentOfBloodTimer;
    uint32 m_uiReadyTimer;

    bool m_bIsReady;

    void Reset()
    {
        m_uiScentOfBloodTimer = 5000;

        m_uiReadyTimer = 2000;
        m_bIsReady = false;

        SetCombatMovement(false);
        m_creature->SetWalk(true);
    }

    void JustReachedHome()
    {
        m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_bIsReady)
        {
            if (m_uiReadyTimer <= uiDiff)
            {
                m_bIsReady = true;
                SetCombatMovement(true);
                m_creature->SetInCombatWithZone();
                if (m_creature->getVictim())
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
            }
            else
                m_uiReadyTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_blood_beast(Creature* pCreature)
{
    return new mob_blood_beastAI(pCreature);
}

void AddSC_boss_deathbringer_saurfang()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_deathbringer_saurfang";
    newscript->GetAI = &GetAI_boss_deathbringer_saurfang;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_blood_beast";
    newscript->GetAI = &GetAI_mob_blood_beast;
    newscript->RegisterSelf();
}
