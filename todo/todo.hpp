#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

using namespace eosio;
using std::string;

CONTRACT todo : public contract
{
  public:
    todo(name receiver, name code, datastream<const char*> ds) : contract(receiver, code, ds) {}

    ACTION create(const name account,
                const string &content);

    ACTION update(const name account,
                const string &content,
                uint64_t id,
                uint64_t isDone);

    ACTION remove(const name account, uint64_t id);

  private:
    TABLE task
    {
        uint64_t id;
        //name account;
        string content;
        uint64_t isDone;

        uint64_t primary_key() const { return id; }
        //EOSLIB_SERIALIZE(task, (id)(account)(content)(isDone))
    };

    typedef eosio::multi_index<"task"_n, task> task_table;
};

EOSIO_DISPATCH(todo, (create)(update)(remove))