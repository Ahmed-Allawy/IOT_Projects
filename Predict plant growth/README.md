<img src="images/5.jpg" alt=""> 

#  <img src="https://cdn3.iconfinder.com/data/icons/startup-management-flat/256/-_gears_descriptions_management_project-512.png" alt="" style="width:20px;height:20px;">  وصف المشروع

 تطبيقا على مجال انترنت الاشياء, قياس درجة حرارة النبات لمعرفة معدل نمو النبات في اليوم Growing degree days

 # <img src="https://cdn0.iconfinder.com/data/icons/project-management-scrum-and-agile/96/agile_scrum_goal_target_planning_iteration_business-512.png" alt="" style="width:30px;height:30px;">   الهدف من المشروع

 يمكن استخدام المشروع في الزراعة الذكية  حيث يتيح لنا معرفة متى ينمو النبات وذلك من خلال Growing degree days حيث يتم احتسابه من خلال درجة الحرارة

 <img src="images/4.PNG" alt="" >


# <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcdn2.iconfinder.com%2Fdata%2Ficons%2Fadvertisement-marketing%2F512%2Fpuzzle-512.png&f=1&nofb=1&ipt=d8b5faa6f09d533d606dbbda1cb362d52891402538e5306dcfa147431b9e7d38&ipo=images" alt="" style="width:30px;height:30px;"> الادوات المستخدمة 

## => الهاردوير

أ. esp 32

<img src="https://leantec.es/wp-content/uploads/2018/02/p_3_3_2_7_3327-NodeMcu-Lua-ESP8266-ESP12E-CP2102-WiFi-Wireless-Nueva-version.jpg" alt="esp" style="width:300px;height:300px;">

ب. DHt 11 (temperature sensor) 

<img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Ftse1.mm.bing.net%2Fth%3Fid%3DOIP.TKlPr6ULRzTfsCDINlpoMgHaHa%26pid%3DApi&f=1&ipt=49571d655c64d07bdea5c8f949fe0dd23208145d19bf735bcd6d2bf933b1b029&ipo=images" alt="esp" style="width:300px;height:300px;">

## => السوفتوير 

### أ.visual studio code 

 ------>استخدام البرنامج لكتابة اكواد السيرفر, يمكن تحميله من [هنا](https://code.visualstudio.com/Download)

### ب.CounterFit

------>   لعمل سيميوليشن لبعض السينسورات  

# <img src="images\7.png" alt="" style="width:30px;height:30px;"> التركيب والتثبيت

## => السوفتوير 
بعد تحميل الاكواد تأكد انك مثبت python على جهازك.

 نفذ هذا الامر في ال terminal .
هذا الامر سوف يظهر لك اصدار بايثون المثبت لديك
```
$ python --version
```
ان لم يكن لديك بايثون فثبتها اولا 
[من هنا](https://www.python.org/downloads/)

هذا الامر لتشغيل ال environment
```
$ .\.venv\Scripts\Activate.ps1
```
بعد ذلك ثبت المكتبات الازمة والتى بداخل ملف ال requirements.txt
```
(.venv) pip install -r requirements.txt
```
## الان يمكنك تشغيل المشروع
اولا شغل ملف ال server.
افتح ملف app.py الموجود بتاخل فولدر server ثم اضفط سهم run  اعلى اليمين 

ثانيا في حالة انك سوف تستخدم Counterfit 
هذا الامر يشغل counterFit server والذي يتعطينا واجهة رسومية للسينسورات التي نستخدمها
```
(.venv)  CounterFit
```
افتح هذا الرباط في المتصفح 
http://localhost:5000/

ثم اتبع الخطوات كما في الصورة

<img src="images\3.PNG" >

<br>
 افتح ملف app.py الموجود بداخل فولدر virtual-device ثم اضفط سهم run  اعلى اليمين 

 الان اصبح هناك كود السيرفير وكود السينسور . فعند تغير الحرارة ترسل هذه القيمة للبروكير ثم يرسل البروكير القيمة للسيرفير وهنا يقوم السيرفير بتخزين القيمة في ملف <b>csv
<br>

ثالثا افتح كود Growing_Degree_Days.ipynb اعمل تشغيل لجميع الخلايا

<img src="images\1.PNG" >
<br>
<br>
<img src="images\2.PNG" >