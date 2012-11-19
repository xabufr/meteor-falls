#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class Singleton
{
public:
    static T* get()
    {
        if(m_instance == 0)
            m_instance = new T();
        return m_instance;
    }
    static void kill()
    {
        if(m_instance!=0)
        {
            delete m_instance;
            m_instance=0;
        }

    }
    protected:
        Singleton<T>() {}
        ~Singleton<T>() {}
    private:
        static T *m_instance;
};
template<class T>
T *Singleton<T>::m_instance = 0;

#endif // SINGLETON_H
