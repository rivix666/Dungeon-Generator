#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_DungeonGenerator.h"
#include <QGraphicsScene>
#include <QTime>

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

public:
    DungeonGenerator(QWidget *parent = 0);
    ~DungeonGenerator();

protected:
    void                        InitGraphicsScene();
    void                        InitActions();
    void                        InitConnections();
    void                        InitMazeArray();
    void                        InitDirectionArrays();

    void                        ClearMazeArray();
    void                        DestroyMazeArray();
    void                        ShuffleDirArray(uint* arr, uint size);
    void                        DrawMazeFromArray();

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

    const uint                  TILE_SIZE;
    const uint                  MAX_WIDTH;
    const uint                  MAX_HEIGHT;

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
    void                        GenRooms(int attempts);
    bool                        AreFieldsEmpty(uint x, uint y, uint size_x, uint size_y);
    void                        TakeFields(uint x, uint y, uint size_x, uint size_y);

private slots:

    // Others
    void                        OnBtnNewClicked();
    void                        OnBtnZoomIn();
    void                        OnBtnZoomOut();
    void                        OnBtnDungeonGenerate();

};