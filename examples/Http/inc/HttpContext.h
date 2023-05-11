#pragma once
#include<string>
#include<map>

//解析状态
enum ParseState{
    kExpectLine,
    kExpectHeaders,
    kExpectBody,
    kFinshed
};

class Buffer;

class HttpContext
{
public:
    HttpContext() = default;
    ~HttpContext() = default;

    bool parseFinshed() const { return _parseState == kFinshed;}
    bool parse(Buffer* buf);
    bool parseRequestLine(std::string& line);
    bool parseHeaders(std::string& line);
    bool parseBody();

    bool getConnection() const {return _isKeepAlive;}
    std::string getVersion() const {return _version;}
    std::string getPath() const {return _path;}

private:
    ParseState _parseState;     //当前解析状态

    std::string _method;        //请求方法
    std::string _version;       //HTTP版本
    std::string _path;          //请求路径
    std::string _body;          //请求体
    size_t _contentLen;         //请求体的长度
    bool _isKeepAlive;          //是否保持连接
    std::map<std::string, std::string> _headers;    //请求头
    
};