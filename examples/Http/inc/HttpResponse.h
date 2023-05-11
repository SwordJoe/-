#pragma once
#include<string>
#include<map>

enum HttpStatusCode
{
    k200OK = 200, 
    k301MovePermanently = 301,
    k400BadRequest = 400,
    k404NotFound = 404
};

class HttpResponse
{
public:
    HttpResponse(bool isKeepAlive):_isKeepAlive(isKeepAlive){}
    ~HttpResponse() = default;

    void setStatusCode(int code){_statusCode = code;}
    void setStatusMessage(const std::string& str){_statusMessage = str;}
    void addHeader(const std::string& key, const std::string& value){ _headers[key] = value;}
    void setBody(const std::string& str){ _body = str;}
    
    std::string makeResponseMsg(){
        std::string msg;
        msg = "HTTP/1.1 " + std::to_string(_statusCode) + " " + _statusMessage + "\r\n";

        if(!_isKeepAlive){
            msg += "Connection: close\r\n";
        }
        else{
            msg += "Connection: Keep-Alive\r\n";
            msg += ("Content-Length: " + std::to_string(_body.size()) + "\r\n");
        }
        
        for(const auto& header : _headers){
            msg += (header.first + ": " + header.second + "\r\n");
        }
        msg += "\r\n";
        msg += _body;

        return msg;
    }

private:
    int _statusCode;
    std::string _statusMessage;
    std::map<std::string, std::string> _headers;
    std::string _body;
    bool _isKeepAlive;
};