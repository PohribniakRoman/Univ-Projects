"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.PlotsService = void 0;
const tslib_1 = require("tslib");
const common_1 = require("@nestjs/common");
const rxjs_1 = require("rxjs");
const operators_1 = require("rxjs/operators");
let PlotsService = class PlotsService {
    constructor() {
        this.plotEntities = new Map();
        this.plotIds$ = new rxjs_1.BehaviorSubject(new Set());
        this.currentPlotId = 0;
    }
    setBuffer(buffer$) {
        var _a;
        (_a = this.bufferSubscription) === null || _a === void 0 ? void 0 : _a.unsubscribe();
        this.bufferSubscription = buffer$
            .pipe((0, operators_1.filter)((buffer) => buffer.length > 0))
            .subscribe((buffer) => this.readBuffer(buffer));
    }
    addPlot(plotData) {
        const plot = {
            id: this.currentPlotId++,
            data: plotData.data,
            layout: plotData.layout,
            config: plotData.config,
        };
        this.plotEntities.set(plot.id, plot);
        const plotIds = this.plotIds$.value;
        plotIds.add(plot.id);
        this.plotIds$.next(plotIds);
    }
    /**
     * Function gets executed on the main process and makes the service read
     * the buffered plot data.
     * @param buffer
     */
    readBuffer(buffer) {
        for (const plot of buffer) {
            this.addPlot(plot);
        }
    }
};
PlotsService = tslib_1.__decorate([
    (0, common_1.Injectable)()
], PlotsService);
exports.PlotsService = PlotsService;
//# sourceMappingURL=plots.service.js.map