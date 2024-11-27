#include "Users.h"
#include <drogon/orm/Mapper.h>
#include <drogon/drogon.h>

namespace mynamespace {
namespace usermodel {

// Getters
const int &Users::getId() const {
    return this->id_;
}

const std::string &Users::getName() const {
    return this->name_;
}

const std::string &Users::getEmail() const {
    return this->email_;
}

const std::string &Users::getPassword() const {
    return this->password_;
}

const std::chrono::system_clock::time_point &Users::getCreatedAt() const {
    return this->created_at_;
}

// Setters
void Users::setId(const int &id) {
    this->id_ = id;
}

void Users::setName(const std::string &name) {
    this->name_ = name;
}

void Users::setEmail(const std::string &email) {
    this->email_ = email;
}

void Users::setPassword(const std::string &password) {
    this->password_ = password;
}

void Users::setCreatedAt(const std::chrono::system_clock::time_point &createdAt) {
    this->created_at_ = createdAt;
}

// Insert Operation
void Users::insert(const drogon::orm::DbClientPtr &client) {
    drogon::orm::Mapper<Users> mapper(client);

    mapper.insert(
        *this,
        [](const Users &user) {
            LOG_INFO << "Successfully inserted user with ID: " << user.getId();
        },
        [](const drogon::orm::DrogonDbException &e) {
            LOG_ERROR << "Failed to insert user: " << e.base().what();
        }
    );
}

// Update Operation
void Users::update(const drogon::orm::DbClientPtr &client) {
    drogon::orm::Mapper<Users> mapper(client);

    mapper.update(
        *this,
        [](const size_t count) {
            LOG_INFO << "Successfully updated " << count << " user(s).";
        },
        [](const drogon::orm::DrogonDbException &e) {
            LOG_ERROR << "Failed to update user: " << e.base().what();
        }
    );
}

// Delete Operation
void Users::deleteRecord(const drogon::orm::DbClientPtr &client) {
    drogon::orm::Mapper<Users> mapper(client);

    mapper.deleteBy(
        drogon::orm::Criteria("id", id_),
        [](const size_t count) {
            LOG_INFO << "Successfully deleted " << count << " user(s).";
        },
        [](const drogon::orm::DrogonDbException &e) {
            LOG_ERROR << "Failed to delete user: " << e.base().what();
        }
    );
}

} // namespace usermodel
} // namespace drogon_model
