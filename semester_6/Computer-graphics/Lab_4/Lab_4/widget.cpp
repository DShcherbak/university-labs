
#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

void setButtonColor(QPushButton* button, Qt::GlobalColor color){
    QPalette pal = button->palette();
    pal.setColor(QPalette::Button, color);
    button->setAutoFillBackground(true);
    button->setPalette(pal);
    button->update();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setFixedSize(800, 600); // Фиксированный размер окна
    ui->setupUi(this);
    setButtonColor(ui->pushButton, Qt::lightGray);
    setButtonColor(ui->pushButton_2, Qt::lightGray);
}



void Widget::printNode(std::shared_ptr<GraphicNode<int>> node, int r){
    QPainter painter(this);

    QPen pen;
    pen.setWidth(3);
    pen.setBrush(node->nodeColor);
    painter.setPen(pen);
    painter.setBrush(node->nodeColor);
    painter.drawEllipse(node->x-r,node->y-r,2*r,2*r);
    pen.setBrush(Qt::magenta);
    painter.setPen(Qt::darkMagenta);
    painter.setBrush(Qt::red);
    painter.setFont(QFont("Arial", 30));
}

void Widget::printEdge(std::shared_ptr<Edge> edge){
    QPainter painter(this);
    QPen pen;
    pen.setWidth(3);
    pen.setBrush(edge->color);
    painter.setPen(pen);
    painter.drawLine(edge->first.x,
                     edge->first.y,
                     edge->second.x,
                     edge->second.y);
}


void Widget::paintEvent(QPaintEvent * event) {
    QPainter painter(this);

    QPen pen;
    pen.setWidth(3);
    pen.setBrush(Qt::red);

    painter.setPen(pen);

    for(auto node : nodes){
        printNode(node);
    }

    if(kdtree != nullptr){
        for(auto edge : kdtree->lines){
            printEdge(edge);
        }

    }

    for(auto edge : boundaries){
        printEdge(edge);
    }

}

void Widget::mousePressEvent(QMouseEvent *event){
    boundaries = {};
    int x = event->x(), y = event->y();
    if(currentState == NodesBuilding && y <= 530){
        nodes.push_back(std::make_shared<GraphicNode<int>>(x,y,Qt::black, 0));
    }
    else if(currentState == AreaChoose){
        selectedPoint = std::make_shared<Point>(x,y);
        currentState = AreaDown;
    }
    update();
}

std::vector <std::shared_ptr<Edge>> make_boundaries(std::shared_ptr<Point> p1, std::shared_ptr<Point>p2){
    std::vector <std::shared_ptr<Edge>> result {
        std::make_shared<Edge>(p1->x, p1->y, p2->x, p1->y),
        std::make_shared<Edge>(p1->x, p1->y, p1->x, p2->y),
        std::make_shared<Edge>(p2->x, p2->y, p2->x, p1->y),
        std::make_shared<Edge>(p2->x, p2->y, p1->x, p2->y)
    };
    return result;
}

void Widget::mouseMoveEvent(QMouseEvent *event){
    if(currentState == AreaDown){
        boundaries = make_boundaries(selectedPoint,
                                     std::make_shared<Point>(event->x(), event->y()));
    }
    update();
}

void Widget::mouseReleaseEvent(QMouseEvent *event){
    if(currentState == AreaDown){
        for(auto &node : nodes)
            node->nodeColor = Qt::black;

        auto p2 = std::make_shared<Point>(event->x(), event->y());
        auto res = kdtree->checkArea(selectedPoint, p2);

        for(size_t i = 0; i < nodes.size(); i++){
            for(size_t j = 0; j < res.size(); j++){
                if(nodes[i]->x == res[j]->x && nodes[i]->y == res[j]->y){
                    nodes[i]->nodeColor = Qt::darkRed;
                }
            }
        }
        currentState = AreaChoose;
    }
    update();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    nodes.clear();
    boundaries.clear();
    currentState = NodesBuilding;
    kdtree = nullptr;
    setButtonColor(ui->pushButton, Qt::lightGray);
    setButtonColor(ui->pushButton_2, Qt::lightGray);
    update();
}

void Widget::on_pushButton_2_clicked()
{
    std::sort(nodes.begin(), nodes.end(), [](std::shared_ptr<GraphicNode<int>> a, std::shared_ptr<GraphicNode<int>> b)
    {
        if(a->x == b->x){
           return a->y < b->y;
        } else return a->x < b->x;
    });
    kdtree = std::make_shared<KdTree>(nodes);
    currentState = AreaChoose;
    setButtonColor(ui->pushButton, Qt::red);
    setButtonColor(ui->pushButton_2, Qt::darkGray);
}
