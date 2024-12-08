#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graphsin(new QChart())
    , chartView(new QChartView(this))
    , series(new QLineSeries())
    , AxisT1(new QValueAxis())
    , AxisX1(new QValueAxis())

    , xz(new QChart())
    , xzchartView(new QChartView(this))
    , xzseries(new QLineSeries())
    , AxisT2(new QValueAxis())
    , AxisX2(new QValueAxis())

    , errorseries(new QLineSeries(this))
    , averageSeries(new QLineSeries())

{
    ui->setupUi(this);

    l = new QLabel(this);
    l->setText("f1");
    l->setGeometry(60,30,70,40);

    l1 = new QLabel(this);
    l1->setText("f2");
    l1->setGeometry(160,30,70,40);

    l2 = new QLabel(this);
    l2->setText("f3");
    l2->setGeometry(260,30,70,40);

    l3 = new QLabel(this);
    l3->setText("fd");
    l3->setGeometry(60,90,70,40);

    l4 = new QLabel(this);
    l4->setText("Отсчёты");
    l4->setGeometry(160,90,70,40);

    l5 = new QLabel(this);
    l5->setText("t1");
    l5->setGeometry(60,150,70,40);

    l10 = new QLabel(this);
    l10->setText("t2");
    l10->setGeometry(160,150,70,40);

    l6 = new QLabel(this);
    l6->setText("t1*");
    l6->setGeometry(60,210,70,50);

    l7 = new QLabel(this);
    l7->setText("t2*");
    l7->setGeometry(160,210,70,50);

    l8 = new QLabel(this);
    l8->setText("порог");
    l8->setGeometry(40,280,70,50);

    l9 = new QLabel(this);
    l9->setText("ширина");
    l9->setGeometry(150,280,70,50);


    af1 = new QLineEdit(this);
    af1->setGeometry(80,30,70,50);

    af2 = new QLineEdit(this);
    af2->setGeometry(180,30,70,50);

    af3 = new QLineEdit(this);
    af3->setGeometry(280,30,70,50);

    Num = new QLineEdit(this);
    Num->setGeometry(210,90,70,50);

    fdL = new QLineEdit(this);
    fdL->setGeometry(80,90,70,50);

    at1 = new QLineEdit(this);
    at1->setGeometry(80,150,70,50);

    at2 = new QLineEdit(this);
    at2->setGeometry(180,150,70,50);

    t1lockL = new QLineEdit(this);
    t1lockL->setGeometry(80,210,70,50);

    t2lockL = new QLineEdit(this);
    t2lockL->setGeometry(180,210,70,50);

    nL = new QLineEdit(this);
    nL->setGeometry(80,280,70,50);

    stepL=new QLineEdit(this);
    stepL->setGeometry(195,280,70,50);

    chartView->setGeometry(500,1,800,310);
    chartView->setPalette(Qt::white);
    chartView->setChart(graphsin);
    graphsin->addSeries(series);

    graphsin->setTitle("График исходного сигнала");
    AxisT1 = new QValueAxis();
    AxisX1 = new QValueAxis();
    AxisT1->setTitleText("T, c");
    AxisX1->setTitleText("X");
    graphsin->addAxis(AxisT1, Qt::AlignBottom);
    graphsin->addAxis(AxisX1, Qt::AlignLeft);
    series->attachAxis(AxisX1);
    series->attachAxis(AxisT1);

    xzchartView->setGeometry(500,281,800,313);
    xzchartView->setPalette(Qt::white);
    xzchartView->setChart(xz);

    xz->addSeries(xzseries);
    xz->setTitle("График error");
    AxisT2 = new QValueAxis();
    AxisX2 = new QValueAxis();
    AxisT2->setTitleText("t");
    AxisX2->setTitleText("x");
    xz->addAxis(AxisT2, Qt::AlignBottom);
    xz->addAxis(AxisX2, Qt::AlignLeft);
    xzseries->attachAxis(AxisX2);
    xzseries->attachAxis(AxisT2);

    xz->addSeries(averageSeries);
    averageSeries->attachAxis(AxisX2);
    averageSeries->attachAxis(AxisT2);

    QPushButton *ParametrsButton = new QPushButton("По умолчанию",this);
    ParametrsButton->setGeometry(160, 350, 100, 40);
    ParametrsButton->setStyleSheet(
        "QPushButton { background-color: blue; color: white; }"
        "QPushButton:hover { background-color: darkorange; }"
        );
    connect(ParametrsButton, &QPushButton::clicked,this, &MainWindow::onParametrsButtonClicked);

    QPushButton *playButton = new QPushButton("Старт", this);
    playButton->setGeometry(80, 350, 60, 40);
    playButton->setStyleSheet(
        "QPushButton { background-color: red; color: white; }"
        "QPushButton:hover { background-color: darkred; }"
        );
    connect(playButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete graphsin;
    delete chartView;
    delete series;
    delete xz;
    delete xzchartView;
    delete xzseries;
    delete AxisT1;
    delete AxisX1;
    delete AxisX2;
    delete AxisT2;
    delete errorseries;
    delete averageSeries;
}

void MainWindow::onParametrsButtonClicked()
{
    af1->setText("20");
    af2->setText("40");
    af3->setText("60");
    at1->setText("0.2");
    at2->setText("0.4");
    Num->setText("150");
    fdL->setText("300");
    nL->setText("0.03");
    stepL->setText("5");
}

void MainWindow::onPlayButtonClicked()
{
    QString f1Str = af1->text();
    double f1 = f1Str.toDouble();

    QString f2Str = af2->text();
    double f2 = f2Str.toDouble();

    QString f3Str = af3->text();
    double f3 = f3Str.toDouble();

    QString at1Str = at1->text();
    double t1 = at1Str.toDouble();

    QString at2Str = at2->text();
    double t2 = at2Str.toDouble();

    QString NumStr = Num->text();
    double N = NumStr.toDouble();

    QString fdStr = fdL->text();
    double fd = fdStr.toDouble();

    QString stepStr = stepL->text();
    int step = stepStr.toInt();

    QString nStr = nL->text();
    double n = nStr.toDouble();

    QString t1lockStr = t1lockL->text();
    double t1lock = t1lockStr.toDouble();

    QString t2lockStr = t2lockL->text();
    double t2lock = t2lockStr.toDouble();

    double minT = std::numeric_limits<double>::max();
    double maxT = std::numeric_limits<double>::lowest(); // Максимальное значение для оси T (Максимальное минимальное с учетом знака. (отличие от мин)
    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();

    QVector<double> graphsinus;
    graphsinus.resize(N);

    series->clear();
    xzseries->clear();
    errorseries->clear();
    averageSeries->clear();

    double fi = 0;
    double t = 0;
    double dlt_fi = 0;
    double del_t=1/fd;  //шаг по времени,
    for(int i=0;i<N;i++)
    {
        t=i/fd;

        if (t<t1)
        {
            dlt_fi = 2*M_PI*f1*del_t;
        }
        else if (t<t2)
        {
            dlt_fi = 2*M_PI*f2*del_t;
        }
        else
        {
            dlt_fi = 2*M_PI*f3*del_t;
        }
        fi+=dlt_fi;
        graphsinus[i]=qSin(fi);
        series->append(t,graphsinus[i]);

    if (t < minT) minT = t;
    if (t > maxT) maxT = t;

    if (graphsinus[i] < minX) minX = graphsinus[i];
    if (graphsinus[i] > maxX) maxX = graphsinus[i];

    qDebug() << "graphsin[" << i << "] = " << graphsinus[i];

    }

    if (graphsin->series().isEmpty())
    {
        graphsin->addSeries(series);
        series->attachAxis(AxisT1); // Привязываем ось времени (T)
        series->attachAxis(AxisX1); // Привязываем ось амплитуды (X)
    }

    AxisT1->setRange(minT, maxT); // Устанавливаем диапазон оси T
    AxisX1->setRange(minX, maxX); // Устанавливаем диапазон оси X

    graphsin->update();

//используем авторегрессионную модель прогнозирования, соответственно знаем след по 2 пред

    QVector<double> prediction;
    prediction.resize(N);

    int a1 = 1;
    double a2 = -2 * qCos(2 * M_PI * f2 * del_t);//-1.62
    qDebug()<<a2;
    // Вычисление автокорреляции для f2


    QVector <double> Esum;
    Esum.resize(N);

//нам нужно знать два предыдущих, чтобы строить все остальное.
    for (int i = 0; i < 2; i++)
    {
        prediction[i] = graphsinus[i];
        qDebug() << "Prediction[" << i << "] = " << prediction[i];
    }

    for (int i = 2; i < N; i++)
    {
        prediction[i] = -(a2 * graphsinus[i - 1] + a1 * graphsinus[i - 2]);
        qDebug() << "Prediction[" << i << "] = " << prediction[i];
    }

    for(int i=0;i<N;i++)
    {
        Esum[i] = pow((graphsinus[i] - prediction[i]),2);
        t=i/fd;
        xzseries->append(t, Esum[i]);
        qDebug()<<"prediction ["<<i<<"] ="<<Esum[i];


        if (t < minT) minT = t;
        if (t > maxT) maxT = t;

        if (Esum[i] < minX) minX = Esum[i];
        if (Esum[i] > maxX) maxX = Esum[i];
    }

    double windowSum = 0;
    QVector<double> average(N);

    for(int k=step;k<N-step-1;k++)
    {
        windowSum=0;
        double t = k * 1/fd;

        for(int i=-step;i<= step;i++)
        {
            windowSum += Esum[k+i];
        }
        average[k]=windowSum/(2*step+1);

        averageSeries->append(t, average[k]);  // Добавление среднего на график
        qDebug() << "Среднее значение для отсчёта [" << k << "] = " << average[k];

        if (t < minT) minT = t;
        if (t > maxT) maxT = t;

        if (average[k] < minX) minX = average[k];
        if (average[k] > maxX) maxX = average[k];
    }

    //Определение t1 и t2 на основе порога n

    bool t1_found = false, t2_found = false;

    for(int i=step;i<N-step;i++)
{
    double t = i * 1/fd;
    double currentAverage = average[i];

    if (!t1_found && currentAverage < n)
    {
        t1lock = t;  // Фиксируем момент уменьшения
        t1lockL->setText(QString::number(t1lock));
        t1_found = true;
    }

     if(t1_found && !t2_found && currentAverage > n)
        {
            t2lock = t;  // Фиксируем момент увеличения
            t2lockL->setText(QString::number(t2lock));
            t2_found = true;
            break;
        }
}

    AxisT2->setRange(minT, maxT);
    AxisX2->setRange(minX, maxX);

    xz->update();
}
