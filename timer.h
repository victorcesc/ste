#ifdef __TIMER_H__
#define __TIMER_H__


typedef unsigned long long Microseconds;


class Timer
{

    public:
        Timer();
        ~Timer();
        void handleIsr();
        Microseconds micros();
        static Timer * singleton(){ return _singleton; }

    private:
        static Timer * _singleton;
        Microseconds microseconds;

};

#endif /* __TIMER_H__ */