#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = new RenderArea;
    kSelectArea = new KSelectArea;
    this->ui->renderAreaLayout->addWidget(this->renderArea);
    this->ui->KSelectLayout->addWidget(this->kSelectArea);

    this->displayedValue = 0;
    this->updateRenderer();
    this->simuRunning=0;
    this->simuStarted=0;
    this->isLoading=false;
    this->isDrawing=0;

    this->inrx=320;
    this->inry=160;

    timer.start(50, this);

    // default simulation parameters
    this->simulationSettings=SimulationSettings();
    this->simulationSettings.setRx(320);
    this->simulationSettings.setRy(160);

    SimulationSettings::initSimulationSettingsSystem();

    this->simulationSettings.potDistr->zeroPotential();
    this->simulationSettings.potDistr->setRectangle(400,410,156,164,100000);
    this->simulationSettings.potDistr->setRectangle(400,410,170,300,100000);
    this->simulationSettings.potDistr->setRectangle(400,410,10,150,100000);
    this->qwave.initiateWavePacket(this->simulationSettings);
    this->qwave.initiatePropx();

    // connecting the UI elements to the right functions
    connect(this->ui->startButton, SIGNAL(clicked()),this, SLOT(start_butt()));
    connect(this->ui->addPotButton, SIGNAL(clicked()),this, SLOT(addr_butt()));
    connect(this->ui->resetButton, SIGNAL(clicked()),this, SLOT(rst_butt()));
    connect(this->ui->resetPotentialButton, SIGNAL(clicked()),this, SLOT(rstpot_butt()));
    connect(this->ui->setkSlider, SIGNAL(valueChanged(int)),this,SLOT(sliderChange()));
    connect(this->ui->setSigmaSlider, SIGNAL(valueChanged(int)),this,SLOT(sliderChange()));
    connect(this->ui->setRButton,SIGNAL(clicked()),this, SLOT(setR_butt()));
    connect(this->ui->deleteButton,SIGNAL(clicked()),this, SLOT(del_butt()));

    connect(this->ui->actionSave, SIGNAL(triggered()), this, SLOT(saveSimulation()));
    connect(this->ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadSimulation()));
    connect(this->ui->menuFile, SIGNAL(aboutToShow()),this, SLOT(stopRenderAreaInteractions()));
    connect(this->ui->menuHelp, SIGNAL(aboutToShow()),this, SLOT(stopRenderAreaInteractions()));
    connect(this->ui->actionAbout, SIGNAL(triggered()) ,this, SLOT(aboutWindow()));
    connect(this->ui->actionOnline_help , SIGNAL(triggered()) ,this, SLOT(onlineHelp()));
    connect(this->ui->actionNew , SIGNAL(triggered()) ,this, SLOT(newSimulation()));

    connect(this->ui->radioRe, SIGNAL(clicked()) ,this, SLOT(setDisplayRe()));
    connect(this->ui->radioIm, SIGNAL(clicked()) ,this, SLOT(setDisplayIm()));
    connect(this->ui->radioNorm, SIGNAL(clicked()) ,this, SLOT(setDisplayNorm()));

    setWindowTitle(tr("Schrödinger Sandbox"));
    this->updateRenderer();
    this->rst_butt();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInitialCond()
{
    this->inkx = this->kSelectArea->getkx()*this->ui->setkSlider->sliderPosition()/kSliderFactor;
    this->inky = -this->kSelectArea->getky()*this->ui->setkSlider->sliderPosition()/kSliderFactor;

    this->simulationSettings.setKx(this->kSelectArea->getkx()*this->ui->setkSlider->sliderPosition()/kSliderFactor);
    this->simulationSettings.setKy(-this->kSelectArea->getky()*this->ui->setkSlider->sliderPosition()/kSliderFactor);

    this->insigma = this->ui->setSigmaSlider->sliderPosition()/sigmaSliderFactor;

    this->simulationSettings.setSigma(this->ui->setSigmaSlider->sliderPosition()/sigmaSliderFactor);

    double sliderKPos = (double) this->ui->setkSlider->sliderPosition();
    QString kNorm;
    QString kLabel = "|k| = ";
    kNorm.setNum(sliderKPos);
    this->ui->kValueLabel->setText(kLabel + kNorm);

    double sliderSigmaPos = (double) this->ui->setSigmaSlider->sliderPosition();
    QString sigma;
    QString sigmaLabel = "sigma = ";
    sigma.setNum(sliderSigmaPos);
    this->ui->sigmaValueLabel->setText(sigmaLabel + sigma);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (this->simuRunning==1)
    {
        this->qwave.propagate();
        this->updateRenderer();
    }
}

void MainWindow::updateRenderer()
{
    for (int i=0;i<640;i++)
        for (int j=0;j<320;j++)
        {
            renderArea->updateGrid(i,j,this->qwave.returnSquarePot(i,j));
            switch(displayedValue)
            {
                case 0 :
                    renderArea->updateGrid(i,j,this->qwave.returnSquarePot(i,j));
                    break;
                case 1 :
                    renderArea->updateGrid(i,j,this->qwave.returnReal(i,j));
                    break;
                case 2 :
                    renderArea->updateGrid(i,j,this->qwave.returnIm(i,j));
                    break;
                case 3 :
                    renderArea->updateGrid(i,j,this->qwave.returnSquarePotk(i,j));
                    break;
            }
        }
    renderArea->updateRectPotList(this->simulationSettings.potDistr->rectanglePotList);
    renderArea->repaint();
}

void MainWindow::rstpot_butt()
{
    this->simulationSettings.potDistr->zeroPotential();
    this->qwave.initiateWavePacket(this->simulationSettings);
    this->qwave.initiatePropx();
    this->updateRenderer();
    this->stopRenderAreaInteractions();
}

// add rectangle potential
void MainWindow::addr_butt()
{
    this->stopRenderAreaInteractions();
    this->setCursor(Qt::CrossCursor);
    this->isDrawing=1;
}

void MainWindow::rst_butt()
{
    this->simuRunning=0;
    this->simuStarted=0;
    this->ui->startButton->setText("Start the simulation");

    this->ui->setkSlider->setEnabled(true);
    this->ui->setSigmaSlider->setEnabled(true);
    this->ui->addPotButton->setEnabled(true);
    this->ui->resetPotentialButton->setEnabled(true);
    this->ui->setRButton->setEnabled(true);
    this->ui->deleteButton->setEnabled(true);

    this->kSelectArea->setkSelectActive();

    this->updateInitialCond();

    this->qwave.initiateWavePacket(this->simulationSettings);
    this->qwave.initiatePropx();
    this->updateRenderer();
}

void MainWindow::start_butt()
{
    this->stopRenderAreaInteractions();

    if (this->simuRunning==0)
    {
        this->ui->setkSlider->setEnabled(false);
        this->ui->setSigmaSlider->setEnabled(false);
        this->ui->startButton->setText("Pause");

        this->ui->addPotButton->setEnabled(false);
        this->ui->resetPotentialButton->setEnabled(false);
        this->ui->setRButton->setEnabled(false);
        this->ui->deleteButton->setEnabled(false);

        if (this->simuStarted==0)
        {
            this->simuStarted=1;
            this->qwave.initiatePropx();
            this->kSelectArea->setkSelectInactive();
        }
        this->simuRunning=1;

    }
    else
    {
        if (this->simuStarted==1)
        {
            this->simuRunning=0;
            this->ui->startButton->setText("Resume");
        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (this->renderArea->underMouse())
    {
        // if the user is drawing a potential rectangle
        if (this->isDrawing == 2)
        {
            this->coord2=event->pos();
            int xmin = std::min(this->coord1.x()-xShift,coord2.x()-xShift);
            int xmax = std::max(this->coord1.x()-xShift,coord2.x()-xShift);
            int ymin = std::min(320+yShift-this->coord1.y(),320+yShift-coord2.y());
            int ymax = std::max(320+yShift-this->coord1.y(),320+yShift-coord2.y());

            EnergySelection *energyWindows = new EnergySelection(this);

            float energyDial;
            if (energyWindows->exec() == 1)
            {
                if (energyWindows->Accepted) energyDial = energyWindows->returnEnergy();
                this->simulationSettings.potDistr->setRectangle(xmin,xmax,ymin,ymax,energyDial);
            }

            this->isDrawing=0;
            this->renderArea->setIsDrawingRectangle(false);
            this->rst_butt();
        }   
    }
    this->stopRenderAreaInteractions();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // if the user is drawing a potential rectangle
    if (this->isDrawing == 2)
    {
        QPoint coord3=event->pos();
        int xtemp=coord3.x()-xShift;
        // 320
        int ytemp=-yShift+coord3.y();
        QPoint temp = QPoint(xtemp,ytemp);
        this->renderArea->setCoord2(temp);
        this->rst_butt();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (this->simuRunning == 0 && this->simuStarted == 0)
    {
        // change the direction of the wave
        if (this->kSelectArea->underMouse())
        {
            QPoint coord = event->pos();
            this->kSelectArea->clicDetected(coord);
            this->updateInitialCond();
            this->rst_butt();
        }

        if (this->isDrawing == 1 && !this->renderArea->underMouse())
        {
            this->isDrawing = 0;
        }

        if (this->renderArea->underMouse())
        {
            // select a rectangle
            if (this->isDrawing == 0)
            {
                QPoint coordtemp = event->pos();
                int xtemp=coordtemp.x()-xShift;
                //342
                int ytemp=320+yShift-coordtemp.y();
                int recttemp = this->qwave.getPotentialDistribution()->isOnRectangle(xtemp,ytemp,this->renderArea->getSelectedRectangle());
                if (recttemp != -1)
                {
                    this->renderArea->setSelectedRectangle(recttemp);
                }
                else
                {
                    this->renderArea->setSelectedRectangle(-1);
                }
                this->updateRenderer();
            }

            // start drawing a rectangle (if the user clicked "add potential")
            if (this->isDrawing == 1)
            {
                this->coord1=event->pos();
                this->isDrawing=2;
                int xtemp=this->coord1.x()-xShift;
                int ytemp=-yShift+this->coord1.y();
                QPoint temp = QPoint(xtemp,ytemp);
                this->renderArea->setCoord1(temp);
                this->renderArea->setIsDrawingRectangle(true);
            }

            // change the position of the wave
            if (this->isSettingR == true)
            {
                QPoint coord=event->pos();
                int xtemp=coord.x()-xShift;
                int ytemp=-yShift+coord.y();
                this->simulationSettings.setRx(xtemp);
                this->simulationSettings.setRy(ytemp);
                this->isSettingR=false;
                this->rst_butt();
            }
        }
    }
}

void MainWindow::sliderChange()
{
    this->stopRenderAreaInteractions();
    if (this->simuRunning == 0 && this->simuStarted == 0 && this->isLoading == false)
    {
        this->updateInitialCond();
        this->rst_butt();
    }
}

void MainWindow::saveSimulation()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save simulation settings"), "",
            tr("Simulation settings (*.dat);;All Files (*)"));

    if (fileName.isEmpty())
             return;
    else
    {
             QFile file(fileName);
             if (!file.open(QIODevice::WriteOnly))
             {
                 QMessageBox::information(this, tr("Unable to open file"), file.errorString());
                 return;
             }


        QDataStream out(&file);   // we will serialize the data into the file
        out << this->simulationSettings;
        file.close();
    }

}

void MainWindow::loadSimulation()
{
    this->isLoading=true;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load simulation settings"), "",
            tr("Simulation settings (*.dat);;All Files (*)"));

    if (fileName.isEmpty())
             return;
    else
    {
             QFile file(fileName);
             if (!file.open(QIODevice::ReadOnly))
             {
                 QMessageBox::information(this, tr("Unable to open file"), file.errorString());
                 return;
             }


        QDataStream in(&file);   // we will serialize the data into the file
        SimulationSettings simuTemp;
        in >> simuTemp;
        this->simulationSettings = simuTemp;
        this->simulationSettings.potDistr->updatePotentialFromAllDatas();
        file.close();


        this->ui->setSigmaSlider->setSliderPosition(sigmaSliderFactor*this->simulationSettings.getSigma());
        this->ui->setkSlider->setSliderPosition(kSliderFactor*sqrt( this->simulationSettings.getKx()*this->simulationSettings.getKx()+this->simulationSettings.getKy()*this->simulationSettings.getKy()));
        this->kSelectArea->setkx(this->simulationSettings.getKx()*kSliderFactor/this->ui->setkSlider->sliderPosition());
        this->kSelectArea->setky(this->simulationSettings.getKy()*kSliderFactor/this->ui->setkSlider->sliderPosition());

        this->qwave.initiateWavePacket(this->simulationSettings);
        this->qwave.initiatePropx();
        this->rst_butt();
    }
    this->isLoading=false;


}

void MainWindow::setR_butt()
{
    this->stopRenderAreaInteractions();
    this->isSettingR=true;
    this->setCursor(Qt::CrossCursor);
}

void MainWindow::stopRenderAreaInteractions()
{
    this->isDrawing=0;
    this->isSettingR=false;
    this->setCursor(Qt::ArrowCursor);
}

void MainWindow::aboutWindow()
{
    if (this->simuRunning==1)
    {
        start_butt();
    }
    AboutDialog *about = new AboutDialog(this);
    about->exec();
}

void MainWindow::onlineHelp()
{
    if (this->simuRunning==1)
    {
        start_butt();
    }
    QString link = "https://github.com/JulienBordaz/SchrodingerSandbox/blob/master/README.md";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::newSimulation()
{
    if (this->simuRunning==1)
    {
        start_butt();
    }
    NewSimDialog *newSimulationDialog = new NewSimDialog(this);
    if(newSimulationDialog->exec() == 1)
    {
        int option = newSimulationDialog->getOption();
        switch (option)
        {
            case 0:
                rstpot_butt();
                this->simulationSettings=SimulationSettings();
                this->simulationSettings.setRx(320);
                this->simulationSettings.setRy(160);
                this->simulationSettings.potDistr->zeroPotential();
                this->simulationSettings.potDistr->setRectangle(395,400,5,310,0.0035);
                this->ui->setSigmaSlider->setSliderPosition(50);
                this->ui->setkSlider->setSliderPosition(50);
                this->kSelectArea->setkx(1);
                this->kSelectArea->setky(0);
                updateInitialCond();
                this->qwave.initiateWavePacket(this->simulationSettings);
                this->qwave.initiatePropx();
                rst_butt();
                break;
            case 1:
                rstpot_butt();
                this->simulationSettings=SimulationSettings();
                this->simulationSettings.setRx(320);
                this->simulationSettings.setRy(160);
                this->simulationSettings.potDistr->zeroPotential();
                this->simulationSettings.potDistr->setRectangle(400,410,156,164,10000);
                this->simulationSettings.potDistr->setRectangle(400,410,170,300,10000);
                this->simulationSettings.potDistr->setRectangle(400,410,10,150,10000);
                this->ui->setSigmaSlider->setSliderPosition(50);
                this->ui->setkSlider->setSliderPosition(50);
                this->kSelectArea->setkx(1);
                this->kSelectArea->setky(0);
                updateInitialCond();
                this->qwave.initiateWavePacket(this->simulationSettings);
                this->qwave.initiatePropx();
                rst_butt();
                break;
            case 2:
                rstpot_butt();
                this->simulationSettings=SimulationSettings();
                this->simulationSettings.setRx(320);
                this->simulationSettings.setRy(160);
                this->simulationSettings.potDistr->zeroPotential();
                this->ui->setSigmaSlider->setSliderPosition(50);
                this->ui->setkSlider->setSliderPosition(50);
                this->kSelectArea->setkx(1);
                this->kSelectArea->setky(0);
                updateInitialCond();
                this->qwave.initiateWavePacket(this->simulationSettings);
                this->qwave.initiatePropx();
                rst_butt();
                break;
        }
    }
}

void MainWindow::setDisplayRe()
{
    this->displayedValue=1;
    this->updateRenderer();
}

void MainWindow::setDisplayIm()
{
    this->displayedValue=2;
    this->updateRenderer();
}

void MainWindow::setDisplayNorm()
{
    this->displayedValue=0;
    this->updateRenderer();
}

void MainWindow::del_butt()
{
    this->simulationSettings.potDistr->removePotentialData(this->renderArea->getSelectedRectangle());
    this->qwave.initiateWavePacket(this->simulationSettings);
    this->qwave.initiatePropx();
    this->rst_butt();
}
