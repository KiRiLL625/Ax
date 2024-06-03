#include <iostream>
#include <fstream>
#include "tasks_parser.h"
#include "task.h"

void progress_bar(int current, int total) {
    std::cout << "\rAdding tasks: " << current + 1 << "/" << total << " [" << std::string((current + 1) * 10 / total, '#')
              << std::string(10 - (current + 1) * 10 / total, ' ') << "]" << std::flush;
}

int main(int argc, char **argv) {
    std::ios::sync_with_stdio(false);
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " <path> <page_id>\n";
        return 1;
    }
    ax::tasks_parser parser(argv[1]);
    int page_id = std::stoi(argv[2]);
    try{
        parser.parse_files();
    }
    catch(const std::runtime_error& e){
        std::cout << "Directory does not exist" << std::endl;
        return 2;
    }
    std::cout << "Finding tasks..." << std::flush;
    int task_count = parser.get_task_count();
    std::cout << "\rFound " << task_count << " tasks       \n";
    std::vector<std::string> tasks_no_tests;
    int cur_task = 0;
    for(const auto & task : parser.get_tasks()) {
        progress_bar(cur_task, task_count);
        if(parser.current_has_tests(task.first)) {
            ax::task t(page_id, 1, task.first, "5", 1, std::string(argv[1]));
            t.add_query_task();
            ax::file f(2, task.second, "", 1, 0, argv[1]);
            f.add_query_file();
            t.add_file(f);
            cur_task++;
        }
        else{
            tasks_no_tests.push_back(task.first.substr(0, task.first.size() - 3));
        }
    }
    if(!tasks_no_tests.empty()){
        std::cout << "\rTasks without tests:                        \n";
        for(const auto & task : tasks_no_tests){
            std::cout << task << std::endl;
        }
        std::cout << "Do you want to add this tasks anyway? (y/n)\n";
        char ans;
        std::cin >> ans;
        if(ans == 'y') {
            cur_task = task_count - tasks_no_tests.size();
            for (const auto &task: tasks_no_tests) {
                progress_bar(cur_task, task_count);
                ax::task t(page_id, 1, task + ".md", "5", 1, argv[1]);
                t.add_query_task();
                cur_task++;
            }
            std::cout << "\rTasks without tests added                  \n";
        }
        else{
            std::cout << "Tasks with tests added\n";
        }
    }
    else if(parser.get_task_count() != 0) {
        std::cout << "\rAll tasks added\n";
    }
    return 0;
}
