#pragma once
//#ifndef C_API_ROUTER_H
//#define C_API_ROUTER_H

#include <string>
#include <vector>

#include <pistache/endpoint.h>
#include <pistache/http.h>

#include <rapidjson/document.h>
#include "rapidjson/schema.h"
#include "note.h"
//#include <bits/stdc++.h>

//http://rapidjson.org/md_doc_tutorial.html
using namespace Pistache;
using namespace rapidjson;

//typedef void(*)(const Http::Request&, Http::ResponseWriter) t_http_handler;
typedef std::map<std::string, void(*)(const Http::Request&, Http::ResponseWriter)> t_func_map;
typedef std::map<std::string, void(*)(const Http::Request&, Http::ResponseWriter)>::iterator t_func_map_iter;

class THandler : public Http::Handler {
public:
//  HTTP_PROTOTYP(Handler)
  HTTP_PROTOTYPE(THandler)

  std::vector<Note> notes;
  std::string token;
  unsigned int id_count = 0;

  void load_token();
  std::string create(Document&);
  std::string list(Document&);
  std::string delete_note(Document&);

  void onRequest(const Http::Request& request, Http::ResponseWriter response) override{

      Document document;
    std::string req = request.body();
    const char *cstr = req.c_str();



    if (1 == document.Parse(cstr).HasParseError()){
      response.send(Pistache::Http::Code::Not_Found, "{'error':'json is required'}");
      return;
    }
    document.Parse(cstr);
    load_token();

    if(0 == document.HasMember("token") || 0 == document["token"].IsString()){
      response.send(Pistache::Http::Code::Not_Found, "{'error':'token is missing or wrong datatype'}");
      return;
    }

    if(token != ((std::string)document["token"].GetString()) + "\n"){
      response.send(Pistache::Http::Code::Unauthorized, "{'error':'invalid auth token'}");
      return;
    }

    if (request.resource() == "/create_note/"){

       std::string return_data = create(document);
       response.send(Pistache::Http::Code::Ok, return_data);
    }
    if(request.resource() == "/list_notes/"){

        std::string return_data = list(document);
        response.send(Pistache::Http::Code::Ok, return_data);

    }
    if(request.resource() == "/delete_note/"){

        std::string return_data = delete_note(document);

        response.send(Pistache::Http::Code::Ok, return_data);

    }
    response.send(Pistache::Http::Code::Not_Found, "{'error':'Unkown endpoint'}");

  };


};
//#endif
