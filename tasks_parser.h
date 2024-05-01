//
// Created by Admin on 25.04.2024.
//

#ifndef AX_TEST3_TASKS_PARSER_H
#define AX_TEST3_TASKS_PARSER_H

#include <string>
#include <filesystem>
#include <unordered_map>

namespace ax {

    class tasks_parser {
    private:
        std::string path;
        std::unordered_map<std::string, std::string> tasks;
    public:
        tasks_parser() = delete;
        explicit tasks_parser(std::string path);
        void parse_files();
        int get_task_count() const;
        bool current_has_tests(const std::string& task_name) const;
        //debug
        void print_tasks() const;
        std::unordered_map<std::string, std::string> get_tasks() const;
    };

} // ax

#endif //AX_TEST3_TASKS_PARSER_H
