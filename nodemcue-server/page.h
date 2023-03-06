const char MAIN_page[] PROGMEM = R"=====(<!DOCTYPE html>
<html lang='en'>
<head>
    <meta charset='UTF-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>
    <title>IOt</title>

    <script
    src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.js">
    </script>

    <style>
       table, th, td {
        border: 1px solid black;
        border-collapse: collapse;
        border-color: #96D4D4;
        text-align: center;
      }
    </style>
</head>
<body>
    <p>
        <div id='tem'></div>
        <div id='hum'></div>
        <div id='soil'></div>
        <table>
          <tr>
            <th>Temperature</th>
            <th>Humidity</th>
            <th>Soil Moisture Percentage</th>
            <th>Time [minutes:seconde]</th>
          </tr>
          <tr>
            <td id='t0'>0</td>
            <td id='h0'>0</td>
            <td id='s0'>0</td>
            <td id='m0'>0</td>
          </tr>
          <tr>
            <td id='t1'>0</td>
            <td id='h1'>0</td>
            <td id='s1'>0</td>
            <td id='m1'>0</td>
          </tr>
          <tr>
            <td id='t2'>0</td>
            <td id='h2'>0</td>
            <td id='s2'>0</td>
            <td id='m2'>0</td>
          </tr>
          <tr>
            <td id='t3'>0</td>
            <td id='h3'>0</td>
            <td id='s3'>0</td>
            <td id='m3'>0</td>
          </tr>
          <tr>
            <td id='t4'>0</td>
            <td id='h4'>0</td>
            <td id='s4'>0</td>
            <td id='m4'>0</td>
          </tr>
          <tr>
            <td id='t5'>0</td>
            <td id='h5'>0</td>
            <td id='s5'>0</td>
            <td id='m5'>0</td>
          </tr>
          <tr>
            <td id='t6'>0</td>
            <td id='h6'>0</td>
            <td id='s6'>0</td>
            <td id='m6'>0</td>
          </tr>
          <tr>
            <td id='t7'>0</td>
            <td id='h7'>0</td>
            <td id='s7'>0</td>
            <td id='m7'>0</td>
          </tr>
          <tr>
            <td id='t8'>0</td>
            <td id='h8'>0 </td>
            <td id='s8'>0</td>
            <td id='m8'>0</td>
          </tr>
          <tr>
            <td id='t9'>0</td>
            <td id='h9'>0</td>
            <td id='s9'>0</td>
            <td id='m9'>0</td>
          </tr>
        </table> 
    </p>

<canvas id="myChart" style="width:100%;max-width:700px"></canvas>

</body>
<script>
    var Socket;
    function init() {
        Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
        Socket.onmessage = function(event) {
        receiveData(event);
    };
  }
  function receiveData(event) {
	var obj = JSON.parse(event.data);
    console.log(obj.soil);
    fillTable(obj);
    average(obj);
    drawChart(obj)
  }
  function fillTable(obj){
    var t = new Date();
    for(var i=0; i<10;i++){
      document.getElementById('t'+i).innerText = obj.temperature[i];
      document.getElementById('h'+i).innerText = obj.humidity[i];
      document.getElementById('s'+i).innerText = obj.soil[i];
        }
  }
  function average(obj){
    var temSum =0;
    var humSum =0;
    var soilSum =0;
    for(var i=0; i<10;i++){
      temSum += obj.temperature[i];
      humSum += obj.humidity[i];
      soilSum += obj.soil[i];
    }
    document.getElementById('tem').innerText='average Temperature = '+temSum/10;

    console.log(obj.temperature);
    document.getElementById('hum').innerText='average Humidity = '+humSum/10;

    console.log(obj.humidity);
    document.getElementById('soil').innerText='average Soil = '+soilSum/10;
  }
  function drawChart(obj){
    var yValues = [1,2,3,4,5,6,7,8,9,10];
    new Chart('myChart', {
        type: 'line',
        data: {
          labels: yValues,
          datasets: [{
            // backgroundColor: 'rgba(0,0,0,1.0)',
            borderColor: 'rgba(0,0,0,0.1)',
            data: obj.soil
          }]
      },
     // options:{...}
    });
  }
  window.onload = function(event) {
    init();
  }
</script>
</html>







)=====";