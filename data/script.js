"use strict";
var maxleds = 100;
var ledslist = [];
var recievedLEDParams ={};

//set slider settings

var startSlider = document.getElementById("startSlider");
var startNum = document.getElementById("startLight");
var endSlider = document.getElementById("endSlider");
var endNum =  document.getElementById("endLight");



function getLEDparameters(){
    var xhttp = new XMLHttpRequest();
;
    function onRecieveParams(response,dummyParam){
        var recievedText = response.currentTarget.responseText;
        recievedLEDParams =JSON.parse(recievedText);
        var a =document.getElementsByClassName("lightslider")
        for(var i =0;i<(a.length); i++){
            maxleds = (recievedLEDParams.maxLeds)
            a[i].max=maxleds;
            
        }
        endSlider.value=maxleds;
        endLight.value = maxleds;
    }
    createHttpRequest("not used","GET","http://esp8266/getParameters",onRecieveParams);
};
window.onload = getLEDparameters(); 


function setPresetColor(callingElement){
    document.getElementById('chosenColor').value
    console.log(callingElement.style.backgroundColor);
}
function colorslider(currentSlider){
    
    //console.log(numElement);
    var currValue = currentSlider.value;
    if(currentSlider===startSlider && currValue > endSlider.value){
        endSlider.value=currValue;
        console.log(startNum.value);
    }else if (currentSlider===endSlider && currValue < startSlider.value){
        startSlider.value=currValue;
        console.log(endNum.value);
    }
    
    startNum.value=startSlider.value;
    endNum.value=endSlider.value;
    

    //Haze = currentSlider.style.borderColor;
    //currentSlider.style.background="hsl("+hexRed+","+hexGreen+","+ hexBlue+","+(currentSlider.value/101+0.05)+")";
    //currentSlider.style.boxShadow="0 0 "+(currentSlider.value/33-1)+"vh "+thisHaze;
}


function createSpecificSwitchRequest(element){
    var xhttp = new XMLHttpRequest();
    
    var startLight = document.getElementById("startLight");
    var endLight = document.getElementById("endLight");
    var color = document.getElementById('chosenColor').value;

    var requestWithParams = "http://esp8266/lights?start="+startLight.value
        +"&end="+endLight.value
        +"&showBool="+true
        +"&color="+color.replace("#","");
    
    function responseFunction(response, element){
        console.log("recieved state:" + xhttp.responseText);
            element.style.backgroundColor=color;
            element.style.color=color;
            element.checked=false;
    }

    createHttpRequest(element, "POST", requestWithParams, responseFunction);
    
    element.style.boxShadow="0 0 2vh "+color;
}

function createHttpRequest(callingObject,requestType="GET",requestAddress,onResponseFunction){
    var xhttp = new XMLHttpRequest();
    xhttp.open(requestType, requestAddress, true);
    xhttp.onreadystatechange = function(response) {
        if (this.readyState == 4 && this.status == 200) {
            onResponseFunction(response,callingObject)
        }
    };
   //xhttp.setRequestHeader("Access-Control-Allow-Origin", "*");
    xhttp.send();
} 