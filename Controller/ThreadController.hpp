#pragma once
#include <boost/thread.hpp>
#include "../Data/DataManager.hpp"

class ThreadController {
public:
    ThreadController();
    void startThreads();
    void stopThreads();

private:
    void captureThread();
    void inferenceThread();
    void displayThread();
    
    bool running_;
    boost::thread captureThread_;
    boost::thread inferenceThread_;
    boost::thread displayThread_;
    DataManager& dataManager_;
}; 