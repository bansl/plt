#include "../server.h"
#include <iostream>
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
    if (!service)
		
        throw ServiceException(HttpStatus::NOT_FOUND,"Service "+url+" not found");
    // Recherche un éventuel id (ex: /mon/service/<id>)
    const string& resourceType(service->resourceType);
    int id = 0;
	
    if (url.size() > resourceType.size()) {
        string end = url.substr(resourceType.size());
        if (end[0] != '/')
            throw ServiceException(HttpStatus::BAD_REQUEST,"wrong syntax: <service>/<number> expected");
        end = end.substr(1);
        if (end.empty())
            throw ServiceException(HttpStatus::BAD_REQUEST,"wrong syntax: <service>/<number> expected");
        try {
            size_t pos = 0;
            id = stoi(end,&pos);
            if (pos != end.size())
                throw ServiceException(HttpStatus::BAD_REQUEST,"wrong syntax: '"+end+"' NaN");
        }
        catch(...) {
            throw ServiceException(HttpStatus::BAD_REQUEST,"wrong syntax: '"+end+"' NaN");
        }
    }
    // Traite les différentes méthodes
    if (method == "GET") {
		int n_id=0;
		for(size_t i=0; i<services.size(); i++){
			// if(!services[i]->isVersion()){
				PlayerService& player_service=static_cast<PlayerService&>(*services[i]);
				n_id=player_service.getGame().getIDseq();
			// }
		}
		if(id<n_id){
        	cerr << "GET Request" << resourceType << " id:" << id << endl;
		}
        Json::Value jsonOut;
        HttpStatus status = service->get(jsonOut,id);
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
        cerr << "PUT Request" << resourceType << " body: {\"name\":" << jsonIn["name"].asString()<<" ,\"inlobby\":"<<jsonIn["inlobby"]<<"}" << endl;
        
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
	
    else if (method=="DELETE" || (method == "POST" && in[0]=='D')) {
        cerr << "DELETE Request" << endl;
        return service->remove(id);
    }
    throw ServiceException(HttpStatus::BAD_REQUEST,"Invalid "+method+" Method");
}


