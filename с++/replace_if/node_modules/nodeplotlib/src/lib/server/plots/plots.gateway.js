"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.PlotsGateway = void 0;
const tslib_1 = require("tslib");
const websockets_1 = require("@nestjs/websockets");
const rxjs_1 = require("rxjs");
const operators_1 = require("rxjs/operators");
const bridge_service_1 = require("../services/bridge.service");
const plots_service_1 = require("./plots.service");
let PlotsGateway = class PlotsGateway {
    constructor(bridgeService, plotsService) {
        this.bridgeService = bridgeService;
        this.plotsService = plotsService;
        this.clientMap = new Map();
        this.plotDataStream$ = this.plotsService.plotIds$.pipe((0, operators_1.switchMap)((plotIds) => (0, rxjs_1.merge)(...Array.from(plotIds).map((id) => {
            const plotDataStream = this.plotsService.plotEntities.get(id);
            if (!plotDataStream) {
                return new rxjs_1.Observable();
            }
            return (0, rxjs_1.combineLatest)([
                plotDataStream.data,
                plotDataStream.layout,
            ]).pipe((0, operators_1.map)(([data, layout]) => ({
                id,
                data,
                layout,
                config: plotDataStream.config,
            })));
        }))), (0, operators_1.share)());
    }
    handleEvent() {
        return this.plotDataStream$.pipe((0, operators_1.map)((plotData) => ({
            event: 'plotdata',
            data: plotData,
        })));
    }
    handleConnection(client) {
        console.log('[Nodeplotlib] client connected');
        this.clientMap.set(client, Date.now());
    }
    handleDisconnect(client) {
        console.log('[Nodeplotlib] client disconnected');
        this.clientMap.delete(client);
        if (this.clientMap.size === 0) {
            this.bridgeService.shutdown$.next(null);
        }
    }
};
tslib_1.__decorate([
    (0, websockets_1.SubscribeMessage)('readplots'),
    tslib_1.__metadata("design:type", Function),
    tslib_1.__metadata("design:paramtypes", []),
    tslib_1.__metadata("design:returntype", void 0)
], PlotsGateway.prototype, "handleEvent", null);
PlotsGateway = tslib_1.__decorate([
    (0, websockets_1.WebSocketGateway)({ transports: ['polling'] }),
    tslib_1.__metadata("design:paramtypes", [bridge_service_1.BridgeService,
        plots_service_1.PlotsService])
], PlotsGateway);
exports.PlotsGateway = PlotsGateway;
//# sourceMappingURL=plots.gateway.js.map