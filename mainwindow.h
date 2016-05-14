#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QBasicTimer>
#include <QMouseEvent>
#include <QPoint>
#include <QWidget>
#include <QString>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <algorithm>
#include <QString>
#include <QFileDialog>
#include <QDesktopServices>
# include <cmath>

#include <quantumwave.h>
#include <renderarea.h>
#include <kselectarea.h>
#include <energyselection.h>
#include <aboutdialog.h>
#include <simulationsettings.h>
#include <newsimdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QuantumWave qwave;
    QBasicTimer timer;
    void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;
    void updateInitialCond();
    void updateRenderer();

    RenderArea *renderArea;
    KSelectArea *kSelectArea;
    int displayedValue;
    bool simuRunning;
    bool simuStarted;
    bool isLoading;
    bool isSettingR;
    QPoint coord1;
    QPoint coord2;
    // the state of drawing rectangle potential
    // 0 : not drawing
    // 1 : user clicked on "add potential"
    // 2 : user clicked then on the area and is actualy drawing
    int isDrawing;


    float inkx;
    float inky;
    float inrx;
    float inry;
    float insigma;

    SimulationSettings simulationSettings;

private slots:
    void start_butt();
    void addr_butt();
    void rst_butt();
    void del_butt();
    void rstpot_butt();
    void sliderChange();
    void saveSimulation();
    void loadSimulation();
    void setR_butt();
    void stopRenderAreaInteractions();
    void aboutWindow();
    void onlineHelp();
    void setDisplayRe();
    void setDisplayIm();
    void setDisplayNorm();
    void newSimulation();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
