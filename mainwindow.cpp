#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAttribute(Qt::WA_Hover, true);
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->setMouseTracking(true);
    connect(ui->menuOpen->addAction("Image"), &QAction::triggered, this, &MainWindow::onOpenImage);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::onOpenImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image File", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!fileName.isEmpty())
    {
        QPixmap pixmap(fileName);
        if (!pixmap.isNull())
        {
            // Clear the scene and add the image
            scene->clear();
            scene->addPixmap(pixmap);
            scene->setSceneRect(pixmap.rect()); // Adjust the scene size to fit the image
        }
        else
        {
            // Handle invalid image loading
            QMessageBox::warning(this, "Error", "Failed to load the image.");
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->graphicsView && (event->type() == QEvent::MouseMove || event->type() == QEvent::HoverMove))
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());

        qDebug() << "Mouse position in scene:" << scenePos;

        if (scenePos.x() >= 0 && scenePos.y() >= 0) {
            ui->coord->setText(QString("X: %1, Y: %2")
                                   .arg(static_cast<int>(scenePos.x()))
                                   .arg(static_cast<int>(scenePos.y())));
        } else {
            ui->coord->setText("");
        }

        return true;
    }

    return QMainWindow::eventFilter(obj, event); // Pass unhandled events to the base class
}
