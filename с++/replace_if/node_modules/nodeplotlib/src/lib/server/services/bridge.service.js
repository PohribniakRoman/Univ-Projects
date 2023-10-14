"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.BridgeService = void 0;
const tslib_1 = require("tslib");
const common_1 = require("@nestjs/common");
const rxjs_1 = require("rxjs");
const open_window_1 = require("../../utils/open-window");
/**
 * The BridgeService is used to build a bridge between the
 * NestJS server and the outside of the NestJS server.
 * The two purposes are to get the port of the express server
 * inside of the NestJS server and to provide a shutdown$
 * steam so that the NestJS server can trigger a full shutdown.
 *
 * @see nodeplotlib.ts
 */
let BridgeService = class BridgeService {
    constructor() {
        this.shutdown$ = new rxjs_1.Subject();
        this.port$ = new rxjs_1.Subject();
        this.port$.subscribe((port) => {
            (0, open_window_1.openWindow)(`http://localhost:${port}`);
        });
    }
    setPort(port) {
        this.port$.next(port);
    }
    shutdown() {
        this.shutdown$.next(null);
    }
};
BridgeService = tslib_1.__decorate([
    (0, common_1.Injectable)(),
    tslib_1.__metadata("design:paramtypes", [])
], BridgeService);
exports.BridgeService = BridgeService;
//# sourceMappingURL=bridge.service.js.map