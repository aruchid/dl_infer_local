#pragma once
#include <QImage>
#include "../../Data/DataManager.hpp"

class DisplayController {
public:
    DisplayController();
    
    // 显示控制
    void updateDisplay(QWidget* displayWidget);
    void setDisplayMode(DisplayMode mode);
    void showResults(const cv::Mat& frame, const std::vector<float>& results);

private:
    QImage matToQImage(const cv::Mat& mat);
    DisplayMode currentMode_;
    DataManager& dataManager_;
}; 