#ifdef GUI
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto centralWidget = new QWidget;
    auto layout = new QVBoxLayout;
    auto view = new QGraphicsView(&m_scene);

    layout->addWidget(view);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

}

void MainWindow::addPoint(QString id, qreal x, qreal y)
{

    if(!m_pathItems.contains(id)) {
        auto m_pathItem = new QGraphicsPathItem();
        m_scene.addItem(m_pathItem);

        m_pathItems[id] = m_pathItem;

        int hue = (m_pathItems.count() * 10) % 360;  // Ensure the hue wraps back around to 0 once it hits 360. Multiply by 10 to get distinct colors
        m_pathItem->setPen(QPen(QColor::fromHsv(hue, 255, 255), 3));
    }


    auto m_pathItem = m_pathItems[id];
    QPainterPath path = m_pathItem->path();

    if(path.elementCount() == 0) {
        path.moveTo(x, y);
        path.lineTo(x, y);
    }
    path.lineTo(x, y);

    m_pathItem->setPath(path);



}
#endif
