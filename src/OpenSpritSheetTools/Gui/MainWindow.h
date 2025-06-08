#pragma once

#include "./ui_MainWindow.h"
#include <QMainWindow>

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget * _parent = nullptr);

protected:
    void closeEvent(QCloseEvent * _event) override;

private slots:
    void showSheetSplitter();
    void closeTab(int _index);
};
