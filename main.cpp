#include <iostream>
#include <cassert>
#include <leveldb/db.h>
#include <httplib.h>
#include "loguru/loguru.hpp"
int main(int argc, char** argv) {
    loguru::init(argc, argv);
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "testdb", &db);
    assert(status.ok());
    httplib::Server svr;

    svr.Get(R"(/.+)", [&db](const httplib::Request &req, httplib::Response &res) {
        auto path = req.path;
        if (!path.empty()){
            std::string value;
            leveldb::Status s = db->Get(leveldb::ReadOptions(), path, &value);
            if (s.ok()){
                LOG_F(INFO, "Get short url %s", path.c_str());
                res.set_redirect(value);
            }
            else{
                res.status = 404;
            }
        }
        else{
            res.status = 500;
        }
    });
    svr.Put(R"(/.+)", [&db](const httplib::Request &req, httplib::Response &res) {
        auto path = req.path;
        auto body = req.body;
        if (!path.empty()){
            leveldb::Status s = db->Put(leveldb::WriteOptions(), path, body);
            if (s.ok()){
                LOG_F(INFO, "Add short url %s -> %s", path.c_str(), body.c_str());
                res.status = 200;
            }
            else{
                res.status = 500;
            }
        }
        else{
            res.status = 500;
        }
    });
    svr.Delete(R"(/.+)", [&db](const httplib::Request &req, httplib::Response &res) {
        auto path = req.path;
        if (!path.empty()){
            leveldb::Status s = db->Delete(leveldb::WriteOptions(), path);
            if (s.ok()){
                LOG_F(INFO, "Delete short url %s", path.c_str());
                res.status = 200;
            }
            else{
                res.status = 500;
            }
        }
        else{
            res.status = 500;
        }
    });
    LOG_F(INFO, "server start in port %d", 8080);
    svr.listen("0.0.0.0", 8080);
    delete db;
    return 0;
}
