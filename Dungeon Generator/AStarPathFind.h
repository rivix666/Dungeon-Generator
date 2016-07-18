#pragma once
#include "Misc.h"

class AStarPathFind
{
public:
    AStarPathFind(uint** arr, uint max_w, uint max_h, std::vector <SRoom>* rooms);
    ~AStarPathFind();

    uint**                      g_MazeArr;
    uint                        m_MaxWidth;
    uint                        m_MaxHeight;

    std::vector <SRoom>*        m_RoomsVec;

    SPoint                      m_StartPos;
    SPoint                      m_EndPos;

    bool                        AreAllRoomsConnectedToRoot(SRoom root, std::vector <SRoom*>& unconnected); // if false 'unconnected' will be filled with romms that are not connected to root
    void                        CheckAStarOpenPaths(const SPoint& pt, const uint& g_weight, std::vector <SWeight>& out);
    bool                        AreDoorsNearby(SPoint& pt);
    uint                        CalcAStarWeight(const SPoint& pt, const uint& g_weight);
};

