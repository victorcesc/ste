#ifndef __CFIFO_H__
#define __CFIFO_H__


template<int N,typename T>
class CircularFifo{
public:
    CircularFifo() : in(0), out(0), size(0){
        for (int = 0;i<N; i++){
            data[i] =0;
        }
        in = N-1;
    }
    ~CircularFifo(){}
    void enqueue(T obj){
        in = ((in ==N-1) ? 0 : (in+1));
        data[in] = obj;
    }
    T dequeue(int out){
        int ii = ((unsigned)(in - out)) % N;
        return data[ii];
    }

    int length(){
        return size;
    }

private:
    T data[N];
    int in,out,size;

};




#endif /* __QUEUE_H__ */