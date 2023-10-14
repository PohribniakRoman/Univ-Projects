"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getPort = void 0;
function getPort() {
    const portAsString = process.env.NODEPLOTLIB_PORT;
    const port = Number(portAsString);
    if (isNaN(port)) {
        return 0;
    }
    return port;
}
exports.getPort = getPort;
//# sourceMappingURL=get-port.js.map