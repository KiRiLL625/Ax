//
// Created by Admin on 18.04.2024.
//

#ifndef AX_TEST3_TASK_H
#define AX_TEST3_TASK_H

#include <string>
#include "file.h"

namespace ax {
    class task {
    private:
        int id;
        int page_id;
        int type;
        std::string title;
        std::string description;
        std::string max_mark;
        int status;
        std::string path;
    public:
        task() = delete;
        task(int page_id, int type, std::string title, std::string max_mark,
             int status, std::string path);
        std::string parse_task();
        void add_query_task();
        void add_file(const file& f) const;
        //unused + debug
        void get_task_files() const;
        int get_id() const;
        int get_page_id() const;
        int get_type() const;
        std::string get_title() const;
        std::string get_description() const;
        std::string get_max_mark() const;
        int get_status() const;
        void set_id(int id);
        void set_page_id(int page_id);
        void set_type(int type);
        void set_title(std::string title);
        void set_description(std::string description);
        void set_max_mark(std::string max_mark);
        void set_status(int status);
        void update_task();
    };

} // ax

#endif //AX_TEST3_TASK_H
