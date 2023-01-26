#  <img src="https://cdn3.iconfinder.com/data/icons/startup-management-flat/256/-_gears_descriptions_management_project-512.png" alt="" style="width:20px;height:20px;">  وصف المشروع

 تطبيقا على مجال انترنت الاشياء, قمت بأستخدام مجموعة من السنسورات التي تقيس كميات فيزيائية مثل درجة الحرارة والرطوبة ورطوبة التربة, من خلال مايكروكنترولر ثم ربطه بسيرفر , وقمت بتصميم صفحة ويب لعرض هذه المعلومات عند اتصالها بالسيرفر

 # <img src="https://cdn0.iconfinder.com/data/icons/project-management-scrum-and-agile/96/agile_scrum_goal_target_planning_iteration_business-512.png" alt="" style="width:30px;height:30px;">   الهدف من المشروع

 يمكن استخدام المشروع في مجال الزراعة حيث يتيح لنا مراقبة رطوبة التربة الزراعية نفسها وايضا مراقبة درجات الحرارة حول الارض الزراعية , مما يتيح لنا اكبر قدر من مراقبة المحاصيل الزراعية ومعرفة متى تحتاج الي الماء اللازم, وهذا يؤدي الي تقليل استهلاك المياه ومتابعة المحاصيل جيدا

# <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcdn2.iconfinder.com%2Fdata%2Ficons%2Fadvertisement-marketing%2F512%2Fpuzzle-512.png&f=1&nofb=1&ipt=d8b5faa6f09d533d606dbbda1cb362d52891402538e5306dcfa147431b9e7d38&ipo=images" alt="" style="width:30px;height:30px;"> الادوات المستخدمة 

## => الهاردوير

أ. esp 8266

<img src="https://leantec.es/wp-content/uploads/2018/02/p_3_3_2_7_3327-NodeMcu-Lua-ESP8266-ESP12E-CP2102-WiFi-Wireless-Nueva-version.jpg" alt="esp" style="width:300px;height:300px;">

ب. DHT 11 

<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Ftse1.mm.bing.net%2Fth%3Fid%3DOIP.TKlPr6ULRzTfsCDINlpoMgHaHa%26pid%3DApi&f=1&ipt=49571d655c64d07bdea5c8f949fe0dd23208145d19bf735bcd6d2bf933b1b029&ipo=images" alt="esp" style="width:300px;height:300px;">

ج.Soil moisture

<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcircuit.pk%2Fwp-content%2Fuploads%2F2017%2F02%2Fsoil-moisture-sensor.jpg&f=1&nofb=1&ipt=ea792254bf376a2d1605bbee42e1379e69dc6a9bea1318ffddf53ffd94b1ce85&ipo=images" alt="esp" style="width:300px;height:300px;">

## => السوفتوير 

أ.visual studio code 

 ------>استخدام البرنامج لكتابة اكواد السيرفر وصفحة الويب, يمكن تحميله من [هنا](https://code.visualstudio.com/Download)

ب.Arduino IDE

------>استخدام البرنامج لكتابة اكواد المايكروكنترولر يمكن تحميله من [هنا](https://www.arduino.cc/en/software)


ج.node js, express, websocket

يمكن تحميل node js من [هنا](https://www.arduino.cc/en/software) 
بعد ذلك ندخل على ال visual studio code ونفتح ال terminal ونكتب هذان الامران

```
$ npm install --save express
$ npm install --save ws
```

# <img src="images\Screenshot_2023-01-26_09-21-52.png" alt="" style="width:30px;height:30px;"> التركيب والتثبيت

## => الهاردوير
<img src="images\Screenshot_2023-01-26_08-46-04.png">

## => السوفتوير 

نضع هذا الرابط (http://arduino.esp8266.com/stable/package_esp8266com_index.json) في ال preferences وذلك لتحميل بوردة المايكرو كنترولر

<img src="images\Screenshot_2023-01-26_08-56-50.png" >

نقوم بالبحث عن بوردة esp8266 وتثبيتها

<img src="images\Screenshot_2023-01-26_08-57-25.png" >

نثبت المكتبات اللازمة 

<img src="images\Screenshot_2023-01-26_08-56-25.png" >

# <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcdn4.iconfinder.com%2Fdata%2Ficons%2Frcons-application%2F32%2Fapplication_go_run-512.png&f=1&nofb=1&ipt=8c36d1bb33936005ee1a6a4fa6dd36bcd48f581108091b104f684b73d3c3d488&ipo=images" alt="" style="width:30px;height:30px;"> التشغيل
شغل السيرفر من خلال الكتابة في ال terminal 
```
$ npm start
```
افتح المتصفح ثم ادخل على
```
localhost:4000
```
4000 is port number you can chane it from server and esp codes