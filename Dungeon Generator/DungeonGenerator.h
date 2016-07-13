#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_DungeonGenerator.h"
#include <QGraphicsScene>
#include <QTime>
#include <vector>

typedef unsigned int uint;

class DungeonGenerator : public QMainWindow
{
    Q_OBJECT
private:
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
        Doors
    };

    struct SRoom
    {
        uint PosX;
        uint PosY;
        uint SizeX;
        uint SizeY;

        SRoom() : PosX(0), PosY(0), SizeX(0), SizeY(0) {}
        SRoom(uint x, uint y, uint size_x, uint size_y) :
            PosX(x), PosY(y), SizeX(size_x), SizeY(size_y) {}
        ~SRoom() {}
    };

    struct SRegion
    {
        std::vector <SRoom*> Rooms;
    };

public:

    /*
        TODO: Zobaczyæ co jest nie tak ze wspolrzednymi bo dziwnie dzialaja raz tak raz tak, mozliwe ze sa pomieszane gdzies.
    */

    DungeonGenerator(QWidget *parent = 0);
    ~DungeonGenerator();

protected:
    void                        InitGraphicsScene();
    void                        InitActions();
    void                        InitConnections();
    void                        InitMazeArray();
    void                        InitDirectionArrays();
    void                        InitDebugCombo();

    void                        ClearMazeArray();
    void                        DestroyMazeArray();
    void                        ShuffleDirArray(uint* arr, uint size);
    void                        DrawMazeFromArray(bool clear = true);
    void                        DrawDebug(int type);

    virtual bool                eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::DungeonGeneratorClass   ui;
    QGraphicsScene*             m_Scene;
    QAction*                    m_ActGenSnake;
    QAction*                    m_ActGenRecBack;
    QShortcut*                  m_GenDungeonSC;

    uint**                      m_MazeArr;
    uint                        m_DirXArr[9];
    uint                        m_DirYArr[9];
    uint                        m_DirOppositeArr[9];

    std::vector <SRoom>         m_RoomsVec;
    std::vector <SRegion>       m_RegionsVec;

    uint                        m_MaxWidth;
    uint                        m_MaxHeight;

    const uint                  TILE_SIZE;
    const QColor                TILE_BASE_COLOR;
    const QColor                TILE_BORDERS_COLOR;
    const QPen                  TILE_BORDERS;
    const QBrush                TILE_BASE;

    const float                 SCALE_ZOOM_IN;
    const float                 SCALE_ZOOM_OUT;

    // Mazes
    void                        GenMazeSnake();
    void                        GenMazeRecursiveBacktracking(uint pos_x, uint pos_y);
    int                         CheckNeighbours(uint dir, uint x, uint y);
    int                         CheckNeighbours(uint x, uint y);
    void                        GenRooms(int attempts);
    bool                        AreFieldsEmpty(uint x, uint y, uint size_x, uint size_y);
    void                        CarveRoom(uint x, uint y, uint size_x, uint size_y);
    void                        CarveCorridorsBetweenRooms(uint attempts = 0); // with attempts == 0, slow but check every possibility, with attempts > 0 faster but may result with empty spaces
    void                        ConnectRooms(int root = -1); // -1 mean that it will be randomly draw from m_RoomsVec
    void                        ConnectRoom(SRoom room);
    bool                        AreAllRoomsConnectedToRoot(SRoom root, std::vector <SRoom*> unconnected); // if false 'unconnected' will be filled with romms that are not connected to root
    void                        UncarveDungeon(uint when_stop = -1); // if when_stop == -1 the uncarve to perfect dungeon
    void                        UncarveCorridor(uint x, uint y);
    bool                        NextTileInCorridor(uint& nx, uint& ny); // false == end of corridor

private slots:

    // PushButtons
    void                        OnBtnNewClicked();
    void                        OnBtnZoomIn();
    void                        OnBtnZoomOut();
    void                        OnBtnDungeonGenerate();

    // CheckBoxes
    void                        OnDebugCheckBoxToggled(bool toggled);

    // ComboBoxes
    void                        OnDebugComboIndexChanged(int index);

    // SpinBoxes
    void                        OnSpinBoxesSizeValueChanged(int i);

};