#include <typeinfo>  // nur Test
#include <ostream>

#include "./router.h"
//#include <pistache/endpoint.h>
//#include <pistache/http.h>

//#include <rapidjson/document.h>
//#include <bits/stdc++.h>

// Ctor

// Dtor
void THandler::load_token() {
    if(token.size() != 36){
        FILE * pFile;
        char buffer[100];
        pFile = fopen ("token.txt" , "r");
        if (pFile == NULL) perror ("Error opening file");
        else{
            while ( ! feof (pFile) ){
                if ( fgets (buffer , 100 , pFile) == NULL ) break;
                fputs (buffer , stdout);
            }
            fclose (pFile);
        }
        token = std::to_string(*buffer);
}}


std::string THandler::create(Document& document) {
    if(0 == document.HasMember("message")){
        return "{'error':'message is missing'}";

    }
    if(0 == document["message"].IsString()){
        return "{'error':'invalid datatype'}";
    }
    std::string category;
    if(1 == document.HasMember("category") && 1 == document["category"].IsString()){
        category = document["category"].GetString();
    }
    else{
        category = "";
    }
    std::string text = document["message"].GetString();
    Note note(text, id_count, category);
    id_count += 1;
    notes.push_back(note);
    return "{'ok':True}";

}

std::string THandler::list(Document & document) {

    std::string category;
    if(1 == document.HasMember("category") && 1 == document["category"].IsString()){
        category = document["category"].GetString();
    }
    else{
        category = "";
    }

    std::string return_data = "{data : [";

    for(int count = 0; count < notes.size();count ++){
        if(notes[count].category == category || category.empty()){
            return_data += "[";
            return_data += "'" + notes[count].message + "',";
            return_data += std::to_string(notes[count].id) + "]";
            if (count != notes.size()-1){
                return_data += ",";
            }
        }
    }
    return_data += "]}";
    return return_data;
}

std::string THandler::delete_note(Document & document) {
    if(0 == document.HasMember("id")){
        return "'error':'id is missing'}";
    }
    if(0 == document["id"].IsInt()){
        return "{'error':'invalid datatype'}";
    }

    for(int count = 0;count < notes.size();count++){
        if(notes[count].id == document["id"].GetInt()){
            notes.erase(notes.begin()+count);
            return "{'ok':True}";
        }

    }
    return "{'error':'No element with this id'}";
}