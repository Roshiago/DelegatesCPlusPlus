#ifndef _CDELEGATES_
#define _CDELEGATES_

#include <list>

#define ARGS2(type) type,type
#define ARGS3(type) type,type,type
#define ARGS4(type) type,type,type,type
#define ARGS5(type) type,type,type,type,type

#define MPtr(class_name, args) (class_name::*)(args)

template<class RetrType, typename ...Args>
class IWrapFunc{
public:
    virtual RetrType Invoke(Args... params){ return RetrType();};
};

template<typename RetrType, class Source, typename Method, typename ...Args>
class WrapMethod: IWrapFunc<RetrType, Args...>{
public:
    WrapMethod(Source* src, Method method){
        this->m_src = src;
        this->m_method = method;
    }

    RetrType Invoke(Args... params){
        return (m_src->*m_method)(params...);
    }

    operator IWrapFunc<RetrType, Args...>*() const{
        return (IWrapFunc<RetrType, Args...>*)this;
    }
private:
    Source* m_src;
    Method m_method;
};

template<typename RetrType, typename Method, typename ...Args>
class WrapFunc: IWrapFunc<RetrType, Args...>{
public:
    WrapFunc(Method method){
        this->m_method = method;
    }

    RetrType Invoke(Args... params){
        return m_method(params...);
    }

    operator IWrapFunc<RetrType, Args...>*() const{
        return (IWrapFunc<RetrType, Args...>*)this;
    }
private:
    Method m_method;
};

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

    std::list<RetrType> operator()(Args... params){
        std::list<RetrType> output;
        for(auto& f: m_funcs){
            output.push_back(f->Invoke(params...));
        }
        return output;
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