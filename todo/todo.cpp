#include "todo.hpp"

void todo::create(const name account,
                  const string &content)
{
    print("todo:create ", account, content); 

    require_auth(account);

    uint64_t id;
    task_table _tasks(_self, account.value);
    _tasks.emplace(account, [&](auto &p) {
        id = _tasks.available_primary_key();
        p.id = id;
//        p.account = account;
        p.content = content;
        p.isDone = 0;
    });

    print(name{account}, " Task created:", id);
}

void todo::update(const name account,
                  const string &content,
                  uint64_t id,
                  uint64_t isDone)
{
    eosio::print("todo:update ", account, content, id, isDone); 

    require_auth(account);

    task_table _tasks(_self, account.value);
    auto itr = _tasks.find(id);

    eosio_assert(itr != _tasks.end(), "no task found for Id");

    _tasks.modify(itr, account, [&](auto &p) {
        p.content = content;
        p.isDone = isDone;
    });

    print(name{account}, " modified");
}

void todo::remove(const name account, uint64_t id)
{
    eosio::print("todo:update ", id, account); 

    require_auth(account);

    task_table _tasks(_self, account.value);
    auto itr = _tasks.find(id);

    eosio_assert(itr != _tasks.end(), "Task not Found for Id");

    _tasks.erase(itr);
    print(name{account}, " Task removed");
}
