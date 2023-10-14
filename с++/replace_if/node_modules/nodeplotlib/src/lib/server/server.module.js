"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.ServerModule = void 0;
const tslib_1 = require("tslib");
const common_1 = require("@nestjs/common");
const serve_static_1 = require("@nestjs/serve-static");
const path_1 = require("path");
const plots_gateway_1 = require("./plots/plots.gateway");
const plots_service_1 = require("./plots/plots.service");
const bridge_service_1 = require("./services/bridge.service");
let ServerModule = class ServerModule {
};
ServerModule = tslib_1.__decorate([
    (0, common_1.Module)({
        imports: [
            serve_static_1.ServeStaticModule.forRoot({
                rootPath: (0, path_1.join)(__dirname, 'web'),
            }),
        ],
        providers: [plots_gateway_1.PlotsGateway, plots_service_1.PlotsService, bridge_service_1.BridgeService],
    })
], ServerModule);
exports.ServerModule = ServerModule;
//# sourceMappingURL=server.module.js.map