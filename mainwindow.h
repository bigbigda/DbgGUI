#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "codeedit.h"
#include "addresswidget.h"
#include "memoryviewer.h"

class QAction;
class QListWidget;
class QMenu;
class QTextEdit;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadFile(const QString &fileName);
    void loadFile2(const QString &fileName);

      QFile file;


private slots:

    void newLetter();
    void open();
    void open2();
    void save();
    void saveAs();
    void run();
    void step();
    void reRun();
    void stop();
    void hideFloat();
    void showFloat();
private:

    int commandStatus;   // 0 run  1 step  2  reRun  3 stop
    void createActions();
    void createStatusBar();
    void createDockWindows();
    void createFloatDock();
    void setupData();

    CodeEditor      *SPUEdit;
    CodeEditor      *MPUEdit;
    QListWidget     *customerList;
    QListWidget     *paragraphsList;
    AddressWidget   *addressWidget;
    MemoryViewer    *memoryviewer;
    QMenu           *viewMenu;
    QDockWidget     *dock4;

    QDockWidget     *floatDock[17];
    CodeEditor      *floatEdit[17];
    double scaleFactorX;
    double scaleFactorY;

};



#endif // MAINWINDOW_H
