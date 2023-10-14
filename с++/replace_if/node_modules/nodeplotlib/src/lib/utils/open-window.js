"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.openWindow = void 0;
const child_process_1 = require("child_process");
const os_1 = require("os");
function openWindow(location) {
    if (process.env.NODEPLOTLIB_PORT) {
        return;
    }
    switch ((0, os_1.type)()) {
        case 'Linux':
            (0, child_process_1.exec)(`xdg-open ${location}`);
            break;
        case 'Darwin':
            (0, child_process_1.exec)(`open ${location}`);
            break;
        case 'Windows_NT':
            (0, child_process_1.exec)(`start ${location}`);
            break;
    }
}
exports.openWindow = openWindow;
//# sourceMappingURL=open-window.js.map