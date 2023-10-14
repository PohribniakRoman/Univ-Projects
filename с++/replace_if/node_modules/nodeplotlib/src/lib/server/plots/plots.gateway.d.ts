import { OnGatewayConnection, OnGatewayDisconnect } from '@nestjs/websockets';
import { PlotData } from '../../interfaces';
import { Observable } from 'rxjs';
import { BridgeService } from '../services/bridge.service';
import { PlotsService } from './plots.service';
export declare class PlotsGateway implements OnGatewayConnection, OnGatewayDisconnect {
    private bridgeService;
    private plotsService;
    private clientMap;
    private plotDataStream$;
    constructor(bridgeService: BridgeService, plotsService: PlotsService);
    handleEvent(): Observable<{
        event: string;
        data: PlotData;
    }>;
    handleConnection(client: WebSocket): void;
    handleDisconnect(client: WebSocket): void;
}
