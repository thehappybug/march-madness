#ifndef QUERY_FACTORY_H
#define QUERY_FACTORY_H

#include "QueryBase.hpp"

#include <memory>
#include <string>
#include <map>
#include <functional>

using namespace std;

// A helper class to register a factory function
class QueryRegistrar {
public:
    QueryRegistrar(string className, function<QueryBase*(void)> classFactoryFunction);
};

// A preprocessor define used by derived classes
#define REGISTER_QUERY_CLASS(NAME, TYPE) static QueryRegistrar Queryregistrar(NAME, [](void) -> QueryBase * { return new TYPE();});

// The factory - implements singleton pattern!
class QueryFactory
{
public:
    // Get the single instance of the factory
    static QueryFactory * Instance();

    // register a factory function to create an instance of className
    void RegisterFactoryFunction(string name, function<QueryBase*(void)> classFactoryFunction);

    // create an instance of a registered class
    shared_ptr<QueryBase> Create(string name);

private:
    // a private ctor
    QueryFactory(){}

    // the registry of factory functions
    map<string, function<QueryBase*(void)>> factoryFunctionRegistry;

};

#endif