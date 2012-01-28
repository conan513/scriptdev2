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
SDName: Icecrown
SD%Complete: 100
SDComment: Vendor support: 34885
Quest Support: 13663, 13665, 13745, 13750, 13756, 13761, 13767, 13772, 13777, 13782, 13787, 14107
SDCategory: Icecrown
EndScriptData */

/* ContentData
npc_dame_evniki_kapsalis
npc_scourge_conventor
npc_fallen_hero_spirit
npc_valiants
npc_champions
npc_black_knights_gryphon
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"
#include "TemporarySummon.h"
#include "Vehicle.h"

/*#####
## npc_black_knights_gryphon
#####*/
 
struct MANGOS_DLL_DECL npc_black_knights_gryphonAI : public npc_escortAI
{
    npc_black_knights_gryphonAI(Creature* pCreature) : npc_escortAI(pCreature) { Reset(); }
 
    void Reset() { }
 
    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(((TemporarySummon*)m_creature)->GetSummonerGuid()))
            pPlayer->KilledMonsterCredit(m_creature->GetEntry(), m_creature->GetObjectGuid());
 
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetSpeedRate(MOVE_RUN, 3.0f);
        Start(true, ((Player*)pCaster));
    }
 
    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 0:
                SetRun();
                break;
            case 10:
                m_creature->SetLevitate(true);
                m_creature->SetSpeedRate(MOVE_RUN, 6.0f);
                break;
            case 15:
                //if (Player* pPlayer = GetPlayerForEscort())
                    //hack to prevent Player's death
                  //  pPlayer->CastSpell(pPlayer, 64505, true);
                    break;
            case 16:
                m_creature->ForcedDespawn(2000);
                return;
            default:
                break;
        }
    }
};
 
CreatureAI* GetAI_npc_black_knights_gryphon(Creature* pCreature)
{
    return new npc_black_knights_gryphonAI(pCreature);
}

/*######
## npc_dame_evniki_kapsalis
######*/

enum
{
    TITLE_CRUSADER    = 123
};

bool GossipHello_npc_dame_evniki_kapsalis(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->HasTitle(TITLE_CRUSADER))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_dame_evniki_kapsalis(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
    return true;
}

/*######
## npc_scourge_conventor  //quest 14107
######*/

// grip of scourge still needs implented and used

enum QuestFate // shared enum by conventor mob and fallen hero mob
{
    QUEST_THE_FATE_OF_THE_FALLEN        = 14107,
    NPC_FALLEN_HERO_SPIRIT              = 32149,
    NPC_FALLEN_HERO_SPIRIT_PROXY        = 35055,
};

enum
{
    SPELL_CONE_OF_COLD              = 20828,
    SPELL_FORST_NOVA                = 11831,
    SPELL_FROSTBOLT                 = 20822,
    SPELL_GRIP_OF_THE_SCOURGE       = 60212,     // spell casted by mob
};

struct MANGOS_DLL_DECL npc_scourge_conventorAI : public ScriptedAI
{
    npc_scourge_conventorAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiConeofCold_Timer;
    uint32 m_uiFrostNova_Timer;
    uint32 m_uiFrostBolt_Timer;
    //uint32 m_uiGrip_Timer;

    void Reset()
    {
        m_uiConeofCold_Timer  = 10000;
        m_uiFrostNova_Timer    = 11000;
        m_uiFrostBolt_Timer    = 9000;
        //m_uiGrip_Timer = 10000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiConeofCold_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CONE_OF_COLD);
            m_uiConeofCold_Timer = 10000;
        }
        else
            m_uiConeofCold_Timer -= uiDiff;

        if (m_uiFrostNova_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_FORST_NOVA);
            m_uiFrostNova_Timer = 11000;
        }
        else
            m_uiFrostNova_Timer -= uiDiff;

        if (m_uiFrostBolt_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_FROSTBOLT);
            m_uiFrostBolt_Timer = 9000;
        }
        else
            m_uiFrostBolt_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_npc_scourge_conventor(Creature* pCreature)
{
    return new npc_scourge_conventorAI(pCreature);
}

/*######
## npc_fallen_hero_spirit  //quest 14107
######*/

enum
{
    SAY_BLESS_1                         = -1999819,
    SAY_BLESS_2                         = -1999820,
    SAY_BLESS_3                         = -1999821,
    SAY_BLESS_4                         = -1999822,
    SAY_BLESS_5                         = -1999823,

    SPELL_STRIKE                        = 11976,
    SPELL_BLESSING_OF_PEACE             = 66719,     //spell casted from relic of light
    GRIP_OF_THE_SCOURGE_AURA            = 60231      //might need server side spell script support (when mob has this spell it's immune to fate of light spell)
};

/*######
## npc_argent_champion  //quest 13713
######*/

enum
{
        SAY_AGGRO =		-1800000,
	SAY_QUEST_COMPLETE =	-1800001,
};

struct MANGOS_DLL_DECL npc_argent_championAI : public ScriptedAI
{
    npc_argent_championAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset() {}

    void JustDied(Unit* pKiller) {}

    void KilledUnit(Unit* pVictim)
    {
        m_creature->ForcedDespawn();
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 1;

            if (Unit* pPlayer = pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                if (pPlayer->GetTypeId() != TYPEID_PLAYER)
                     return;
                ((Player*)pPlayer)->KilledMonsterCredit(38595);
                ((Player*)pPlayer)->KilledMonsterCredit(33708);
                ((Player*)pPlayer)->CompleteQuest(13680);
                ((Player*)pPlayer)->CompleteQuest(13679);
                m_creature->setFaction(35);
                m_creature->SetHealth(m_creature->GetMaxHealth());
                DoScriptText(SAY_QUEST_COMPLETE, m_creature);
                EnterEvadeMode();
                m_creature->ForcedDespawn(4000);
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_argent_champion(Creature* pCreature)
{
    return new npc_argent_championAI(pCreature);
}

/*######
## npc_squire_danny  //quest 13713
######*/

bool GossipHello_npc_squire_danny(Player* pPlayer, Creature* pCreature)
{
	if (pPlayer->GetQuestStatus(13713) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	else if (pPlayer->GetQuestStatus(13699) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	else if (pPlayer->GetQuestStatus(13723) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	else if (pPlayer->GetQuestStatus(13724) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	else if (pPlayer->GetQuestStatus(13725) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	else if (pPlayer->GetQuestStatus(13726) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	else if (pPlayer->GetQuestStatus(13727) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	else if (pPlayer->GetQuestStatus(13728) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	else if (pPlayer->GetQuestStatus(13729) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	else if (pPlayer->GetQuestStatus(13731) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetObjectGuid());
	return true;
}
bool GossipSelect_npc_squire_danny(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
{
	if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            if (Creature* pChampion = pCreature->SummonCreature(33707, 8533.11f, 1069.66f, 551.884f, 1.55575f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 120000))
            {
                pChampion->GetMotionMaster()->Clear();
                pChampion->GetMotionMaster()->MovePoint(0, 8544.034180f, 1091.534180f, 556.787598f);
                pChampion->setFaction(22);
            }
        }
	pPlayer->CLOSE_GOSSIP_MENU();
	return true;
}

/*######
## npc_squire_danny  //quest The Grand Melee
######*/

struct MANGOS_DLL_DECL quest_the_grand_meleeAI : public ScriptedAI
{
    quest_the_grand_meleeAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset()
    {
        m_creature->setFaction(35);
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void BeginSpeech(Player* pTarget)
    {
        m_creature->AI()->AttackStart(pTarget);
        m_creature->AddThreat(pTarget, 999999);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 1;

            if (Unit* pPlayer = pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                m_creature->setFaction(35);
                pPlayer->CastSpell(pPlayer, 62724, true);
                DoScriptText(-1800004, m_creature);
                m_creature->ForcedDespawn(7000);
                EnterEvadeMode();
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_quest_the_grand_melee(Creature* pCreature)
{
    return new quest_the_grand_meleeAI(pCreature);
}

bool GossipHello_quest_the_grand_melee(Player* pPlayer, Creature* pCreature)
{
        if (pPlayer->GetQuestStatus(13665) == QUEST_STATUS_INCOMPLETE ||
                pPlayer->GetQuestStatus(13745) == QUEST_STATUS_INCOMPLETE ||
		pPlayer->GetQuestStatus(13750) == QUEST_STATUS_INCOMPLETE ||
		pPlayer->GetQuestStatus(13756) == QUEST_STATUS_INCOMPLETE ||
		pPlayer->GetQuestStatus(13761) == QUEST_STATUS_INCOMPLETE ||
		pPlayer->GetQuestStatus(13767) == QUEST_STATUS_INCOMPLETE ||
		pPlayer->GetQuestStatus(13772) == QUEST_STATUS_INCOMPLETE ||
		pPlayer->GetQuestStatus(13777) == QUEST_STATUS_INCOMPLETE ||
		pPlayer->GetQuestStatus(13782) == QUEST_STATUS_INCOMPLETE ||
		pPlayer->GetQuestStatus(13787) == QUEST_STATUS_INCOMPLETE)
		pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
		
	pPlayer->SEND_GOSSIP_MENU(14384, pCreature->GetObjectGuid());	
	return true;
}

bool GossipSelect_quest_the_grand_melee(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
{
	if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            switch (urand(0,1))
            {
            case 0:
                DoScriptText(-1800002, pCreature);
                break;
            case 1:
                DoScriptText(-1800003, pCreature);
                break;
            default:
                break;
            }
            if (quest_the_grand_meleeAI* pMeleeAI = dynamic_cast<quest_the_grand_meleeAI*>(pCreature->AI()))
            {
                pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                pCreature->setFaction(22);
                pMeleeAI->BeginSpeech(pPlayer);
            }
	}
	pPlayer->CLOSE_GOSSIP_MENU();
	return true;
}

/*######
## quest Among the Champions
######*/

struct MANGOS_DLL_DECL quest_among_the_championsAI : public ScriptedAI
{
    quest_among_the_championsAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    void Reset()
    {
        m_creature->setFaction(35);
        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void BeginSpeech(Player* pTarget)
    {
        m_creature->AI()->AttackStart(pTarget);
        m_creature->AddThreat(pTarget, 9999999);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 1;

            if (Unit* pPlayer = pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                m_creature->setFaction(35);
                m_creature->AttackStop();
                pPlayer->CastSpell(pPlayer, 63596, true);
                DoScriptText(-1800004, m_creature);
                EnterEvadeMode();
                m_creature->ForcedDespawn(4000);
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_quest_among_the_champions(Creature* pCreature)
{
    return new quest_among_the_championsAI(pCreature);
}

bool GossipHello_quest_among_the_champions(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(13790) == QUEST_STATUS_INCOMPLETE ||
            pPlayer->GetQuestStatus(13793) == QUEST_STATUS_INCOMPLETE ||
            pPlayer->GetQuestStatus(13811) == QUEST_STATUS_INCOMPLETE ||
            pPlayer->GetQuestStatus(13814) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, -3700000, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
		
	pPlayer->SEND_GOSSIP_MENU(14384, pCreature->GetObjectGuid());	
	return true;
}

bool GossipSelect_quest_among_the_champions(Player *pPlayer, Creature *pCreature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF + 1)
    {
        switch (urand(0,1))
        {
        case 0:
            DoScriptText(-1800002, pCreature);
            break;
        case 1:
            DoScriptText(-1800003, pCreature);
            break;
        default:
            break;
        }
        if (quest_among_the_championsAI* pAmongAI = dynamic_cast<quest_among_the_championsAI*>(pCreature->AI()))
        {
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            pCreature->setFaction(22);
            pAmongAI->BeginSpeech(pPlayer);
        }
    }

    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

/*######
## quest_mastery_of_melee
######*/

struct MANGOS_DLL_DECL quest_mastery_of_meleeAI : public ScriptedAI
{
    quest_mastery_of_meleeAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    ObjectGuid m_playerGuid;
    bool castspell;

    void Reset()
    {
        castspell = false;
        m_playerGuid.Clear();
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 1;

            if (Unit* pPlayer = pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
            {
                m_creature->SetHealth(m_creature->GetMaxHealth());
                pPlayer->CastSpell(pPlayer, 62672, true);
                pPlayer->CombatStop();
                EnterEvadeMode();
            }
        }
    }

    void JustDied(Unit* pKiller) {}

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_quest_mastery_of_melee(Creature* pCreature)
{
    return new quest_mastery_of_meleeAI(pCreature);
}

struct MANGOS_DLL_DECL npc_fallen_hero_spiritAI : public ScriptedAI
{
    npc_fallen_hero_spiritAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiStrike_Timer;

    void Reset()
    {
        m_uiStrike_Timer = 10000;
    }

    void SpellHit(Unit *pCaster, const SpellEntry *pSpell)
    {
        // if (m_creature->HasAura(GRIP_OF_THE_SCOURGE_AURA))
        //     return fasle;

        if (pCaster->GetTypeId() == TYPEID_PLAYER && m_creature->isAlive() && ((pSpell->Id == SPELL_BLESSING_OF_PEACE)))
        {
            if (((Player*)pCaster)->GetQuestStatus(QUEST_THE_FATE_OF_THE_FALLEN) == QUEST_STATUS_INCOMPLETE)
            {
                ((Player*)pCaster)->KilledMonsterCredit(NPC_FALLEN_HERO_SPIRIT_PROXY);
                m_creature->ForcedDespawn();
                switch(urand(0, 4))
                {
                    case 0: DoScriptText(SAY_BLESS_1, m_creature); break;
                    case 1: DoScriptText(SAY_BLESS_2, m_creature); break;
                    case 2: DoScriptText(SAY_BLESS_3, m_creature); break;
                    case 3: DoScriptText(SAY_BLESS_4, m_creature); break;
                    case 4: DoScriptText(SAY_BLESS_5, m_creature); break;
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiStrike_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_STRIKE);
            m_uiStrike_Timer = 10000;
        }
        else
            m_uiStrike_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_npc_fallen_hero_spirit(Creature* pCreature)
{
    return new npc_fallen_hero_spiritAI(pCreature);
}

/*#####
## npc_valiants
#####*/

enum
{
    SAY_DEFEATED          = -1999824,
    SPELL_VCHARGE         = 63010,
    SPELL_VSHIELDBREAKER  = 65147,

    SPELL_MOUNTED_MELEE_VICTORY = 62724,
};

struct MANGOS_DLL_DECL npc_valiantsAI : public ScriptedAI
{
   npc_valiantsAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    //uint32 m_uiVCHARGE_Timer;
    //uint32 m_uiVSHIELDBREAKER_Timer;

    void Reset()
    {
       //m_uiVCHARGE_Timer          = 2000;  need correct timers
       //m_uiVSHIELDBREAKER_Timer   = 5000;  need correct timers
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 5;

            if (Unit* pPlayer = pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
                pPlayer->CastSpell(pPlayer, SPELL_MOUNTED_MELEE_VICTORY, true);

            DoScriptText(SAY_DEFEATED, m_creature);
            EnterEvadeMode();
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
       /* {    STILL HAVE ATTACK SPELLS TO DO
        }*/

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_valiants(Creature* pCreature)
{
    return new npc_valiantsAI(pCreature);
}

/*#####
## npc_champions
#####*/

enum
{
    // spells are defined above
    SPELL_CHAMP_MOUNTED_MELEE_VICTORY = 63596,
};

struct MANGOS_DLL_DECL npc_championsAI : public ScriptedAI
{
   npc_championsAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    //uint32 m_uiVCHARGE_Timer;
    //uint32 m_uiVSHIELDBREAKER_Timer;

    void Reset()
    {
       //m_uiVCHARGE_Timer          = 2000;  need correct timers
       //m_uiVSHIELDBREAKER_Timer   = 5000;  need correct timers
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 5;

            if (Unit* pPlayer = pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
                pPlayer->CastSpell(pPlayer, SPELL_CHAMP_MOUNTED_MELEE_VICTORY, true);

            DoScriptText(SAY_DEFEATED, m_creature);
            EnterEvadeMode();
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
       /* {    STILL HAVE ATTACK SPELLS TO DO
        }*/

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_champions(Creature* pCreature)
{
    return new npc_championsAI(pCreature);
}

void AddSC_icecrown()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_black_knights_gryphon";
    pNewScript->GetAI = &GetAI_npc_black_knights_gryphon;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_dame_evniki_kapsalis";
    pNewScript->pGossipHello = &GossipHello_npc_dame_evniki_kapsalis;
    pNewScript->pGossipSelect = &GossipSelect_npc_dame_evniki_kapsalis;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_scourge_conventor";
    pNewScript->GetAI = &GetAI_npc_scourge_conventor;
    pNewScript->RegisterSelf();
	
    pNewScript = new Script;
    pNewScript->Name = "npc_argent_champion";
    pNewScript->GetAI = &GetAI_npc_argent_champion;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="npc_squire_danny";
    pNewScript->pGossipHello =  &GossipHello_npc_squire_danny;
    pNewScript->pGossipSelect = &GossipSelect_npc_squire_danny;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="quest_the_grand_melee";
    pNewScript->GetAI = &GetAI_quest_the_grand_melee;
    pNewScript->pGossipHello =  &GossipHello_quest_the_grand_melee;
    pNewScript->pGossipSelect = &GossipSelect_quest_the_grand_melee;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="quest_among_the_champions";
    pNewScript->GetAI = &GetAI_quest_among_the_champions;
    pNewScript->pGossipHello =  &GossipHello_quest_among_the_champions;
    pNewScript->pGossipSelect = &GossipSelect_quest_among_the_champions;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="quest_mastery_of_melee";
    pNewScript->GetAI = &GetAI_quest_mastery_of_melee;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_fallen_hero_spirit";
    pNewScript->GetAI = &GetAI_npc_fallen_hero_spirit;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_valiants";
    pNewScript->GetAI = &GetAI_npc_valiants;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_champions";
    pNewScript->GetAI = &GetAI_npc_champions;
    pNewScript->RegisterSelf();
}
