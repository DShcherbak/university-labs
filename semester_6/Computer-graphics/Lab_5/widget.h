#ifndef WIDGET_H
#define WIDGET_H

#include "visualelements.h"
#include "quickhall.h"
#include <QWidget>
#include <QThread>
#include <QMouseEvent>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

enum widgetState {
    NodesBuilding, Reset, AreaChoose, AreaDown
};

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent * event) override;
    void printNode(std::shared_ptr<GraphicNode<int>> node, int r = 10);
    void printEdge(std::shared_ptr<Edge> edge);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    widgetState currentState = NodesBuilding;
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    Qt::WindowState defaultState = Qt::WindowFullScreen;
    std::vector<std::shared_ptr<GraphicNode<int>>> nodes;
    std::shared_ptr<Point> selectedPoint = nullptr;
    std::vector <std::shared_ptr<Edge>> boundaries;
    std::vector <std::shared_ptr<Edge>> saved_boundaries;
    std::vector<std::vector<std::shared_ptr<Edge>>> steps_of_quickhull;
    int id = 0;
};
#endif // WIDGET_H
