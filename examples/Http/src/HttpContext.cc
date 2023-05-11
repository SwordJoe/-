#include"HttpContext.h"
#include"Buffer.h"
#include<regex>
#include<algorithm>

const char CRLF[] = "\r\n";

bool HttpContext::parse(Buffer* buf)
{  
    while(buf->readableBytes()){
        char* lineEnd;
        std::string line;

        if(_parseState != kExpectBody){
            lineEnd = std::search(buf->beginRead(), buf->beginWrite(), CRLF, CRLF+2);
            if(lineEnd == buf->beginWrite()){
                return false;
            }
            line = std::string(buf->beginRead(), lineEnd);
            buf->retrieve(lineEnd + 2 - buf->beginRead()); //紧缩请求行和末尾的"\r\n"两个字符
        }
        else{
            if(buf->readableBytes() < _contentLen){
                return false;
            }
            //_request->setBody(buf->retrieveAllAsString());
            _body = buf->retrieveAllAsString();
        }

        switch(_parseState){
            case kExpectLine:
            {
                bool ret = parseRequestLine(line);
                if(ret == false){
                    return false;
                }
                break;
            }
            case kExpectHeaders:
            {
                bool ret = parseHeaders(line);
                if(ret){
                    return true;
                }
                break;
            }
            case kExpectBody:
            {
                bool ret = parseBody();
                if(ret){
                    return true;
                }
                break;
            }
            case kFinshed:
            {
                return true;
            }
        }
    }

    //没有在while循环里return，说明读空了缓存仍然没有收到完整请求
    return false;
}

bool HttpContext::parseRequestLine(std::string& line)
{
    std::regex pattern("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
    std::smatch subMatch;

    if(std::regex_match(line, subMatch, pattern)){
        _method = subMatch[1];
        _path = subMatch[2];
        _version = subMatch[3];
        _parseState = kExpectHeaders;
        return true;
    }
    return false;
}

bool HttpContext::parseHeaders(std::string& line)
{
    std::regex pattern("^([^:]*): ?(.*)$");
    std::smatch subMatch;

    if(std::regex_match(line, subMatch, pattern)){
        _headers[subMatch[1]] = subMatch[2];
        if(subMatch[1] == "Connection"){
            _isKeepAlive = (subMatch[2] == "keep-alive");
        }
        if(subMatch[1] == "Content-Length"){
            _contentLen = std::stoi(subMatch[2]);
        }
        return false;
    }
    else if(_contentLen){       //说明后续还有请求体数据，继续返回false
        _parseState = kExpectBody;
        return false;
    }
    else{       //说明请求头解析完毕，后面也没有请求体数据，返回true
        return true;
    }
}

bool HttpContext::parseBody()
{

}
