#include "mainwindow.hpp"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::selectFile()
{
  QString str;
  str = QFileDialog::getOpenFileName(this, "Select File", "", "All Files (*.*);; TXT Files (*.txt);; HUF Files (*.huf);");

  ui->textEdit->setText(str);

  ui->progressBar->setValue(0);
  ui->statusbar->showMessage("");
};

void MainWindow::on_actionOpen_triggered()
{
  selectFile();
};

void MainWindow::on_actionExit_triggered()
{
  QApplication::quit();
};

void MainWindow::on_actionAbout_triggered()
{
  QMessageBox::about(
    NULL,
    "About",
    "This program uses the huffman algorithm to zip and unzip text files"
  );
};

void MainWindow::on_pushButtonSelectFile_clicked()
{
  selectFile();
};

std::string MainWindow::getFormat(const std::string& filePath)
{
  size_t dot = filePath.rfind('.');
  if (dot == std::string::npos)
    return nullptr;

  const std::string fileFormat = filePath.substr(dot + 1, filePath.size() - (dot + 1));

  return fileFormat;
};

bool MainWindow::formatHuf(const std::string& filePath)
{
  const std::string formatHuf("huf");

  return (formatHuf == getFormat(filePath));
};

void MainWindow::on_pushButtonZip_clicked()
{
  ui->progressBar->setValue(0);

  try
  {
    const std::string filePath = ui->textEdit->toPlainText().toStdString();

    Huffman huffman(filePath);

    if (!formatHuf(filePath))
    {
      ui->statusbar->showMessage("Zipping file...");
      huffman.zip();
    }
    else
    {
      ui->statusbar->showMessage("Unzipping file...");
      huffman.unzip();
    }

    ui->statusbar->showMessage("Successfully");
    ui->progressBar->setValue(100);
  }
  catch (...)
  {
    ui->statusbar->showMessage("Something is wrong");
  }
};
