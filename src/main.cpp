#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <rapidjson/document.h>
#include "rapidjson/schema.h"
#include <iostream>
#include <string>
#include "note.h"
#include "router.h"

using namespace Pistache;
using namespace rapidjson;

int main() {
    Pistache::Port port(9080);

    Pistache::Address addr(Pistache::Ipv4::any(), port);
    auto opts = Pistache::Http::Endpoint::options().threads(1);

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<THandler>());
    server.serve();

    server.shutdown();
}

