#include "RequestParser.hpp"

RequestParser::RequestParser() : state(START_LINE), contentLength(0) {}

void RequestParser::reset() {
    state = START_LINE;
    request = HttpRequest();
    buffer.clear();
    contentLength = 0;
}

bool RequestParser::isDone() const {
    return state == DONE;
}

const HttpRequest& RequestParser::getRequest() const {
    return request;
}

RequestParser::ParseResult RequestParser::parse(const char* data, size_t len) {
    buffer.append(data, len);

    while (true) {
        switch (state) {
            case START_LINE:
                if (!parseStartLine()) return INCOMPLETE;
                state = HEADERS;
                break;

            case HEADERS:
                if (!parseHeaders()) return INCOMPLETE;
                state = BODY;
                break;

            case BODY:
                if (!parseBody()) return INCOMPLETE;
                state = DONE;
                return COMPLETE;

            case DONE:
                return COMPLETE;

            case ERROR:
                return BAD;
        }
    }
}

bool RequestParser::parseStartLine() {
    size_t pos = buffer.find("\r\n");
    if (pos == std::string::npos) return false;

    std::istringstream line(buffer.substr(0, pos));
    if (!(line >> request.method >> request.uri >> request.http_version)) {
        state = ERROR;
        return false;
    }
    buffer.erase(0, pos + 2);
    return true;
}

bool RequestParser::parseHeaders() {
    size_t pos;
    while ((pos = buffer.find("\r\n")) != std::string::npos) {
        std::string line = buffer.substr(0, pos);
        buffer.erase(0, pos + 2);
        if (line.empty()) return true; // End of headers

        size_t colon = line.find(":");
        if (colon == std::string::npos) {
            state = ERROR;
            return false;
        }
        std::string key = line.substr(0, colon);
        std::string value = line.substr(colon + 1);
        request.headers[key] = value;
    }
    return false; // wait for more data
}

bool RequestParser::parseBody() {
    if (request.method != "POST") return true;

    auto it = request.headers.find("Content-Length");
    if (it == request.headers.end()) {
        state = ERROR;
        return false;
    }

    contentLength = std::stoi(it->second);
    if (buffer.size() < contentLength) return false;

    request.body = buffer.substr(0, contentLength);
    buffer.erase(0, contentLength);
    return true;
}

