/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>

#include <QPixmap>
#include <QMessageBox>
#include <QDesktopServices>
#include <QTimer>
#include <QLabel>
#include <QGLWidget>
#include <QPair>
#include <QColor>
#include <QDebug>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass)
    , m_statusBarTimer(new QTimer(this))
    , m_statusBarTime(new QLabel(this))
    , m_pendulumCount(0)
    , m_maskUpdates(false)
{
    ui->setupUi(this);

    // Create a timer to update the status bar
    connect(m_statusBarTimer, SIGNAL(timeout()), this, SLOT(updateStatusBar()));

    // Status bar widgets
    m_statusBarTime->setMinimumWidth(m_statusBarTime->fontMetrics().width("Time: 000.00s"));
    statusBar()->addPermanentWidget(m_statusBarTime);

    resetStatusBar();

    connect(ui->actionUseOpenGL, SIGNAL(toggled(bool)), this, SLOT(useOpenGL(bool)));

    // Boiler-plate actions
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    // Adding/removing pendulums
    connect(ui->toolButton_addPendulum, SIGNAL(clicked()),
            this, SLOT(addPendulum()));
    connect(ui->toolButton_removePendulum, SIGNAL(clicked()),
            this, SLOT(removePendulum()));
    connect(ui->pendulums, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changePendulum(int)));

    // Starting/stopping/pausing the simulation
    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(startSim()));
    QShortcut *start = new QShortcut(QKeySequence("Ctrl+R"), this);
    connect(start, SIGNAL(activated()), this, SLOT(startSim()));
    connect(ui->actionPause, SIGNAL(triggered()), this, SLOT(pauseSim()));
    connect(ui->actionStop, SIGNAL(triggered()), this, SLOT(stopSim()));
    QShortcut *stop = new QShortcut(QKeySequence("Ctrl+S"), this);
    connect(stop, SIGNAL(activated()), this, SLOT(stopSim()));

    // Zooming the simulation
    connect(ui->actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(ui->actionBestFit, SIGNAL(triggered()), this, SLOT(zoomBestFit()));

    // Update solving method
    connect(ui->odeSolver, SIGNAL(currentIndexChanged(QString)), this, SLOT(updatePendulum()));

    // Update dt and g
    connect(ui->dt, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->g, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));

    // Updating initial starting conditions (upper node)
    connect(ui->theta1, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->omega1, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->m1, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->l1, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));

    // Update initial starting conditions (lower node)
    connect(ui->theta2, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->omega2, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->m2, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));
    connect(ui->l2, SIGNAL(valueChanged(double)), this, SLOT(updatePendulum()));

    // Update pendulum colour and opacity
    connect(ui->upperColor, SIGNAL(colorChanged(QColor)), this, SLOT(updatePendulum()));
    connect(ui->lowerColor, SIGNAL(colorChanged(QColor)), this, SLOT(updatePendulum()));
    connect(ui->opacity, SIGNAL(valueChanged(int)), this, SLOT(updatePendulum()));

    // Update the combo box icon when the pendulum colour changes
    connect(ui->upperColor, SIGNAL(colorChanged(QColor)), this, SLOT(updateNodeColors()));
    connect(ui->lowerColor, SIGNAL(colorChanged(QColor)), this, SLOT(updateNodeColors()));

    // Defaults button
    connect(ui->defaults, SIGNAL(clicked()), this, SLOT(setDefaults()));

    // Add a default pendulum item
    addPendulum();
}

MainWindow::~MainWindow()
{
    delete ui;
}

Item *MainWindow::activeItem()
{
    return ui->pendulumView->pendula()[ui->pendulums->currentText()];
}

void MainWindow::resetStatusBar()
{
    // Restore the status bar items to their default values
    m_statusBarTime->setText("Time: 0.00s");
}

void MainWindow::addPendulum()
{
    // Create a new pendulum (will be delete by graphicsviewframwork)
    Item *pendulum = new Item();

    // Generate the name of the new pendulum
    QString name = QString("Pendulum %1").arg(++m_pendulumCount);

    // Add the pendulum to the scene
    ui->pendulumView->addPendulum(name, pendulum);

    // Add an item in the Pendulum's combo box for the new pendulum
    ui->pendulums->addItem(name);

    // Get the index of the newly added item
    int index = ui->pendulums->findText(name);

    // Make this the selected item
    ui->pendulums->setCurrentIndex(index);

    // Set the values to the defaults
    setDefaults();

    // Enable the remove button if there are >= 2 pendulums present
    if (ui->pendulums->count() >= 2)
    {
        ui->toolButton_removePendulum->setEnabled(true);
    }
}

void MainWindow::removePendulum()
{
    Item *active = activeItem();

    // Remove the item from the scene
    ui->pendulumView->removePendulum(ui->pendulums->currentText());

    // Release the memory associated with item
    delete active;

    // Remove the item from the combo box
    ui->pendulums->removeItem(ui->pendulums->currentIndex());

    // If there is only one pendulum left, disable the button
    if (ui->pendulums->count() == 1)
    {
        ui->toolButton_removePendulum->setEnabled(false);
    }
}

void MainWindow::changePendulum(int)
{
    // Mask update events
    m_maskUpdates = true;

    // Update the solver
    ui->odeSolver->setCurrentIndex(ui->odeSolver->findText(activeItem()->solver()));

    // dt & g
    ui->dt->setValue(activeItem()->dt());
    ui->g->setValue(activeItem()->g());

    // Update the spin-box values
    ui->theta1->setValue(activeItem()->upper().theta);
    ui->omega1->setValue(activeItem()->upper().omega);
    ui->m1->setValue(activeItem()->upper().m);
    ui->l1->setValue(activeItem()->upper().l);

    ui->theta2->setValue(activeItem()->lower().theta);
    ui->omega2->setValue(activeItem()->lower().omega);
    ui->m2->setValue(activeItem()->lower().m);
    ui->l2->setValue(activeItem()->lower().l);

    ui->lowerColor->setColor(activeItem()->lowerColor());
    ui->upperColor->setColor(activeItem()->upperColor());
    ui->opacity->setValue(activeItem()->opacity());

    // Unmask updates
    m_maskUpdates = false;
}

void MainWindow::startSim()
{
    // Disable the start action and options dock
    ui->actionStart->setEnabled(false);
    ui->dockWidgetContents_model->setEnabled(false);

    // Enable the stop and pause actions
    ui->actionPause->setEnabled(true);
    ui->actionStop->setEnabled(true);

    // Enable the zoom controls
    ui->actionZoomIn->setEnabled(true);
    ui->actionZoomOut->setEnabled(true);
    ui->actionBestFit->setEnabled(true);

    // Start updating the status bar
    m_statusBarTimer->start(75);

    ui->pendulumView->startSim();
}

void MainWindow::pauseSim()
{
    ui->pendulumView->pauseSim();
}

void MainWindow::stopSim()
{
    // Enable the options dock and start buttons again
    ui->actionStart->setEnabled(true);
    ui->dockWidgetContents_model->setEnabled(true);

    // Disable the pause and stop actions
    ui->actionPause->setEnabled(false);
    ui->actionStop->setEnabled(false);

    // Disable the zoom controls
    ui->actionZoomIn->setEnabled(false);
    ui->actionZoomOut->setEnabled(false);
    ui->actionBestFit->setEnabled(false);

    // Stop the status bar timer
    m_statusBarTimer->stop();

    // Reset the status bar (time to 0)
    resetStatusBar();

    ui->pendulumView->stopSim();
}

void MainWindow::zoomIn()
{
    double newScale = ui->pendulumView->scaleFactor() / 1.25;

    ui->pendulumView->setScaleFactor(newScale);
}

void MainWindow::zoomOut()
{
    double newScale = ui->pendulumView->scaleFactor() * 1.25;

    ui->pendulumView->setScaleFactor(newScale);
}

void MainWindow::zoomBestFit()
{
    // Get the ideal scaling factor the the view
    double idealScale = ui->pendulumView->idealScaleFactor();

    // Set this to be the new scaling factor
    ui->pendulumView->setScaleFactor(idealScale);
}

void MainWindow::useOpenGL(bool on)
{
    if (on)
    {
        QGLFormat fmt;
        fmt.setSwapInterval(1);
        fmt.setSampleBuffers(true);

        ui->pendulumView->setViewport(new QGLWidget(fmt));
    }
    else
    {
        ui->pendulumView->setViewport(0);
    }
}

void MainWindow::updatePendulum()
{
    // Ensure that updates are not masked (such as when changing pendulums)
    if (m_maskUpdates)
    {
        return;
    }

    Item *item = activeItem();

    // Solver
    item->setSolver(ui->odeSolver->currentText());

    // dt & g
    item->setDt(ui->dt->value());
    item->setG(ui->g->value());

    // Upper node
    item->upper().theta = ui->theta1->value();
    item->upper().omega = ui->omega1->value();
    item->upper().m = ui->m1->value();
    item->upper().l = ui->l1->value();

    // Lower node
    item->lower().theta = ui->theta2->value();
    item->lower().omega = ui->omega2->value();
    item->lower().m = ui->m2->value();
    item->lower().l = ui->l2->value();

    // Color
    item->setUpperColor(ui->upperColor->color());
    item->setLowerColor(ui->lowerColor->color());
    item->setOpacity(ui->opacity->value());
}

void MainWindow::updateNodeColors()
{
    int index = ui->pendulums->currentIndex();

    QPixmap pm(ui->pendulums->iconSize());
    QPainter painter(&pm);

    activeItem()->drawIcon(&painter, pm.rect());

    // Set the icon to be the generated pixmap
    ui->pendulums->setItemIcon(index, QIcon(pm));
}

void MainWindow::updateStatusBar()
{
    QString timeStr;
    timeStr.setNum(ui->pendulumView->time() / 1000.0, 'f', 2);
    m_statusBarTime->setText(QString("Time: %1s").arg(timeStr));
}

QPair<QColor, QColor> MainWindow::randNodeColor()
{
    const double hue1 = qrand() * (1.0 / RAND_MAX);
    const double hue2 = fmod(hue1 + 0.3, 1.0);

    return qMakePair(QColor::fromHsvF(hue1, 1.0, 1.0),
                     QColor::fromHsvF(hue2, 1.0, 1.0));
}

void MainWindow::setDefaults()
{
    // Mask update events
    m_maskUpdates = true;

    ui->odeSolver->setCurrentIndex(0);
    ui->dt->setValue(0.005);
    ui->g->setValue(9.81);

    ui->theta1->setValue(1.0);
    ui->omega1->setValue(0.0);
    ui->m1->setValue(1.0);
    ui->l1->setValue(1.0);

    ui->theta2->setValue(1.0);
    ui->omega2->setValue(15.0);
    ui->m2->setValue(0.5);
    ui->l2->setValue(1.0);

    const QPair<QColor, QColor> nodeColors = randNodeColor();

    ui->upperColor->setColor(nodeColors.first);
    ui->lowerColor->setColor(nodeColors.second);
    ui->opacity->setValue(100);

    // Unmask update events and force an update
    m_maskUpdates = false;
    updatePendulum();

    // Update the pendulum's icon
    updateNodeColors();
}
