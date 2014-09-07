#ifndef DOMOTICASIMULATOR_H
#define DOMOTICASIMULATOR_H

#include <QMainWindow>

namespace Ui {
class DomoticaSimulator;
}

class DomoticaSimulator : public QMainWindow
{
    Q_OBJECT

public:
    explicit DomoticaSimulator(QWidget *parent = 0);
    ~DomoticaSimulator();

private:
    Ui::DomoticaSimulator *ui;
};

#endif // DOMOTICASIMULATOR_H
