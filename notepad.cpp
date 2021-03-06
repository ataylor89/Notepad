#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    struct passwd *pw = getpwuid(getuid());
    homeDirectory = QString(pw->pw_dir);
    this->loadSettings();

    connect(ui->actionNew, &QAction::triggered, this, &Notepad::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::open);
    connect(ui->actionSave, &QAction::triggered, this, &Notepad::save);
    connect(ui->actionSave_As, &QAction::triggered, this, &Notepad::saveAs);
    connect(ui->actionExit, &QAction::triggered, this, &Notepad::exit);
    connect(ui->actionCopy, &QAction::triggered, this, &Notepad::copy);
    connect(ui->actionPaste, &QAction::triggered, this, &Notepad::paste);
    connect(ui->actionUndo, &QAction::triggered, this, &Notepad::undo);
    connect(ui->actionRedo, &QAction::triggered, this, &Notepad::redo);
    connect(ui->actionSelect_font, &QAction::triggered, this, &Notepad::selectFont);
    connect(ui->actionSelect_fgcolor, &QAction::triggered, this, &Notepad::selectForegroundColor);
    connect(ui->actionSelect_bgcolor, &QAction::triggered, this, &Notepad::selectBackgroundColor);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::keyPressEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->matches(QKeySequence::Save))
    {
        save();
    }
    if (keyEvent->matches(QKeySequence::Open))
    {
        open();
    }
}

void Notepad::loadSettings() {
    settings = new QSettings(homeDirectory + "/.notepad", QSettings::Format::IniFormat, nullptr);
    QString fontFamily = settings->value("fontFamily", "Chalkboard").toString();
    int fontSize = settings->value("fontSize", "14").toInt();
    QColor fgcolor = QColor(settings->value("foregroundColor", "FFFFFF").toString().toInt(nullptr, 16));
    QColor bgcolor = QColor(settings->value("backgroundColor", "0099FF").toString().toInt(nullptr, 16));
    QFont font = QFont(fontFamily, fontSize, -1, false);
    ui->textEdit->setFont(font);
    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Text, fgcolor);
    p.setColor(QPalette::Base, bgcolor);
    ui->textEdit->setPalette(p);
}

void Notepad::newDocument() {
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::open() {
    QString directory = homeDirectory + "/Documents";
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", directory, nullptr);
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
       // QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
       return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::save()
{
    QString directory = homeDirectory + "/Documents";
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save", directory, nullptr);
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        // QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::saveAs()
{
    QString directory = homeDirectory + "/Documents";
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", directory, nullptr);
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        // QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::exit()
{
    QCoreApplication::quit();
}

void Notepad::copy()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->copy();
#endif
}

void Notepad::paste()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->paste();
#endif
}

void Notepad::undo()
{
     ui->textEdit->undo();
}

void Notepad::redo()
{
    ui->textEdit->redo();
}

void Notepad::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void Notepad::selectForegroundColor()
{
    QColor color = QColorDialog::getColor(Qt::black,this);

    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Text, color);
    ui->textEdit->setPalette(p);
}

void Notepad::selectBackgroundColor()
{
    QColor color = QColorDialog::getColor(Qt::white,this);

    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, color);
    ui->textEdit->setPalette(p);
}
