/*
 * Copyright (C) 2011 TrioraCore <http://www.trioracore.ru/>
 * Copyright (C) 2011 TrioraCore <http://www.trioracore.ru/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* Script Data Start
SDName: Dalaran
SDAuthor: WarHead, MaXiMiUS
SD%Complete: 99%
SDComment: For what is 63990+63991? Same function but don't work correct...
SDCategory: Dalaran
Script Data End */

#include "ScriptPCH.h"

/*******************************************************
 * npc_mageguard_dalaran
 *******************************************************/

enum Spells
{
    SPELL_TRESPASSER_A = 54028,
    SPELL_TRESPASSER_H = 54029
};

enum NPCs // All outdoor guards are within 35.0f of these NPCs
{
    NPC_APPLEBOUGH_A = 29547,
    NPC_SWEETBERRY_H = 29715,
};

class npc_mageguard_dalaran : public CreatureScript
{
public:
    npc_mageguard_dalaran() : CreatureScript("npc_mageguard_dalaran") { }

    struct npc_mageguard_dalaranAI : public Scripted_NoMovementAI
    {
        npc_mageguard_dalaranAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
        {
            pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            pCreature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_NORMAL, true);
            pCreature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);
        }

        void Reset(){}

        void EnterCombat(Unit* /*pWho*/){}

        void AttackStart(Unit* /*pWho*/){}

        void MoveInLineOfSight(Unit *pWho)
        {
            if (!pWho || !pWho->IsInWorld() || pWho->GetZoneId() != 4395)
                return;

            if (!me->IsWithinDist(pWho, 65.0f, false))
                return;

            Player *pPlayer = pWho->GetCharmerOrOwnerPlayerOrPlayerItself();

            if (!pPlayer || pPlayer->isGameMaster() || pPlayer->IsBeingTeleported())
                return;
                
            if (pWho->HasAura(70973) || pWho->HasAura(70974) || pWho->HasAura(70971) || pWho->HasAura(70972))
                return;

            switch (me->GetEntry())
            {
                case 29254:
                    if (pPlayer->GetTeam() == HORDE)              // Horde unit found in Alliance area
                    {
                        if (GetClosestCreatureWithEntry(me, NPC_APPLEBOUGH_A, 32.0f))
                        {
                            if (me->isInBackInMap(pWho, 12.0f))   // In my line of sight, "outdoors", and behind me
                                DoCast(pWho, SPELL_TRESPASSER_A); // Teleport the Horde unit out
                        }
                        else                                      // In my line of sight, and "indoors"
                            DoCast(pWho, SPELL_TRESPASSER_A);     // Teleport the Horde unit out
                    }
                    break;
                case 29255:
                    if (pPlayer->GetTeam() == ALLIANCE)           // Alliance unit found in Horde area
                    {
                        if (GetClosestCreatureWithEntry(me, NPC_SWEETBERRY_H, 32.0f))
                        {
                            if (me->isInBackInMap(pWho, 12.0f))   // In my line of sight, "outdoors", and behind me
                                DoCast(pWho, SPELL_TRESPASSER_H); // Teleport the Alliance unit out
                        }
                        else                                      // In my line of sight, and "indoors"
                            DoCast(pWho, SPELL_TRESPASSER_H);     // Teleport the Alliance unit out
                    }
                    break;
            }
            me->SetOrientation(me->GetHomePosition().GetOrientation());
            return;
        }

        void UpdateAI(const uint32 /*diff*/){}
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_mageguard_dalaranAI(creature);
    }
};

/*######
## npc_hira_snowdawn
######*/

enum eHiraSnowdawn
{
    SPELL_COLD_WEATHER_FLYING                   = 54197
};

#define GOSSIP_TEXT_TRAIN_HIRA "I seek training to ride a steed."

class npc_hira_snowdawn : public CreatureScript
{
public:
    npc_hira_snowdawn() : CreatureScript("npc_hira_snowdawn") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (!pCreature->isVendor() || !pCreature->isTrainer())
            return false;

        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_TRAIN_HIRA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

        if (pPlayer->getLevel() >= 80 && pPlayer->HasSpell(SPELL_COLD_WEATHER_FLYING))
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_TRAIN)
            pPlayer->SEND_TRAINERLIST(pCreature->GetGUID());

        if (uiAction == GOSSIP_ACTION_TRADE)
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());

        return true;
    }
};

/*######
## npc_36776
######*/
enum eNPC_36776
{
    FACTION_ENEMY       = 14,
    QUEST_14457         = 14457,
    QUEST_24557         = 24557,
};

class npc_36776 : public CreatureScript
{
public:
    npc_36776() : CreatureScript("npc_36776") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                pCreature->setFaction(FACTION_ENEMY);
                pCreature->AI()->AttackStart(pPlayer);
            break;
        }
        return true;
    }
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if ((pPlayer->GetTeam() == ALLIANCE && pPlayer->GetQuestStatus(QUEST_14457) == QUEST_STATUS_INCOMPLETE) ||
            (pPlayer->GetTeam() == HORDE && pPlayer->GetQuestStatus(QUEST_24557) == QUEST_STATUS_INCOMPLETE))
                pPlayer->ADD_GOSSIP_ITEM( 0, "Ага! Попался!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_36776AI(pCreature);
    }

    struct npc_36776AI : public ScriptedAI
    {
        npc_36776AI(Creature *c) : ScriptedAI(c)
        {
            m_uiNormalFaction = c->getFaction();
        }

        uint32 m_uiNormalFaction;

        void Reset()
        {
            if (me->getFaction() != m_uiNormalFaction)
            {
                me->setFaction(m_uiNormalFaction);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            }
        }

        void AttackedBy(Unit* pAttacker)
        {
            if (me->getVictim())
                return;

            if (me->IsFriendlyTo(pAttacker))
                return;

            AttackStart(pAttacker);
        }
    };
};

/*######
## npc_36670
######*/
enum eNPC_36670
{
    QUEST_20439         = 20439,
    QUEST_24451         = 24451,
    SPELL_CREATE_BOOK   = 69722,
    
    SAY_01              = -1800071,
    
    SAY_02_1            = -1800072,
    SAY_03_1            = -1800073,
     
    SAY_02_2            = -1800074,
    SAY_03_2            = -1800075,
    
    NPC_36670           = 36670,
    NPC_36669           = 36669,
};

class npc_36670 : public CreatureScript
{
public:
    npc_36670() : CreatureScript("npc_36670") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->setFaction(35);
                pCreature->CastSpell(pPlayer, SPELL_CREATE_BOOK, true);
            break;
        }
        return true;
    }
    
    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if ((pPlayer->GetTeam() == ALLIANCE && pPlayer->GetQuestStatus(QUEST_20439) == QUEST_STATUS_INCOMPLETE) ||
            (pPlayer->GetTeam() == HORDE && pPlayer->GetQuestStatus(QUEST_24451) == QUEST_STATUS_INCOMPLETE))         
                pPlayer->ADD_GOSSIP_ITEM( 0, "Я готов получить книгу у магистра Хатореля.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID()); 
        
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }
    
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_36670AI (pCreature);
    }

    struct npc_36670AI : public ScriptedAI
    {
        npc_36670AI(Creature *pCreature) : ScriptedAI(pCreature) 
        {
        }
        
        uint32 StepTimer;
        uint32 Step;
        uint32 Start;
        uint64 uiPlayerGUID;
        
        void Reset()
        {
            Step = 0;
            Start = 0;
            uiPlayerGUID = 0;
        }
        
        void JumpNextStep(uint32 Time)
        {
            StepTimer = Time;
            Step++;
        }
        
        void StartEvent()
        {
            Step = 1;
            Start = 1;
            StepTimer = 100;
        }
        
        void Event()
        {
            switch(Step)
            {
                case 1:
                    DoScriptText(SAY_01, me);
                    JumpNextStep(4000);
                    break;
                case 2:
                    if (me->GetEntry() == NPC_36670)
                        DoScriptText(SAY_02_1, me);
                    else if (me->GetEntry() == NPC_36669)
                        DoScriptText(SAY_02_2, me);
                    JumpNextStep(1000);
                    break;
                case 3:
                    if (me->GetEntry() == NPC_36670)
                        DoScriptText(SAY_03_1, me);
                    else if (me->GetEntry() == NPC_36669)
                        DoScriptText(SAY_03_2, me);
                    me->RestoreFaction();
                    Step = 0;
                    break;
            }
        }
        
        void UpdateAI(const uint32 diff)
        {
            if (me->getFaction()==35 && Start != 1)
                StartEvent();
                
            if(StepTimer < diff && Start == 1)
                Event();
            else 
                StepTimer -= diff;

            return;
        }
    };
};

void AddSC_dalaran()
{
    new npc_mageguard_dalaran;
    new npc_hira_snowdawn;
    new npc_36776;
    new npc_36670;
}
