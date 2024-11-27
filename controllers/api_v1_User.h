#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace api
{
namespace v1
{
class UserController : public drogon::HttpController<UserController>
{
  public:
    METHOD_LIST_BEGIN
    METHOD_ADD(UserController::signup,"/signup",Post);
    METHOD_LIST_END

    void signup(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const;
};
}
}
