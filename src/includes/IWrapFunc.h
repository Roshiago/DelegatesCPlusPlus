#ifndef WrapFuncTemplate
#define WrapFuncTemplate

#define ClsMethodDef(name, class_name, retr_type, args) retr_type(class_name::* name)(args)
#define FuncDef(retr_type, args) retr_type(*)(args)


template<class RetrType, typename ...Args>
class IWrapFunc {
public:
    virtual RetrType Invoke(Args... params) { return RetrType(); };
};

template<typename RetrType, class Source, typename Method, typename ...Args>
class WrapMethod : IWrapFunc<RetrType, Args...> {
public:
    WrapMethod(Source* src, Method method) {
        this->m_src = src;
        this->m_method = method;
    }

    RetrType Invoke(Args... params) {
        return (m_src->*m_method)(params...);
    }

    operator IWrapFunc<RetrType, Args...>* () const {
        return (IWrapFunc<RetrType, Args...>*)this;
    }
private:
    Source* m_src;
    Method m_method;
};

template<typename RetrType, typename Method, typename ...Args>
class WrapFunc : IWrapFunc<RetrType, Args...> {
public:
    WrapFunc(Method method) {
        this->m_method = method;
    }

    RetrType Invoke(Args... params) {
        return m_method(params...);
    }

    operator IWrapFunc<RetrType, Args...>* () const {
        return (IWrapFunc<RetrType, Args...>*)this;
    }
private:
    Method m_method;
};

#endif // !WrapFuncTemplate
