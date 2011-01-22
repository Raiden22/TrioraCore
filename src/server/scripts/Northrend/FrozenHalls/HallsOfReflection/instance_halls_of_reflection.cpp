/*
 * Copyright (C) 2011 TrioraCore <http://www.trioracore.ru/>
 */

#include "ScriptPCH.h"
#include "halls_of_reflection.h"

#define MAX_ENCOUNTER 3

class instance_halls_of_reflection : public InstanceMapScript
{
public:
    instance_halls_of_reflection() : InstanceMapScript("instance_halls_of_reflection", 668) { }

    struct instance_halls_of_reflection_InstanceMapScript : public InstanceScript
    {
        instance_halls_of_reflection_InstanceMapScript(Map* pMap) : InstanceScript(pMap) 
        {
            Initialize();
        };
        
        uint64 uiFrostmourne;
        uint64 uiFrostmourneAltar;
        uint64 uiIcecrownDoor;
        uint64 uiImpenetrableDoor;
        
        uint64 uiJainaPart1;
        uint64 uiLichKingEvent;
        uint64 uiFalric;
        uint64 uiMarwyn;
        
        uint32 uiEncounter[MAX_ENCOUNTER];
        uint32 uiWaveCount;
        
        void Initialize()
        {
            uiFrostmourne = 0;
            uiFrostmourneAltar = 0;
            uiIcecrownDoor = 0;
            uiImpenetrableDoor = 0;
            
            uiJainaPart1 = 0;
            uiLichKingEvent = 0;
            uiFalric = 0;
            uiMarwyn = 0;
            
            uiWaveCount = 0;
            
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                uiEncounter[i] = NOT_STARTED;
        }

        void OnCreatureCreate(Creature* pCreature)
        {
            switch(pCreature->GetEntry())
            {
                case NPC_JAINA_PART1:
                    uiJainaPart1 = pCreature->GetGUID();
                    break;
                case NPC_LICH_KING_EVENT:
                    uiLichKingEvent = pCreature->GetGUID();
                    break;
                case NPC_FALRIC:
                    uiFalric = pCreature->GetGUID();
                    break;
                case NPC_MARWYN:
                    uiMarwyn = pCreature->GetGUID();
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* pGo)
        {
            switch(pGo->GetEntry())
            {
                case GO_FROSTMOURNE:
                    uiFrostmourne = pGo->GetGUID();
                    pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                    HandleGameObject(0, false, pGo);
                    break;
                case GO_FROSTMOURNE_ALTAR:
                    uiFrostmourneAltar = pGo->GetGUID();
                    pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                    HandleGameObject(0, true, pGo);
                    break;
                case GO_ICECROWN_DOOR:
                    uiIcecrownDoor = pGo->GetGUID();
                    pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                    HandleGameObject(0, true, pGo);
                    break;
                case GO_IMPENETRABLE_DOOR:
                    uiImpenetrableDoor = pGo->GetGUID();
                    pGo->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                    HandleGameObject(0, false, pGo);
                    break;
            }
        }

        void SetData(uint32 type, uint32 data)
        {
        }

        uint32 GetData(uint32 type)
        {
            switch(type)
            {
                case DATA_WAVE_COUNT:
                    return uiWaveCount;
            }
        }
        
        void SetData64(uint32 data, uint64 uiGuid)
        {
        }

        uint64 GetData64(uint32 data)
        {
            switch (data)
            {
                case DATA_FROSTMOURNE:
                    return uiFrostmourne;
                case DATA_ICECROWN_DOOR:
                    return uiIcecrownDoor;
                case DATA_IMPENETRABLE_DOOR:
                    return uiImpenetrableDoor;
                case DATA_FALRIC:
                    return uiFalric;
                case DATA_MARWYN:
                    return uiMarwyn;
            }
            return 0;
        }
    };
    InstanceScript* GetInstanceScript(InstanceMap* pMap) const
    {
        return new instance_halls_of_reflection_InstanceMapScript(pMap);
    }
};

void AddSC_instance_halls_of_reflection()
{
    new instance_halls_of_reflection();
}
