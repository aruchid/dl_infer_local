#pragma once
#include <QMainWindow>
#include "../Controller/ThreadController.hpp"
#include "../Controller/Input/CameraController.hpp"
#include "../Controller/Processing/TensorRTController.hpp"
#include "../Controller/Display/DisplayController.hpp"
#include "../Controller/Communication/TCPController.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartButtonClicked();
    void onStopButtonClicked();
    void updateDisplay();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<ThreadController> threadController_;
    std::unique_ptr<CameraController> cameraController_;
    std::unique_ptr<TensorRTController> tensorRTController_;
    std::unique_ptr<DisplayController> displayController_;
    std::unique_ptr<TCPController> tcpController_;
}; 