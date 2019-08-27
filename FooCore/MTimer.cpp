#include "MTimer.hpp"

using namespace FooGE;

void MTimer::Reset(){
    m_StartTime = std::chrono::system_clock::now();
}

void MTimer::Start(){
    m_StartTime = std::chrono::system_clock::now();
}

void MTimer::Stop(){
    m_EndTime = std::chrono::system_clock::now();
    isStopped = true;
}

void MTimer::SetTimeout(auto func, float delayTime){
    std::thread t([=]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000*delay));
        func();
    });
    t.detach();
}
float MTimer::ElapsedMilliseconds(){
    std::chrono::time_point<std::chrono::system_clock> endTime;
    
    if(!isStopped){
        endTime = std::chrono::system_clock::now();
    }
    else
    {
        endTime = m_EndTime;
    }
    
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}