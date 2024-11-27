#include "api_v1_User.h"
#include <json/json.h>
#include "bcrypt/BCrypt.hpp"
#include<drogon/drogon.h>
#include <drogon/orm/Mapper.h>
#include <jwt-cpp/jwt.h>
#include<iostream>
#include <models/Users.h>
#include <drogon/orm/DbClient.h>
using namespace api::v1;
using namespace drogon;
using namespace mynamespace::usermodel;

std::string mySecretKey="kelggkljgnkfghhnhdn";
std::string hashPass(std::string &pass,int salt){
    return BCrypt::generateHash(pass,10);
}
std::string genToken(std::string name,std::string email){
    return jwt::create()
    .set_type("JWS")
    .set_issuer("auth0")
    .set_payload_claim("user",jwt::claim(std::string(name)))
    .set_payload_claim("email",jwt::claim(std::string(email)))
    .set_payload_claim("iat", jwt::claim(std::chrono::system_clock::now()))
    .set_payload_claim("exp", jwt::claim(std::chrono::system_clock::now() + std::chrono::hours(1)))
    .sign(jwt::algorithm::hs256{mySecretKey});
}


void UserController::signup(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) const{
    auto userData=req->getJsonObject();
    if(!userData || !userData->isMember("email") || !userData->isMember("password") || !userData->isMember("name")) {
        auto res=drogon::HttpResponse::newHttpResponse();
        res->setStatusCode(drogon::k400BadRequest);
        res->setBody("All fields are required");
        callback(res);
        return;
    }
    std::string nameStr=(*userData)["name"].asString();
    std::string emailStr=(*userData)["email"].asString();
    std::string passwordStr=(*userData)["password"].asString();

    auto dbClient=drogon::app().getDbClient();
    if(!dbClient) {
         auto res=drogon::HttpResponse::newHttpResponse();
        res->setStatusCode(drogon::k400BadRequest);
        res->setBody("Internal Server error");
        callback(res);
        return;
    }

    //hash password
    std::string hashedPassword=hashPass(passwordStr,10);
    auto user=std::make_shared<Users>();
    user->setName(nameStr);
    user->setPassword(hashedPassword);
    user->setEmail(emailStr);

    //save in databse
    user->insert(dbClient);
    //generation of token
    std::string token=genToken(nameStr,emailStr);
    Json::Value resObj;
    resObj["statusCode"]=200;
    resObj["message"]="user created successfully";
    resObj["user"]=*userData;
    auto res=drogon::HttpResponse::newHttpJsonResponse(resObj);
    callback(res);
}
