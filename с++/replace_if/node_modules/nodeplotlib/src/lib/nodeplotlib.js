"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.plot = void 0;
const tslib_1 = require("tslib");
const core_1 = require("@nestjs/core");
const rxjs_1 = require("rxjs");
const plots_service_1 = require("./server/plots/plots.service");
const server_module_1 = require("./server/server.module");
const bridge_service_1 = require("./server/services/bridge.service");
const get_port_1 = require("./utils/get-port");
let app = null;
let plotsService;
let bridgeService;
// This variable is used to determine if the nestjs app is running
// or starting. Because it is "async" and the plot function is not,
// we need to make sure that we do not bootstrap the app twice in the
// same macro-task.
let appRuns = false;
let shutdownSubscription;
const plotsBuffer$ = new rxjs_1.BehaviorSubject([]);
const port = (0, get_port_1.getPort)();
/**
 * Plots the given data with the given layout. This function
 * starts a server if one is not already running.
 * @param data
 * @param layout
 * @param cb
 */
function plot(data, layout, config) {
    bootstrap(port);
    const bufferedPlots = plotsBuffer$.value;
    const streamData$ = data instanceof rxjs_1.Observable ? data : (0, rxjs_1.of)(data);
    plotsBuffer$.next([
        ...bufferedPlots,
        { data: streamData$, layout: (0, rxjs_1.of)(layout), config },
    ]);
}
exports.plot = plot;
function bootstrap(port) {
    return tslib_1.__awaiter(this, void 0, void 0, function* () {
        if (appRuns) {
            console.log('[Nodeplotlib] App is already up and running');
            return;
        }
        appRuns = true;
        app = yield core_1.NestFactory.create(server_module_1.ServerModule);
        plotsService = app.get(plots_service_1.PlotsService);
        bridgeService = app.get(bridge_service_1.BridgeService);
        yield app.listen(port);
        const actualPort = app.getHttpServer().address().port;
        bridgeService.setPort(actualPort);
        plotsService.setBuffer(plotsBuffer$);
        console.log('[Nodeplotlib] Server running at', `http://localhost:${actualPort}`);
        shutdownSubscription = bridgeService.shutdown$.subscribe(shutdown);
    });
}
function shutdown() {
    return tslib_1.__awaiter(this, void 0, void 0, function* () {
        console.log('[Nodeplotlib] Server shutting down');
        shutdownSubscription === null || shutdownSubscription === void 0 ? void 0 : shutdownSubscription.unsubscribe();
        appRuns = false;
        if (app) {
            yield app.close();
        }
    });
}
//# sourceMappingURL=nodeplotlib.js.map