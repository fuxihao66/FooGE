namespace FooGE{
    class MTimer{
    public:
        void Start();
        void Stop();
        void Reset();
        void Resume();
        float ElapsedMilliseconds();


        template<typename Function>
        void SetTimeout(Function func, float delayTime);
    private:
        bool isStopped = false;
        // float timeScale = 1.0;     // 时间流逝速度 暂不考虑
        
        std::chrono::time_point<std::chrono::system_clock> m_StartTime;
        std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    };
}