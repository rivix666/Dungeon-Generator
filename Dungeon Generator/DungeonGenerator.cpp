#include "DungeonGenerator.h"
#include <math.h>
#include <ctime>
#include <QMenu>
#include <QCursor>
#include <QDebug>
#include <QKeyEvent>
#include <QInputDialog>
#include <QShortcut>

DungeonGenerator::DungeonGenerator(QWidget *parent)
    : QMainWindow(parent), m_MaxWidth(50),
    m_MaxHeight(50), TILE_SIZE(15), TILE_BASE_COLOR("#BDB8AE"),
    TILE_BORDERS_COLOR("#949188"), TILE_BORDERS(QBrush(TILE_BORDERS_COLOR), 2),
    TILE_BASE(TILE_BASE_COLOR), SCALE_ZOOM_IN(1.1f), SCALE_ZOOM_OUT(0.9f),
    m_GenDungeonSC(new QShortcut(QKeySequence(Qt::Key_Return), this))
{
    ui.setupUi(this);
    InitGraphicsScene();
    InitActions();
    InitConnections();
    InitMazeArray();
    InitDirectionArrays();
    InitDebugCombo();

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
    // PushButtons
    connect(ui.pushButton_New, &QPushButton::clicked, this, &DungeonGenerator::OnBtnNewClicked);
    connect(ui.pushButton_zoomIn, &QPushButton::clicked, this, &DungeonGenerator::OnBtnZoomIn);
    connect(ui.pushButton_zoomOut, &QPushButton::clicked, this, &DungeonGenerator::OnBtnZoomOut);
    connect(ui.pushButton_Dungeon, &QPushButton::clicked, this, &DungeonGenerator::OnBtnDungeonGenerate);

    // Shortcuts
    connect(m_GenDungeonSC, &QShortcut::activated, this, &DungeonGenerator::OnBtnDungeonGenerate);

    // CheckBoxes
    connect(ui.checkBox_debug, &QCheckBox::toggled, this, &DungeonGenerator::OnDebugCheckBoxToggled);

    // ComboBoxes
    connect(ui.comboBox_debug, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DungeonGenerator::OnDebugComboIndexChanged);

    // SpinBoxes
    connect(ui.spinBox_width , static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &DungeonGenerator::OnSpinBoxesSizeValueChanged);
    connect(ui.spinBox_height, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &DungeonGenerator::OnSpinBoxesSizeValueChanged);

    // Actions
    connect(m_ActGenSnake, &QAction::triggered, this, [=] { GenMazeSnake(); });
    connect(m_ActGenRecBack, &QAction::triggered, this, [=] { ClearMazeArray(); GenMazeRecursiveBacktracking(1, 1); DrawMazeFromArray(); });
}

void DungeonGenerator::InitMazeArray()
{
    m_MazeArr = new uint*[m_MaxWidth];
    for (int i = 0; i < m_MaxWidth; i++)
    {
        m_MazeArr[i] = new uint[m_MaxHeight];
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

void DungeonGenerator::InitDebugCombo()
{
    ui.comboBox_debug->addItem("Nothing");
    ui.comboBox_debug->addItem("SolidRock");
    ui.comboBox_debug->addItem("Room");
    ui.comboBox_debug->addItem("Corridor");
    ui.comboBox_debug->addItem("Doors");
}

// Others
//////////////////////////////////////////////////////////////////////////
void DungeonGenerator::ClearMazeArray()
{
    for (int i = 0; i < m_MaxWidth; i++)
    {
        for (int j = 0; j < m_MaxHeight; j++)
        {
            m_MazeArr[i][j] = SolidRock;
        }
    }

    m_RoomsVec.clear();
}

void DungeonGenerator::DestroyMazeArray()
{
    for (int i = 0; i < m_MaxWidth; i++)
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

void DungeonGenerator::DrawMazeFromArray(bool clear /*=true*/)
{
    if(clear)
        m_Scene->clear();
 #ifdef _DEBUG | DEBUG
     for (int i = 0; i < m_MaxWidth; i++)
     {
         QString str = "";
         for (int j = 0; j < m_MaxHeight; j++)
         {
             str += QString::number(m_MazeArr[i][j]);
             if (m_MazeArr[i][j] == SolidRock)
             {
                 QRect rect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                 m_Scene->addRect(rect, TILE_BORDERS, TILE_BASE);
             }
         }
         qDebug() << str;
     }
 #else
     for (int i = 0; i < m_MaxWidth; i++)
     {
         for (int j = 0; j < m_MaxHeight; j++)
         {
             if (m_MazeArr[i][j] == SolidRock)
             {
                 QRect rect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                 m_Scene->addRect(rect, TILE_BORDERS, TILE_BASE);
             }
         }
     }
 #endif
}

void DungeonGenerator::DrawDebug(int type)
{
    if (ui.checkBox_debug->isChecked())
    {
        for (int i = 0; i < m_MaxWidth; i++)
        {
            for (int j = 0; j < m_MaxHeight; j++)
            {
                if (m_MazeArr[i][j] == type)
                {
                    QRect rect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                    m_Scene->addRect(rect, TILE_BORDERS, QBrush(QColor(Qt::red)));
                }
            }
        }
    }
}

// Mazes
void DungeonGenerator::GenMazeSnake()
{
    int tiles_per_x = m_MaxWidth;
    int tiles_per_y = m_MaxHeight;
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

            if (((nx < m_MaxWidth - 1) & (nx >= 1)) & ((ny < m_MaxHeight - 1) & (ny >= 1)))
            {
                 if (m_MazeArr[nx][ny] == SolidRock)
                 {
                     if (CheckNeighbours(dir, nx, ny) > 4) // 2 with cross walls
                     {
                         m_MazeArr[nx][ny] = Corridor;
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
            if(m_MazeArr[x - 1][y] == SolidRock)walls++;
            if(m_MazeArr[x + 1][y] == SolidRock)walls++;
            if(m_MazeArr[x][y - 1] == SolidRock)walls++;
            if(m_MazeArr[x - 1][y - 1] == SolidRock)walls++; // delete this two ever case to unlock cross walls
            if(m_MazeArr[x + 1][y - 1] == SolidRock)walls++;

            break;
        }
        case S:
        {
            if(m_MazeArr[x - 1][y] == SolidRock)walls++;
            if(m_MazeArr[x + 1][y] == SolidRock)walls++;
            if(m_MazeArr[x][y + 1] == SolidRock)walls++;
            if(m_MazeArr[x - 1][y + 1] == SolidRock)walls++;
            if(m_MazeArr[x + 1][y + 1] == SolidRock)walls++;
            break;
        }
        case E:
        {
            if(m_MazeArr[x][y + 1] == SolidRock)walls++;
            if(m_MazeArr[x][y - 1] == SolidRock)walls++;
            if(m_MazeArr[x + 1][y] == SolidRock)walls++;
            if(m_MazeArr[x + 1][y + 1] == SolidRock)walls++;
            if(m_MazeArr[x + 1][y - 1] == SolidRock)walls++;
            break;
        }
        case W:
        {
            if(m_MazeArr[x][y + 1] == SolidRock)walls++;
            if(m_MazeArr[x][y - 1] == SolidRock)walls++;
            if(m_MazeArr[x - 1][y] == SolidRock)walls++;
            if(m_MazeArr[x - 1][y + 1] == SolidRock)walls++;
            if(m_MazeArr[x - 1][y - 1] == SolidRock)walls++;
            break;
        }
    }
    return walls;
}

int DungeonGenerator::CheckNeighbours(uint x, uint y)
{
    uint walls = 0;
    if(m_MazeArr[x + 1][y] == SolidRock) walls++;
    if(m_MazeArr[x - 1][y] == SolidRock) walls++;
    if(m_MazeArr[x][y + 1] == SolidRock) walls++;
    if(m_MazeArr[x][y - 1] == SolidRock) walls++;
    return walls;
}

void DungeonGenerator::GenRooms(int attempts)
{
    uint nx, ny;
    uint size_x, size_y;
    for (int i = 0; i < attempts; i++)
    {
        if ((qrand() % 2) == SolidRock)
        {
            size_x = (qrand() % 6) + 5;
            size_y = (qrand() % (size_x / 2)) + 5;
        }
        else
        {
            size_y = (qrand() % 6) + 5;
            size_x = (qrand() % (size_y / 2)) + 5;            
        }

        nx = (qrand() % (m_MaxWidth - size_x - 1)) + 1;
        ny = (qrand() % (m_MaxHeight - size_y - 1)) + 1;

        if (AreFieldsEmpty(nx, ny, size_x, size_y))
        {
            CarveRoom(nx, ny, size_x, size_y);
        }
    }
}

bool DungeonGenerator::AreFieldsEmpty(uint x, uint y, uint size_x, uint size_y)
{
    uint nx = x - 1;
    uint ny = y - 1;
    uint size_nx = size_x + 2;
    uint size_ny = size_y + 2;

    for (int i = 0; i < size_nx; i++)
    {
        for (int j = 0; j < size_ny; j++)
        {
            if (m_MazeArr[nx + i][ny + j] != SolidRock)
                return false;
        }
    }

    return true;
}

void DungeonGenerator::CarveRoom(uint x, uint y, uint size_x, uint size_y)
{
    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < size_y; j++)
        {
            m_MazeArr[x + i][y + j] = Room;
        }
    }

    m_RoomsVec.push_back(SRoom(x, y, size_x, size_y)); //todo obadac czemu miesza
}

void DungeonGenerator::CarveCorridorsBetweenRooms(uint attempts)
{
    if (attempts > 0)
    {
        uint nx, ny;
        for (uint i = 0; i < attempts; i++)
        {
            nx = (qrand() % m_MaxWidth - 1) + 1;
            ny = (qrand() % m_MaxHeight - 1) + 1;
            GenMazeRecursiveBacktracking(nx, ny);
        }
    }
    else
    {
        for (uint i = 1; i < m_MaxWidth - 1; i += 2)
        {
            for (uint j = 1; j < m_MaxHeight - 1; j += 2)
            {
                if (CheckNeighbours(i, j) > 2)
                {
                    GenMazeRecursiveBacktracking(i, j);
                }
            }
        }
    }
}

void DungeonGenerator::ConnectRooms(int root /*= -1*/)
{
    if (root < 0)
        root = qrand() % m_RoomsVec.size();

    SRoom root_room = m_RoomsVec[root];

    for (SRoom r : m_RoomsVec)
        ConnectRoom(r);

}

void DungeonGenerator::ConnectRoom(SRoom room)
{
    while (true)
    {
        uint nx = 0;
        uint ny = 0;
                                     
        if ((qrand() % 2) == 0)
        {
            // go horizontal
            if ((qrand() % 2) == 0)
            {
                // ceil
                nx = (qrand() % room.SizeX) + room.PosX;
                ny = room.PosY - 1;

                if (nx < 2 || nx > m_MaxWidth - 2 || ny < 2 || ny > m_MaxHeight - 2)
                    continue;

                if (CheckNeighbours(nx, ny) < 3)
                {
                    m_MazeArr[nx][ny] = Doors;
                    break;
                }
            }
            else
            {
                // floor
                nx = (qrand() % room.SizeX) + room.PosX;
                ny = room.PosY + room.SizeY;

                if (nx < 2 || nx > m_MaxWidth - 2 || ny < 2 || ny > m_MaxHeight - 2)
                    continue;

                if (CheckNeighbours(nx, ny) < 3)
                {
                    m_MazeArr[nx][ny] = Doors;
                    break;
                }
            }
        }
        else
        {
            // go vertical
            if ((qrand() % 2) == 0)
            {
                // left
                nx = room.PosX - 1;
                ny = (qrand() % room.SizeY) + room.PosY;

                if (nx < 2 || nx > m_MaxWidth - 2 || ny < 2 || ny > m_MaxHeight - 2)
                    continue;

                if (CheckNeighbours(nx, ny) < 3)
                {
                    m_MazeArr[nx][ny] = Doors;
                    break;
                }
            }
            else
            {
                // right
                nx = room.PosX + room.SizeX;
                ny = (qrand() % room.SizeY) + room.PosY;

                if (nx < 2 || nx > m_MaxWidth - 2 || ny < 2 || ny > m_MaxHeight - 2)
                    continue;

                if (CheckNeighbours(nx, ny) < 3)
                {
                    m_MazeArr[nx][ny] = Doors;
                    break;
                }
            }
        }
    }
}

bool DungeonGenerator::AreAllRoomsConnectedToRoot(SRoom root, std::vector <SRoom*> unconnected) //todo
{
    return true;
}

void DungeonGenerator::UncarveDungeon(uint when_stop /*= -1*/)
{
    int w = m_MaxWidth - 1;
    int h = m_MaxHeight - 1;
    for (int i = 1; i < w; i++)
    {
        for (int j = 1; j < h; j++)
        {
            UncarveCorridor(i, j);
        }
    }
}

void DungeonGenerator::UncarveCorridor(uint x, uint y)
{
    uint nx = x;
    uint ny = y;
    while (true)
    {
        if (CheckNeighbours(nx, ny) < 3)
            return;

        m_MazeArr[nx][ny] = SolidRock;
        if (!NextTileInCorridor(nx, ny))
            return;
    }
}

bool DungeonGenerator::NextTileInCorridor(uint& nx, uint& ny)
{
    if (m_MazeArr[nx + 1][ny] != SolidRock) { nx++; return true; }
    if (m_MazeArr[nx - 1][ny] != SolidRock) { nx--; return true; }
    if (m_MazeArr[nx][ny + 1] != SolidRock) { ny++; return true; }
    if (m_MazeArr[nx][ny - 1] != SolidRock) { ny--; return true; }
    return false;
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

void DungeonGenerator::OnBtnDungeonGenerate()
{
    bool result = false;
    int seed = QInputDialog::getInt(this, tr("Question?"), tr("How many attempts?"), 50, 1, 2147483647, 1, &result);

    if (result)
    {
        ClearMazeArray();
        GenRooms(seed);
        CarveCorridorsBetweenRooms(0);
        ConnectRooms();
        UncarveDungeon();
        DrawMazeFromArray();
        DrawDebug(ui.comboBox_debug->currentIndex() - 1);
    }
}

void DungeonGenerator::OnDebugCheckBoxToggled(bool toggled)
{
    if (toggled && ui.comboBox_debug->currentIndex() != 0)
    {
        DrawDebug(ui.comboBox_debug->currentIndex() - 1);
    }
    else
    {
        DrawMazeFromArray();
    }
}

void DungeonGenerator::OnDebugComboIndexChanged(int index)
{
    if (ui.checkBox_debug->isChecked() && ui.comboBox_debug->currentIndex() != 0)
    {
        DrawMazeFromArray();
        DrawDebug(index - 1);
    }
    else if(ui.comboBox_debug->currentIndex() == 0)
    {
        DrawMazeFromArray();
    }
}

void DungeonGenerator::OnSpinBoxesSizeValueChanged(int i)
{
    DestroyMazeArray();

    m_MaxWidth = ui.spinBox_width->value();
    m_MaxHeight = ui.spinBox_height->value();

    InitMazeArray();
    m_Scene->clear();
}
