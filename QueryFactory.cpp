/**
 * Query Factory
 * 
 * Based on C++ Object Factory
 * http://www.codeproject.com/Articles/567242/AplusC-b-bplusObjectplusFactory
 */

#include "QueryFactory.hpp"


QueryRegistrar::QueryRegistrar(string name, function<QueryBase*(void)> classFactoryFunction)
{
    // register the class factory function
    QueryFactory::Instance()->RegisterFactoryFunction(name, classFactoryFunction);
}


QueryFactory * QueryFactory::Instance()
{
    static QueryFactory factory;
    return &factory;
}


void QueryFactory::RegisterFactoryFunction(string name, function<QueryBase*(void)> classFactoryFunction)
{
    // register the class factory function 
    factoryFunctionRegistry[name] = classFactoryFunction;
}


shared_ptr<QueryBase> QueryFactory::Create(string name)
{
    QueryBase * instance = nullptr;

    // find name in the registry and call factory method.
    auto it = factoryFunctionRegistry.find(name);
    if(it != factoryFunctionRegistry.end())
        instance = it->second();
    
    // wrap instance in a shared ptr and return
    if(instance != nullptr)
        return std::shared_ptr<QueryBase>(instance);
    else
        return nullptr;
}