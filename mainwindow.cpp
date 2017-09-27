#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextEdit"
#include <QHBoxLayout>

ProjectData projectdata;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

//    QTextEdit * textEdit=new QTextEdit;

//    setCorner(Qt::BottomRightCorner,dock3 );

    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    scaleFactorX = double(width) /1920;
    scaleFactorY = double(height) /1080;
    qDebug()<<height;
    qDebug()<<width;
    qDebug()<<scaleFactorX;
    qDebug()<<scaleFactorY;

    setupData();

    createActions();
    createStatusBar();
    createDockWindows();
    createFloatDock();
//    dock4->resize(500,500);
//    setBaseSize(500,600);
//    this->resize(800,500);
    this->setGeometry(1050*scaleFactorX,290*scaleFactorY,850*scaleFactorX,500*scaleFactorY);
//    setMinimumHeight(500);
//    setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
    setWindowTitle(tr("Dock Widgets"));

}

MainWindow::~MainWindow()
{

}

void MainWindow::setupData(){
    projectdata.regviewtablelist << "Main"<<"CUs" << "SHU" << "BIU"<< "MFetch" << "MReg" << "SPU";

    /**************************************************************/
    //QVector< QList<QPair<QString, QString>>>   vectorListofPairs;
    QPair<QString, QString> pair;
    QList<QPair<QString, QString> > listofPairs;


    pair.first = " MPU_PC";
    pair.second = "00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000";
    listofPairs.append(pair);
    pair.first = " SPU_PC";
    pair.second = "0";
    listofPairs.append(pair);
    projectdata.vectorListofPairs.append(listofPairs);
    listofPairs.clear();

    pair.first = " IALU.T0";
    pair.second= "1";
    listofPairs.append(pair);
    pair.first = " IALU.T1";
    pair.second= "2";
    listofPairs.append(pair);
    projectdata.vectorListofPairs.append(listofPairs);
    listofPairs.clear();

    pair.first="SHU0.T0";
    pair.second="3";
    listofPairs.append(pair);
    pair.first="SHU.T1";
    pair.second="4";
    listofPairs.append(pair);
    pair.first="SHU.T2";
    pair.second="5";
    listofPairs.append(pair);
    pair.first="SHU.T3";
    pair.second="6";
    listofPairs.append(pair);

   projectdata.vectorListofPairs.append(listofPairs);

   projectdata.memorydata = QByteArray("abcdefg!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1234567890");
}

//! [2]
void MainWindow::newLetter()
{
//    textEdit->clear();

//    QTextCursor cursor(textEdit->textCursor());
//    cursor.movePosition(QTextCursor::Start);
//    QTextFrame *topFrame = cursor.currentFrame();
//    QTextFrameFormat topFrameFormat = topFrame->frameFormat();
//    topFrameFormat.setPadding(16);
//    topFrame->setFrameFormat(topFrameFormat);

//    QTextCharFormat textFormat;
//    QTextCharFormat boldFormat;
//    boldFormat.setFontWeight(QFont::Bold);
//    QTextCharFormat italicFormat;
//    italicFormat.setFontItalic(true);

//    QTextTableFormat tableFormat;
//    tableFormat.setBorder(1);
//    tableFormat.setCellPadding(16);
//    tableFormat.setAlignment(Qt::AlignRight);
//    cursor.insertTable(1, 1, tableFormat);
//    cursor.insertText("The Firm", boldFormat);
//    cursor.insertBlock();
//    cursor.insertText("321 City Street", textFormat);
//    cursor.insertBlock();
//    cursor.insertText("Industry Park");
//    cursor.insertBlock();
//    cursor.insertText("Some Country");
//    cursor.setPosition(topFrame->lastPosition());
//    cursor.insertText(QDate::currentDate().toString("d MMMM yyyy"), textFormat);
//    cursor.insertBlock();
//    cursor.insertBlock();
//    cursor.insertText("Dear ", textFormat);
//    cursor.insertText("NAME", italicFormat);
//    cursor.insertText(",", textFormat);
//    for (int i = 0; i < 3; ++i)
//        cursor.insertBlock();
//    cursor.insertText(tr("Yours sincerely,"), textFormat);
//    for (int i = 0; i < 3; ++i)
//        cursor.insertBlock();
//    cursor.insertText("The Boss", textFormat);
//    cursor.insertBlock();
//    cursor.insertText("ADDRESS", italicFormat);
}
void MainWindow::loadFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);

    SPUEdit->setPlainText(in.readAll());

//    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::loadFile2(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);

    QString textMPUCode = in.readAll();
    MPUEdit->setPlainText(textMPUCode);

    for(int i =0;i<17;i++){
        floatEdit[i]->setPlainText(textMPUCode);

       QTextCursor text_cursor(floatEdit[i]->document()->findBlockByNumber(10+i*5));
        floatEdit[i]->setTextCursor(text_cursor);
        floatEdit[i]->centerCursor();
    }
    file.close();

//    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
        loadFile(fileName);
}
void MainWindow::open2(){
    QString fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty())
        loadFile2(fileName);


}
void MainWindow::save(){

}

void MainWindow::saveAs(){

}
void MainWindow::run(){

    QTextCursor text_cursor(SPUEdit->document()->findBlockByNumber(100));
    SPUEdit->setTextCursor(text_cursor);
//    SPUEdit->verticalScrollBar()->setValue(12);
    SPUEdit->centerCursor();
    dock4->show();
//    resi
    QList<QDockWidget*> tmpDockWidget;
//    tmpDockWidget.append(dock3);
    tmpDockWidget.append(dock4);
    QList<int> tmpSizeList;
    tmpSizeList.append(500*scaleFactorY);
    resizeDocks(tmpDockWidget,tmpSizeList,Qt::Vertical);
    commandStatus = 0;

    //chrzControl
        //setnumber
                //      SPUEdit->setTextCursor(text_cursor);
                //      SPUEdit->centerCursor();
                //      dock4->show();
        //setMemory
        //     projectdata.memorydata = QByteArray("abcdefg!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        //     qDebug()<<projectdata.memorydata.toHex();
                //      memoryviewer->setData(projectdata.memorydata);
       // paint or delete the breakpoint in view
                //    int blockNumber = 2;
                //    int index = SPUEdit->breakpoints.indexOf(blockNumber);
                //    if(index != -1){
                //        SPUEdit->breakpoints.remove(index);
                //    }
                //    else
                //        SPUEdit->breakpoints<<blockNumber;
                //    SPUEdit->update();


}

void MainWindow::step(){

    qDebug()<<"step";
    commandStatus = 1;
    qDebug()<<SPUEdit->breakpoints.size();
//    int blockNumber = 2;
//    int index = SPUEdit->breakpoints.indexOf(blockNumber);
//    if(index != -1){
//        SPUEdit->breakpoints.remove(index);
//    }
//    else
//        SPUEdit->breakpoints<<blockNumber;
//    SPUEdit->update();

    //chrzControl
}

void MainWindow::reRun(){

    QString fileName = QFileDialog::getOpenFileName(this, "Open File",QDir::homePath());
           if(!fileName.isEmpty()){
               file.setFileName(fileName);
               memoryviewer->setData(file);
               qDebug()<<"fsfds";
           }
    commandStatus = 2;
    //chrzControl
}


void MainWindow::stop(){

    qDebug()<<"stop";
    commandStatus = 3;
    //chrzControl

}

void MainWindow::createActions(){

//new
    QMenu *fileMenu = menuBar() -> addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));
//    const QIcon newIcon = QIcon::fromTheme("document-new",QIcon(":/images/new.png"));
//    QAction *newLetterAct = new QAction(newIcon, tr("&New Letter"), this);
//    newLetterAct->setShortcuts(QKeySequence::New);
//    newLetterAct->setStatusTip(tr("Create a new form letter"));
//    connect(newLetterAct, &QAction::triggered, this, &MainWindow::newLetter);
//    fileToolBar->addAction(newLetterAct);
//    fileMenu->addAction(newLetterAct);
//open1
    const QIcon openIcon = QIcon::fromTheme("document-open",QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon,tr("&Open SPU"),this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a SPU file"));
    connect(openAct,&QAction::triggered,this,&MainWindow::open);
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);
//open2

    QIcon n1   = QIcon::fromTheme("document-open",QIcon(":/images/open.png"));
    QPixmap n2 = n1.pixmap(n1.actualSize(QSize(128,128)));
//    QBitmap mask = n2.createMaskFromColor(QColor('white'),Qt::MaskInColor);
//    n2.fill((QColor('blue')));
//    n2.setMask(mask);


        const QIcon openIcon2 = QIcon(n2);
        QAction *openAct2 = new QAction(openIcon2,tr("&Open MPU"),this);
        openAct2->setShortcut(QKeySequence::Print);
        openAct2->setStatusTip(tr("Open a MPU file"));
        connect(openAct2,&QAction::triggered,this,&MainWindow::open2);
        fileMenu->addAction(openAct2);
        fileToolBar->addAction(openAct2);

////Save As
//    const QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
//    QAction *saveAsAct = fileMenu->addAction(saveAsIcon, tr("Save &As..."), this, &MainWindow::saveAs);
//    saveAsAct->setShortcuts(QKeySequence::SaveAs);
//    saveAsAct->setStatusTip(tr("Save the document under a new name"));

//run
    QMenu *debugMenu = menuBar()->addMenu(tr("&Debug"));
    QToolBar*debugToolBar = addToolBar(tr("Debug"));
    const QIcon runIcon = QIcon::fromTheme("media-playback-start", QIcon(":/images/undo.png"));  //view-refresh process-stop
    QAction *runAct = new QAction(runIcon, tr("&Run"), this);
    runAct->setShortcuts(QKeySequence::Refresh);
    runAct->setStatusTip(tr("run the simulation"));
    connect(runAct, &QAction::triggered, this, &MainWindow::run);
    debugMenu->addAction(runAct);
    debugToolBar->addAction(runAct);

    //step
        const QIcon stepIcon = QIcon::fromTheme("media-seek-forward", QIcon(":/images/undo.png"));  //view-refresh process-stop
        QAction *stepAct = new QAction(stepIcon, tr("&Step"), this);
    //    stepIconAct->setShortcuts(QKeySequence::Undo);
        stepAct->setStatusTip(tr("step"));
        connect(stepAct, &QAction::triggered, this, &MainWindow::step);
        debugMenu->addAction(stepAct);
        debugToolBar->addAction(stepAct);

//reRun
    const QIcon undoIcon = QIcon::fromTheme("view-refresh", QIcon(":/images/undo.png"));  //view-refresh process-stop
    QAction *reRunAct = new QAction(undoIcon, tr("&reRun"), this);
//    reRunAct->setShortcuts(QKeySequence::Undo);
    reRunAct->setStatusTip(tr("rerun the simulation"));
    connect(reRunAct, &QAction::triggered, this, &MainWindow::reRun);
    debugMenu->addAction(reRunAct);
    debugToolBar->addAction(reRunAct);

    //Stop
        const QIcon stopIcon = QIcon::fromTheme("media-playback-stop", QIcon(":/images/undo.png"));  //view-refresh process-stop
        QAction *stopAct = new QAction(stopIcon, tr("&Stop"), this);
    //    reRunAct->setShortcuts(QKeySequence::Undo);
        stopAct->setStatusTip(tr("stop the simulation"));
        connect(stopAct, &QAction::triggered, this, &MainWindow::stop);
        debugMenu->addAction(stopAct);
        debugToolBar->addAction(stopAct);

    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QToolBar*helpToolBar = addToolBar(tr("Help"));
    const QIcon helpIcon = QIcon::fromTheme("help-content"),QIcon(":/images/save.png");
    QAction *aboutAct = new QAction(helpIcon,tr("&Help"),this);
    aboutAct->setShortcuts(QKeySequence::HelpContents);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct,&QAction::triggered,this,&QApplication::aboutQt);
    helpToolBar->addAction(aboutAct);
    helpMenu->addAction(aboutAct);

}

void MainWindow::createStatusBar(){
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createFloatDock(){

    QStringList floatName;
    floatName<< "BIU2" <<"BIU1" <<"BIU0" << "MReg5" <<"MReg4"<<"MReg3" << "MReg2" <<"MReg1"<<"MReg0" <<"IFMAC" <<  "IFALU" << "IMAC" << "IALU"  << "SHU2" <<"SHU1"<<"SHU0" << "MFetch";

    floatDock[0] = new QDockWidget(floatName[0], this);
    floatDock[0]->setAllowedAreas(Qt::DockWidgetArea_Mask);
    floatEdit[0] = new CodeEditor;
    floatDock[0]->setWidget(floatEdit[0]);
    addDockWidget(Qt::BottomDockWidgetArea, floatDock[0]);
    floatDock[0]->setFloating(true);
    floatDock[0]->setGeometry(100,(150*0+40)*scaleFactorY,280*scaleFactorX,130*scaleFactorY);
    viewMenu->addAction(floatDock[0]->toggleViewAction());


    for (int i=1;i<17;i++){
        floatDock[i] = new QDockWidget(floatName[i], this);
        floatDock[i]->setAllowedAreas(Qt::DockWidgetArea_Mask);
        floatEdit[i] = new CodeEditor;
        floatDock[i]->setWidget(floatEdit[i]);
        floatDock[i]->setFloating(true);
//        floatEdit[i]->setGeometry();

//        floatEdit[i]->setSizePolicy();
        if(i<6){
            floatDock[i]->setGeometry(100,(150*i+40)*scaleFactorY,280*scaleFactorX,130*scaleFactorY);
        } else if (i <12) {
            floatDock[i]->setGeometry(100+300*scaleFactorX,(150*(i-6)+40)*scaleFactorY,280*scaleFactorX,130*scaleFactorY);
        }else {
            floatDock[i]->setGeometry(100+600*scaleFactorX,(150*(i-12)+40)*scaleFactorY,280*scaleFactorX,130*scaleFactorY);
        }
        addDockWidget(Qt::BottomDockWidgetArea, floatDock[i]);

        viewMenu->addAction(floatDock[i]->toggleViewAction());
//        floatEdit[i]->resize(100,200);
    }


}


//! [9]
void MainWindow::createDockWindows()
{
//    QWidget * textwidget = new QWidget(this);
//    textwidget->setWindowFlags(Qt::Widget);
    QVBoxLayout * spuvbox = new QVBoxLayout ;
    SPUEdit = new CodeEditor;
    QLabel *label1 = new QLabel("SPU Code");
    spuvbox->addWidget(label1);
    spuvbox->addWidget(SPUEdit);
    QWidget    * spuwidget = new QWidget;
    spuwidget->setLayout(spuvbox);
    spuvbox->setSpacing(0);
    SPUEdit->setContentsMargins(0,0,0,0);
    label1->setContentsMargins(0,0,0,0);
    SPUEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

    QVBoxLayout * mpuvbox = new QVBoxLayout ;
    MPUEdit = new CodeEditor;
    QLabel *label2 = new QLabel("MPU Code");
    mpuvbox->addWidget(label2);
    mpuvbox->addWidget(MPUEdit);
    QWidget    * mpuwidget = new QWidget;
    mpuwidget->setLayout(mpuvbox);
    mpuvbox->setSpacing(0);
    QSplitter * textsplitter = new QSplitter(Qt::Horizontal,0);
    mpuvbox->setContentsMargins(0,0,0,0);
    spuvbox->setContentsMargins(0,0,0,0);
    MPUEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

    MPUEdit->setContentsMargins(0,0,0,0);
    label2->setContentsMargins(0,0,0,0);
    textsplitter->setHandleWidth(2);
    textsplitter->addWidget(spuwidget);
    textsplitter->addWidget(mpuwidget);
//    textsplitter->setContentsMargins(0,0,0,0);
    setCentralWidget(textsplitter);
    setDockNestingEnabled(true);
// enable the dock can contain tow row(horizontal and vertiacal)

//    QDockWidget *dock = new QDockWidget(tr("SPU code"), this);
//    dock->setAllowedAreas(Qt::DockWidgetArea_Mask);


//    dock->setWidget(SPUEdit);
//    addDockWidget(Qt::TopDockWidgetArea, dock);
//    viewMenu->addAction(dock->toggleViewAction());

//    QDockWidget *dock2 = new QDockWidget(tr("MPU code"), this);
//    dock2->setAllowedAreas(Qt::DockWidgetArea_Mask);
//    addDockWidget(Qt::LeftDockWidgetArea,dock);



//    dock2->setWidget(MPUEdit);
//    splitDockWidget(dock,dock2,Qt::Horizontal);
//    viewMenu->addAction(dock2->toggleViewAction());

//    textwidget->layout()->layout()
//    textwidget->layout()->addWidget(MPUEdit);

//Regs
    QDockWidget *dock3 = new QDockWidget(tr("Registers"), this);
    dock3->setAllowedAreas(Qt::DockWidgetArea_Mask);
    addressWidget = new AddressWidget;
    dock3->setWidget(addressWidget);
    addDockWidget(Qt::BottomDockWidgetArea, dock3);
    viewMenu->addAction(dock3->toggleViewAction());

    dock4 = new QDockWidget(tr("Memory view"), this);
    dock4->setAllowedAreas(Qt::DockWidgetArea_Mask);
    memoryviewer = new MemoryViewer;

    dock4->setWidget(memoryviewer);
    addDockWidget(Qt::RightDockWidgetArea, dock4);
    viewMenu->addAction(dock4->toggleViewAction());
    memoryviewer->setData(projectdata.memorydata);
    dock4->hide();

//    dock4->setMinimumWidth(300);
    for(int i = 0; i<17; i++){
        floatDock[i] = 0;
    }
    QAction *hideAction = new QAction(tr("&HideFloat"),this);
    hideAction->setShortcut(QKeySequence::Replace);
    hideAction->setStatusTip(tr("Hide the float wigets for each slot"));
    connect(hideAction,&QAction::triggered,this,&MainWindow::hideFloat);
    viewMenu->addAction(hideAction);

    QAction *showAction = new QAction(tr("&ShowFloat"),this);
    showAction->setShortcut(QKeySequence::Save);
    showAction->setStatusTip(tr("Show all float wigets for each slot"));
    connect(showAction,&QAction::triggered,this,&MainWindow::showFloat);
    viewMenu->addAction(showAction);

}

void MainWindow::hideFloat(){
    for(int i = 0; i<17; i++){
        floatDock[i]->hide();
//         qDebug()<<"hide ";
//                ->hide();
    }
}

void MainWindow::showFloat(){
    QRect rec = QApplication::desktop()->screenGeometry();
    int height = rec.height();
    int width = rec.width();
    qDebug()<<height;
    qDebug()<<width;
//    scaleFactorX = double(width) ;
//    scaleFactorY = double(height) ;

    for(int i = 0; i<17; i++){
        floatDock[i]->setFloating(true);
        floatDock[i]->show();
////        floatEdit[i]->setGeometry();

////        floatEdit[i]->setSizePolicy();
        if(i<6){
            floatDock[i]->setGeometry(100,(150*i+40)*scaleFactorY,280*scaleFactorX,130*scaleFactorY);
        } else if (i <12) {
            floatDock[i]->setGeometry(100+300*scaleFactorX,(150*(i-6)+40)*scaleFactorY,280*scaleFactorX,130*scaleFactorY);
        }else {
            floatDock[i]->setGeometry(100+600*scaleFactorX,(150*(i-12)+40)*scaleFactorY,280*scaleFactorX,130*scaleFactorY);
        }
    }
}

/////////////////////////////////////////////////// add codeedit below

//the space of line number column
#define width_circle 5

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
    connect(lineNumberArea, &LineNumberArea::clicked, this, &CodeEditor::onClicked);
    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}


int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = width_circle + 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}


void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEditor::onClicked(int h)
{
    QTextBlock block = firstVisibleBlock();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    int blockNumber =  block.blockNumber();
    while (block.isValid()) {
        if (block.isVisible()) {
            if(h > top && h<bottom){
                int index = breakpoints.indexOf(blockNumber);
                if(index != -1){
                    breakpoints.remove(index);
                }
                else
                    breakpoints<<blockNumber;
                update();
                return;
            }
        }
        blockNumber++;
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
    }
}


void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            if(breakpoints.indexOf(blockNumber) != -1){
                painter.setBrush(Qt::red);
                painter.drawEllipse(0, top + (fontMetrics().height()-width_circle)/2, width_circle, width_circle);
            }
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

#undef width_circle
