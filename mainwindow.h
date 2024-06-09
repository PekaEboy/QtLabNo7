#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include "list.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QGraphicsScene *scene;
    QPen pen;
    float xmin;
    float xmax;
    float ymin;
    float ymax;
    float deltax;
    float Sx;
    float Sy;
    double f(float v);
    List Px;
    float Vx(List p, float c);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbBuild_clicked();

    void on_pbScaleXPlus_clicked();

    void on_pbScaleXMinus_clicked();

    void on_pbScaleYPlus_clicked();

    void on_pbScaleYPlus_2_clicked();

    void on_pbRight_clicked();

    void on_pbDown_clicked();

    void on_pbLeft_clicked();

    void on_pbUp_clicked();

    void on_pbAdd_clicked();

    void on_lwPx_itemChanged(QListWidgetItem *item);

    void on_pbRemove_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
