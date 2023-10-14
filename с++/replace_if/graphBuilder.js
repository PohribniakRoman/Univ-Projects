const fs = require('fs');
const plot = require('nodeplotlib');

const data = fs.readFileSync('replace_if_performance.txt', 'utf8').trim().split('\n');
const values = data.map(line => line.split(' '));

const sizes = values.map(pair => Number(pair[1]));
const sizesXtimes = values.map(pair => Number(pair[0])*Number(pair[1])); // threadPolyfillAnalyticsV2
const times = values.map(pair => +pair[0]);


// plot.plot([{y:times,x:sizes,type:"bar"}], {title: 'Miliseconds per replace'}); // replace
plot.plot([{x:times,y:sizes,type:"bar"}], {title: 'AVG Miliseconds per thread'}); // threadPolyfillAnalyticsV2
plot.plot([{x:times,y:sizesXtimes,type:"bar"}], {title: 'Thread count * Miliseconds per thread'}); // threadPolyfillAnalyticsV2
// plot.plot([{x:times,y:sizes,type:"bar"}], {title: 'Miliseconds per replace'}); // thread
