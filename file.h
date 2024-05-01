//
// Created by Admin on 22.04.2024.
//

#ifndef AX_TEST3_FILE_H
#define AX_TEST3_FILE_H

#include <string>
#include <pqxx/pqxx>

namespace ax {

    class file {
    private:
        int id;
        int type;
        std::string file_name;
        std::string download_url;
        std::string full_text;
        int status;
        int visibility;
        std::string path;
    public:
        file() = delete;
        file(int type, std::string file_name, std::string download_url,
             int status, int visibility, std::string path);
        void add_query_file();
        int get_id() const;
        int get_type() const;
        std::string get_file_name() const;
        std::string get_download_url() const;
        std::string get_full_text() const;
        std::string parse_file();
        int get_status() const;
        int get_visibility() const;
        void set_id(int id);
        void set_type(int type);
        void set_file_name(std::string file_name);
        void set_download_url(std::string download_url);
        void set_full_text(std::string full_text);
        void set_status(int status);
        void set_visibility(int visibility);
        void update_file();
    };

} // ax

#endif //AX_TEST3_FILE_H
