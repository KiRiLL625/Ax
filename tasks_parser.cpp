//
// Created by Admin on 25.04.2024.
//

#include <algorithm>
#include "tasks_parser.h"
#include <iostream>

namespace ax {
    tasks_parser::tasks_parser(std::string path): path(std::move(path)) {}
    //мб быстрее можно
    void tasks_parser::parse_files() {
        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() == ".md") {
                tasks.insert({entry.path().filename().string(), ""});
            }
        }
        //не слишком ли долго?
        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() == ".cpp" || entry.path().extension() == ".cxx") {
                std::string filename = entry.path().filename().replace_extension().string();
                auto it = std::find_if(tasks.begin(), tasks.end(), [filename](const std::pair<std::string, std::string> & p) {
                    return p.first == filename + ".md";
                });
                if (it != tasks.end()) {
                    it->second = entry.path().filename().string();
                }
            }
        }
    }

    int tasks_parser::get_task_count() const {
        return tasks.size();
    }

    void tasks_parser::print_tasks() const {
        for (const auto & task : tasks) {
            std::cout << task.first << " " << task.second << std::endl;
        }
    }

    std::unordered_map<std::string, std::string> tasks_parser::get_tasks() const {
        return tasks;
    }

    bool tasks_parser::current_has_tests(const std::string& task_name) const{
        return !tasks.at(task_name).empty();
    }
} // ax