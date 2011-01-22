/*
 * Copyright (C) 2011 TrioraCore <http://www.trioracore.ru/>
 */

#ifndef DEF_HALLS_OF_REFLECTION_H
#define DEF_HALLS_OF_REFLECTION_H

enum Data
{
    ACTION_START_INTRO,
    DATA_WAVE_COUNT,
};

enum Data64
{
    DATA_FROSTMOURNE,
    DATA_ICECROWN_DOOR,
    DATA_IMPENETRABLE_DOOR,
    
    DATA_FALRIC,
    DATA_MARWYN,
};

enum Creatures
{
    NPC_UTHER                                     = 37225,
    NPC_JAINA_PART1                               = 37221,
    NPC_SYLVANAS_PART1                            = 37223,
    NPC_LICH_KING_EVENT                           = 37226,
    NPC_FALRIC                                    = 38112,
    NPC_MARWYN                                    = 38113,
    
    NPC_ALTAR_TARGET                              = 37704,
    
    NPC_WAVE_MERCENARY                            = 38177,
    NPC_WAVE_FOOTMAN                              = 38173,
    NPC_WAVE_RIFLEMAN                             = 38176,
    NPC_WAVE_PRIEST                               = 38175,
    NPC_WAVE_MAGE                                 = 38172,
    NPC_WAVE_HALLUCINATION                        = 38567,
};

enum GO
{
    GO_FROSTMOURNE                                = 202302,
    GO_FROSTMOURNE_ALTAR                          = 202236,
    
    GO_ICECROWN_DOOR                              = 201976,
    GO_IMPENETRABLE_DOOR                          = 197341,
};

enum WorldState
{
    WORLD_STATE_HOR                               = 4884,
    WORLD_STATE_HOR_WAVE_COUNT                    = 4882,
};

struct Locations
{
    float x, y, z, o;
    uint32 id;
};

static Locations SpawnLoc[]=
{
    //Wing 01
    {5277.409f, 1993.161f, 707.694f, 0.05f}, //27
    {5301.876f, 2041.699f, 707.694f, 4.71f}, //1
    {5339.830f, 2020.887f, 707.694f, 3.14f}, //13
    {5311.041f, 2042.935f, 707.694f, 4.71f}, //3
    {5314.750f, 2039.969f, 707.694f, 4.71f}, //4
    {5342.823f, 2003.801f, 707.694f, 3.14f}, //10
    {5311.579f, 1972.823f, 707.694f, 1.62f}, //16
    
    //Wing 02
    {5272.491f, 2005.673f, 707.694f, 0.05f}, //23
    {5302.669f, 1973.050f, 707.694f, 1.62f}, //18
    {5346.187f, 2008.058f, 707.694f, 3.14f}, //9
    {5319.752f, 2041.321f, 707.694f, 4.71f}, //5
    {5344.882f, 1998.714f, 707.694f, 3.14f}, //11
    {5340.552f, 1994.735f, 707.694f, 3.14f}, //12
    {5306.441f, 2040.358f, 707.694f, 4.71f}, //2
    
    //Wing 03
    {5273.297f, 2014.009f, 707.694f, 0.05f}, //25
    {5316.062f, 1970.777f, 707.694f, 1.62f}, //15
    {5322.498f, 2037.415f, 707.694f, 4.71f}, //6
    {5307.087f, 1970.065f, 707.694f, 1.62f}, //17
    {5342.460f, 2012.391f, 707.694f, 3.14f}, //8
    {5297.601f, 1971.420f, 707.694f, 1.62f}, //19
    {5295.668f, 1975.853f, 707.694f, 1.62f}, //20
    
    //Wing 04
    {5273.661f, 1996.767f, 707.694f, 0.05f}, //21
    {5275.228f, 2001.275f, 707.694f, 0.05f}, //22
    {5344.153f, 2017.753f, 707.694f, 3.14f}, //7
    {5275.310f, 2009.686f, 707.694f, 0.05f}, //24
    {5319.835f, 1975.177f, 707.694f, 1.62f}, //14
    {5277.445f, 2017.197f, 707.694f, 0.05f}, //26
    {5298.198f, 2037.762f, 707.694f, 4.71f}  //0
};

#endif
