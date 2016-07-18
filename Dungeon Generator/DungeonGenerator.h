#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_DungeonGenerator.h"
#include "AStarPathFind.h"
#include "Misc.h"
#include <QGraphicsScene>
#include <QTime>
#include <vector>

class DungeonGenerator : public QMainWindow
{
    Q_OBJECT
public:
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
    void                        UncarveDungeon(int when_stop = -1); // if when_stop == -1 the uncarve to perfect dungeon
    void                        UncarveCorridor(uint x, uint y, int when_stop);
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



private:

    SPoint                      m_StartPos;
    SPoint                      m_EndPos;

    bool                        AreAllRoomsConnectedToRoot(SRoom root, std::vector <SRoom*>& unconnected); // if false 'unconnected' will be filled with romms that are not connected to root
    void                        CheckAStarOpenPaths(const SPoint& pt, const uint& g_weight, std::vector <SWeight>& out);
    bool                        AreDoorsNearby(SPoint& pt);
    uint                        CalcAStarWeight(const SPoint& pt, const uint& g_weight);
};