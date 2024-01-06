# Stock detection and count with azure

* Azure IoT architecture
<center>
<img src="images\iot-refarch.PNG" alt="" > 
</center>

<br>


* demos
    - [YouTube video](https://youtu.be/SV9JVf1AlAs)


* Azure services
    - custom vision
    - machine learning

* Tools
    - python programming language
    - counterfit (virtual devices)
    - customvision [link](https://www.customvision.ai/)

* to run the code :
    ```sh
    python3 -m venv .venv
    ```
    ```sh
    .venv\Scripts\activate.bat
    ```
    ```sh
    pip install -r requirements.txt
    ```
    --> to run virtual sensors
    ```sh
    counterfit
    ```
    open `http://localhost:5000/` in browser and add devices as this image
    <img src="images\sensors.PNG" alt="" style="width:500px">


    <!-- ---------------------------------------------------->

    ## create model on customVision
    ### 1- Create a Resource Group for this project called `Resource-Group-name`
    ```sh
    az group create --name <Resource-Group-name> --location <location>
    ```
    ### 2- Create a free Custom Vision training resource, and a free Custom Vision prediction resource in your resource group. Name them `Resource-Group-name-training` and `Resource-Group-name-prediction`
    ```sh
    az cognitiveservices account create --name <Resource-Group-name-training> --resource-group <Resource-Group-name> --kind CustomVision.Training --sku F0 --yes --location <location>
    ```
    ```sh
    az cognitiveservices account create --name <Resource-Group-name-prediction>--resource-group <Resource-Group-name> --kind CustomVision.Prediction --sku F0 --yes --location <location>
    ```
    - replace anything between <> with names as you want.
    ### 3- go to [customvision](https://www.customvision.ai/)
    - create your model as shown in image
    <img src="images\custom-vision-create-object-detector-project.png" alt="" > 

    ### 4- train your object detector
    ### 5-  publish an iteration of your object detector
    - Select the Performance tab from the options at the top
    - Select the latest iteration from the Iterations list on the side
    - Select the Publish button for the iteration

        <img src="images\publish.png" alt="" > 

    ### 6- Once published, select the Prediction URL button, and copy url and prediction-ket to `app.py file in camera-sensor folder`
    <img src="images\url.png" alt="" > 

    
    <img src="images\code_url.png" alt="" > 

    ### 7- run your code, and set images with counterfit
    <!-- ---------------------------------------------------->


    ## After finish you should remove resource group from your account 
    ```sh 
    az group delete --name <resource-group-name>
    ```
    ```sh
    Are you sure you want to perform this operation? (y/n): 
    ```
    Enter <b>y</b> to confirm and delete the Resource Group. It will take a while to delete all the services.