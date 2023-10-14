import { Layout as PlotlyLayout, PlotData as PlotlyPlotData, Config as PlotlyConfig } from 'plotly.js';
import { Observable } from 'rxjs';
export declare type Plot = Partial<PlotlyPlotData>;
export declare type Layout = Partial<PlotlyLayout>;
export declare type Config = Partial<PlotlyConfig>;
export interface PlotDataStream {
    id: number;
    data: Observable<Plot[]>;
    layout: Observable<Layout | undefined>;
    config: Config | undefined;
}
export interface PlotData {
    id: number;
    data: Plot[];
    layout?: Layout;
    config?: Config;
}
