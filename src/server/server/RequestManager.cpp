// #include <SFML/Network.hpp>
// #include "json/json.h"
// #include <iostream>
// #include <cstring>
// #include <unistd.h>

// using namespace std;

// void RequestManager::makeRequest (std::string destination, std::string method, std::string uri, std::string body)
// {
//     sf::Http http(destination, 8080);
//     sf::Http::Request request;
//     if(method=="GET") request.setMethod(sf::Http::Request::Get);
//     else if(method=="POST") request.setMethod(sf::Http::Request::Post);
//     else if(method=="PUT") request.setMethod(sf::Http::Request::Put);
//     else if(method=="DELETE") request.setMethod(sf::Http::Request::Delete);
//     request.setUri(uri);
//     request.setHttpVersion(1, 0);
//     request.setBody(body);

//     sf::Http::Response response = http.sendRequest(request);
//     cout<< "status : "<<response.getStatus()<<endl;
//     cout<<"HTTP version : "<<response.getMajorHttpVersion()<< "." <<response.getMinorHttpVersion()<<endl;
//     cout<<"Content-type header :"<<response.getField("Content-Type")<<endl;
//     cout<<"body :"<<response.getBody()<<endl;

// }