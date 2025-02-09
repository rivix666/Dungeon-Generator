#pragma once
#include <vector>
typedef unsigned int uint;

enum EDirections
{
    N = 1,
    S = 2,
    E = 4,
    W = 8
};

enum ETileType
{
    SolidRock = 0,
    Room,
    Corridor,
    Doors,
    Nothing
};

struct SPoint
{
    uint X;
    uint Y;

    SPoint() : X(0), Y(0) {}
    SPoint(uint x, uint y) : X(x), Y(y) {}
    ~SPoint() {}

    bool operator==(const SPoint& r)
    {
        bool result = true;
        result = result && (X == r.X);
        result = result && (Y == r.Y);
        return result;
    }
};

struct SRoom
{
    uint PosX;
    uint PosY;
    uint SizeX;
    uint SizeY;

    std::vector <SPoint> RoomDoors;

    SRoom() : PosX(0), PosY(0), SizeX(0), SizeY(0) {}
    SRoom(uint x, uint y, uint size_x, uint size_y) :
        PosX(x), PosY(y), SizeX(size_x), SizeY(size_y) {}
    ~SRoom() {}

    bool operator==(const SRoom& r)
    {
        bool result = true;
        result = result && (PosX == r.PosX);
        result = result && (PosY == r.PosY);
        result = result && (SizeX == r.SizeX);
        result = result && (SizeY == r.SizeY);
        return result;
    }
};

// f == g + h;
struct SWeight
{
    SPoint Pos;
    uint Weight;
    uint G_Weight;

    SWeight() : Pos(SPoint()), Weight(0) {}
    SWeight(SPoint pt, uint w, uint g) : Pos(pt), Weight(w), G_Weight(g) {}
    ~SWeight() {}

    bool operator== (const SWeight& w) { return Weight == w.Weight; }
    bool operator< (const SWeight& w) { return Weight < w.Weight; }
    bool operator> (const SWeight& w) { return Weight > w.Weight; }
    bool operator!= (const SWeight& w) { return Weight != w.Weight; }
};

struct SRegion
{
    std::vector <SRoom*> Rooms;
};
