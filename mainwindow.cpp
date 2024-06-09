#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cmath"
#include <QMessageBox>
#include <QListWidgetItem>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->gvGraphics->setScene(scene);
    scene->setSceneRect(0, 0, ui->gvGraphics->width(), ui->gvGraphics->height());

    ui->gvGraphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gvGraphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    xmin = -2;
    xmax = 2;
    ymin = -1;
    ymax = 3;
    deltax=0.01;
    Sx = ui->gvGraphics->width()/(xmax-xmin);
    Sy = ui->gvGraphics->height()/(ymax-ymin);
    pen.setColor(Qt::gray);
    for(int i = 0; i<5; i++) {
        scene->addLine(i*(xmax-xmin)*Sx/4, 0, i*(xmax-xmin)*Sx/4, ui->gvGraphics->height(), pen);
        scene->addLine(0, i*(ymax-ymin)*Sy/4, ui->gvGraphics->width(), i*(ymax-ymin)*Sy/4, pen);
        switch(i) {
            case 0:
                ui->lblX1->setText(QString::number(xmin+i*(xmax-xmin)/4));
                ui->lblY1->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
            break;
            case 1:
                ui->lblX2->setText(QString::number(xmin+i*(xmax-xmin)/4));
                ui->lblY2->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
            break;
            case 2:
                ui->lblX3->setText(QString::number(xmin+i*(xmax-xmin)/4));
                ui->lblY3->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
            break;
            case 3:
                ui->lblX4->setText(QString::number(xmin+i*(xmax-xmin)/4));
                ui->lblY4->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
            break;
            case 4:
                ui->lblX5->setText(QString::number(xmin+i*(xmax-xmin)/4));
                ui->lblY5->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
            break;
        }
    }
    pen.setColor(Qt::blue);
    scene->addLine(0, -ymin*Sy, (xmax-xmin)*Sx, Sy*(-ymin), pen);
    scene->addLine(-xmin*Sx, 0, -xmin*Sx, ui->gvGraphics->height(), pen);
    pen.setColor(Qt::black);
    ui->lwFunc->addItem("SIN(P(x))");
    ui->lwFunc->addItem("TAN(P(x))");
    ui->lwFunc->addItem("EXP(P(x))");
    ui->lwFunc->addItem("1/P(x)");
    ui->lwFunc->addItem("SQRT(P(x))");
    ui->lwFunc->addItem("P(x)");
    Px.push_back(0);
    Px.push_back(1);
    ui->lwPx->addItem(QString::number(0));
    ui->lwPx->addItem(QString::number(1));
    for(int i = 0; i<Px.length(); i++) {
        ui->lwPx->item(i)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    }
    QGraphicsTextItem* osx = new QGraphicsTextItem(0);
    osx->setPlainText("y");
    osx->setPos(-xmin*Sx+2, 0);
    scene->addItem(osx);
    QGraphicsTextItem* osy = new QGraphicsTextItem(0);
    osy->setPlainText("x");
    osy->setPos(ui->gvGraphics->width()-10, -ymin*Sy+2);
    scene->addItem(osy);

}

void showMessage(QString str) {
    QMessageBox msg;
    msg.setText(str);
    msg.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::f(float v) {
    if(ui->lwFunc->selectionModel()->hasSelection()) {
        switch(ui->lwFunc->currentRow()) {
            case 0:
                return sin(v);
            case 1:
                return tan(v);
            case 2:
                return exp(v);
            case 3:
                return 1/v;
            case 4:
                return sqrt((abs(v)+v)/2);
            case 5:
                return v;
        }
    }
}

float MainWindow::Vx(List p, float c) {
    Node* q = p.first;
    float s = 0;
    while(q) {
        s += q->val*pow(c, q->number);
        q=q->next;
    }
    return s;
}

void MainWindow::on_pbBuild_clicked()
{
    if(ui->lwFunc->selectionModel()->hasSelection() && !Px.is_empty()) {
        scene->clear();

        float deltaf;
        float deltag;
        pen.setColor(Qt::gray);
        for(int i = 0; i<5; i++) {
            scene->addLine(i*(xmax-xmin)*Sx/4, 0, i*(xmax-xmin)*Sx/4, ui->gvGraphics->height(), pen);
            scene->addLine(0, i*(ymax-ymin)*Sy/4, ui->gvGraphics->width(), i*(ymax-ymin)*Sy/4, pen);
            switch(i) {
                case 0:
                    ui->lblX1->setText(QString::number(xmin+i*(xmax-xmin)/4));
                    ui->lblY1->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
                break;
                case 1:
                    ui->lblX2->setText(QString::number(xmin+i*(xmax-xmin)/4));
                    ui->lblY2->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
                break;
                case 2:
                    ui->lblX3->setText(QString::number(xmin+i*(xmax-xmin)/4));
                    ui->lblY3->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
                break;
                case 3:
                    ui->lblX4->setText(QString::number(xmin+i*(xmax-xmin)/4));
                    ui->lblY4->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
                break;
                case 4:
                    ui->lblX5->setText(QString::number(xmin+i*(xmax-xmin)/4));
                    ui->lblY5->setText(QString::number(-1*(ymin+i*(ymax-ymin)/4)));
                break;
            }
        }
        pen.setColor(Qt::blue);
        scene->addLine(0, -ymin*Sy, (xmax-xmin)*Sx, Sy*(-ymin), pen);
        scene->addLine(-xmin*Sx, 0, -xmin*Sx, ui->gvGraphics->height(), pen);
        pen.setColor(Qt::black);
        if(f(Vx(Px, 0)!=0)){
            QGraphicsTextItem* tm = new QGraphicsTextItem(0);
            tm->setPlainText(QString::number(0)+ " " + QString::number(f(Vx(Px, 0))));
            tm->setPos(-xmin*Sx+2, -(f(Vx(Px, 0))+ymin)*Sy+2);
            scene->addItem(tm);
        }
        QGraphicsTextItem* osx = new QGraphicsTextItem(0);
        osx->setPlainText("y");
        osx->setPos(-xmin*Sx+2, 0);
        scene->addItem(osx);
        QGraphicsTextItem* osy = new QGraphicsTextItem(0);
        osy->setPlainText("x");
        osy->setPos(ui->gvGraphics->width()-15, -ymin*Sy+2);
        scene->addItem(osy);
        for(float x=xmin; x<xmax; x+=deltax) {
            deltag=Vx(Px, x+deltax)-Vx(Px, x);
            deltaf=f(Vx(Px, x)+deltag)-f(Vx(Px, x));
            if(f(Vx(Px,x)+deltag)*f(Vx(Px,x))>=0){
                scene->addLine((x-xmin)*Sx, -(f(Vx(Px, x))+ymin)*Sy, (x+deltax-xmin)*Sx, -(f(Vx(Px, x))+deltaf+ymin)*Sy, pen);
            } else {
                QGraphicsTextItem* tms = new QGraphicsTextItem(0);
                tms->setPlainText(QString::number(x)+ " " + QString::number(f(Vx(Px, x))));
                tms->setPos((x-xmin)*Sx+2, -(f(Vx(Px, x))+ymin)*Sy+2);
                scene->addItem(tms);
            }

        }
    }
}


void MainWindow::on_pbScaleXPlus_clicked()
{
    xmax++;
    xmin--;
    Sx = ui->gvGraphics->width()/(xmax-xmin);
    on_pbBuild_clicked();
}


void MainWindow::on_pbScaleXMinus_clicked()
{
    if(xmax-xmin>2) {
        xmax--;
        xmin++;
        Sx = ui->gvGraphics->width()/(xmax-xmin);
        on_pbBuild_clicked();
    }
}


void MainWindow::on_pbScaleYPlus_clicked()
{
    ymax++;
    ymin--;
    Sy = ui->gvGraphics->height()/(ymax-ymin);
    on_pbBuild_clicked();
}


void MainWindow::on_pbScaleYPlus_2_clicked()
{
    if(ymax-ymin>2) {
        ymax--;
        ymin++;
        Sy = ui->gvGraphics->height()/(ymax-ymin);
        on_pbBuild_clicked();
    }
}


void MainWindow::on_pbRight_clicked()
{
    xmax++;
    xmin++;
    on_pbBuild_clicked();
}


void MainWindow::on_pbDown_clicked()
{
    ymax++;
    ymin++;
    on_pbBuild_clicked();
}


void MainWindow::on_pbLeft_clicked()
{
    xmax--;
    xmin--;
    on_pbBuild_clicked();
}


void MainWindow::on_pbUp_clicked()
{
    ymax--;
    ymin--;
    on_pbBuild_clicked();
}


void MainWindow::on_pbAdd_clicked()
{
    Px.push_back(0);
    ui->lwPx->clear();
    Node* q = Px.first;
    while(q) {
        ui->lwPx->addItem(QString::number(q->val));
        q=q->next;
    }
    for(int i = 0; i<Px.length(); i++) ui->lwPx->item(i)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
}


void MainWindow::on_lwPx_itemChanged(QListWidgetItem *item)
{
    Node* q = Px.first;
    while(q) {
        q->val=ui->lwPx->item(q->number)->text().toFloat();
        q=q->next;
    }
}


void MainWindow::on_pbRemove_clicked()
{
    if(!Px.is_empty()) {
        Px.remove(Px.last->number);
        ui->lwPx->clear();
        Node* q = Px.first;
        while(q) {
            ui->lwPx->addItem(QString::number(q->val));
            q=q->next;
        }
        for(int i = 0; i<Px.length(); i++) ui->lwPx->item(i)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    }
}

