import { Subject } from 'rxjs';
/**
 * The BridgeService is used to build a bridge between the
 * NestJS server and the outside of the NestJS server.
 * The two purposes are to get the port of the express server
 * inside of the NestJS server and to provide a shutdown$
 * steam so that the NestJS server can trigger a full shutdown.
 *
 * @see nodeplotlib.ts
 */
export declare class BridgeService {
    shutdown$: Subject<unknown>;
    port$: Subject<number>;
    constructor();
    setPort(port: number): void;
    shutdown(): void;
}
