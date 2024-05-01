#include <iostream>
#include <fstream>
#include "tasks_parser.h"
#include "task.h"

int main(int argc, char **argv) {
    if(argc != 3){
        std::cerr << "Usage: " << argv[0] << " <path> <page_id>\n";
        return 1;
    }
    ax::tasks_parser parser(argv[1]);
    int page_id = std::stoi(argv[2]);
    parser.parse_files();
    std::cout << "Found " << parser.get_task_count() << " tasks\n";
    std::vector<std::string> tasks_no_tests;
    for(const auto & task : parser.get_tasks()) {
        if(parser.current_has_tests(task.first)) { //напрягает
            ax::task t(page_id, 1, task.first, "5", 1, std::string(argv[1]));
            t.add_query_task();
            ax::file f(2, task.second, "", 1, 0, argv[1]);
            f.add_query_file();
            t.add_file(f);
        }
        else{
            tasks_no_tests.push_back(task.first.substr(0, task.first.size() - 3));
        }
    }
    //+ напрягает время добавления тасков и файлов
    if(!tasks_no_tests.empty()){
        std::cout << "Tasks without tests:\n";
        for(const auto & task : tasks_no_tests){
            std::cout << task << std::endl;
        }
        std::cout << "Do you want to add tests for these tasks? (y/n)\n";
        char ans;
        std::cin >> ans;
        if(ans == 'y') {
            for (const auto &task: tasks_no_tests) {
                ax::task t(page_id, 1, task + ".md", "5", 1, argv[1]);
                t.add_query_task();
            }
            std::cout << "All tasks added\n";
        }
        else{
            std::cout << "Tasks with tests added\n";
        }
    }
    else {
        std::cout << "All tasks added\n";
    }
    /*
    std::string path = "/home/kirill0503/ax_test3/test_files";
    std::string title = "Task4";
    std::ifstream file(path + "/" + title + ".md");
    std::cout << path << std::endl;
    if(file.is_open()) {
        std::cout << "File is open\n";
        std::cout << std::string(argv[1]) + "/" + title + ".md" << std::endl;
    }
     */
    return 0;
}
