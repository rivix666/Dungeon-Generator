#include "DungeonGenerator.h"
#include <math.h>
#include <ctime>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QKeyEvent>

DungeonGenerator::DungeonGenerator(QWidget *parent)
    : QMainWindow(parent), MAX_WIDTH(50),
    MAX_HEIGHT(50), TILE_SIZE(15), TILE_BASE_COLOR("#BDB8AE"),
    TILE_BORDERS_COLOR("#949188"), TILE_BORDERS(QBrush(TILE_BORDERS_COLOR), 2),
    TILE_BASE(TILE_BASE_COLOR), SCALE_ZOOM_IN(1.1f), SCALE_ZOOM_OUT(0.9f)
{
    ui.setupUi(this);
    InitGraphicsScene();
    InitActions();
    InitConnections();
    InitMazeArray();
    InitDirectionArrays();

    qsrand(QTime::currentTime().msec());
    ui.graphicsView->installEventFilter(this);
}

DungeonGenerator::~DungeonGenerator()
{
    DestroyMazeArray();
}

// Init
//////////////////////////////////////////////////////////////////////////
void DungeonGenerator::InitGraphicsScene()
{
    m_Scene = new QGraphicsScene(this);
    m_Scene->setBackgroundBrush(QBrush(QColor(Qt::black)));
    ui.graphicsView->setScene(m_Scene);
    ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
}

void DungeonGenerator::InitActions()
{
    m_ActGenSnake = new QAction(tr("Generate Maze Snake"), this);
    m_ActGenRecBack = new QAction(tr("Generate Recursive Backtraced Maze"), this);

    m_ActGenSnake->setShortcut(QKeySequence(Qt::Key_1));
    m_ActGenRecBack->setShortcut(QKeySequence(Qt::Key_2));
}

void DungeonGenerator::InitConnections()
{
    // Others
    connect(ui.pushButton_New, &QPushButton::clicked, this, &DungeonGenerator::OnBtnNewClicked);
    connect(ui.pushButton_zoomIn, &QPushButton::clicked, this, &DungeonGenerator::OnBtnZoomIn);
    connect(ui.pushButton_zoomOut, &QPushButton::clicked, this, &DungeonGenerator::OnBtnZoomOut);

    // Actions
    connect(m_ActGenSnake, &QAction::triggered, this, [=] { GenMazeSnake(); });
    connect(m_ActGenRecBack, &QAction::triggered, this, [=] { ClearMazeArray(); GenMazeRecursiveBacktracking(1, 1); DrawMazeFromArray(); });
}

void DungeonGenerator::InitMazeArray()
{
    m_MazeArr = new uint*[MAX_WIDTH];
    for (int i = 0; i < MAX_WIDTH; i++)
    {
        m_MazeArr[i] = new uint[MAX_HEIGHT];
    }

    ClearMazeArray();
}

void DungeonGenerator::InitDirectionArrays()
{
    m_DirXArr[N] = 0;
    m_DirXArr[E] = 1;
    m_DirXArr[S] = 0;
    m_DirXArr[W] = -1;

    m_DirYArr[N] = -1;
    m_DirYArr[E] = 0;
    m_DirYArr[S] = 1;
    m_DirYArr[W] = 0;

    m_DirOppositeArr[N] = S;
    m_DirOppositeArr[E] = W;
    m_DirOppositeArr[S] = N;
    m_DirOppositeArr[W] = E;
}

// Others
//////////////////////////////////////////////////////////////////////////
void DungeonGenerator::ClearMazeArray()
{
    for (int i = 0; i < MAX_WIDTH; i++)
    {
        for (int j = 0; j < MAX_HEIGHT; j++)
        {
            m_MazeArr[i][j] = 0;
        }
    }
}

void DungeonGenerator::DestroyMazeArray()
{
    for (int i = 0; i < MAX_WIDTH; i++)
    {
        delete[] m_MazeArr[i];
    }

    delete[] m_MazeArr;
}

void DungeonGenerator::ShuffleDirArray(uint* arr, uint size)
{
    for (int i = 0; i < (size - 1); i++)
    {
        int r = i + (qrand() % (size - i));
        int temp = arr[i];
        arr[i] = arr[r];
        arr[r] = temp;
    }
}

void DungeonGenerator::DrawMazeFromArray()
{
    m_Scene->clear();
 #ifdef _DEBUG | DEBUG
     for (int i = 0; i < MAX_WIDTH; i++)
     {
         QString str = "";
         for (int j = 0; j < MAX_HEIGHT; j++)
         {
             str += QString::number(m_MazeArr[i][j]);
             if (m_MazeArr[i][j] == 0)
             {
                 QRect rect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                 m_Scene->addRect(rect, TILE_BORDERS, TILE_BASE);
             }
         }
         qDebug() << str;
     }
 #else
     for (int i = 0; i < MAX_WIDTH; i++)
     {
         for (int j = 0; j < MAX_HEIGHT; j++)
         {
             if (m_MazeArr[i][j] == 0)
             {
                 QRect rect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                 m_Scene->addRect(rect, TILE_BORDERS, TILE_BASE);
             }
         }
     }
 #endif
}

// Mazes
void DungeonGenerator::GenMazeSnake()
{
    int tiles_per_x = MAX_WIDTH;
    int tiles_per_y = MAX_HEIGHT;
    int x_offset = 0;
    int y_offset = 0;

    m_Scene->clear();
    for (int i = 0, h = 0; i < tiles_per_y; i += 2, h++) // h for different supplys rect pos
    {
        for (int j = 0; j < tiles_per_x; j++)
        {
            QRect rect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            m_Scene->addRect(rect, TILE_BORDERS, TILE_BASE);
        }

        if (h % 2 == 0)
        {
            QRect supply_rect((tiles_per_x - 1) * TILE_SIZE, (i + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            m_Scene->addRect(supply_rect, TILE_BORDERS, TILE_BASE);
        }
        else
        {
            QRect supply_rect(0, (i + 1) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
            m_Scene->addRect(supply_rect, TILE_BORDERS, TILE_BASE);
        }
    }
}

void DungeonGenerator::GenMazeRecursiveBacktracking(uint pos_x, uint pos_y)
{
    uint nx, ny;
    uint directions[4]{ N, S, E, W };
    for(int i = 0; i < 100; i++)
    {
        ShuffleDirArray(directions, 4);
        for (uint dir : directions)
        {
            nx = pos_x + m_DirXArr[dir];
            ny = pos_y + m_DirYArr[dir];

            if (((nx < MAX_WIDTH - 1) & (nx >= 1)) & ((ny < MAX_HEIGHT - 1) & (ny >= 1)))
            {
                 if (m_MazeArr[nx][ny] == 0)
                 {
                     if (CheckNeighbours(dir, nx, ny) > 4) // 2 with cross walls
                     {
                         m_MazeArr[nx][ny] = 1;
                         GenMazeRecursiveBacktracking(nx, ny);
                     }
                 }
            }
        }
    }
}


int DungeonGenerator::CheckNeighbours(uint dir, uint x, uint y)
{
    int walls = 0;
    switch (dir)
    {
        case N:
        {
            if(m_MazeArr[x - 1][y] == 0)walls++;
            if(m_MazeArr[x + 1][y] == 0)walls++;
            if(m_MazeArr[x][y - 1] == 0)walls++;
            if (m_MazeArr[x - 1][y - 1] == 0)walls++; // delete this two ever case to unlock cross walls
            if (m_MazeArr[x + 1][y - 1] == 0)walls++;

            break;
        }
        case S:
        {
            if(m_MazeArr[x - 1][y] == 0)walls++;
            if(m_MazeArr[x + 1][y] == 0)walls++;
            if(m_MazeArr[x][y + 1] == 0)walls++;
            if (m_MazeArr[x - 1][y + 1] == 0)walls++;
            if (m_MazeArr[x + 1][y + 1] == 0)walls++;
            break;
        }
        case E:
        {
            if(m_MazeArr[x][y + 1] == 0)walls++;
            if(m_MazeArr[x][y - 1] == 0)walls++;
            if(m_MazeArr[x + 1][y] == 0)walls++;
            if (m_MazeArr[x + 1][y + 1] == 0)walls++;
            if (m_MazeArr[x + 1][y - 1] == 0)walls++;
            break;
        }
        case W:
        {
            if(m_MazeArr[x][y + 1] == 0)walls++;
            if(m_MazeArr[x][y - 1] == 0)walls++;
            if(m_MazeArr[x - 1][y] == 0)walls++;
            if (m_MazeArr[x - 1][y + 1] == 0)walls++;
            if (m_MazeArr[x - 1][y - 1] == 0)walls++;
            break;
        }
    }
    return walls;
}

// Events
//////////////////////////////////////////////////////////////////////////
bool DungeonGenerator::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui.graphicsView)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* evt = static_cast<QKeyEvent*>(event);

            switch (evt->key())
            {
            case Qt::Key_1:
                m_ActGenSnake->triggered();
                return true;

            case Qt::Key_2:
                m_ActGenRecBack->triggered();
                return true;
            }
        }
    }

    return false;
}

// Slots
//////////////////////////////////////////////////////////////////////////
// Others
void DungeonGenerator::OnBtnNewClicked()
{
    QMenu menu(this);
    menu.addAction(m_ActGenSnake);
    menu.addAction(m_ActGenRecBack);
    menu.exec(QCursor::pos());
}

void DungeonGenerator::OnBtnZoomIn()
{
    ui.graphicsView->scale(SCALE_ZOOM_IN, SCALE_ZOOM_IN);
}

void DungeonGenerator::OnBtnZoomOut()
{
    ui.graphicsView->scale(SCALE_ZOOM_OUT, SCALE_ZOOM_OUT);
}
