import { PlotDataStream } from '../../interfaces';
import { BehaviorSubject, Observable } from 'rxjs';
export declare class PlotsService {
    plotEntities: Map<number, PlotDataStream>;
    plotIds$: BehaviorSubject<Set<number>>;
    private currentPlotId;
    private bufferSubscription?;
    setBuffer(buffer$: Observable<Omit<PlotDataStream, 'id'>[]>): void;
    addPlot(plotData: Omit<PlotDataStream, 'id'>): void;
    /**
     * Function gets executed on the main process and makes the service read
     * the buffered plot data.
     * @param buffer
     */
    readBuffer(buffer: Omit<PlotDataStream, 'id'>[]): void;
}
