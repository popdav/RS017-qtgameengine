#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include <QRectF>
#include <QScrollBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int width = this->size().width();
    int height = this->size().height();
    ui->gvMainScene->setRenderHint(QPainter::Antialiasing);
    ui->gvMainScene->setFixedSize(width* 0.7, height*0.95);
    ui->gvMainScene->setSceneRect(0,0,4000,height * 0.95);
    ui->gvMainScene->fitInView(0, 0, 4000, height * 0.95 , Qt::KeepAspectRatioByExpanding);
    gameBuilder.reset(new GameBuilder(ui->gvMainScene));
    ui->gvMainScene->setScene(&(*gameBuilder));

    ui->gvMainScene->verticalScrollBar()->setValue(ui->gvMainScene->verticalScrollBar()->maximum());
    ui->gvMainScene->horizontalScrollBar()->setValue(ui->gvMainScene->horizontalScrollBar()->minimum());

    addSignalsAndSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSignalsAndSlots()
{
    connect(ui->pbRectangle, SIGNAL(clicked()), this, SLOT(addRectangle()));
    connect(ui->pbChooseFromDefault, SIGNAL(clicked()), this, SLOT(loadDefaultBackground()));
    connect(ui->pbEnemyOne, SIGNAL(clicked()), this, SLOT(addEnemyOne()));
}

void MainWindow::loadGame()
{

}

void MainWindow::saveGame()
{

}

void MainWindow::closeApp()
{

}


void MainWindow::addRectangle()
{

    ComponentInfoDialog* dialog = new ComponentInfoDialog(this);
    dialog->exec();

    if(dialog->accepted()){
        qreal x = dialog->x();
        qreal y = dialog->y();
        qreal width = dialog->width();
        qreal height = dialog->height();
        QList<QLineEdit*> rectangleInfo;
        rectangleInfo.append(ui->leRectangleX);
        rectangleInfo.append(ui->leRectangleY);
        rectangleInfo.append(ui->leRectangleWidth);
        rectangleInfo.append(ui->leRectangleHeight);
        gameBuilder->addRectangle(x, y, width, height, ui->tbComponentInfo, rectangleInfo, ui->pbRectangleApply);

    }
    else{
        return;
    }
}

void MainWindow::addEnemyOne()
{
    EnemyDialog* enemyDialog = new EnemyDialog(this);
    enemyDialog->exec();
    QString lookPath = QFileDialog::getOpenFileName(this, tr("Choose File"),"../RS_game_engine/enemies/", tr("Images (*.png *.jpg *.jpeg)"));
    qDebug() << lookPath;
    if(enemyDialog->accepted()){
        qreal x = enemyDialog->x();
        qreal y = enemyDialog->y();
        qreal width = enemyDialog->width();
        qreal height = enemyDialog->height();
        qreal range = enemyDialog->range();
        QList<QLineEdit*> enemyInfo;
        enemyInfo.append(ui->leEnemyX);
        enemyInfo.append(ui->leEnemyY);
        enemyInfo.append(ui->leEnemyWidth);
        enemyInfo.append(ui->leEnemyHeight);
        enemyInfo.append(ui->leEnemyRange);
        gameBuilder->addEnemy(x, y, width, height, range, lookPath,ui->tbComponentInfo, enemyInfo, ui->pbEnemyApply);
    }
    else{
        return;
    }
}

QString fileName;
void MainWindow::loadDefaultBackground()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Choose File"),"../RS_game_engine/backgrounds/", tr("Images (*.png *.jpg)"));
    QPixmap bkgnd(fileName);
    bkgnd = bkgnd.scaled(ui->gvMainScene->size());
    QPalette palette;
    palette.setBrush(QPalette::Base, bkgnd);
    ui->gvMainScene->setPalette(palette);
}



void MainWindow::resizeEvent(QResizeEvent *event)
{
    int width = this->size().width();
    int height = this->size().height();
    ui->gvMainScene->setFixedSize(width* 0.7, height*0.95);
    QPixmap bkgnd(fileName);
    bkgnd = bkgnd.scaled(ui->gvMainScene->size());
    QPalette palette;
    palette.setBrush(QPalette::Base, bkgnd);
    ui->gvMainScene->setPalette(palette);
}
