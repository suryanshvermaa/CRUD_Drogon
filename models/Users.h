
#pragma once
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Criteria.h>


namespace mynamespace {
namespace usermodel {  

class Users {
public:
    // Constructor, getters, and setters
    using PrimaryKeyType = int;
    static constexpr const char *primaryKeyName = "id";
    Users() = default;

    const int &getId() const;
    const std::string  &getName() const;
    const std::string &getEmail() const;
    const std::string &getPassword() const;
    const std::chrono::system_clock::time_point &getCreatedAt() const;
    void setId(const int &id);

    const std::string &getName();
    void setName(const std::string &name);

    const std::string &getEmail() ;
    void setEmail(const std::string &email);

    const std::string &getPassword() ;
    void setPassword(const std::string &password);

    const std::chrono::system_clock::time_point &getCreatedAt() ;
    void setCreatedAt(const std::chrono::system_clock::time_point &createdAt);

    // ORM-related methods
    void insert(const drogon::orm::DbClientPtr &client);
    void update(const drogon::orm::DbClientPtr &client);
    void deleteRecord(const drogon::orm::DbClientPtr &client);

private:
    int id_=0;
    std::string name_;
    std::string email_;
    std::string password_;
    std::chrono::system_clock::time_point created_at_;
};

}  // namespace your_namespace
}  // namespace drogon_model
