#ifndef _CDELEGATES_
#define _CDELEGATES_

#include "IWrapFunc.h"
#include <vector>

template<typename RetrType, typename ...Args>
class CDelegate{
public:
    using RefWrap = IWrapFunc<RetrType, Args...>*;

    CDelegate() = default;

    CDelegate operator+(RefWrap f){
        CDelegate<RetrType, Args...> delegate;
        for(auto f_t: this->m_funcs){
            delegate.m_funcs.push_back(f_t);
        }
        delegate.m_funcs.push_back(f);
        return delegate;
    }
    
    CDelegate& operator+=(RefWrap f){
        m_funcs.push_back(f);
        return *this;
    }

    template<class R = RetrType>
    typename std::enable_if<!std::is_same<R, void>::value, std::vector<RetrType>>::type operator()(Args... params){
        std::vector<RetrType> output;
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
private:
    std::vector<RefWrap> m_funcs;
};

#endif // !_CDELEGATES_