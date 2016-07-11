#include "DungeonGenerator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DungeonGenerator w;
    w.show();
    return a.exec();
}
