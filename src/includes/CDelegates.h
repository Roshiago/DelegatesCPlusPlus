#ifndef _CDELEGATES_
#define _CDELEGATES_

#include "IWrapFunc.h"
#include <list>

template<typename RetrType, typename ...Args>
class CDelegate{
public:
    CDelegate(){

    }
    CDelegate operator+(IWrapFunc<RetrType, Args...>* f){
        CDelegate<RetrType, Args...> delegate;
        for(auto f_t: this->m_funcs){
            delegate.m_funcs.push_back(f_t);
        }
        delegate.m_funcs.push_back(f);
        return delegate;
    }
    
    CDelegate& operator+=(IWrapFunc<RetrType, Args...>* f){
        m_funcs.push_back(f);
        return *this;
    }
    template<class R = RetrType>
    typename std::enable_if<!std::is_same<R, void>::value, std::list<RetrType>>::type operator()(Args... params){
        std::list<RetrType> output;
        for(auto& f: m_funcs){
            output.push_back(f->Invoke(params...));
        }
        return output;
    }

    template<class R = RetrType>
    typename std::enable_if<std::is_same<R, void>::value, void>::type operator()(Args... params) {
        for (auto& f : m_funcs) {
            f->Invoke(params...);
        }
    }

    void clear() {
        for (auto& f : m_funcs) {
            delete f;
        }
    }

private:
    std::list<IWrapFunc<RetrType, Args...>*> m_funcs;
};

#endif // !_CDELEGATES_