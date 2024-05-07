//
// Created by Admin on 18.04.2024.
//

#include "task.h"
#include <pqxx/pqxx>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace ax {
    task::task(int page_id, int type, std::string title,
               std::string max_mark, int status, std::string path) : page_id(page_id), type(type),
               title(std::move(title.substr(0, title.size() - 3))),
                max_mark(std::move(max_mark)), status(status), path(path) { description = parse_task();}

    void task::add_query_task() {
        pqxx::connection conn("dbname=accelerator user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
        pqxx::work txn(conn);

        std::string query = "INSERT INTO ax_task VALUES(DEFAULT, $1, $2, $3, $4, $5, $6) RETURNING id";
        pqxx::result r = txn.parameterized(query)
                            (page_id)
                            (type)
                            (title)
                            (description)
                            (max_mark)
                            (status)
                            .exec();
        this->id = r[0][0].as<int>();
        txn.commit();
        conn.disconnect();
    }

    void task::add_file(const file& f) const {
        pqxx::connection conn("dbname=accelerator user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
        pqxx::work txn(conn);
        txn.exec("INSERT INTO ax_task_files VALUES (DEFAULT, " + txn.quote(id) + ", " + txn.quote(f.get_id()) + ")");
        txn.commit();
        conn.disconnect();
    }

    std::string task::parse_task() {
        std::ifstream file(std::filesystem::path(path) / (title + ".md")); //todo: сделать абсолютный путь
        //std::ifstream file(title + ".md"); //работает и считывает содержимое файла, но только если в clion указать текущую директорию как рабочую
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

    void task::get_task_files() const {
        pqxx::connection conn("dbname=accelerator user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
        pqxx::work txn(conn);
        pqxx::result r = txn.exec("SELECT * FROM ax_task WHERE id=" + txn.quote(id));
        std::cout << "Task info:" << std::endl;
        for (const auto &row: r) {
            std::cout << "____________________________________________________" << std::endl;
            std::cout << "Task id: " << row[0].as<int>() << std::endl;
            std::cout << "Page id: " << row[1].as<int>() << std::endl;
            std::cout << "Type: " << row[2].as<int>() << std::endl;
            std::cout << "Title: " << row[3].as<std::string>() << std::endl;
            std::cout << "Description: " << row[4].as<std::string>() << std::endl;
            std::cout << "Max mark: " << row[5].as<std::string>() << std::endl;
            std::cout << "Status: " << row[6].as<int>() << std::endl;
            std::cout << "____________________________________________________" << std::endl;
        }

        std::cout << "Files info:" << std::endl;
        pqxx::result r2 = txn.exec("SELECT * FROM ax_file WHERE id IN (SELECT file_id FROM ax_task_files WHERE task_id=" + txn.quote(id) + ")");
        for (const auto &row: r2) {
            std::cout << "____________________________________________________" << std::endl;
            std::cout << "File id: " << row[0].as<int>() << std::endl;
            std::cout << "Type: " << row[1].as<int>() << std::endl;
            std::cout << "File name: " << row[2].as<std::string>() << std::endl;
            std::cout << "Download url: " << row[3].as<std::string>() << std::endl;
            std::cout << "Full text: " << row[4].as<std::string>() << std::endl;
            std::cout << "Status: " << row[5].as<int>() << std::endl;
            std::cout << "Visibility: " << row[6].as<int>() << std::endl;
            std::cout << "____________________________________________________" << std::endl;
        }
        txn.commit();
        conn.disconnect();
    }

    int task::get_id() const {
        return id;
    }

    int task::get_page_id() const {
        return page_id;
    }

    int task::get_type() const {
        return type;
    }

    std::string task::get_title() const {
        return title;
    }

    std::string task::get_description() const {
        return description;
    }

    std::string task::get_max_mark() const {
        return max_mark;
    }

    int task::get_status() const {
        return status;
    }

    void task::set_id(int id) {
        this->id = id;
        update_task();
    }

    void task::set_page_id(int page_id) {
        this->page_id = page_id;
        update_task();
    }

    void task::set_type(int type) {
        this->type = type;
        update_task();
    }

    void task::set_title(std::string title) {
        this->title = std::move(title);
        update_task();
    }

    void task::set_description(std::string description) {
        this->description = std::move(description);
        update_task();
    }

    void task::set_max_mark(std::string max_mark) {
        this->max_mark = std::move(max_mark);
        update_task();
    }

    void task::set_status(int status) {
        this->status = status;
        update_task();
    }

    void task::update_task() {
        pqxx::connection conn("dbname=accelerator user=postgres password=postgres hostaddr=127.0.0.1 port=5432");
        pqxx::work txn(conn);

        std::string query = "UPDATE ax_task SET page_id=$1, type=$2, title=$3, description=$4, max_mark=$5, status=$6 WHERE id=$7";
        pqxx::result r = txn.parameterized(query)
                            (page_id)
                            (type)
                            (title)
                            (description)
                            (max_mark)
                            (status)
                            (id)
                            .exec();

        txn.commit();
        conn.disconnect();
    }
} // ax