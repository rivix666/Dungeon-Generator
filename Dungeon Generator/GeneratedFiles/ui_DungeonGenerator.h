/********************************************************************************
** Form generated from reading UI file 'DungeonGenerator.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DUNGEONGENERATOR_H
#define UI_DUNGEONGENERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QPushButton *pushButton_zoomOut;
    QPushButton *pushButton_zoomIn;
    QPushButton *pushButton_New;

    void setupUi(QMainWindow *DungeonGeneratorClass)
    {
        if (DungeonGeneratorClass->objectName().isEmpty())
            DungeonGeneratorClass->setObjectName(QStringLiteral("DungeonGeneratorClass"));
        DungeonGeneratorClass->resize(600, 400);
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

        pushButton_zoomOut = new QPushButton(centralWidget);
        pushButton_zoomOut->setObjectName(QStringLiteral("pushButton_zoomOut"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/DungeonGenerator/Resources/magnifier_zoom_out.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_zoomOut->setIcon(icon);
        pushButton_zoomOut->setFlat(true);

        horizontalLayout->addWidget(pushButton_zoomOut);

        pushButton_zoomIn = new QPushButton(centralWidget);
        pushButton_zoomIn->setObjectName(QStringLiteral("pushButton_zoomIn"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/DungeonGenerator/Resources/magnifier_zoom_in.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_zoomIn->setIcon(icon1);
        pushButton_zoomIn->setFlat(true);

        horizontalLayout->addWidget(pushButton_zoomIn);

        pushButton_New = new QPushButton(centralWidget);
        pushButton_New->setObjectName(QStringLiteral("pushButton_New"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/DungeonGenerator/Resources/maze.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_New->setIcon(icon2);
        pushButton_New->setFlat(true);

        horizontalLayout->addWidget(pushButton_New);


        verticalLayout->addLayout(horizontalLayout);

        DungeonGeneratorClass->setCentralWidget(centralWidget);

        retranslateUi(DungeonGeneratorClass);

        QMetaObject::connectSlotsByName(DungeonGeneratorClass);
    } // setupUi

    void retranslateUi(QMainWindow *DungeonGeneratorClass)
    {
        DungeonGeneratorClass->setWindowTitle(QApplication::translate("DungeonGeneratorClass", "DungeonGenerator", 0));
#ifndef QT_NO_TOOLTIP
        pushButton_zoomOut->setToolTip(QApplication::translate("DungeonGeneratorClass", "Zoom Out", 0));
#endif // QT_NO_TOOLTIP
        pushButton_zoomOut->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_zoomIn->setToolTip(QApplication::translate("DungeonGeneratorClass", "Zoom In", 0));
#endif // QT_NO_TOOLTIP
        pushButton_zoomIn->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_New->setToolTip(QApplication::translate("DungeonGeneratorClass", "Generate Maze", 0));
#endif // QT_NO_TOOLTIP
        pushButton_New->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DungeonGeneratorClass: public Ui_DungeonGeneratorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DUNGEONGENERATOR_H
