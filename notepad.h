#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QSettings>
#include <QKeyEvent>
#include <QKeySequence>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

protected:
    void keyPressEvent(QKeyEvent *keyEvent);

private slots:
    void loadSettings();
    void newDocument();
    void open();
    void save();
    void saveAs();
    void exit();
    void copy();
    void paste();
    void undo();
    void redo();
    void selectFont();
    void selectForegroundColor();
    void selectBackgroundColor();

private:
    Ui::Notepad *ui;
    QSettings *settings;
    QString currentFile;
    QString homeDirectory;
};

#endif // NOTEPAD_H
