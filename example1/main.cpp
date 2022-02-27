#include <QMainWindow>
#include <QApplication>
#include <QtCharts>

int main (int argc, char *argv[]) {

    static const QStringList themes = { "Light", "Cerulean", "Dark", "Sand",
                                        "NCS", "Contrast", "Icy", "Qt" };

    static const auto withCheck = [](QAction *a, bool checked) {
        a->setCheckable(true);
        a->setChecked(checked);
        return a;
    };

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QMainWindow w;

    // -------- CHART SETUP --------------------------------------------------

    QLineSeries *series = new QLineSeries;
    series->setName("Extremely Interesting Data");
    series->append(0, 0);
    series->append(1, 2);
    series->append(2, 1);
    series->append(3, 4);

    QChart *chart = new QChart;
    chart->addSeries(series);

    // laxis = left side y axis, xaxis = x axis
    chart->createDefaultAxes();
    QAbstractAxis *laxis = chart->axes(Qt::Vertical).first();

    // raxis = right side y axis
    QValueAxis *raxis = new QValueAxis;
    raxis->setTickCount(11); // so grid lines don't line up with left axis
    chart->addAxis(raxis, Qt::AlignRight);
    series->attachAxis(raxis);

    QChartView *view = new QChartView(chart);
    w.setCentralWidget(view);

    // -------- TOOLBAR SETUP ------------------------------------------------

    QToolBar *toolbar = w.addToolBar("Controls");
    QActionGroup *actions = new QActionGroup(&w);
    for (int theme = 0; theme < themes.size(); ++ theme)
        withCheck(actions->addAction(toolbar->addAction(themes[theme], [&,theme](){
            chart->setTheme((QChart::ChartTheme)theme);
        })), theme == chart->theme());

    toolbar->addSeparator();
    QAction *lvis = withCheck(toolbar->addAction("Left Axis", [&]() {
        laxis->setVisible(lvis->isChecked());
    }), true);
    QAction *rvis = withCheck(toolbar->addAction("Right Axis", [&]() {
        raxis->setVisible(rvis->isChecked());
    }), true);

    // -----------------------------------------------------------------------

    w.resize(800, 600);
    w.show();
    return a.exec();

}
