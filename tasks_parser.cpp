//
// Created by Admin on 25.04.2024.
//

#include <algorithm>
#include "tasks_parser.h"
#include <iostream>

namespace ax {
    tasks_parser::tasks_parser(std::string path): path(std::move(path)) {}

    void tasks_parser::parse_files() {
        if(!std::filesystem::exists(path)){
            throw std::runtime_error("Path does not exist");
        }
        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            if (entry.path().extension() == ".md") {
                const auto & it = std::find_if(
                    std::filesystem::directory_iterator(path),
                    std::filesystem::directory_iterator(),
                    [entry](const std::filesystem::directory_entry & e) {
                        return (e.path().extension() == ".cpp" || e.path().extension() == ".cxx")
                        && e.path().filename().replace_extension().string() ==
                        entry.path().filename().replace_extension().string();
                });
                tasks.insert({entry.path().filename().string(),
                              it != std::filesystem::directory_iterator() ?
                              it->path().filename().string() : ""});
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