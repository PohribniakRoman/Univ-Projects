import { Layout, Plot } from './interfaces';
import { Observable } from 'rxjs';
import { Config } from './interfaces/plot';
/**
 * Plots the given data with the given layout. This function
 * starts a server if one is not already running.
 * @param data
 * @param layout
 * @param cb
 */
export declare function plot(data: Plot[] | Observable<Plot[]>, layout?: Layout, config?: Config): void;
