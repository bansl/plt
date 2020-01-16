#include "../server.h"
#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;
using namespace server;

void ServicesManager::registerService (unique_ptr<Service> service) {
    services.push_back(std::move(service));
}

Service* ServicesManager::findService (const string& url) const {
	
    for (auto& service : services) {
        const string& resourceType(service->resourceType);
		
        if (url.find(resourceType) != 0)
			
            continue;
        if (url.size() > resourceType.size() && url[resourceType.size()] != '/')
			
            continue;
        return service.get();
    }
    return nullptr;
}

HttpStatus ServicesManager::queryService (string& out, const string& in, const string& url, const string& method) { 
    Service* service = findService(url);
    cout << "my url"<<url << endl;
    if (!service) throw ServiceException(HttpStatus::NOT_FOUND,"Service "+url+" not found");
    
    const string& resourceType(service->resourceType);
    int id = 0;
    
    if (method == "GET") {
        Json::Value jsonOut;
        HttpStatus status;
        string inst = url.substr(resourceType.size()+1);
        if (inst=="all") {
            status = service->getall(jsonOut);
            cout << "GET Request" << resourceType << " list" << endl;
        }
        else {
            cout << "GET Request" << resourceType << " id:" << inst << endl;
            int id=stoi(inst);
            status = service->get(jsonOut,id);
        }
        out = jsonOut.toStyledString();
        return status;
    }
    else if (method == "POST" && in[2]!='r' && in[0]=='{') {
        cerr << "POST Request" << resourceType << " body: " << in << endl;
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid Data: "+jsonReader.getFormattedErrorMessages());
        return service->post(jsonIn,id);
    }
    else if ((method == "POST" && in[2]=='r'&& in[0]=='{')) {
		
		Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn)){
            throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid Data: "+jsonReader.getFormattedErrorMessages());
			cerr << "POST Request " << resourceType << " body:" << in << endl;
		}
        cerr << "POST Request " << resourceType << " body:" << in << endl;
        Json::Value jsonOut;
        HttpStatus status = service->put(jsonOut,jsonIn);
        out = jsonOut.toStyledString();
        return status;
    }
	else if (method=="PUT"){
		
        cerr << "PUT Request" << resourceType << " body: " << in << endl;
        Json::Reader jsonReader;
        Json::Value jsonIn;
        if (!jsonReader.parse(in,jsonIn))
            throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid Data: "+jsonReader.getFormattedErrorMessages());
        Json::Value jsonOut;
        HttpStatus status = service->put(jsonOut,jsonIn);
        out = jsonOut.toStyledString();
        return status;
	}
	
    else if (method=="DELETE" || (method == "POST" && in[0]=='d')) {
        cerr << "DELETE Request" << endl;
        string inst = url.substr(resourceType.size()+1);
        int id=stoi(inst);
        return service->remove(id);
    }
    throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid "+method+" Method");
}


