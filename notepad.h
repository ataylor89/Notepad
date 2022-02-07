#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
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
};
#endif // NOTEPAD_H
