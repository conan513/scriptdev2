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
SDName: instance_pit_of_saron
SD%Complete: 50%
SDComment: support event
SDCategory: Pit of Saron
EndScriptData */

#include "precompiled.h"
#include "pit_of_saron.h"

instance_pit_of_saron::instance_pit_of_saron(Map* pMap) : BSWScriptedInstance(pMap)
{
    Initialize();
}

 void instance_pit_of_saron::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

	m_auiEventTimer = 1000;
	_teamInInstance = 0;
}

void instance_pit_of_saron::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_TYRANNUS_INTRO:
        case NPC_GARFROST:
        case NPC_KRICK:
        case NPC_ICK:
        case NPC_TYRANNUS:
        case NPC_RIMEFANG:
		case NPC_SINDRAGOSA:
		case NPC_MARITN_VICTUS:
		case NPC_GORKUN_IRONSKULL:
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
    }
}
void instance_pit_of_saron::OnPlayerEnter(Player* pPlayer)
{
	if (!_teamInInstance)
		_teamInInstance = pPlayer->GetTeam();
}
void instance_pit_of_saron::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_ICEWALL:
			m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
			 if (m_auiEncounter[TYPE_GARFROST] == DONE && m_auiEncounter[TYPE_KRICK] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_HALLS_OF_REFLECT_PORT:
			m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
    }
}

void instance_pit_of_saron::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
		case TYPE_EVENT:
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_GARFROST:
			m_auiEncounter[uiType] = uiData;
            if (uiData == DONE && m_auiEncounter[TYPE_KRICK] == DONE)
				DoOpenDoor(GO_ICEWALL);
            break;
        case TYPE_KRICK:
			m_auiEncounter[uiType] = uiData;
			if (uiData == SPECIAL)
			{
				if (Creature* pKrick = GetSingleCreatureFromStorage(NPC_KRICK))
				{
					if (_teamInInstance == HORDE)
						pKrick->SummonCreature(NPC_SYLVANAS_PART1, 821.757080f, 118.749359f, 509.322723f, 0.051814f, TEMPSUMMON_DEAD_DESPAWN, 0);
					else
						pKrick->SummonCreature(NPC_JAINA_PART1, 821.757080f, 118.749359f, 509.322723f, 0.051814f, TEMPSUMMON_DEAD_DESPAWN, 0);
				}
			}
            if (uiData == DONE && m_auiEncounter[TYPE_GARFROST] == DONE)
				DoOpenDoor(GO_ICEWALL);
            break;
        case TYPE_TYRANNUS:
            m_auiEncounter[uiType] = uiData;
			if (uiData == 5)
			{
				if (Creature* pRimegang = GetSingleCreatureFromStorage(NPC_RIMEFANG))
				{
					if (_teamInInstance == HORDE)
					{
						pRimegang->SummonCreature(NPC_SYLVANAS_PART2, 1063.784668f, 101.132202f, 630.996704f, 2.18949f, TEMPSUMMON_DEAD_DESPAWN, 0);
					} else {
						pRimegang->SummonCreature(NPC_JAINA_PART2, 1063.784668f, 101.132202f, 630.996704f, 2.18949f, TEMPSUMMON_DEAD_DESPAWN, 0);
					}
				}
			}
            break;
		case TYPE_EVENT_TIMER:  m_auiEventTimer = uiData; uiData = NOT_STARTED; break;
        default:
            return;
	}

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2];

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_pit_of_saron::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2];

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

uint32 instance_pit_of_saron::GetData(uint32 uiType)
{
	switch(uiType)
        {
		case DATA_TEAM_IN_INSTANCE: return _teamInInstance;
		case TYPE_EVENT:         return m_auiEncounter[uiType];
		case TYPE_EVENT_TIMER:   return m_auiEventTimer;
		case TYPE_EVENT_NPC:
			{
				switch (m_auiEncounter[TYPE_EVENT])
				{
					case 5:
					case 10:
					case 15:
					case 20:
					case 25:
					case 30:
					case 35:
					case 40:
					case 45:
					case 50:
					case 55:
					case 60:
					case 65:
					case 70:
					case 75:
					case 80:
					case 85:
					case 86:
					case 87:
					case 88:
					case 89:
					case 90:
					case 91:
					case 92:
					case 93:
					case 94:
					case 95:
					case 100:
						if (_teamInInstance == HORDE)
							return NPC_SYLVANAS_PART1;
						else return NPC_JAINA_PART1;
						break;
					case 101:
					case 102:
					case 103:
					case 104:
					case 105:
					case 110:
					case 115:
					case 116:
					case 117:
					case 118:
					case 119:
					case 120:
					case 121:
					case 122:
					case 123:
					case 124:
					case 125:
					case 126:
					case 127:
						if (_teamInInstance == HORDE)
							return NPC_SYLVANAS_PART2;
						else return NPC_JAINA_PART2;
						break;
					default:
						break;
				}
			}
			break;
		}

    if (uiType < MAX_ENCOUNTER)
        return m_auiEncounter[uiType];

    return 0;
}

bool AreaTrigger_at_tyrannus(Player* pPlayer, AreaTriggerEntry const* pAt)
{
    if (instance_pit_of_saron* pInstance = (instance_pit_of_saron*)pPlayer->GetInstanceData())
    {
        if (pInstance->GetData(TYPE_TYRANNUS) == NOT_STARTED)
            pInstance->SetData(TYPE_TYRANNUS, SPECIAL);
    }

    return false;
}

InstanceData* GetInstanceData_instance_pit_of_saron(Map* pMap)
{
    return new instance_pit_of_saron(pMap);
}

void AddSC_instance_pit_of_saron()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_pit_of_saron";
    pNewScript->GetInstanceData = &GetInstanceData_instance_pit_of_saron;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_tyrannus";
    pNewScript->pAreaTrigger = &AreaTrigger_at_tyrannus;
    pNewScript->RegisterSelf(false);
}
