#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef GUI

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QVBoxLayout>
#include <QPen>

#include <QMap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void addPoint(QString id, qreal x, qreal y);

private:
    QGraphicsScene m_scene;
    QMap<QString, QGraphicsPathItem*> m_pathItems;
};

#endif
#endif // MAINWINDOW_H
