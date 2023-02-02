// Create the charts when the web page loads
window.addEventListener('load', onload);

function onload(event){
  chartX = createXChart();
  chartY = createYChart();
  chartZ = createZChart();
}

// Create Temperature Chart
function createXChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-X',
      type: 'spline' 
    },
    series: [
      {
        name: 'Gyro'
      }
    ],
    title: { 
      text: undefined
    },
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'X orientation' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create Humidity Chart
function createYChart(){
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-Y',
      type: 'spline'  
    },
    series: [{
      name: 'Gyro'
    }],
    title: { 
      text: undefined
    },    
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      },
      series: { 
        color: '#50b8b4' 
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'Y orientation' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create Pressure Chart
function createZChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-Z',
      type: 'spline'  
    },
    series: [{
      name: ''
    }],
    title: { 
      text: undefined
    },    
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      },
      series: { 
        color: '#A62639' 
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'Z Orientation' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}