/********************************************************************************
** Form generated from reading UI file 'DungeonGenerator.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DUNGEONGENERATOR_H
#define UI_DUNGEONGENERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DungeonGeneratorClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QFrame *line_2;
    QCheckBox *checkBox_debug;
    QComboBox *comboBox_debug;
    QFrame *line_3;
    QSpinBox *spinBox_width;
    QSpinBox *spinBox_height;
    QFrame *line;
    QPushButton *pushButton_zoomOut;
    QPushButton *pushButton_zoomIn;
    QPushButton *pushButton_New;
    QPushButton *pushButton_Dungeon;

    void setupUi(QMainWindow *DungeonGeneratorClass)
    {
        if (DungeonGeneratorClass->objectName().isEmpty())
            DungeonGeneratorClass->setObjectName(QStringLiteral("DungeonGeneratorClass"));
        DungeonGeneratorClass->resize(600, 400);
        QIcon icon;
        icon.addFile(QStringLiteral(":/DungeonGenerator/Resources/maze.png"), QSize(), QIcon::Normal, QIcon::Off);
        DungeonGeneratorClass->setWindowIcon(icon);
        centralWidget = new QWidget(DungeonGeneratorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 0, 6, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        checkBox_debug = new QCheckBox(centralWidget);
        checkBox_debug->setObjectName(QStringLiteral("checkBox_debug"));

        horizontalLayout->addWidget(checkBox_debug);

        comboBox_debug = new QComboBox(centralWidget);
        comboBox_debug->setObjectName(QStringLiteral("comboBox_debug"));

        horizontalLayout->addWidget(comboBox_debug);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        spinBox_width = new QSpinBox(centralWidget);
        spinBox_width->setObjectName(QStringLiteral("spinBox_width"));
        spinBox_width->setMaximum(500);
        spinBox_width->setValue(50);

        horizontalLayout->addWidget(spinBox_width);

        spinBox_height = new QSpinBox(centralWidget);
        spinBox_height->setObjectName(QStringLiteral("spinBox_height"));
        spinBox_height->setMaximum(500);
        spinBox_height->setValue(50);

        horizontalLayout->addWidget(spinBox_height);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        pushButton_zoomOut = new QPushButton(centralWidget);
        pushButton_zoomOut->setObjectName(QStringLiteral("pushButton_zoomOut"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DungeonGenerator/Resources/magnifier_zoom_out.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_zoomOut->setIcon(icon1);
        pushButton_zoomOut->setFlat(true);

        horizontalLayout->addWidget(pushButton_zoomOut);

        pushButton_zoomIn = new QPushButton(centralWidget);
        pushButton_zoomIn->setObjectName(QStringLiteral("pushButton_zoomIn"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DungeonGenerator/Resources/magnifier_zoom_in.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_zoomIn->setIcon(icon2);
        pushButton_zoomIn->setFlat(true);

        horizontalLayout->addWidget(pushButton_zoomIn);

        pushButton_New = new QPushButton(centralWidget);
        pushButton_New->setObjectName(QStringLiteral("pushButton_New"));
        pushButton_New->setIcon(icon);
        pushButton_New->setFlat(true);

        horizontalLayout->addWidget(pushButton_New);

        pushButton_Dungeon = new QPushButton(centralWidget);
        pushButton_Dungeon->setObjectName(QStringLiteral("pushButton_Dungeon"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/DungeonGenerator/Resources/dungeon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Dungeon->setIcon(icon3);
        pushButton_Dungeon->setFlat(true);

        horizontalLayout->addWidget(pushButton_Dungeon);


        verticalLayout->addLayout(horizontalLayout);

        DungeonGeneratorClass->setCentralWidget(centralWidget);

        retranslateUi(DungeonGeneratorClass);

        QMetaObject::connectSlotsByName(DungeonGeneratorClass);
    } // setupUi

    void retranslateUi(QMainWindow *DungeonGeneratorClass)
    {
        DungeonGeneratorClass->setWindowTitle(QApplication::translate("DungeonGeneratorClass", "Dungeon Generator", 0));
        checkBox_debug->setText(QApplication::translate("DungeonGeneratorClass", "Debug", 0));
#ifndef QT_NO_TOOLTIP
        spinBox_width->setToolTip(QApplication::translate("DungeonGeneratorClass", "Dungeon Width (WARNING: Values bigger than 200 may result in stack overflow!)", 0));
#endif // QT_NO_TOOLTIP
        spinBox_width->setPrefix(QApplication::translate("DungeonGeneratorClass", "w = ", 0));
#ifndef QT_NO_TOOLTIP
        spinBox_height->setToolTip(QApplication::translate("DungeonGeneratorClass", "Dungeon Height (WARNING: Values bigger than 200 may result in stack overflow!)", 0));
#endif // QT_NO_TOOLTIP
        spinBox_height->setPrefix(QApplication::translate("DungeonGeneratorClass", "h = ", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_zoomOut->setToolTip(QApplication::translate("DungeonGeneratorClass", "Zoom Out", 0));
#endif // QT_NO_TOOLTIP
        pushButton_zoomOut->setText(QString());
        pushButton_zoomOut->setShortcut(QApplication::translate("DungeonGeneratorClass", "-", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_zoomIn->setToolTip(QApplication::translate("DungeonGeneratorClass", "Zoom In", 0));
#endif // QT_NO_TOOLTIP
        pushButton_zoomIn->setText(QString());
        pushButton_zoomIn->setShortcut(QApplication::translate("DungeonGeneratorClass", "+", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_New->setToolTip(QApplication::translate("DungeonGeneratorClass", "Generate Maze", 0));
#endif // QT_NO_TOOLTIP
        pushButton_New->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_Dungeon->setToolTip(QApplication::translate("DungeonGeneratorClass", "Generate Dungeon!", 0));
#endif // QT_NO_TOOLTIP
        pushButton_Dungeon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DungeonGeneratorClass: public Ui_DungeonGeneratorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DUNGEONGENERATOR_H
