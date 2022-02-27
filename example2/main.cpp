#include <QMainWindow>
#include <QApplication>
#include <QtCharts>

int main (int argc, char *argv[]) {

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QMainWindow w;

    // -------- CHART SETUP --------------------------------------------------

    const QChart::ChartTheme Theme = QChart::ChartThemeHighContrast;
    enum When { BeforeAddSeries, BeforeAddAxes, BeforeSetView, BeforeShowView, AfterEverything };

    QChartView *view = nullptr;

    static const auto setupChart = [&](When when){ return [&,when]() {

        if (view) {
            view->deleteLater();
            view = nullptr;
        }

        QLineSeries *series = new QLineSeries;
        series->setName("Extremely Interesting Data");
        series->append(0, 0);
        series->append(1, 2);
        series->append(2, 1);
        series->append(3, 4);

        QChart *chart = new QChart;

        if (when == BeforeAddSeries) chart->setTheme(Theme);
        chart->addSeries(series);
        if (when == BeforeAddAxes) chart->setTheme(Theme);
        chart->createDefaultAxes();
        if (when == BeforeSetView) chart->setTheme(Theme);
        view = new QChartView(chart);
        if (when == BeforeShowView) chart->setTheme(Theme);
        w.setCentralWidget(view);
        if (when == AfterEverything) chart->setTheme(Theme);

    }; };

    setupChart(BeforeSetView)();

    // -------- TOOLBAR SETUP ------------------------------------------------

    QToolBar *toolbar = w.addToolBar("Controls");
    toolbar->addAction("BeforeAddSeries", setupChart(BeforeAddSeries));
    toolbar->addAction("BeforeAddAxes", setupChart(BeforeAddAxes));
    toolbar->addAction("BeforeSetView", setupChart(BeforeSetView));
    toolbar->addAction("BeforeShowView", setupChart(BeforeShowView));
    toolbar->addAction("AfterEverything", setupChart(AfterEverything));

    // -----------------------------------------------------------------------

    w.resize(800, 600);
    w.show();
    return a.exec();

}
