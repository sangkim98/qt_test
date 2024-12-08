#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgraphicsscene.h>
#include <QGraphicsView>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void onOpenImage();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
