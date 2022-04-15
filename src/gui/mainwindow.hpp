#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <stdexcept>

#include "./../huffman.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_pushButtonSelectFile_clicked();

    void on_pushButtonZip_clicked();

private:
    Ui::MainWindow *ui;

    void selectFile();

    std::string getFormat(const std::string& filePath);
    bool formatHuf(const std::string& file);
};
#endif // MAINWINDOW_H
