#ifndef THREADSAFEARRAY_H
#define THREADSAFEARRAY_H

template<typename T>
class ThreadSafeArray {
public:
    
    ThreadSafeArray() = default;
    
    // Append data to the QByteArray
    void append(const T& data) {
        QMutexLocker locker(&mutex); // Lock the mutex for thread-safe access
        _data.append(data);
    }
    
    // Retrieve and remove data from the QByteArray
    QList<T> get() {
        QMutexLocker locker(&mutex); // Lock the mutex for thread-safe access
        return _data;
    }
    
    void removeFirst(qint64 len){
        QMutexLocker locker(&mutex); // Lock to safely access size
        //_data.removeAt(0, len);
        _data.erase(_data.begin(), _data.begin() + len);
    }
    
private:
    QList<T> _data;
    QMutex mutex;
};

#endif // THREADSAFEARRAY_H
