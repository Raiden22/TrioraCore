/*
 * Copyright (C) 2011 TrioraCore <http://www.trioracore.ru/>
 */

#include "ScriptPCH.h"
#include "halls_of_reflection.h"

enum Yells
{
    SAY_JAINA_INTRO_1                             = -1668001,//case 2
    SAY_JAINA_INTRO_2                             = -1668002,
    SAY_JAINA_INTRO_3                             = -1668003,
    SAY_JAINA_INTRO_4                             = -1668004,
    SAY_UTHER_INTRO_A_1                           = -1668005,
    SAY_JAINA_INTRO_5                             = -1668006,
    SAY_UTHER_INTRO_A_2                           = -1668007,
    SAY_JAINA_INTRO_6                             = -1668008,
    SAY_UTHER_INTRO_A_3                           = -1668009,
    SAY_JAINA_INTRO_7                             = -1668010,
    SAY_UTHER_INTRO_A_4                           = -1668011,
    SAY_JAINA_INTRO_8                             = -1668012,
    SAY_UTHER_INTRO_A_5                           = -1668013,
    SAY_JAINA_INTRO_9                             = -1668014,
    SAY_UTHER_INTRO_A_6                           = -1668015,
    SAY_UTHER_INTRO_A_7                           = -1668016,
    SAY_JAINA_INTRO_10                            = -1668017,
    SAY_UTHER_INTRO_A_8                           = -1668018,
    SAY_JAINA_INTRO_11                            = -1668019,
    SAY_UTHER_INTRO_A_9                           = -1668020,

    SAY_SYLVANA_INTRO_1                           = -1668021,
    SAY_SYLVANA_INTRO_2                           = -1668022,
    SAY_SYLVANA_INTRO_3                           = -1668023,
    SAY_UTHER_INTRO_H_1                           = -1668024,
    SAY_SYLVANA_INTRO_4                           = -1668025,
    SAY_UTHER_INTRO_H_2                           = -1668026,
    SAY_SYLVANA_INTRO_5                           = -1668027,
    SAY_UTHER_INTRO_H_3                           = -1668028,
    SAY_SYLVANA_INTRO_6                           = -1668029,
    SAY_UTHER_INTRO_H_4                           = -1668030,
    SAY_SYLVANA_INTRO_7                           = -1668031,
    SAY_UTHER_INTRO_H_5                           = -1668032,
    SAY_UTHER_INTRO_H_6                           = -1668033,
    SAY_SYLVANA_INTRO_8                           = -1668034,
    SAY_UTHER_INTRO_H_7                           = -1668035,

    SAY_LK_INTRO_1                                = -1668036,
    SAY_LK_INTRO_2                                = -1668037,
    SAY_LK_INTRO_3                                = -1668038,
    SAY_FALRIC_INTRO_1                            = -1668039,
    SAY_MARWYN_INTRO_1                            = -1668040,
    SAY_FALRIC_INTRO_2                            = -1668041,

    SAY_JAINA_INTRO_END                           = -1668042,
    SAY_SYLVANA_INTRO_END                         = -1668043,
};

enum eSpells
{
    SPELL_CAST_VISUAL           = 65633,  //Jaina And Sylavana cast this when summon uther.
    SPELL_FROSTMOURNE_SOUNDS    = 70667,
    SPELL_UTHER_DESPAWN         = 70693,
    SPELL_TAKE_FROSTMOURNE      = 72729,
    SPELL_FROSTMOURNE_VISUAL    = 73220,
    SPELL_BOSS_SPAWN_AURA       = 72712,
};

class npc_jaina_intro_hor : public CreatureScript
{
public:
    npc_jaina_intro_hor() : CreatureScript("npc_jaina_intro_hor") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->CLOSE_GOSSIP_MENU();
                if (pCreature->AI())
                    pCreature->AI()->DoAction(ACTION_START_INTRO);
                pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                break;
        }
        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        pPlayer->ADD_GOSSIP_ITEM( 0, "Леди Джайна, мы готовы к следующей миссии!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    struct npc_jaina_intro_horAI : public ScriptedAI
    {
        npc_jaina_intro_horAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = me->GetInstanceScript();
            Reset();
        }
        
        InstanceScript* pInstance;
        
        uint32 Step;
        uint32 StepTimer;
        
        uint64 uiUther;
        uint64 uiLichKing;
        
        uint64 uiFrostmourne;
        
        void Reset()
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        
        void DoAction(const int32 actionId)
        {
            switch(actionId)
            {
                case ACTION_START_INTRO:
                    StartEvent();
                    break;
            }
        }
        
        void StartEvent()
        {
            if(!pInstance)
                return;
                
            Step = 1;
            StepTimer = 100;
        }
        
        void JumpNextStep(uint32 Time)
        {
            StepTimer = Time;
            Step++;
        }
        
        void Event()
        {
            switch(Step)
            {
                case 1:
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    JumpNextStep(2000);
                    break;
                case 2:
                    DoScriptText(SAY_JAINA_INTRO_1, me);
                    JumpNextStep(5000);
                    break;
                case 3:
                    DoScriptText(SAY_JAINA_INTRO_2, me);
                    JumpNextStep(5000);
                    break;
                case 4:
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    me->GetMotionMaster()->MovePoint(0, 5307.031f, 1997.920f, 709.341f);
                    JumpNextStep(10000);
                    break;
                case 5:
                    if(Creature* pTarget = me->SummonCreature(NPC_ALTAR_TARGET,5309.374f,2006.788f,711.615f,1.37f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,360000))
                    {
                        me->SetUInt64Value(UNIT_FIELD_TARGET, pTarget->GetGUID());
                        pTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    }
                    JumpNextStep(1000);
                    break;
                case 6:
                    DoScriptText(SAY_JAINA_INTRO_3, me);
                    JumpNextStep(5000);
                    break;
                case 7:
                    DoCast(me, SPELL_CAST_VISUAL);
                    DoScriptText(SAY_JAINA_INTRO_4, me);
                    JumpNextStep(3000);
                    break;
                case 8:
                    DoCast(me, SPELL_FROSTMOURNE_SOUNDS);
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_FROSTMOURNE), true);
                    JumpNextStep(12000);
                    break;
                case 9:
                    if(Creature* pUther = me->SummonCreature(NPC_UTHER,5308.228f,2003.641f,709.341f,4.17f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,360000))
                    {
                        pUther->GetMotionMaster()->MoveIdle();
                        pUther->SetReactState(REACT_PASSIVE);
                        uiUther = pUther->GetGUID();
                        Step=24;
                        JumpNextStep(1000);
                    }
                    break;
                case 10:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_A_1, pUther);
                    JumpNextStep(3000);
                    break;
                case 11:
                    DoScriptText(SAY_JAINA_INTRO_5, me);
                    JumpNextStep(5000);
                    break;
                case 12:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_A_2, pUther);
                    JumpNextStep(7000);
                    break;
                case 13:
                    DoScriptText(SAY_JAINA_INTRO_6, me);
                    JumpNextStep(7000);
                    break;
                case 14:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_A_3, pUther);
                    JumpNextStep(10000);
                    break;
                case 15:
                    DoScriptText(SAY_JAINA_INTRO_7, me);
                    JumpNextStep(5000);
                    break;
                case 16:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_A_4, pUther);
                    JumpNextStep(12000);
                    break;
                case 17:
                    DoScriptText(SAY_JAINA_INTRO_8, me);
                    JumpNextStep(6000);
                    break;
                case 18:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_A_5, pUther);
                    JumpNextStep(12000);
                    break;
                case 19:
                    DoScriptText(SAY_JAINA_INTRO_9, me);
                    JumpNextStep(11000);
                    break;
                case 20:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_A_6, pUther);
                    JumpNextStep(24000);
                    break;
                case 21:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_A_7, pUther);
                    JumpNextStep(5000);
                    break;
                case 22:
                    DoScriptText(SAY_JAINA_INTRO_10, me);
                    JumpNextStep(5000);
                    break;
                case 23:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                    {
                        pUther->HandleEmoteCommand(EMOTE_ONESHOT_NO);
                        DoScriptText(SAY_UTHER_INTRO_A_8, pUther);
                    }
                    JumpNextStep(12000);
                    break;
                case 24:
                    DoScriptText(SAY_JAINA_INTRO_11, me);
                    JumpNextStep(2000);
                    break;
                case 25:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                    {
                        pUther->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
                        DoScriptText(SAY_UTHER_INTRO_A_9, pUther);
                    }
                    JumpNextStep(2000);
                    break;
                case 26:
                    if (Creature* pLichKing = me->SummonCreature(NPC_LICH_KING_EVENT, 5362.469f,2062.342f,707.695f,3.97f, TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        pLichKing->GetMotionMaster()->MovePoint(0, 5314.881f, 2012.496f, 709.341f);
                        pLichKing->SetReactState(REACT_PASSIVE);
                        uiLichKing = pLichKing->GetGUID();
                    }
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), true);
                    JumpNextStep(1500);
                    break;
                case 27:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), false);
                    JumpNextStep(5000);
                    break;
                case 28:                   
                    if (Creature* pLichKing = me->GetCreature(*me, uiLichKing))
                        DoScriptText(SAY_LK_INTRO_1, pLichKing);
                    
                    JumpNextStep(3000);
                    break;
                case 29:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        pUther->CastSpell(pUther, SPELL_UTHER_DESPAWN, true);
                    
                    JumpNextStep(3000);
                    break;
                case 30:
                    if (Creature* pLichKing = me->GetCreature(*me, uiLichKing))
                        DoScriptText(SAY_LK_INTRO_2, pLichKing);
                        
                    JumpNextStep(10000);
                    break;
                case 31:
                    if (Creature* pLichKing = me->GetCreature(*me, uiLichKing))
                    {
                        pLichKing->CastSpell(pLichKing, SPELL_TAKE_FROSTMOURNE, true);
                        pInstance->HandleGameObject(pInstance->GetData64(DATA_FROSTMOURNE), false);
                        pLichKing->CastSpell(pLichKing, SPELL_FROSTMOURNE_VISUAL, false);
                    }
                    
                    JumpNextStep(2000);
                    break;
                case 32:
                    if(GameObject* pFrostmourne = ObjectAccessor::GetGameObject(*me, pInstance->GetData64(DATA_FROSTMOURNE)))
                        pFrostmourne->SetPhaseMask(0, true);
                    
                    me->RemoveAurasDueToSpell(SPELL_FROSTMOURNE_SOUNDS);
                    JumpNextStep(5000);
                    break;
                case 33:
                    if (Creature* pLichKing = me->GetCreature(*me, uiLichKing))
                    {
                        DoScriptText(SAY_LK_INTRO_3, pLichKing);
                        pLichKing->GetMotionMaster()->MovePoint(0, 5362.917480f, 2062.307129f, 707.695374f);
                    }
                        
                    if (Creature* pFalric = me->SummonCreature(NPC_FALRIC, 5337.578f,1979.716f,709.319f,2.348f, TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        pFalric->CastSpell(pFalric, SPELL_BOSS_SPAWN_AURA, false);
                    }
                    
                    if (Creature* pMarwyn = me->SummonCreature(NPC_MARWYN, 5281.414f,2033.164f,709.319f,5.509f, TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        pMarwyn->CastSpell(pMarwyn, SPELL_BOSS_SPAWN_AURA, false);
                    }
                    JumpNextStep(5000);
                    break;
                case 34:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), true);
                    JumpNextStep(1500);
                    break;
                case 35:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), false);
                    JumpNextStep(1500);
                    break;
                case 36:
                    if (Creature* pFalric = me->GetCreature(*me, pInstance->GetData64(DATA_FALRIC)))
                        DoScriptText(SAY_FALRIC_INTRO_1, pFalric);
                    JumpNextStep(3000);
                    break;
                case 37:
                    if (Creature* pMarwyn = me->GetCreature(*me, pInstance->GetData64(DATA_MARWYN)))
                        DoScriptText(SAY_MARWYN_INTRO_1, pMarwyn);
                    JumpNextStep(3000);
                    break;
                case 38:
                    DoScriptText(SAY_JAINA_INTRO_END, me);
                    me->GetMotionMaster()->MovePoint(0, 5362.917480f, 2062.307129f, 707.695374f);
                    JumpNextStep(8000);
                    break;
                case 39:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), true);
                    JumpNextStep(1500);
                    break;
                case 40:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), false);
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_ICECROWN_DOOR), false);
                    JumpNextStep(3000);
                    break;
                case 41:
                    if (Creature* pFalric = me->GetCreature(*me, pInstance->GetData64(DATA_FALRIC)))
                        DoScriptText(SAY_FALRIC_INTRO_2, pFalric);
                    JumpNextStep(2000);
                    break;
            }
        }
        
        void UpdateAI(const uint32 diff)
        {
            if(!pInstance)
                return;
                
            if(StepTimer < diff)
                Event();
            else StepTimer -= diff;
            
            return;
        }
    };
    
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_jaina_intro_horAI(pCreature);
    }
};

class npc_sylvana_intro_hor : public CreatureScript
{
public:
    npc_sylvana_intro_hor() : CreatureScript("npc_sylvana_intro_hor") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->CLOSE_GOSSIP_MENU();
                if (pCreature->AI())
                    pCreature->AI()->DoAction(ACTION_START_INTRO);
                pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                break;
        }
        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        pPlayer->ADD_GOSSIP_ITEM( 0, "Леди Сильвана, мы готовы к следующей миссии!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    struct npc_sylvana_intro_horAI : public ScriptedAI
    {
        npc_sylvana_intro_horAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
            pInstance = me->GetInstanceScript();
            Reset();
        }
        
        InstanceScript* pInstance;
        
        uint32 Step;
        uint32 StepTimer;
        
        uint64 uiUther;
        uint64 uiLichKing;
        
        uint64 uiFrostmourne;
        
        void Reset()
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        
        void DoAction(const int32 actionId)
        {
            switch(actionId)
            {
                case ACTION_START_INTRO:
                    StartEvent();
                    break;
            }
        }
        
        void StartEvent()
        {
            if(!pInstance)
                return;
                
            Step = 1;
            StepTimer = 100;
        }
        
        void JumpNextStep(uint32 Time)
        {
            StepTimer = Time;
            Step++;
        }
        
        void Event()
        {
            switch(Step)
            {
                case 1:
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    JumpNextStep(2000);
                    break;
                case 2:
                    DoScriptText(SAY_SYLVANA_INTRO_1, me);
                    JumpNextStep(8500);
                    break;
                case 3:
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    me->GetMotionMaster()->MovePoint(0, 5307.031f, 1997.920f, 709.341f);
                    JumpNextStep(10000);
                    break;
                case 4:
                    if(Creature* pTarget = me->SummonCreature(NPC_ALTAR_TARGET,5309.374f,2006.788f,711.615f,1.37f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,360000))
                    {
                        me->SetUInt64Value(UNIT_FIELD_TARGET, pTarget->GetGUID());
                        pTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    }
                    JumpNextStep(1000);
                    break;
                case 5:
                    DoScriptText(SAY_SYLVANA_INTRO_2, me);
                    JumpNextStep(6000);
                    break;
                case 6:
                    DoCast(me, SPELL_CAST_VISUAL);
                    DoScriptText(SAY_SYLVANA_INTRO_3, me);
                    JumpNextStep(3000);
                    break;
                case 7:
                    DoCast(me, SPELL_FROSTMOURNE_SOUNDS);
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_FROSTMOURNE), true);
                    JumpNextStep(8000);
                    break;
                case 8:
                    if(Creature* pUther = me->SummonCreature(NPC_UTHER,5308.228f,2003.641f,709.341f,4.17f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,360000))
                    {
                        pUther->GetMotionMaster()->MoveIdle();
                        pUther->SetReactState(REACT_PASSIVE);
                        uiUther = pUther->GetGUID();
                        //Step=24;
                        JumpNextStep(1000);
                    }
                    break;
                case 9:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_H_1, pUther);
                    JumpNextStep(10000);
                    break;
                case 10:
                    DoScriptText(SAY_SYLVANA_INTRO_4, me);
                    JumpNextStep(3000);
                    break;
                case 11:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_H_2, pUther);
                    JumpNextStep(6000);
                    break;
                case 12:
                    DoScriptText(SAY_SYLVANA_INTRO_5, me);
                    JumpNextStep(5000);
                    break;
                case 13:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_H_3, pUther); 
                    JumpNextStep(19000);
                    break;
                case 14:
                    DoScriptText(SAY_SYLVANA_INTRO_6, me); 
                    JumpNextStep(2000);
                    break;
                case 15:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_H_4, pUther);
                    JumpNextStep(20000);
                    break;
                case 16:
                    DoScriptText(SAY_SYLVANA_INTRO_7, me);
                    JumpNextStep(3000);
                    break;
                case 17:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_H_5, pUther);
                    JumpNextStep(11000);
                    break;
                case 18:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        DoScriptText(SAY_UTHER_INTRO_H_6, pUther);
                    JumpNextStep(9000);
                    break;
                case 19:
                    DoScriptText(SAY_SYLVANA_INTRO_8, me);
                    JumpNextStep(2100);
                    break;
                case 20:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                    {
                        pUther->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_COWER);
                        DoScriptText(SAY_UTHER_INTRO_H_7, pUther);
                    }
                    JumpNextStep(2000);
                    break;
                case 21:
                    if (Creature* pLichKing = me->SummonCreature(NPC_LICH_KING_EVENT, 5362.469f,2062.342f,707.695f,3.97f, TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        pLichKing->GetMotionMaster()->MovePoint(0, 5314.881f, 2012.496f, 709.341f);
                        pLichKing->SetReactState(REACT_PASSIVE);
                        uiLichKing = pLichKing->GetGUID();
                    }
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), true);
                    JumpNextStep(1500);
                    break;
                case 22:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), false);
                    JumpNextStep(5000);
                    break;
                case 23:                   
                    if (Creature* pLichKing = me->GetCreature(*me, uiLichKing))
                        DoScriptText(SAY_LK_INTRO_1, pLichKing);
                    
                    JumpNextStep(3000);
                    break;
                case 24:
                    if (Creature* pUther = me->GetCreature(*me, uiUther))
                        pUther->CastSpell(pUther, SPELL_UTHER_DESPAWN, false);
                    
                    JumpNextStep(3000);
                    break;
                case 25:
                    if (Creature* pLichKing = me->GetCreature(*me, uiLichKing))
                        DoScriptText(SAY_LK_INTRO_2, pLichKing);
                        
                    JumpNextStep(10000);
                    break;
                case 26:
                    if (Creature* pLichKing = me->GetCreature(*me, uiLichKing))
                    {
                        pLichKing->CastSpell(pLichKing, SPELL_TAKE_FROSTMOURNE, true);
                        pInstance->HandleGameObject(pInstance->GetData64(DATA_FROSTMOURNE), false);
                        pLichKing->CastSpell(pLichKing, SPELL_FROSTMOURNE_VISUAL, false);
                    }
                    
                    JumpNextStep(2000);
                    break;
                case 27:
                    if(GameObject* pFrostmourne = ObjectAccessor::GetGameObject(*me, pInstance->GetData64(DATA_FROSTMOURNE)))
                        pFrostmourne->SetPhaseMask(0, true);
                    
                    me->RemoveAurasDueToSpell(SPELL_FROSTMOURNE_SOUNDS);
                    JumpNextStep(5000);
                    break;
                case 28:
                    if (Creature* pLichKing = me->GetCreature(*me, uiLichKing))
                    {
                        DoScriptText(SAY_LK_INTRO_3, pLichKing);
                        pLichKing->GetMotionMaster()->MovePoint(0, 5362.917480f, 2062.307129f, 707.695374f);
                    }
                        
                    if (Creature* pFalric = me->SummonCreature(NPC_FALRIC, 5337.578f,1979.716f,709.319f,2.348f, TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        pFalric->CastSpell(pFalric, SPELL_BOSS_SPAWN_AURA, false);
                    }
                    
                    if (Creature* pMarwyn = me->SummonCreature(NPC_MARWYN, 5281.414f,2033.164f,709.319f,5.509f, TEMPSUMMON_MANUAL_DESPAWN))
                    {
                        pMarwyn->CastSpell(pMarwyn, SPELL_BOSS_SPAWN_AURA, false);
                    }
                    JumpNextStep(5000);
                    break;
                case 29:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), true);
                    JumpNextStep(1500);
                    break;
                case 30:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), false);
                    JumpNextStep(1500);
                    break;
                case 31:
                    if (Creature* pFalric = me->GetCreature(*me, pInstance->GetData64(DATA_FALRIC)))
                        DoScriptText(SAY_FALRIC_INTRO_1, pFalric);
                    JumpNextStep(3000);
                    break;
                case 32:
                    if (Creature* pMarwyn = me->GetCreature(*me, pInstance->GetData64(DATA_MARWYN)))
                        DoScriptText(SAY_MARWYN_INTRO_1, pMarwyn);
                    JumpNextStep(3000);
                    break;
                case 33:
                    DoScriptText(SAY_SYLVANA_INTRO_END, me);
                    me->GetMotionMaster()->MovePoint(0, 5362.917480f, 2062.307129f, 707.695374f);
                    JumpNextStep(8000);
                    break;
                case 34:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), true);
                    JumpNextStep(1500);
                    break;
                case 35:
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_IMPENETRABLE_DOOR), false);
                    pInstance->HandleGameObject(pInstance->GetData64(DATA_ICECROWN_DOOR), false);
                    JumpNextStep(1500);
                    break;
                case 36:
                    if (Creature* pFalric = me->GetCreature(*me, pInstance->GetData64(DATA_FALRIC)))
                        DoScriptText(SAY_FALRIC_INTRO_2, pFalric);
                    JumpNextStep(2000);
                    break;
            }
        }
        
        void UpdateAI(const uint32 diff)
        {
            if(!pInstance)
                return;
                
            if(StepTimer < diff)
                Event();
            else StepTimer -= diff;
            
            return;
        }
    };
    
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_sylvana_intro_horAI(pCreature);
    }
};

void AddSC_halls_of_reflection()
{
    new npc_jaina_intro_hor();
    new npc_sylvana_intro_hor();
}
