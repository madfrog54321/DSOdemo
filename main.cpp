#include <uWS/uWS.h>
#include <iostream>

int main() {
    uWS::Hub h;

    h.onMessage([](uWS::WebSocket<uWS::SERVER> ws, char *message, size_t length, uWS::OpCode opCode) {
        if (length && message[0] != 'S' && length < 4096) {
            // add this message to the store, cut off old messages
            std::cout << "Message posted: " << std::string(message, length) << std::endl;
        }
        ws.send(message, length, opCode);
    });

    h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t length, size_t remainingBytes) {
        res->end("", 0);
    });

    h.listen(3000);
    h.run();
}
