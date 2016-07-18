#include "AStarPathFind.h"



AStarPathFind::AStarPathFind(uint** arr, uint max_w, uint max_h, std::vector <SRoom>* rooms) : 
    g_MazeArr(arr), m_MaxWidth(max_w), m_MaxHeight(max_h), m_RoomsVec(rooms)
{
}


AStarPathFind::~AStarPathFind()
{
}


bool AStarPathFind::AreAllRoomsConnectedToRoot(SRoom root, std::vector <SRoom*>& unconnected) //todo
{
    uint g = 10;

    if (root.RoomDoors.size() < 1)
        return false;

    m_StartPos = root.RoomDoors[0];
    for (SRoom room : *m_RoomsVec)
    {
        if (root == room)
            continue;

        if (room.RoomDoors.size() < 1)
        {
            unconnected.push_back(&room);
            continue;
        }

        g = 10;
        m_StartPos = room.RoomDoors[0];
        SPoint pt = m_StartPos;
        while (true)
        {
            std::vector <SWeight> open_paths;
            CheckAStarOpenPaths(pt, g, open_paths);
            if (AreDoorsNearby(pt))
                continue;
            SWeight w = open_paths[0];
            for (int i = 1; i < open_paths.size(); i++)
            {
                if (w.Weight > open_paths[i].Weight)
                    w = open_paths[i];
            }
            pt = w.Pos;
            g += 10;
        }

    }

    return true;
}

void AStarPathFind::CheckAStarOpenPaths(const SPoint& pt, const uint& g_point, std::vector <SWeight>& out)
{
    uint nx, ny;
    nx = pt.X + 1; ny = pt.Y;
    if (g_MazeArr[nx][ny] == Corridor)
    {
        SPoint pt2(nx, ny);
        out.push_back(SWeight(pt2, CalcAStarWeight(pt2, g_point), g_point));
    }

    nx = pt.X - 1;
    if (g_MazeArr[nx][ny] == Corridor)
    {
        SPoint pt2(nx, ny);
        out.push_back(SWeight(pt2, CalcAStarWeight(pt2, g_point), g_point));
    }

    nx = pt.X; ny = pt.Y + 1;
    if (g_MazeArr[nx][ny] == Corridor)
    {
        SPoint pt2(nx, ny);
        out.push_back(SWeight(pt2, CalcAStarWeight(pt2, g_point), g_point));
    }

    ny = pt.Y - 1;
    if (g_MazeArr[nx][ny] == Corridor)
    {
        SPoint pt2(nx, ny);
        out.push_back(SWeight(pt2, CalcAStarWeight(pt2, g_point), g_point));
    }
}

bool AStarPathFind::AreDoorsNearby(SPoint& pt)
{
    uint nx, ny;
    nx = pt.X + 1; ny = pt.Y;
    if (g_MazeArr[nx][ny] == Doors)
    {
        pt.X = nx;
        pt.Y = ny;
        return true;
    }

    nx = pt.X - 1;
    if (g_MazeArr[nx][ny] == Doors)
    { 
        pt.X = nx;
        pt.Y = ny;
        return true;
    }

    nx = pt.X; ny = pt.Y + 1;
    if (g_MazeArr[nx][ny] == Doors)
    {
        pt.X = nx;
        pt.Y = ny;
        return true;
    }

    ny = pt.Y - 1;
    if (g_MazeArr[nx][ny] == Doors)
    {
        pt.X = nx;
        pt.Y = ny;
        return true;
    }

    return false;
}

uint AStarPathFind::CalcAStarWeight(const SPoint& pt, const uint& g_weight)
{
    uint weight = g_weight + std::abs(((int)pt.X - (int)m_EndPos.X)) + std::abs(((int)pt.Y) - ((int)m_EndPos.Y));
    return weight;
}