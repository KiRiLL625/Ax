//
// Created by Admin on 22.04.2024.
//

#include "file.h"
#include <fstream>
#include <filesystem>

namespace ax {

    file::file(int type, std::string file_name, std::string download_url, int status,
               int visibility, std::string path): type(type), file_name(std::move(file_name)),
               download_url(std::move(download_url)),
               status(status), visibility(visibility), path(path) {this->full_text = parse_file();}

    void file::add_query_file() {
        pqxx::connection c("dbname=accelerator user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
        pqxx::work txn(c);
        pqxx::result r = txn.exec("INSERT INTO ax_file VALUES (DEFAULT, " + txn.quote(type) + ", " + txn.quote(file_name) +
                                  ", " + txn.quote(download_url) + ", " + txn.quote(full_text) + ", " + txn.quote(status) +
                                  ", " + txn.quote(visibility) + ") RETURNING id");
        this->id = r[0][0].as<int>();
        txn.commit();
        c.disconnect();
    }

    std::string file::parse_file() {
        std::ifstream file(std::filesystem::path(path) / file_name);
        //std::ifstream file(file_name);
        //как и в task.cpp, работает только с относительным путем
        std::string file_content;
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                file_content += line + "\n";
            }
            file.close();
        }
        return file_content;
    }

    int file::get_id() const {
        return id;
    }

    int file::get_type() const {
        return type;
    }

    std::string file::get_file_name() const {
        return file_name;
    }

    std::string file::get_download_url() const {
        return download_url;
    }

    std::string file::get_full_text() const {
        return full_text;
    }

    int file::get_status() const {
        return status;
    }

    int file::get_visibility() const {
        return visibility;
    }

    void file::set_id(int id) {
        this->id = id;
        update_file();
    }

    void file::set_type(int type) {
        this->type = type;
        update_file();
    }

    void file::set_file_name(std::string file_name) {
        this->file_name = std::move(file_name);
        update_file();
    }

    void file::set_download_url(std::string download_url) {
        this->download_url = std::move(download_url);
        update_file();
    }

    void file::set_full_text(std::string full_text) {
        this->full_text = std::move(full_text);
        update_file();
    }

    void file::set_status(int status) {
        this->status = status;
        update_file();
    }

    void file::set_visibility(int visibility) {
        this->visibility = visibility;
        update_file();
    }

    void file::update_file() {
        pqxx::connection c("dbname=accelerator user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
        pqxx::work txn(c);
        pqxx::result r = txn.exec("UPDATE ax_file SET type = " + txn.quote(type) + ", file_name = " + txn.quote(file_name) +
                                  ", download_url = " + txn.quote(download_url) + ", full_text = " + txn.quote(full_text) +
                                  ", status = " + txn.quote(status) + ", visibility = " + txn.quote(visibility) + " WHERE id = " +
                                  txn.quote(id));
        txn.commit();
        c.disconnect();
    }

} // ax