#  <img src="https://cdn3.iconfinder.com/data/icons/startup-management-flat/256/-_gears_descriptions_management_project-512.png" alt="" style="width:20px;height:20px;">  وصف المشروع

 تطبيقا على مجال انترنت الاشياء,امكانية التحكم في اضاءة مصباح  (or led) وتشغيله في الظلام وغلقه في النهار , وهذا يوفر لنا الطاقة ويقلل استهلاكها.

 # <img src="https://cdn0.iconfinder.com/data/icons/project-management-scrum-and-agile/96/agile_scrum_goal_target_planning_iteration_business-512.png" alt="" style="width:30px;height:30px;">   الهدف من المشروع

 يمكن استخدام المشروع في المنازل الذكية او المدن الذكية حيث يتيح لنا التحكم في وقت اضاءة مصابيح الانارة. فيتم تشغيلها ليلا وفصلها نهارا

# <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fcdn2.iconfinder.com%2Fdata%2Ficons%2Fadvertisement-marketing%2F512%2Fpuzzle-512.png&f=1&nofb=1&ipt=d8b5faa6f09d533d606dbbda1cb362d52891402538e5306dcfa147431b9e7d38&ipo=images" alt="" style="width:30px;height:30px;"> الادوات المستخدمة 

## => الهاردوير

أ. esp 32

<img src="https://leantec.es/wp-content/uploads/2018/02/p_3_3_2_7_3327-NodeMcu-Lua-ESP8266-ESP12E-CP2102-WiFi-Wireless-Nueva-version.jpg" alt="esp" style="width:300px;height:300px;">

ب. LDR 

<img src="https://th.bing.com/th/id/R.a5b99eef6696085976ee02460af8408d?rik=UD26Bp48v8F89Q&pid=ImgRaw&r=0&sres=1&sresct=1" alt="esp" style="width:300px;height:200px;">

ج.LED

<img src="https://th.bing.com/th/id/R.a3e96dd20d437f7986eb17cecce48cfe?rik=hY%2fKThi1wHPq0Q&pid=ImgRaw&r=0" alt="esp" style="width:300px;height:200px;">

## => السوفتوير 

### أ.visual studio code 

 ------>استخدام البرنامج لكتابة اكواد السيرفر, يمكن تحميله من [هنا](https://code.visualstudio.com/Download)

### ب.wokwi 

------> استخدام الموقع لعمل سيميوليشن ل ESP32 
[رابط الموقع](https://wokwi.com/)

### ج.CounterFit

------>   لعمل سيميوليشن لبعض السينسورات  

# <img src="images\7.PNG" alt="" style="width:30px;height:30px;"> التركيب والتثبيت

## => الهاردوير
<img src="images\7.PNG" >

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

<img src="images\9.PNG" >

### افتح ملف app.py الموجود بتاخل فولدر virtual-device ثم اضفط سهم run  اعلى اليمين 
<br>
* server code
<img src="images\3.PNG" >
<br>
<br>
* virtual-device code
<img src="images\4.PNG" >


## الان اصبح هناك كود السيرفر وكود السينسور . فعند تغير قيمة الضوء ترسل هذه القيمة للبروكير ثم يرسل البروكير امر لتشغيل الاضاءة او غلقها بناء على هذه القيمة
<img src="images\1.PNG" >
<br>
<br>
<img src="images\2.PNG" >

## في حالة انك تستخدم wokwi 
اعمل مشروع جديد على الموقع ثم استبدل الملفات الموجودة بداخل فولدر ESP32@wokwi ثم شغل السيميوليشن

<img src="images\5.PNG" >
<br>
<br>
<img src="images\6.PNG ">
