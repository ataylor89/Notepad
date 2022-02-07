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

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; struct Settings; }
QT_END_NAMESPACE

typedef struct Settings {
    QFont font;
    QColor foregroundColor;
    QColor backgroundColor;
    QString directory;
} Settings;

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

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
    QString currentFile;
    Settings settings;
};

#endif // NOTEPAD_H
