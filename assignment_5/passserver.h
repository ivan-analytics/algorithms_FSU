#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include <string>
#include <utility>
#include <unistd.h> // For crypt()

#ifdef __linux__
#include <crypt.h>
#endif


namespace cop4530 {

class PassServer {
public:
    PassServer(size_t size = 101);
    ~PassServer();

    bool load(const char *filename);
    bool addUser(std::pair<std::string, std::string> & kv);
    bool addUser(std::pair<std::string, std::string> && kv);
    bool removeUser(const std::string & k);
    bool changePassword(const std::pair<std::string, std::string> & p, const std::string & newpassword);
    bool find(const std::string & user) const;
    void dump() const;
    size_t size() const;
    bool write_to_file(const char *filename) const;

private:
    std::string encrypt(const std::string & str);

    HashTable<std::string, std::string> table;
};

} // end namespace cop4530

#endif
