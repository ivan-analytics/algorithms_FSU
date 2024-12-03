#include "passserver.h"
#include <cstring>
#include <iostream>

namespace cop4530 {

PassServer::PassServer(size_t size) : table(size) {
}

PassServer::~PassServer() {
    table.clear();
}

bool PassServer::load(const char *filename) {
    return table.load(filename);
}

bool PassServer::addUser(std::pair<std::string, std::string> & kv) {
    if (table.contains(kv.first))
        return false;
    kv.second = encrypt(kv.second);
    return table.insert(kv);
}

bool PassServer::addUser(std::pair<std::string, std::string> && kv) {
    if (table.contains(kv.first))
        return false;
    kv.second = encrypt(kv.second);
    return table.insert(std::move(kv));
}

bool PassServer::removeUser(const std::string & k) {
    return table.remove(k);
}

bool PassServer::changePassword(const std::pair<std::string, std::string> & p, const std::string & newpassword) {
    if (newpassword == p.second)
        return false;

    if (!table.contains(p.first))
        return false;

    std::string old_encrypted = encrypt(p.second);
    std::pair<std::string, std::string> kv(p.first, old_encrypted);

    if (!table.match(kv))
        return false;

    std::string new_encrypted = encrypt(newpassword);
    if (old_encrypted == new_encrypted)
        return false;

    std::pair<std::string, std::string> new_kv(p.first, new_encrypted);
    return table.insert(new_kv);
}

bool PassServer::find(const std::string & user) const {
    return table.contains(user);
}

void PassServer::dump() const {
    table.dump();
}

size_t PassServer::size() const {
    return table.size();
}

bool PassServer::write_to_file(const char *filename) const {
    return table.write_to_file(filename);
}

std::string PassServer::encrypt(const std::string & str) {
    // defining the salt using the MD5-based format with a fixed 8-character salt
    char salt[] = "$1$########";
    
    // encrypting the input string using crypt() with the specified salt
    char * encrypted = crypt(str.c_str(), salt);
    
    // checks
    if (encrypted == nullptr)
        return ""; // Return an empty string if encryption fails
    

    std::string encrypted_str(encrypted);    
    // finding the positions of the '$' delimiters
    size_t first = encrypted_str.find('$');
    size_t second = encrypted_str.find('$', first + 1);
    size_t third = encrypted_str.find('$', second + 1);
    
    // ensuring that the third '$' is found and there's at least one character after it
    if (third != std::string::npos && third + 1 < encrypted_str.size())
        return encrypted_str.substr(third + 1);
    else
        return "";
}

} // end namespace cop4530
