#include "DungeonGenerator.h"
#include <math.h>
#include <ctime>
#include <QMenu>
#include <QCursor>
#include <QDebug>

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
}

void DungeonGenerator::InitConnections()
{
    // Others
    connect(ui.pushButton_New, &QPushButton::clicked, this, &DungeonGenerator::OnBtnNewClicked);
    connect(ui.pushButton_zoomIn, &QPushButton::clicked, this, &DungeonGenerator::OnBtnZoomIn);
    connect(ui.pushButton_zoomOut, &QPushButton::clicked, this, &DungeonGenerator::OnBtnZoomOut);

    // Actions
    connect(m_ActGenSnake, &QAction::triggered, this, [=] { GenMazeSnake(); });
    connect(m_ActGenRecBack, &QAction::triggered, this, [=] { GenMazeRecursiveBacktracking(20, 20); DrawMazeFromArray(); });
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
    m_DirYArr[W] = -1;

    m_DirOppositeArr[N] = S;
    m_DirOppositeArr[E] = W;
    m_DirOppositeArr[S] = N;
    m_DirOppositeArr[W] = E;
}

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
        int r = i + (rand() % (size - i));
        int temp = arr[i];
        arr[i] = arr[r];
        arr[r] = temp;
    }
}

void DungeonGenerator::DrawMazeFromArray()
{
    m_Scene->clear();

//     QString str = " ";
//     for (int x = 0; x < (MAX_WIDTH * 2); x++) 
//     {
//         str += "_";
//     }
//     str += "\n";
// 
//     for (int y = 0; y < MAX_HEIGHT; y++) 
//     {
//         str += "|";
//         for (int x = 0; x < MAX_WIDTH; x++) 
//         {
//             str += (m_MazeArr[x][y] & S) != 0 ? " " : "_";
//             if ((m_MazeArr[x][y] & E) != 0) 
//             {
//                 str += ((m_MazeArr[x][y] | m_MazeArr[x + 1][y]) & S) != 0 ? " " : "_";
//             }
//             else {
//                 str += "|";
//             }
//         }
//         str += "\n";
//     }
// 
// 
//     uint count = str.size();
//     uint x = 0;
//     uint y = 0;
//     for (uint i = 0; i < count; i++)
//     {
//         if (str.at(i) == "\n")
//         {
//             y++;
//             x = 0;
//             continue;
//         }
// 
//         if (str.at(i) == " ")
//         {
//             x++;
//             continue;
//         }
// 
//         QRect rect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
//         m_Scene->addRect(rect, TILE_BORDERS, TILE_BASE);
//         x++;
//     }
// 
// 



// 
//     for (int y = 0; y < MAX_HEIGHT; y++)
//     {
//         uint offx = 0;
//         for (int x = 0; x < MAX_WIDTH; x++)
//         {
// 
//             if ((m_MazeArr[x][y] & S) != 0)
//             {
// 
//             }
//             else
//             {
//                 QRect rect((x - 1 + offx) * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
//                 m_Scene->addRect(rect, TILE_BORDERS, TILE_BASE);
// 
//                 QRect rect2((x + 1 + offx) * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
//                 m_Scene->addRect(rect, TILE_BORDERS, TILE_BASE);
//             }
// 
//             if ((m_MazeArr[x][y] & E) != 0)
//             {
//                 if (((m_MazeArr[x][y] | m_MazeArr[x + 1][y]) & S) != 0)
//                 {
// 
//                 }
//             }
//             else
//             {
// 
//             }
//         }
//         offx++;
// 
//     }
// 















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

            if (((nx < MAX_WIDTH) & (nx >= 0)) & ((ny < MAX_HEIGHT) & (ny >= 0)))
            {
                
                if (m_MazeArr[nx][ny] == 0)
                {
                    bool result = false;
                    for (uint dir2 : directions)
                    {
//                         if (dir2 == m_DirOppositeArr[dir])
//                             continue;

                        uint nx2, ny2;

                        nx2 = nx + m_DirXArr[dir2];
                        ny2 = ny + m_DirYArr[dir2];

                        if (((nx2 < MAX_WIDTH) & (nx2 >= 0)) & ((ny2 < MAX_HEIGHT) & (ny2 >= 0)))
                            if (m_MazeArr[nx2][ny2] == 0)
                                result = true;
                    }

                    if (result)
                        m_MazeArr[nx][ny] = 1;
                    else
                        return;
                }
            }
        }
    }



//     for (uint dir : directions)
//     {
//         nx = pos_x + m_DirXArr[dir];
//         ny = pos_y + m_DirYArr[dir];
// 
//         if (((nx < MAX_WIDTH) & (nx >= 0)) & ((ny < MAX_HEIGHT) & (ny >= 0)))
//         {
//             if (m_MazeArr[nx][ny] == 0)
//             {
//                 for (uint dir2 : directions)
//                 {
// 
//                 }
//             }
//         }
//     }
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
